#include "editor_line_model.h"

EditorLineModel::EditorLineModel( QObject *parent ): QAbstractListModel( parent ) {}


int EditorLineModel::rowCount(const QModelIndex &parent) const {
    return m_fields.size();
}

QVariant EditorLineModel::data(const QModelIndex &index, int role) const {
    const LabelField &trackLine = m_fields.at(index.row());
    switch (role) {
        case Label:
            return {};
        default:
            return QVariant();
    }
}

QHash<int, QByteArray> EditorLineModel::roleNames() const {
    return {
        {Label, "trackLine"} // property linkage for delegate attribute QML
    };
}