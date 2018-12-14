import QtQuick 2.6
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3
import QtQuick.Window 2.2
import GameDataBase 1.0

Item {
    id: placeEditorRoot
    property int idToView: 0
    onIdToViewChanged: {
        placeTitle.text = GameDataBase.getTitle(idToView)
        placeDescription.text = GameDataBase.getDescription(idToView)
        refreshButtons()
    }
    Connections {
        target: GameDataBase
        onDirectionDeletedFromId: {
            if (id === idToView) {
                refreshButtons()
            }
        }
        onDirectionAddedForId: {
            if (id === idToView) {
                refreshButtons()
            }
        }
    }

    function refreshButtons() {
        direction1.visible = false
        direction2.visible = false
        direction3.visible = false
        direction4.visible = false
        plusButton.enabled = GameDataBase.getDirectionCount(idToView) < GameDataBase.maxDirections
        switch (GameDataBase.getDirectionCount(idToView)) {
        default:
        case 4:
            direction4.visible = true
            direction4.text = GameDataBase.getDirection(idToView, 3)
            direction4.targetId = GameDataBase.getDirectionTargetId(idToView, 3)
            //fall through
        case 3:
            direction3.visible = true
            direction3.text = GameDataBase.getDirection(idToView, 2)
            direction3.targetId = GameDataBase.getDirectionTargetId(idToView, 2)
            //fall through
        case 2:
            direction2.visible = true
            direction2.text = GameDataBase.getDirection(idToView, 1)
            direction2.targetId = GameDataBase.getDirectionTargetId(idToView, 1)
            //fall through
        case 1:
            direction1.visible = true
            direction1.text = GameDataBase.getDirection(idToView, 0)
            direction1.targetId = GameDataBase.getDirectionTargetId(idToView, 0)
            //fall through
        case 0:
            break;
        }
    }
    ColumnLayout {
        anchors.fill: parent
        spacing: 0
        EditBox {
            id: titleEditor
            height: placeTitle.font.pixelSize + 10
            anchors.left: parent.left
            anchors.right: parent.right
            TextInput {
                id: placeTitle
                anchors.centerIn: parent
                width: parent.width - 10
                text: "Otsikko"
                font.pixelSize: Screen.height / 25
                onEditingFinished: GameDataBase.setTitle(idToView, placeTitle.text)
            }
        }
        EditBox {
            id: descriptionEditor
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
                onEditingFinished: GameDataBase.setDescription(idToView, placeDescription.text)
            }
        }
        DirectionEditor {
            id: direction1
            anchors.left: parent.left
            anchors.right: parent.right
            text: ""
            onRemoveFromDataBase: GameDataBase.deleteDirection(idToView, 0)
            onEditingFinished: GameDataBase.setDirection(idToView, 0, direction1.text)
        }
        DirectionEditor {
            id: direction2
            anchors.left: parent.left
            anchors.right: parent.right
            text: ""
            onRemoveFromDataBase: GameDataBase.deleteDirection(idToView, 1)
            onEditingFinished: GameDataBase.setDirection(idToView, 1, direction2.text)
        }
        DirectionEditor {
            id: direction3
            anchors.left: parent.left
            anchors.right: parent.right
            text: ""
            onRemoveFromDataBase: GameDataBase.deleteDirection(idToView, 2)
            onEditingFinished: GameDataBase.setDirection(idToView, 2, direction3.text)
        }
        DirectionEditor {
            id: direction4
            anchors.left: parent.left
            anchors.right: parent.right
            text: ""
            onRemoveFromDataBase: GameDataBase.deleteDirection(idToView, 3)
            onEditingFinished: GameDataBase.setDirection(idToView, 3, direction4.text)
        }
        Button {
            id: plusButton
            text: "+"
            height: direction1.height
            width: height
            enabled: false
            onClicked: GameDataBase.addDirection(idToView, "Minne?", 0)
        }
    }
}
