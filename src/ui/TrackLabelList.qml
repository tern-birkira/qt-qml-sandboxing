import QtQuick

ListView {
    width:  parent.width
    height: contentHeight
    clip:   true

    delegate: TrackLabelField {
        required property var model
        fieldLabel: model.label
    }
}