// Copyright (C) 2026 Qt Group.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

pragma ComponentBehavior: Bound
import QtQuick
import QtQuick.Controls.Basic
import CppModelsViews_Section5

/*
Controls
    Arrow keys: move the current element up and down
    Escape: de-selects the current element
    Delete: deletes the current element
    Tab: inserts a copy of the current element
    Space: sets the current element to "Greg Doe"
    1: opens popup to insert a new entry
    2: deletes entire model
 */

Item {
    id: root

    height: parent.height
    width: parent.width/4
    required property AbstractItemModel contactsModel
    required property string title
    required property bool viewInteraction

    ListView {
        id: contactsView

        anchors.fill: parent

        delegate: contactsDelegate
        model: root.contactsModel
        header: contactsHeader
        footer: contactsFooter

        orientation: ListView.Vertical

        highlightFollowsCurrentItem: true
        highlight: contactsHighlight
        highlightMoveDuration: 1
        highlightResizeDuration: 1
        focus: root.viewInteraction

        displaced: displacedTransition
        add: addTransition
        remove: removeTransition
        move: moveTransition

        Keys.onDeletePressed: {
            if (contactsView.currentIndex < 0) {
                console.log("Must select an element to delete an entry")
            } else {
                let index = contactsView.model.index(contactsView.currentIndex, 0)
                contactsView.model.removeRows(contactsView.currentIndex, 1, index.parent)
            }
        }

        Keys.onEscapePressed: {
            contactsView.currentIndex = -1
        }

        Keys.onSpacePressed: {
            if (contactsView.currentIndex < 0) {
                console.log("Must select an element to modify an entry")
            } else {
                let index = contactsView.model.index(contactsView.currentIndex, 0)
                contactsView.model.setData(index, "Greg, Doe, 100, 123-456-7890")
            }
        }

        Keys.onDigit1Pressed: {
            newValuePopup.open()
        }

        Keys.onDigit2Pressed: {
            contactsView.model.clearModel(contactsView.count)
        }

        Keys.onUpPressed: {
            if (contactsView.count <= 1) {
                console.log("Not enough elements in model to move an element")
            } else if (contactsView.currentIndex === 0){
                console.log("Cannot move first element up")
            } else {
                let sourceIndex = contactsView.model.index(contactsView.currentIndex, 0)
                let destinationIndex = contactsView.model.index(contactsView.currentIndex - 1, 0)
                contactsView.model.moveRows(sourceIndex.parent, contactsView.currentIndex, 1, destinationIndex.parent, contactsView.currentIndex - 1)
            }
        }

        Keys.onDownPressed: {
            if (contactsView.count <= 1) {
                console.log("Not enough elements in model to move an element")
            } else if (contactsView.currentIndex === (contactsView.count - 1)){
                console.log("Cannot move last element down")
            } else {
                let sourceIndex = contactsView.model.index(contactsView.currentIndex, 0)
                let destinationIndex = contactsView.model.index(contactsView.currentIndex + 1, 0)
                contactsView.model.moveRows(sourceIndex.parent, contactsView.currentIndex, 1, destinationIndex.parent, contactsView.currentIndex + 1)
            }
        }

        Popup {
            id: newValuePopup

            height: 250
            width: 200
            anchors.centerIn: parent

            Column {
                anchors.centerIn: parent
                spacing: 5

                TextField {
                    id: firstNameField

                    font.pointSize: 10
                    placeholderText: qsTr("Enter first name")
                    width: 150
                    height: 30
                }

                TextField {
                    id: lastNameField

                    font.pointSize: 10
                    placeholderText: qsTr("Enter last name")
                    width: 150
                    height: 30
                }

                TextField {
                    id: ageField

                    font.pointSize: 10
                    placeholderText: qsTr("Enter age")
                    width: 150
                    height: 30
                    validator: IntValidator{}
                }

                TextField {
                    id: phoneField

                    font.pointSize: 10
                    placeholderText: qsTr("Enter phone number")
                    width: 150
                    height: 30
                    validator: RegularExpressionValidator{regularExpression: /^\d{3}-\d{3}-\d{4}$/}
                }

                Button {
                    height: 25
                    width: firstNameField.width
                    text: qsTr("Append")
                    anchors.horizontalCenter: parent.horizontalCenter
                    enabled: ((firstNameField.text !== "") && (lastNameField.text !== "") && (ageField.text !== "") && (phoneField.text !== ""))

                    onClicked: {
                        contactsView.model.appendRow(contactsView.count)
                        let index = contactsView.model.index(contactsView.count - 1, 0)
                        contactsView.model.setData(index, "%1, %2, %3, %4"
                                                   .arg(firstNameField.text).arg(lastNameField.text)
                                                   .arg(ageField.text).arg(phoneField.text))
                        newValuePopup.close()
                        firstNameField.text = ""
                        lastNameField.text = ""
                        ageField.text = ""
                        phoneField.text = ""
                    }
                }
            }
        }
    }

    Component {
        id: contactsDelegate

        Rectangle {
            id: delegateRect

            required property string firstName
            required property string lastName
            required property int age
            required property string phoneNumber
            required property int index
            property ItemView listView: ListView.view

            height: 50
            width: parent ? parent.width : 0
            border.color: "black"

            Text {
                anchors.left: parent.left
                anchors.leftMargin: 5
                text: qsTr("Name: %1 %2 \nAge: %3 \nPhone: %4"
                .arg(delegateRect.firstName).arg(delegateRect.lastName)
                .arg(delegateRect.age).arg(delegateRect.phoneNumber))
            }

            MouseArea {
                anchors.fill: parent
                hoverEnabled: true
                enabled: root.viewInteraction

                onReleased: {
                    delegateRect.listView.currentIndex = delegateRect.index
                    delegateRect.color = "white"
                }

                onPressed: {
                    delegateRect.color = "gray"
                }

                onEntered: {
                    delegateRect.color = "lightgray"
                }

                onExited: {
                    delegateRect.color = "white"
                }
            }

            Keys.onTabPressed: {
                if (contactsView.currentIndex < 0) {
                    console.log("Must select an element to insert a new entry")
                } else {
                    let index = contactsView.model.index(contactsView.currentIndex, 0)
                    contactsView.model.insertRows(listView.currentIndex, 1, index.parent)
                    contactsView.model.setData(index, "%1, %2, %3, %4"
                                               .arg(delegateRect.firstName).arg(delegateRect.lastName)
                                               .arg(delegateRect.age).arg(delegateRect.phoneNumber))
                }
            }
        }
    }

    Component {
        id: contactsHeader

        Rectangle {
            id: headerRect

            height: 35
            width: parent.width
            border.color: "black"
            color: "mistyrose"
            z: contactsView.z + 2

            Text {
                anchors.centerIn: parent
                text: root.title
                font.pointSize: 18
            }
        }
    }

    Component {
        id: contactsFooter

        Rectangle {
            id: footerRect

            height: 20
            width: parent.width
            border.color: "black"
            color: "mistyrose"
        }
    }

    Component {
        id: contactsHighlight

        Rectangle {
            id: highlightRect

            border.color: "black"
            color: "yellow"
            opacity: 0.15
            z: root.viewInteraction ? (contactsView.z + 2) : 0
        }
    }

    Transition {
        id: displacedTransition

        NumberAnimation {
            properties: "x,y"
            duration: 300
        }
    }

    Transition {
        id: addTransition

        NumberAnimation {
            property: "opacity"
            from: 0
            to: 1.0
            duration: 300
        }

        NumberAnimation {
            property: "scale"
            from: 0
            to: 1.0
            duration: 300
        }
    }

    Transition {
        id: moveTransition

        NumberAnimation {
            properties: "x,y"
            duration: 300
        }
    }

    Transition {
        id: removeTransition

        NumberAnimation {
            property: "opacity"
            from: 1.0
            to: 0
            duration: 300
        }

        NumberAnimation {
            property: "scale"
            from: 1.0
            to: 0
            duration: 300
        }
    }
}
