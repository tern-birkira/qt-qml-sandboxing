#include "RowListModel.h"
#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>

RowListModel::RowListModel(QObject* parent)
    : QAbstractListModel(parent)
{}

RowListModel::~RowListModel()
{
    qDeleteAll(m_rows);
}

// ── QAbstractListModel interface ─────────────

int RowListModel::rowCount(const QModelIndex& parent) const
{
    if (parent.isValid()) return 0;
    return m_rows.size();
}

QVariant RowListModel::data(const QModelIndex& index, int role) const
{
    if (!index.isValid() || index.row() >= m_rows.size())
        return {};

    switch (role) {
    case CellModelRole:
        // QML receives a RowCellModel* — the Repeater binds to it directly
        return QVariant::fromValue(m_rows.at(index.row()));
    case RowIdRole:
        return m_rowIds.at(index.row());
    default:
        return {};
    }
}

QHash<int, QByteArray> RowListModel::roleNames() const
{
    return {
        { CellModelRole, "cellModel" },
        { RowIdRole,     "rowId"     }
    };
}

// ── Row-level mutations ───────────────────────

void RowListModel::appendRow()
{
    insertRow(m_rows.size());
}

void RowListModel::insertRow(int row)
{
    row = qBound(0, row, m_rows.size());
    beginInsertRows({}, row, row);
    m_rows.insert(row, new RowCellModel(this));
    m_rowIds.insert(row, m_nextRowId++);
    endInsertRows();
}

void RowListModel::removeRow(int row)
{
    if (!validRow(row)) return;
    beginRemoveRows({}, row, row);
    delete m_rows.takeAt(row);
    m_rowIds.removeAt(row);
    endRemoveRows();
}

// ── Cell-level mutations ──────────────────────

void RowListModel::appendCell(int row, const QString& label)
{
    if (!validRow(row)) return;
    TrackLabelField cell;
    cell.id    = nextCellId();
    cell.label = label;
    m_rows[row]->appendCell(cell);
    // RowCellModel already emitted rowsInserted —
    // notify outer model that this row's cellModel changed
    notifyRowChanged(row);
}

void RowListModel::insertCell(int row, int col, const QString& label)
{
    if (!validRow(row)) return;
    TrackLabelField cell;
    cell.id    = nextCellId();
    cell.label = label;
    m_rows[row]->insertCell(col, cell);
    notifyRowChanged(row);
}

void RowListModel::removeCell(int row, int col)
{
    if (!validCell(row, col)) return;
    m_rows[row]->removeCell(col);
    notifyRowChanged(row);
}

void RowListModel::moveCell(int fromRow, int fromCol, int toRow, int toCol)
{
    if (!validCell(fromRow, fromCol)) return;
    if (!validRow(toRow))             return;

    // 1. Take cell out of source row (emits rowsRemoved on that RowCellModel)
    TrackLabelField cell = m_rows[fromRow]->takeCell(fromCol);

    // 2. Insert into destination row (emits rowsInserted on that RowCellModel)
    const int clampedCol = qBound(0, toCol, m_rows[toRow]->count());
    m_rows[toRow]->insertCell(clampedCol, cell);

    // 3. Notify outer model for both affected rows
    notifyRowChanged(fromRow);
    if (toRow != fromRow)
        notifyRowChanged(toRow);
}

// ── Cell data updates ─────────────────────────

void RowListModel::setCellLabel(int row, int col, const QString& label)
{
    if (!validCell(row, col)) return;
    const QModelIndex idx = m_rows[row]->index(col);
    m_rows[row]->setData(idx, label, RowCellModel::LabelRole);
}

void RowListModel::setCellWidth(int row, int col, int width)
{
    if (!validCell(row, col)) return;
    const QModelIndex idx = m_rows[row]->index(col);
    m_rows[row]->setData(idx, width, RowCellModel::WidthRole);
}

void RowListModel::setCellActive(int row, int col, bool active)
{
    if (!validCell(row, col)) return;
    const QModelIndex idx = m_rows[row]->index(col);
    m_rows[row]->setData(idx, active, RowCellModel::IsActiveRole);
}

// ── Persistence ───────────────────────────────

bool RowListModel::saveToFile(const QString& path) const
{
    QJsonArray rowsJson;

    for (int r = 0; r < m_rows.size(); ++r) {
        QJsonArray cellsJson;
        const auto& cells = m_rows[r]->cells();

        for (const TrackLabelField& cell : cells) {
            QJsonObject obj;
            obj["id"]        = cell.id;
            obj["label"]     = cell.label;
            obj["width"]     = cell.width;
            obj["color"]     = cell.color;
            obj["isActive"]  = cell.isActive;
            obj["extraData"] = cell.extraData;
            cellsJson.append(obj);
        }

        QJsonObject rowObj;
        rowObj["rowId"] = m_rowIds[r];
        rowObj["cells"] = cellsJson;
        rowsJson.append(rowObj);
    }

    QJsonDocument doc(rowsJson);
    QFile file(path);
    if (!file.open(QIODevice::WriteOnly)) return false;
    file.write(doc.toJson());
    return true;
}

bool RowListModel::loadFromFile(const QString& path)
{
    QFile file(path);
    if (!file.open(QIODevice::ReadOnly)) return false;

    const QJsonDocument doc = QJsonDocument::fromJson(file.readAll());
    if (!doc.isArray()) return false;

    beginResetModel();
    qDeleteAll(m_rows);
    m_rows.clear();
    m_rowIds.clear();

    for (const QJsonValue& rowVal : doc.array()) {
        const QJsonObject rowObj = rowVal.toObject();
        auto* model = new RowCellModel(this);

        for (const QJsonValue& cellVal : rowObj["cells"].toArray()) {
            const QJsonObject obj = cellVal.toObject();
            TrackLabelField cell;
            cell.id        = obj["id"].toInt();
            cell.label     = obj["label"].toString();
            cell.width     = obj["width"].toInt(120);
            cell.color     = obj["color"].toString("#ffffff");
            cell.isActive  = obj["isActive"].toBool(true);
            cell.extraData = obj["extraData"].toString();
            model->appendCell(cell);

            // keep nextCellId above any loaded id
            m_nextId = qMax(m_nextId, cell.id + 1);
        }

        m_rows.append(model);
        m_rowIds.append(rowObj["rowId"].toInt());
        m_nextRowId = qMax(m_nextRowId, rowObj["rowId"].toInt() + 1);
    }

    endResetModel();
    return true;
}

// ── Private helpers ───────────────────────────

bool RowListModel::validRow(int row) const
{
    return row >= 0 && row < m_rows.size();
}

bool RowListModel::validCell(int row, int col) const
{
    return validRow(row) && col >= 0 && col < m_rows[row]->count();
}

void RowListModel::notifyRowChanged(int row)
{
    const QModelIndex idx = index(row);
    emit dataChanged(idx, idx, { CellModelRole });
}

int RowListModel::nextCellId()
{
    return m_nextId++;
}
