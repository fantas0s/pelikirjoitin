import QtQuick 2.6
import QtQuick.Window 2.2

Window {
    visible: true
    width: Screen.width
    height: Screen.height
    title: qsTr("Pelikirjoitin")
    PlaceList {
        id: listOfPlaces
        anchors.left: parent.left
        anchors.bottom: parent.bottom
        anchors.top: parent.top
        width: parent.width / 3
    }
    PlaceEditor {
        idToView: listOfPlaces.currentId
        anchors.left: listOfPlaces.right
        anchors.bottom: parent.bottom
        anchors.top: parent.top
        width: 2 * parent.width / 3
    }
}
