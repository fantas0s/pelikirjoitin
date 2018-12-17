import QtQuick 2.6
import QtQuick.Window 2.2
import QtQuick.Controls 2.2
import GameDataBase 1.0

Row {
    height: listItemContainer.height
    anchors.left: parent.left
    anchors.right: parent.right
    Rectangle {
        id: listItemContainer
        border.color: "grey"
        border.width: 1
        color: "transparent"
        height: label.height
        width: parent.width - deleteButton.width
        Text {
            id: label
            anchors.left: parent.left
            text: placeTitle
            color: "black"
            font.pixelSize: Screen.height / 25
        }
        MouseArea {
            anchors.fill: parent
            onClicked: placeListView.currentIndex = index
        }
    }
    Button {
        id: deleteButton
        height: listItemContainer.height
        width: height
        text: "-"
        onClicked: GameDataBase.deleteData(placeId)
    }
}
