#pragma once

#include <QAbstractListModel>
#include <QString>
#include <QMap>
#include <qqmlintegration.h>
#include "label_field.h"

class EditorLineModel : public QAbstractListModel {
    /*
    Model that stores a List of Fields
    */
    Q_OBJECT
    QML_ANONYMOUS
public:
    enum EditorLineModelRole {
        Label = Qt::UserRole + 1
    };
    explicit EditorLineModel( QList<LabelField> fields, QObject *parent = nullptr );
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    QHash<int, QByteArray> roleNames() const override;

private:
    QList<LabelField> m_fields;
};
