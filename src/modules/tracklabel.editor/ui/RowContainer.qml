pragma ComponentBehavior: Bound
import QtQuick 2.15
import QtQuick.Controls 2.15
// import TrackLabelModels 1.0

// ─────────────────────────────────────────────
//  Outer delegate — one row in the layout.
//
//  Roles injected by the ListView from RowListModel:
//    cellModel : RowCellModel*   → fed to the Repeater
//    rowId     : int             → stable identity
//
//  index is also available (position in ListView).
// ─────────────────────────────────────────────
Item {
    id: root

    // ── Sizing ──
    // Width: sum of all cell widths + gaps. childrenRect tracks
    // the Repeater's row automatically.
    width:  rowContent.width  + addButton.width + 16
    height: 48

    // ── Row index for passing down to cells ──
    
    // readonly property int rowIndex: index   // ListView injects 'index'
    required property int index // ListView inject index (rowIndex)
    

    // ── Row of cells ──
    Row {
        id: rowContent
        anchors.left:       parent.left
        anchors.verticalCenter: parent.verticalCenter
        spacing: 4

        Repeater {
            
            id: cellRepeater

            // cellModel is the RowCellModel* role from RowListModel.
            // The Repeater subscribes to its rowsInserted / rowsRemoved /
            // dataChanged signals automatically.


            model: model.cellModel

            delegate: TrackLabelField {
                rowIndex: root.index   // pass row coord down to each cell
            }
        }
    }

    // ── Add-cell button ──
    RoundButton {
        id: addButton
        anchors.left:           rowContent.right
        anchors.leftMargin:     4
        anchors.verticalCenter: parent.verticalCenter
        width:  28
        height: 28
        text:   "+"
        font.pixelSize: 16

        onClicked: ListView.view.model.appendCell(root.index, "New")
    }

    // ── Row separator ──
    Rectangle {
        anchors.bottom: parent.bottom
        width:  parent.width
        height: 1
        color:  "#ddd"
    }
}
