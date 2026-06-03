#pragma once

#include <QAbstractListModel>
#include <QString>
#include <QMap>
#include <qqmlintegration.h>
#include "label_field.h"
#include "editor_line_model.h"


// Returns a map of all known track label field names → LabelField instances
// pre-populated with realistic dummy values.
// Ownership: caller takes ownership of the LabelField pointers.

class EditorTrackLabelModel : public QAbstractListModel {
    /*
    Model that contains List of Track Label Lines
    */
    Q_OBJECT
    QML_ELEMENT
public:

    enum EditorTrackLabelRoles {
        TrackLine = Qt::UserRole + 1,
        Think
    };

    explicit EditorTrackLabelModel( QObject *parent = nullptr);
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    QHash<int, QByteArray> roleNames() const override;

private:
    QList<EditorLineModel*> m_rows;
};
