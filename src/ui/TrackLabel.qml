import birkis.models
import QtQuick

Item {
    width: 300
    height: 500

    EditorTrackLabelModel {
        id: tl_model
    }

    ListView {
        anchors.fill: parent
        model: tl_model

        delegate: Column {
            width:  ListView.view.width
            height: childrenRect.height

            TrackLabelList {
                width: parent.width
                model: model.trackLine
            }
        }
    }
}