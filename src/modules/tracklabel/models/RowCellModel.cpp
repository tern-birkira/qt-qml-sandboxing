#include "RowCellModel.h"
#include <qabstractitemmodel.h>
#include <qminmax.h>
#include <qvariant.h>

namespace asd::editor::tracklabel
{
RowCellModel::RowCellModel(
        QVector<asd::editor::tracklabelfield::FieldInterface*> cells,
        QObject* parent
    )
    : m_cells(cells), QAbstractListModel(parent)
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

    
    const auto& cell = m_cells.at(index.row());

    switch (role) {
        case FieldObjectRole:        return QVariant::fromValue(cell);
    default:                         return {};
    }
}

QHash<int, QByteArray> RowCellModel::roleNames() const
{
    return {
        { FieldObjectRole,        "fieldObject"    },
    };
}


// ─────────── QAbstractListModel Built in Model Functions ────────────

bool RowCellModel::removeRows(int position, int rows, const QModelIndex &parent)
/*
    Completely erases underlying Qobject FieldInterface instance.
*/
{

    if (parent.isValid()) {
        return false;
    }
    // 1. Notify the view that rows are about to be removed
    beginRemoveRows(QModelIndex(), position, position + rows - 1);

    // 2. Remove the actual item(s) from your underlying data structure
    for (int i = 0; i < rows; ++i) {
        m_cells[position] -> deleteLater();
        m_cells.removeAt(position); 
    }

    // 3. Notify the view that the removal is complete
    endRemoveRows();

    return true;
}



// ─────────── Signals ────────────

void RowCellModel::requestMoveField(int colIndex, MoveDirection direction)
{
    if (validCell(colIndex)) {
        emit moveFieldRequested(this, colIndex, direction);
    }
}

// ─────────── Public Interfaces ────────────

bool RowCellModel::validCell(int colIndex)
/*
    Checks if cell exists at index
*/
{
    return colIndex >= 0 && colIndex < m_cells.size();
}

asd::editor::tracklabelfield::FieldInterface* RowCellModel::popCell(int idx)
/*
    Removes Pointers without deleting underlying object. 
    Used to transfer FieldInterface pointers between RowCellModel instances. 
    Expects a new parent to be assigned to FieldInterface*
*/
{
    if (!validCell(idx)) return nullptr;
    beginRemoveRows( QModelIndex(), idx, idx);

    auto* field = m_cells.takeAt(idx);

    endRemoveRows();

    // Temporarally make the field an orphan.
    if (field) {
        field->setParent(nullptr);
    }

    return field;
}

bool RowCellModel::insertCell(int col, asd::editor::tracklabelfield::FieldInterface* cell)
/*
    Inserts pointer from already instantiated Qobject of FieldInterface into desired column.
*/
{
    if (!validCell(col)) return false;
    
    col = qBound(0, col, m_cells.size());
    beginInsertRows( QModelIndex(), col, col);

    cell->setParent(this);
    m_cells.insert(col, cell);
    endInsertRows();
    return true;
}

int RowCellModel::cellCount()
/*
    Alias for rowCount, used for readability.
*/
{
    return rowCount();
}

// bool RowCellModel::setData(const QModelIndex& index, const QVariant& value, int role)
// {
//     if (!index.isValid() || index.row() >= m_cells.size())
//         return false;

//     TrackLabelField& cell = m_cells[index.row()];
//     bool changed = false;

//     switch (role) {
//     case LabelRole:
//         if (cell.label != value.toString()) { cell.label = value.toString(); changed = true; }
//         break;
//     default: break;
//     }

//     if (changed)
//         emit dataChanged(index, index, {role});

//     return changed;
// }


// // ── Mutation API ─────────────────────────────

// void RowCellModel::appendCell(const TrackLabelField& cell)
// {
//     const int pos = m_cells.size();
//     beginInsertRows({}, pos, pos);
//     m_cells.append(cell);
//     endInsertRows();
// }

// void RowCellModel::insertCell(int col, const TrackLabelField& cell)
// {
//     col = qBound(0, col, m_cells.size());
//     beginInsertRows({}, col, col);
//     m_cells.insert(col, cell);
//     endInsertRows();
// }

// TrackLabelField RowCellModel::takeCell(int col)
// {
//     Q_ASSERT(col >= 0 && col < m_cells.size());
//     beginRemoveRows({}, col, col);
//     TrackLabelField cell = m_cells.takeAt(col);
//     endRemoveRows();
//     return cell;
// }

// void RowCellModel::removeCell(int col)
// {
//     Q_ASSERT(col >= 0 && col < m_cells.size());
//     beginRemoveRows({}, col, col);
//     m_cells.removeAt(col);
//     endRemoveRows();
// }

// void RowCellModel::updateCell(int col, const TrackLabelField& cell)
// {
//     Q_ASSERT(col >= 0 && col < m_cells.size());
//     m_cells[col] = cell;
//     const QModelIndex idx = index(col);
//     emit dataChanged(idx, idx, {
//         IdRole, LabelRole, WidthRole,
//         ColorRole, IsActiveRole, ExtraDataRole
//     });
// }

// TrackLabelField RowCellModel::cellAt(int col) const
// {
//     Q_ASSERT(col >= 0 && col < m_cells.size());
//     return m_cells.at(col);
// }
} // namespace asd::editor::tracklabel