// Copyright (C) 2026 Qt Group.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

pragma ComponentBehavior: Bound
import QtQuick
import QtQuick.Controls.Basic
import CppModelsViews_Section5

ApplicationWindow {
    id: window

    width: 1000
    height: 550
    visible: true
    title: qsTr("Contacts List Proxy Models")

    required property ContactsListModel contactsListModel
    required property ContactsFilterProxyModel filterModel
    required property ContactsSortProxyModel sortModel
    required property ContactsIdentityProxyModel identityModel

    header: TextField {
        id: filterText

        placeholderText: qsTr("Enter a contacts last name")
        text: window.filterModel.lastName
        font.pointSize: 18
        onEditingFinished: {
            focus = false
            window.filterModel.lastName = text
        }

        Keys.onEscapePressed: {
            focus = false
        }
    }

    Row {
        anchors.fill: parent

        ContactsListView {
            id: contactsListView

            contactsModel: window.contactsListModel
            viewInteraction: filterText.focus ? false : true
            title: qsTr("Contacts List")
        }

        ContactsListView {
            contactsModel: window.filterModel
            viewInteraction: false
            title: qsTr("Filtered By Last Name")
        }

        ContactsListView {
            contactsModel: window.sortModel
            viewInteraction: false
            title: qsTr("Sorted By Age")
        }

        ContactsListView {
            contactsModel: window.identityModel
            viewInteraction: false
            title: qsTr("Hide Info From Minors")
        }
    }
}

