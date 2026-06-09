#include "RowListModel.h"
#include "RowCellModel.h"
#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <qabstractitemmodel.h>
#include <qcontainerfwd.h>

namespace asd::editor::tracklabel 
{
RowListModel::RowListModel(QVector<RowCellModel*> rows, QObject* parent)
    : m_rows(rows), QAbstractListModel(parent)
/*
    Bare bones allocation, emits no signals, only sets internal data
    because view isn't connected to model during instatation.
*/
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

bool RowListModel::insertRows(int position, int count, const QModelIndex &parent) 
/*
    We need a more generic function that takes in RowCellModel data, 
    That still uses beginInsertRows and endInsertRows (when connected to view)
*/
{
    if (count <= 0 || position < 0 || position > m_rows.size()) {
        return false;
    }

    beginInsertRows(parent, position, position + count - 1);
    
    for (int currpos=0; currpos < count; currpos++) {
        auto* cellModel = new RowCellModel(this);
        
        // Connect the inner model's intent channel directly to the supervisor slot
        connect(cellModel, &RowCellModel::moveFieldRequested, 
                this, &RowListModel::handleMoveFieldRequest);

        m_rows.insert(position + currpos, cellModel);
    }

    endInsertRows();
    return true;
}



void RowListModel::handleMoveFieldRequest(RowCellModel* sourceRow, int fromCol, RowCellModel::MoveDirection direction)
/*
    Calculates current and desired pos of moving field.
    Tries to move field into desired pos.
*/
{
    // 1. Identify which exact row index sent the signal
    int fromRow = m_rows.indexOf(sourceRow);
    if (fromRow == -1) return;

    int toRow = fromRow;
    int toCol = fromCol;

    // 2. Perform index displacement safely in C++
    switch (direction) {
    case RowCellModel::MoveLeft:  toCol = fromCol - 1; break;
    case RowCellModel::MoveRight: toCol = fromCol + 1; break;
    case RowCellModel::MoveUp:    toRow = fromRow - 1; break;
    case RowCellModel::MoveDown:  toRow = fromRow + 1; break;
    }

    // 3. Pass execution off to your existing cross-row engine function
    this->moveCell(fromRow, fromCol, toRow, toCol);
}


void RowListModel::moveCell(int fromRow, int fromCol, int toRow, int toCol)
/*
    Moves cell in desired direction, 
    safely migrates field between RowCellModels instances.

    Does nothing if requested cell is out of bounds.
*/
{
    if (!validCell(fromRow, fromCol)) return;
    if (!validCell(toRow, toCol)) return;

    // Remove pointer tracking from old container
    auto* field = m_rows[fromRow]->popCell(fromCol);

    // Insert into destination sub-model structure
    const int clampedCol = qBound(0, toCol, m_rows[toRow]->cellCount());
    m_rows[toRow]->insertCell(clampedCol, field);

    // Trigger visual tree recalculation notifications
    notifyRowChanged(fromRow);
    if (toRow != fromRow) {
        notifyRowChanged(toRow);
    }
}

// // ── Row-level mutations ───────────────────────

// void RowListModel::appendRow()
// {
//     insertRow(m_rows.size());
// }

// void RowListModel::insertRow(int row)
// {
//     row = qBound(0, row, m_rows.size());
//     beginInsertRows({}, row, row);
//     m_rows.insert(row, new RowCellModel(this));
//     m_rowIds.insert(row, m_nextRowId++);
//     endInsertRows();
// }

// void RowListModel::removeRow(int row)
// {
//     if (!validRow(row)) return;
//     beginRemoveRows({}, row, row);
//     delete m_rows.takeAt(row);
//     m_rowIds.removeAt(row);
//     endRemoveRows();
// }

// ── Private helpers ───────────────────────────

bool RowListModel::validRow(int row) const
{
    return row >= 0 && row < m_rows.size();
}

bool RowListModel::validCell(int row, int col) const
{
    return validRow(row) && m_rows[row]->validCell(col);
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
} // namespace asd::editor::tracklabel 
