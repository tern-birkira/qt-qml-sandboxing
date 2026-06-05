#pragma once
#include <QAbstractListModel>
#include <QVector>
#include "TrackLabelField.h"

// ─────────────────────────────────────────────
//  Inner model — owns all cells for ONE row.
//  Exposed to QML via the outer model's
//  CellModelRole.  The Repeater binds to it.
// ─────────────────────────────────────────────
class RowCellModel : public QAbstractListModel
{
    Q_OBJECT

public:
    // ── Roles injected into TrackLabelField delegate ──
    enum Roles {
        IdRole = Qt::UserRole + 1,
        LabelRole,
        WidthRole,
        ColorRole,
        IsActiveRole,
        ExtraDataRole
    };

    explicit RowCellModel(QObject* parent = nullptr);

    // ── QAbstractListModel interface ──
    int           rowCount(const QModelIndex& parent = {}) const override;
    QVariant      data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
    bool          setData(const QModelIndex& index, const QVariant& value, int role = Qt::EditRole) override;
    QHash<int, QByteArray> roleNames() const override;

    // ── Mutation API (called by RowListModel) ──
    void appendCell(const TrackLabelField& cell);
    void insertCell(int col, const TrackLabelField& cell);
    TrackLabelField takeCell(int col);           // remove and return
    void removeCell(int col);
    void updateCell(int col, const TrackLabelField& cell);

    // ── Read ──
    int                count() const { return m_cells.size(); }
    TrackLabelField    cellAt(int col) const;
    const QVector<TrackLabelField>& cells() const { return m_cells; }

private:
    QVector<TrackLabelField> m_cells;
};
