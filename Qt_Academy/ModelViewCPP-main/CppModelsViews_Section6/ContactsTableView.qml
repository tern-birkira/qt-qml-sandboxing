// Copyright (C) 2026 Qt Group.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

pragma ComponentBehavior: Bound
import QtQuick
import QtQuick.Controls.Basic

/*
Controls
    Digit 1: Inserts a row above the current row
    Digit 2: Removes the current row
    Digit 3: Moves the current row to the top of the table
    Digit 4: Modifies the current row
    Digit 5: Clears the entire table
    Digit 6: Removes the last column - rows cannot be added back in
*/

Item {
    height: parent.height
    width: parent.width
    required property bool transposed
    required property AbstractItemModel contactsModel

    function setFullRow(model : AbstractItemModel, firstName : string, lastName : string, age : string, phone : string) {
        for (let i = 0; i < 4; i++) {

            let index = model.index(contactsView.currentRow, i)
            if(contactsView.currentRow === -1){
                index = model.index(0, i)
            }

            switch (i) {
                case 0:
                model.setData(index, firstName)
                break;
                case 1:
                model.setData(index, lastName)
                break;
                case 2:
                model.setData(index, age)
                break;
                case 3:
                model.setData(index, phone)
                break;
            }
        }
    }

    ListModel {
        id: contactsHHeaderData

        ListElement{display: qsTr("First Name")}
        ListElement{display: qsTr("Last Name")}
        ListElement{display: qsTr("Age")}
        ListElement{display: qsTr("Phone Number")}
    }

    HorizontalHeaderView  {
        id: contactsHHeader

        anchors.left: scrollView.left
        anchors.top: parent.top
        syncView: contactsView
        Component.onCompleted: {
            if(!transposed) {
                model = contactsHHeaderData
                delegate = contactsHorizontalDelegate
            }
        }
    }

    VerticalHeaderView  {
        id: contactsVHeader

        anchors.left: parent.left
        anchors.top: scrollView.top
        syncView: contactsView
        clip: true
        Component.onCompleted: {
            if(transposed) {
                model = contactsHHeaderData
                delegate = contactsHorizontalDelegate
            }
        }
    }

    ScrollView {
        id: scrollView

        anchors.left: contactsVHeader.right
        anchors.top: contactsHHeader.bottom
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        clip: true

        TableView {
            id: contactsView

            anchors.fill: parent
            columnSpacing: 1
            rowSpacing: 1
            editTriggers: TableView.DoubleTapped

            resizableColumns: true
            resizableRows: true

            model: contactsModel
            delegate: contactsDelegate

            selectionModel: ItemSelectionModel {
                model: contactsView.model
            }

            Keys.onDigit1Pressed: {
                if (currentRow >= 0) {
                    let index = contactsView.model.index(contactsView.currentRow, 0)
                    contactsView.model.insertRows(contactsView.currentRow, 1, index.parent)
                    setFullRow(contactsView.model, "Greg", "Doe", "100", "123-456-7890")
                } if (currentRow === -1) {
                    let index = contactsView.model.index(contactsView.currentRow, 0)
                    contactsView.model.insertRows(0, 1, index.parent)
                    setFullRow(contactsView.model, "Greg", "Doe", "100", "123-456-7890")
                }
            }

            Keys.onDigit2Pressed: {
                if (currentRow >= 0) {
                    let index = contactsView.model.index(contactsView.currentRow, 0)
                    contactsView.model.removeRows(contactsView.currentRow, 1, index.parent)
                }
            }

            Keys.onDigit3Pressed: {
                if (currentRow >= 1) {
                    let index = contactsView.model.index(contactsView.currentRow, 0)
                    contactsView.model.moveRows(index.parent, contactsView.currentRow, 1, index.parent, 0)
                }
            }

            Keys.onDigit4Pressed: {
                if (currentRow >= 0) {
                    setFullRow(contactsView.model, "Sam", "Smith", "50", "098-765-4321")
                }
            }

            Keys.onDigit5Pressed: {
                contactsView.model.clearModel()
            }

            Keys.onDigit6Pressed: {
                if (currentColumn >= 0) {
                    let index = contactsView.model.index(contactsView.currentColumn, 0)
                    contactsView.model.removeColumns(contactsView.columns-1, 1, index.parent)
                }
            }
        }
    }

    Component {
        id: contactsDelegate

        Rectangle {
            id: delegateRect

            required property bool current
            required property string display

            implicitWidth: 100
            implicitHeight: 50
            color: current ? "pink" : "lightgray"
            border.width: current ? 2 : 0
            TableView.editDelegate: contactsEditDelegate

            Text {
                id: delegateText

                text: delegateRect.display
                padding: 12
                anchors.fill: parent
            }
        }
    }

    Component {
        id: contactsHorizontalDelegate

        Text {
            id: delegateText

            required property string display

            padding: 12
            text: display

            Rectangle {
                anchors.fill: parent
                color: "gray"
                z: -1
            }
        }
    }

    Component {
        id: contactsEditDelegate

        TextField {
            id: delegateTextField

            required property int column
            required property int row
            required property string display

            anchors.fill: parent
            text: display

            horizontalAlignment: TextInput.AlignHCenter
            verticalAlignment: TextInput.AlignVCenter

            TableView.onCommit: {
                let index = TableView.view.index(row, column)
                contactsModel.setData(index, text)
            }
        }
    }
}
