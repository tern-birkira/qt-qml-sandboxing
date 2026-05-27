#include "editor_grid.h"
#include "label_field.h"
#include <qcontainerfwd.h>
#include <qvariant.h>



EditorTrackLabelModel::EditorTrackLabelModel( QObject *parent ): QAbstractListModel( parent ) {

    QList<LabelField> line1 = {
        {"callsign",                  labelFieldsData["callsign"]},
        {"combinedAircraftTypeAndWTC",labelFieldsData["combinedAircraftTypeAndWTC"]},
        {"wakeTurbulenceCategory",    labelFieldsData["wakeTurbulenceCategory"]},
    };

    QList<LabelField> line2 = {
        {"currentFlightLevel", labelFieldsData["currentFlightLevel"]},
        {"verticalRateArrow",  labelFieldsData["verticalRateArrow"]},
        {"clearedFlightLevel", labelFieldsData["clearedFlightLevel"]},
        {"clearedSpeed",       labelFieldsData["clearedSpeed"]},
    };

    QList<LabelField> line3 = {
        {"destinationAerodrome",    labelFieldsData["destinationAerodrome"]},
        {"sectorIndicator",         labelFieldsData["sectorIndicator"]},
        {"currentControllingSector",labelFieldsData["currentControllingSector"]},
    };

    m_rows.append(new EditorLineModel(line1, this));
    m_rows.append(new EditorLineModel(line2, this));
    m_rows.append(new EditorLineModel(line3, this));
}

int EditorTrackLabelModel::rowCount(const QModelIndex &parent) const {
    return m_rows.size();
}

QVariant EditorTrackLabelModel::data(const QModelIndex &index, int role) const {
    EditorLineModel* trackLine = m_rows.at(index.row());
    switch (role) {
        case TrackLine:
            return QVariant::fromValue(trackLine);
        default:
            return QVariant();
    }
}

QHash<int, QByteArray> EditorTrackLabelModel::roleNames() const {
    return {
        {TrackLine, "trackLine"}, // property linkage for delegate attribute QML
    };
}
