import QtQuick 2.15
import QtQuick.Controls 2.15
import TrackLabel.Models 1.0

// ─────────────────────────────────────────────
//  Inner delegate — one TrackLabelField cell.
//
//  Roles injected by the Repeater from RowCellModel:
//    fieldId    : int
//    label      : string
//    fieldWidth : int
//    fieldColor : string
//    isActive   : bool
//    extraData  : string
//
//  index (the Repeater's current index) is also
//  available implicitly.
// ─────────────────────────────────────────────
Rectangle {
    id: root
    // injected values from model
    required property int fieldWidth
    required property string fieldColor
    required property bool isActive
    required property int index // default injected value of curr column
    required property int label 
    required property RowListModel rowlistmodel
    

    // ── Geometry ──
    width:  fieldWidth   // role from RowCellModel
    height: 48

    // ── Appearance ──
    color:  fieldColor  // role from RowCellModel
    opacity: isActive ? 1.0 : 0.4
    radius:  4
    border.color: Qt.darker(fieldColor, 1.3)
    border.width: 1

    // ── Expose cell coords upward so actions know where they are ──
    // rowIndex is set by the outer delegate (see RowContainer.qml)
    property int rowIndex: 0
    property alias colIndex: root.index  // rename injected col index

    // ── Label ──
    Text {
        anchors.centerIn: parent
        text: root.label          // role from RowCellModel
        elide: Text.ElideRight
        width: parent.width - 8
        horizontalAlignment: Text.AlignHCenter
        color: "#222"
        font.pixelSize: 13
    }

    // ── Interaction ──
    MouseArea {
        anchors.fill: parent
        acceptedButtons: Qt.LeftButton | Qt.RightButton

        onClicked: (mouse) => {
            if (mouse.button === Qt.RightButton) {
                contextMenu.popup()
            }
        }

        onDoubleClicked: {
            labelEdit.visible = true
            labelEdit.forceActiveFocus()
            labelEdit.selectAll()
        }
    }

    // Inline label editor (double-click to activate)
    TextInput {
        id: labelEdit
        anchors.centerIn: parent
        width: parent.width - 8
        text: root.label
        visible: false
        horizontalAlignment: Text.AlignHCenter
        font.pixelSize: 13

        onEditingFinished: {
            root.rowlistmodel.setCellLabel(root.rowIndex, root.colIndex, text)
            visible = false
        }
        Keys.onEscapePressed: {
            visible = false
        }
    }

    // ── Context menu ──
    Menu {
        id: contextMenu

        Action {
            text: "Insert cell before"
            onTriggered: root.rowlistmodel.insertCell(root.rowIndex, root.colIndex, "New")
        }
        Action {
            text: "Insert cell after"
            onTriggered: root.rowlistmodel.insertCell(root.rowIndex, root.colIndex + 1, "New")
        }
        MenuSeparator {}
        Action {
            text: "Remove cell"
            onTriggered: root.rowlistmodel.removeCell(root.rowIndex, root.colIndex)
        }
        MenuSeparator {}
        Action {
            text: root.isActive ? "Deactivate" : "Activate"
            onTriggered: root.rowlistmodel.setCellActive(root.rowIndex, root.colIndex, !root.isActive)
        }
    }
}
