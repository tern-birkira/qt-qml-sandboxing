#include "RowCellModel.h"

RowCellModel::RowCellModel(QObject* parent)
    : QAbstractListModel(parent)
{}

// ── QAbstractListModel interface ─────────────

int RowCellModel::rowCount(const QModelIndex& parent) const
{
    if (parent.isValid()) return 0;
    return m_cells.size();
}

QVariant RowCellModel::data(const QModelIndex& index, int role) const
{
    if (!index.isValid() || index.row() >= m_cells.size())
        return {};

    const TrackLabelField& cell = m_cells.at(index.row());

    switch (role) {
    case IdRole:        return cell.id;
    case LabelRole:     return cell.label;
    case WidthRole:     return cell.width;
    case ColorRole:     return cell.color;
    case IsActiveRole:  return cell.isActive;
    case ExtraDataRole: return cell.extraData;
    default:            return {};
    }
}

bool RowCellModel::setData(const QModelIndex& index, const QVariant& value, int role)
{
    if (!index.isValid() || index.row() >= m_cells.size())
        return false;

    TrackLabelField& cell = m_cells[index.row()];
    bool changed = false;

    switch (role) {
    case LabelRole:
        if (cell.label != value.toString()) { cell.label = value.toString(); changed = true; }
        break;
    case WidthRole:
        if (cell.width != value.toInt()) { cell.width = value.toInt(); changed = true; }
        break;
    case ColorRole:
        if (cell.color != value.toString()) { cell.color = value.toString(); changed = true; }
        break;
    case IsActiveRole:
        if (cell.isActive != value.toBool()) { cell.isActive = value.toBool(); changed = true; }
        break;
    case ExtraDataRole:
        if (cell.extraData != value.toString()) { cell.extraData = value.toString(); changed = true; }
        break;
    default: break;
    }

    if (changed)
        emit dataChanged(index, index, {role});

    return changed;
}

QHash<int, QByteArray> RowCellModel::roleNames() const
{
    return {
        { IdRole,        "fieldId"    },
        { LabelRole,     "label"      },
        { WidthRole,     "fieldWidth" },
        { ColorRole,     "fieldColor" },
        { IsActiveRole,  "isActive"   },
        { ExtraDataRole, "extraData"  }
    };
}

// ── Mutation API ─────────────────────────────

void RowCellModel::appendCell(const TrackLabelField& cell)
{
    const int pos = m_cells.size();
    beginInsertRows({}, pos, pos);
    m_cells.append(cell);
    endInsertRows();
}

void RowCellModel::insertCell(int col, const TrackLabelField& cell)
{
    col = qBound(0, col, m_cells.size());
    beginInsertRows({}, col, col);
    m_cells.insert(col, cell);
    endInsertRows();
}

TrackLabelField RowCellModel::takeCell(int col)
{
    Q_ASSERT(col >= 0 && col < m_cells.size());
    beginRemoveRows({}, col, col);
    TrackLabelField cell = m_cells.takeAt(col);
    endRemoveRows();
    return cell;
}

void RowCellModel::removeCell(int col)
{
    Q_ASSERT(col >= 0 && col < m_cells.size());
    beginRemoveRows({}, col, col);
    m_cells.removeAt(col);
    endRemoveRows();
}

void RowCellModel::updateCell(int col, const TrackLabelField& cell)
{
    Q_ASSERT(col >= 0 && col < m_cells.size());
    m_cells[col] = cell;
    const QModelIndex idx = index(col);
    emit dataChanged(idx, idx, {
        IdRole, LabelRole, WidthRole,
        ColorRole, IsActiveRole, ExtraDataRole
    });
}

TrackLabelField RowCellModel::cellAt(int col) const
{
    Q_ASSERT(col >= 0 && col < m_cells.size());
    return m_cells.at(col);
}
