import QtQuick

Window {
    width: 640
    height: 480
    visible: true
    title: qsTr("Hello World")
    ListView {
        anchors.centerIn: parent; width: 400; height: 300
    
        model: EditorTrackLabelModel
        delegate: Column {
            Text { text: model.value }
        }

    }
}
