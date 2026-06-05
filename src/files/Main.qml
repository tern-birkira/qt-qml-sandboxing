import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

// ─────────────────────────────────────────────
//  Root view.
//  layoutModel (RowListModel*) is set on the
//  QML context in main.cpp — visible everywhere.
// ─────────────────────────────────────────────
ApplicationWindow {
    id: window
    visible: true
    width:   900
    height:  600
    title:   "Layout Editor"

    // ── Toolbar ──
    header: ToolBar {
        RowLayout {
            anchors.fill: parent
            anchors.margins: 4
            spacing: 4

            Button {
                text: "Add row"
                onClicked: layoutModel.appendRow()
            }

            Button {
                text: "Remove last row"
                enabled: layoutModel.rowCount() > 0
                onClicked: layoutModel.removeRow(layoutModel.rowCount() - 1)
            }

            Item { Layout.fillWidth: true }   // spacer

            Button {
                text: "Save"
                onClicked: layoutModel.saveToFile("layout.json")
            }

            Button {
                text: "Load"
                onClicked: layoutModel.loadFromFile("layout.json")
            }
        }
    }

    // ── Main scroll area ──
    ScrollView {
        anchors.fill: parent
        contentWidth: availableWidth

        // ── Outer ListView — one RowContainer per row ──
        ListView {
            id: rowListView

            // layoutModel is the RowListModel* from context
            model: layoutModel

            // Delegate is our RowContainer which holds a Repeater internally
            delegate: RowContainer {}

            // Needed so ListView sizes to content rather than clipping
            implicitHeight: contentHeight

            spacing: 2
            clip: true
        }
    }
}
