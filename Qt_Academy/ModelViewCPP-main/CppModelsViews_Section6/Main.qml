// Copyright (C) 2026 Qt Group.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

pragma ComponentBehavior: Bound
import QtQuick
import QtQuick.Controls.Basic
import CppModelsViews_Section6

ApplicationWindow {
    id: window

    width: 450
    height: 550
    visible: true
    title: qsTr("Simple Table Model")

    required property ContactsTableModel contactsTableModel
    required property ContactsTransposeProxyModel transposeModel

    header: Row {
        Button {
            width: window.width/2
            text: qsTr("Click to show original")

            onClicked: {
                originalView.visible = true
                transposedView.visible = false
                window.width = 450
                window.height = 550
            }
        }

        Button {
            width: window.width/2
            text: qsTr("Click to show transposed")

            onClicked: {
                originalView.visible = false
                transposedView.visible = true
                window.width = 1050
                window.height = 300
            }
        }
    }

    ContactsTableView {
        id: originalView

        contactsModel: contactsTableModel
        transposed: false
        visible: true
    }

    ContactsTableView {
        id: transposedView

        contactsModel: transposeModel
        transposed: true
        visible: false
    }
}
