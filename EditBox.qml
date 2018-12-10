import QtQuick 2.6

Rectangle {
    color: "lightgrey"
    border.color: "black"
    border.width: 1
    Rectangle {
        color: "white"
        anchors.centerIn: parent
        radius: 5
        width: parent.width-8
        height: parent.height-8
    }
}
