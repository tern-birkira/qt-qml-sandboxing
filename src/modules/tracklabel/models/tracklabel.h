#pragma once
#include <QAbstractTableModel>
#include <QList>
#include <qabstractitemmodel.h>
#include <qcontainerfwd.h>
#include <qlist.h>
#include <qtmetamacros.h>

struct TrackLabelField {
    QString fieldName;
    QString prefix;
    QString placeholder;
    bool toggleable;
    bool blinking;
    int fontAdjustment;
    bool onlyShowOnFocus;
    QString currentData; // live data
};

class TrackLabel : public QAbstractTableModel
{
    Q_OBJECT
public:
    enum TrackLabelRoles {

    };
    TrackLabel(QObject *parent = nullptr);


    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QHash<int, QByteArray> roleNames() const override;
    
private:
    int m_rows;
    int m_columns;
    QList<QList<TrackLabelField>> m_grid;
};
