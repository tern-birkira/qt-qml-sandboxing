#pragma once
#include <QAbstractListModel>
#include <QVector>
#include "FieldInterface.h"
#include <qabstractitemmodel.h>

// ─────────────────────────────────────────────
//  Inner model — owns all cells for ONE row.
//  Exposed to QML via the outer model's
//  CellModelRole.  The Repeater binds to it.
// ─────────────────────────────────────────────
namespace asd::editor::tracklabel
{
class RowCellModel : public QAbstractListModel
{
    Q_OBJECT

public:
    // ── Roles injected into TrackLabelField delegate ──
    enum Roles {
        FieldObjectRole = Qt::UserRole + 1
    };
    enum MoveDirection {
        MoveLeft,
        MoveRight,
        MoveUp,
        MoveDown
    };
    Q_ENUM(MoveDirection) // Expose direction tokens directly to QML

    explicit RowCellModel(
            QVector<asd::editor::tracklabelfield::FieldInterface*> cells,
            QObject* parent = nullptr);

    // ── QAbstractListModel interface ──
    int           rowCount(const QModelIndex& parent = {}) const override;
    QVariant      data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
    bool          setData(const QModelIndex& index, const QVariant& value, int role = Qt::EditRole) override;
    QHash<int, QByteArray> roleNames() const override;

    //  ── Built in model funcitons (causes updates to Views) ──
    bool removeRows(int position, int rows, const QModelIndex& parent) override;


    // Signal invokers
    Q_INVOKABLE void requestMoveField(int colIndex, MoveDirection direction);

    // Interfaces
    bool validCell(int col);
    asd::editor::tracklabelfield::FieldInterface* popCell(int idx);
    bool insertCell(int col, asd::editor::tracklabelfield::FieldInterface* cell);
    int cellCount();


    // // ── Cell-level mutations (called from QML delegates) ──

    // Q_INVOKABLE void appendCell  (int row, const QString& label);
    // Q_INVOKABLE void insertCell  (int row, int col, const QString& label);
    // Q_INVOKABLE void removeCell  (int row, int col);
    // Q_INVOKABLE void moveCell    (int fromRow, int fromCol, int toRow, int toCol);

signals:
    void moveFieldRequested(RowCellModel* sourceRow, int colIndex, MoveDirection direction);

    // // ── Mutation API (called by RowListModel) ──
    // void appendCell(const TrackLabelField& cell);
    // void insertCell(int col, const TrackLabelField& cell);
    // TrackLabelField takeCell(int col);           // remove and return
    // void removeCell(int col);
    // void updateCell(int col, const TrackLabelField& cell);

    // // ── Read ──
    // int                count() const { return m_cells.size(); }
    // TrackLabelField    cellAt(int col) const;
    // const QVector<TrackLabelField>& cells() const { return m_cells; }

private:
    QVector<asd::editor::tracklabelfield::FieldInterface*> m_cells;
};
} // namespace asd::editor::tracklabel