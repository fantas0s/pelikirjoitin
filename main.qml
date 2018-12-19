import QtQuick 2.6
import QtQuick.Window 2.2
import QtQuick.Controls 2.3
import QtQuick.Layouts 1.3
import GameDataBase 1.0
import DataBaseFileWriter 1.0

Window {
    visible: true
    width: Screen.width
    height: Screen.height
    title: qsTr("Pelikirjoitin")
    RowLayout {
        id: menuBar
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: parent.top
        Button {
            text: "Avaa aikaisempi peli"
        }
        Button {
            text: "Tallenna peli"
            onClicked: fileWriter.saveGame("Esimerkkipeli")
        }
        Item {
            Layout.fillWidth: true
        }
    }
    DataBaseFileWriter {
        id: fileWriter
        onSaveSuccessful: {
            saveResultDialog.title = "Tallennus onnistui."
            saveResultDialog.open()
        }
        onSaveFailed: {
            saveResultDialog.title = "Virhe: "+errorText
            saveResultDialog.open()
        }
    }

    PlaceList {
        id: listOfPlaces
        anchors.left: parent.left
        anchors.bottom: plusbutton.top
        anchors.top: menuBar.bottom
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
        anchors.top: menuBar.bottom
        width: 2 * parent.width / 3
    }
    Dialog {
        id: saveResultDialog
        width: 400
        height: 100
        x: parent.width / 2 - width/2
        y: parent.height / 2 - height/2
        modal: true
        standardButtons: Dialog.Ok
    }
}
