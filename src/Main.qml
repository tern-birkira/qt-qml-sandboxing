import QtQuick
import birkis.models

Window {
    width: 640
    height: 480
    visible: true
    title: qsTr("Hello World")
    color: "black"
    TrackLabel {
    }
    Timer {
        interval: 10000   // 5 seconds after launch
        running: true
        onTriggered: console.log("Timer fired — debugger connected?")
    }
}
