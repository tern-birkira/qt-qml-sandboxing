#pragma once
#include <QAbstractListModel>
#include <QVector>
#include <QQmlEngine>
#include "RowCellModel.h"

// ─────────────────────────────────────────────
//  Outer model — owns all RowCellModel* rows.
//  Exposed to QML as the ListView's model.
//  Also the single entry point for all
//  structural mutations from QML.
// ─────────────────────────────────────────────
class RowListModel : public QAbstractListModel
{
    Q_OBJECT
    QML_ELEMENT

public:
    enum Roles {
        CellModelRole = Qt::UserRole + 1,   // → RowCellModel*
        RowIdRole                            // stable per-row id
    };

    explicit RowListModel(QObject* parent = nullptr);
    ~RowListModel() override;

    // ── QAbstractListModel interface ──
    int      rowCount(const QModelIndex& parent = {}) const override;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
    QHash<int, QByteArray> roleNames() const override;

    // ── Row-level mutations ──
    Q_INVOKABLE void appendRow();
    Q_INVOKABLE void insertRow(int row);
    Q_INVOKABLE void removeRow(int row);

    // ── Cell-level mutations (called from QML delegates) ──
    Q_INVOKABLE void appendCell  (int row, const QString& label);
    Q_INVOKABLE void insertCell  (int row, int col, const QString& label);
    Q_INVOKABLE void removeCell  (int row, int col);
    Q_INVOKABLE void moveCell    (int fromRow, int fromCol, int toRow, int toCol);

    // ── Cell data update ──
    Q_INVOKABLE void setCellLabel (int row, int col, const QString& label);
    Q_INVOKABLE void setCellWidth (int row, int col, int width);
    Q_INVOKABLE void setCellActive(int row, int col, bool active);

    // ── Persistence ──
    Q_INVOKABLE bool saveToFile(const QString& path) const;
    Q_INVOKABLE bool loadFromFile(const QString& path);

private:
    // ── Helpers ──
    bool    validRow(int row) const;
    bool    validCell(int row, int col) const;
    void    notifyRowChanged(int row);
    int     nextCellId();

    QVector<RowCellModel*> m_rows;
    int m_nextId = 0;
    int m_nextRowId = 0;
    QVector<int> m_rowIds;
};
