import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15
import GameDataBase 1.0

Row {
    height: listItemContainer.height
    anchors.left: parent.left
    anchors.right: parent.right
    anchors.rightMargin: parent.width / 20
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
        font.pixelSize: label.font.pixelSize * 0.8
        onClicked: GameDataBase.deleteData(placeId)
    }
}
