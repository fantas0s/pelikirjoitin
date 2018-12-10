import QtQuick 2.6
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3
import QtQuick.Window 2.2
import GameDataBase 1.0

Item {
    id: placeEditorRoot
    property int idToView: 0
    onIdToViewChanged: {
        title.text = GameDataBase.title(idToView)
        placeDescription.text = GameDataBase.description(idToView)
        buttonRow.refreshButtons()
    }
    ColumnLayout {
        anchors.fill: parent
        spacing: 0
        EditBox {
            height: title.font.pixelSize + 10
            anchors.left: parent.left
            anchors.right: parent.right
            TextInput {
                id: title
                anchors.centerIn: parent
                width: parent.width - 10
                text: "Otsikko"
                font.pixelSize: Screen.height / 25
            }
        }
        EditBox {
            anchors.left: parent.left
            anchors.right: parent.right
            height: 200
            Layout.fillHeight: true
            TextEdit {
                id: placeDescription
                anchors.centerIn: parent
                width: parent.width-10
                height: parent.height-10
                text: "Kuvaus tulee tähän"
                font.pixelSize: Screen.height / 25
            }
        }
        Row {
            id: buttonRow
            height: 100
            width: placeEditorRoot.width
            function refreshButtons() {
                buttonlist.model = 0
                buttonlist.model = GameDataBase.directionCount(idToView)
            }
            Repeater {
                id: buttonlist
                model: 0
                delegate: DirectionEditor {
                    text: GameDataBase.direction(idToView, index)
                    width: placeEditorRoot.width / Math.max(1, GameDataBase.directionCount(idToView))
                }
            }
        }
    }
}
