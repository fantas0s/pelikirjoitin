import QtQuick 2.0
import QtQuick.Window 2.2

Rectangle {
    border.color: "grey"
    border.width: 1
    color: "transparent"
    height: label.height
    width: parent.width
    Text {
        id: idNumber
        anchors.left: parent.left
        width: 150
        text: placeId
        color: "black"
        font.pixelSize: Screen.height / 25
    }
    Text {
        id: label
        anchors.left: idNumber.right
        text: placeTitle
        color: "black"
        font.pixelSize: Screen.height / 25
    }
    MouseArea {
        anchors.fill: parent
        onClicked: placeListView.currentIndex = index
    }
}
