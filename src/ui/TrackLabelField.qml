import QtQuick
import QtQuick.Controls

ItemDelegate {
    property string fieldLabel
    width: ListView.view.width
    text:  fieldLabel
}