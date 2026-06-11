#pragma once
#include <QAbstractListModel>
#include <QVector>
#include <QQmlEngine>
#include <qcontainerfwd.h>
#include <qlist.h>
#include "RowCellModel.h"


// ─────────────────────────────────────────────
//  Outer model — owns all RowCellModel* rows.
//  Exposed to QML as the ListView's model.
//  Also the single entry point for all
//  structural mutations from QML.
// ─────────────────────────────────────────────

namespace asd::editor::tracklabel
{
class RowListModel : public QAbstractListModel
{
    Q_OBJECT
    QML_ELEMENT

public:
    enum Roles {
        CellModelRole = Qt::UserRole + 1,   // → RowCellModel*
        RowIdRole                            // stable per-row id
    };

    explicit RowListModel(QObject* parent = nullptr, QVector<RowCellModel*> rows = QVector<RowCellModel*>());

    ~RowListModel() override;

    // ── QAbstractListModel interface ──
    int      rowCount(const QModelIndex& parent = {}) const override;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
    QHash<int, QByteArray> roleNames() const override;

    //  ── Built in model funcitons (causes updates to Views) ──
    bool insertRows(int position, int count, const QModelIndex &parent) override;
    

    // ── Row-level mutations ──
    Q_INVOKABLE void appendRow();
    Q_INVOKABLE void removeRow(int row);


private slots:
    // Internal handler capturing cross-model move requests
    void handleMoveFieldRequest(RowCellModel* sourceRow, int colIndex, RowCellModel::MoveDirection direction);

private:
    // ── Helpers ──
    bool    validRow(int row) const;
    bool    validCell(int row, int col) const;
    void    notifyRowChanged(int row);
    int     nextCellId();
    void    moveCell(int fromRow, int fromCol, int toRow, int toCol);

    QVector<RowCellModel*> m_rows;
    int m_nextId = 0;
    int m_nextRowId = 0;
    QVector<int> m_rowIds;
};
} // namespace asd::editor::tracklabel