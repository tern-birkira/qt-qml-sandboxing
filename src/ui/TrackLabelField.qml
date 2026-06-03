import QtQuick
import QtQuick.Controls

ItemDelegate {
    id: root
    property string fieldLabel
    required property int index
    width: ListView.view.width
    text:  fieldLabel

    MouseArea {
        anchors.fill: parent
        onClicked: {
            ListView.viewcurrentIndex = root.index
        }
    }
}