import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import QtQuick.Window 2.15
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
        function onDirectionDeletedFromId(id) {
            if (id === idToView) {
                refreshButtons()
            }
        }
        function onDirectionAddedForId(id) {
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
            Layout.alignment: Qt.AlignCenter
            height: placeTitle.font.pixelSize + 10
            width: 10
            Layout.fillWidth: true
            TextInput {
                id: placeTitle
                anchors.centerIn: parent
                selectByMouse: true
                width: parent.width - 10
                font.pixelSize: Screen.height / 25
                onEditingFinished: GameDataBase.setTitle(idToView, placeTitle.text)
            }
        }
        EditBox {
            id: descriptionEditor
            height: 200
            width: 10
            Layout.fillWidth: true
            Layout.fillHeight: true
            TextEdit {
                id: placeDescription
                selectByMouse: true
                anchors.centerIn: parent
                width: parent.width-10
                height: parent.height-10
                font.pixelSize: Screen.height / 25
                onEditingFinished: GameDataBase.setDescription(idToView, placeDescription.text)
            }
        }
        DirectionEditor {
            id: direction1
            width: placeEditorRoot.width
            Layout.fillWidth: true
            text: ""
            onRemoveFromDataBase: GameDataBase.deleteDirection(idToView, 0)
            onEditingFinished: GameDataBase.setDirection(idToView, 0, direction1.text)
            onTargetIdChanged: GameDataBase.setDirectionTargetId(idToView, 0, direction1.targetId)
        }
        DirectionEditor {
            id: direction2
            width: placeEditorRoot.width
            Layout.fillWidth: true
            text: ""
            onRemoveFromDataBase: GameDataBase.deleteDirection(idToView, 1)
            onEditingFinished: GameDataBase.setDirection(idToView, 1, direction2.text)
            onTargetIdChanged: GameDataBase.setDirectionTargetId(idToView, 1, direction2.targetId)
        }
        DirectionEditor {
            id: direction3
            width: placeEditorRoot.width
            Layout.fillWidth: true
            text: ""
            onRemoveFromDataBase: GameDataBase.deleteDirection(idToView, 2)
            onEditingFinished: GameDataBase.setDirection(idToView, 2, direction3.text)
            onTargetIdChanged: GameDataBase.setDirectionTargetId(idToView, 2, direction3.targetId)
        }
        DirectionEditor {
            id: direction4
            width: placeEditorRoot.width
            Layout.fillWidth: true
            text: ""
            onRemoveFromDataBase: GameDataBase.deleteDirection(idToView, 3)
            onEditingFinished: GameDataBase.setDirection(idToView, 3, direction4.text)
            onTargetIdChanged: GameDataBase.setDirectionTargetId(idToView, 3, direction4.targetId)
        }
        Button {
            id: plusButton
            text: "+"
            height: direction1.height
            width: height
            enabled: false
            font.pixelSize: placeTitle.font.pixelSize * 0.8
            onClicked: GameDataBase.addDirection(idToView, "Valinnan teksti", 0)
        }
    }
}
