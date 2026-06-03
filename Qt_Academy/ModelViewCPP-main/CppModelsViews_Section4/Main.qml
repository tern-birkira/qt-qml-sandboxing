// Copyright (C) 2026 Qt Group.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

pragma ComponentBehavior: Bound
import QtQuick
import QtQuick.Controls.Basic
import CppModelsViews_Section4

Window {
    width: 640
    height: 480
    visible: true
    title: qsTr("Simple Tree View")

    Rectangle {
        anchors.fill: parent
        color: "lightgray"
    }

    TreeModel {
        id: treeModel
    }

    TreeView {
        id: treeView

        anchors.fill: parent
        model: treeModel
        delegate: treeViewDelegateComponent
        editTriggers: TableView.DoubleTapped
        selectionModel: ItemSelectionModel {
        }
    }

    Component {
        id: treeViewDelegateComponent

        TreeViewDelegate {
            id: treeViewDelegate

            //Defined by roleNames() in backend
            required property string displaying
            required property string edition

            background: Rectangle {
                color: (treeViewDelegate.depth === 0) ? "lavender" :
                       (treeViewDelegate.depth === 1) ? "lightblue" :
                       (treeViewDelegate.depth === 2) ? "honeydew" : "white"
                border.width: treeViewDelegate.current ? 2 : 0
            }

            contentItem: Text {
                id: myTextEdit

                font.pixelSize: 15
                text: treeViewDelegate.displaying
            }

            TableView.editDelegate: TextField {
                anchors.fill: parent
                font.pixelSize: 15
                text: treeViewDelegate.displaying
                TableView.onCommit: treeViewDelegate.model.edition = text
            }

            onEditingChanged: treeView.width = myTextEdit.width
        }
    }
}
