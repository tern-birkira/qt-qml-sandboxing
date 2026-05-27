#include "editor_line_model.h"
#include "label_field.h"
#include <qlist.h>

EditorLineModel::EditorLineModel( QList<LabelField> fields, QObject *parent ): QAbstractListModel( parent ), m_fields(fields) {}


int EditorLineModel::rowCount(const QModelIndex &parent) const {
    return m_fields.size();
}

QVariant EditorLineModel::data(const QModelIndex &index, int role) const {
    const LabelField &trackLine = m_fields.at(index.row());
    switch (role) {
        case Label:
            return trackLine.label_value;
        default:
            return QVariant();
    }
}

QHash<int, QByteArray> EditorLineModel::roleNames() const {
    return {
        {Label, "label"} // property linkage for delegate attribute QML
    };
}