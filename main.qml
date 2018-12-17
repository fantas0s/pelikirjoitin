import QtQuick 2.6
import QtQuick.Window 2.2
import QtQuick.Controls 2.2
import GameDataBase 1.0

Window {
    visible: true
    width: Screen.width
    height: Screen.height
    title: qsTr("Pelikirjoitin")
    PlaceList {
        id: listOfPlaces
        anchors.left: parent.left
        anchors.bottom: plusbutton.top
        anchors.top: parent.top
        width: parent.width / 3
    }
    Button {
        id: plusbutton
        anchors.left: parent.left
        anchors.bottom: parent.bottom
        width: parent.width / 3
        text: "+"
        onClicked: GameDataBase.addData("otsikko", "kuvaus")
    }
    Text {
        color: "black"
        text: "Paina \"+\" lisätäksesi paikan"
        anchors.centerIn: listOfPlaces
        visible: !listOfPlaces.count
    }
    PlaceEditor {
        idToView: listOfPlaces.currentId
        anchors.left: listOfPlaces.right
        anchors.bottom: parent.bottom
        anchors.top: parent.top
        width: 2 * parent.width / 3
    }
}
