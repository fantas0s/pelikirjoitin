import QtQuick 2.6
import QtQuick.Controls 2.0
import GameDataModel 1.0
import GameDataBase 1.0

ListView {
    id: placeListView
    property int currentId: GameDataBase.getIdAt(currentIndex)
    anchors.left: parent.left
    anchors.bottom: parent.bottom
    anchors.top: parent.top
    width: parent.width / 3
    model: GameDataModel {}
    delegate: PlaceListDelegate {}
    focus: true
    highlight: Rectangle { color: "lightsteelblue"; radius: 10 }
    ScrollBar.vertical: ScrollBar {

        anchors.top: placeListView.top
        anchors.right: placeListView.right
        anchors.bottom: placeListView.bottom
        policy: ScrollBar.AlwaysOn
        width: parent.width / 20
    }
}
