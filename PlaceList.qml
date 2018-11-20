import QtQuick 2.6
import QtQuick.Controls 2.0

ListView {
    id: placeListView
    anchors.left: parent.left
    anchors.bottom: parent.bottom
    anchors.top: parent.top
    width: parent.width / 3
    model: ListModel {
        ListElement {
            placeNumber: 1
            placeTitle: "Aula"
        }
        ListElement {
            placeNumber: 2
            placeTitle: "Eteinen"
        }
        ListElement {
            placeNumber: 3
            placeTitle: "Makuuhuone"
        }
    }
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
