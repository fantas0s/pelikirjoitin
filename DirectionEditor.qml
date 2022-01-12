import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import GameDataBase 1.0
import GameDataModel 1.0

RowLayout {
    id: dirEditRoot
    signal removeFromDataBase()
    signal editingFinished()
    property alias text: inputField.text
    property int targetId: 0
    height: dirEditBox.height
    EditBox {
        id: dirEditBox
        color: "lightgray"
        height: inputField.font.pixelSize + 10
        width: 200
        Layout.fillWidth: true
        TextInput {
            id: inputField
            selectByMouse: true
            anchors.centerIn: parent
            width: parent.width - 10
            text: dirEditRoot.text
            font.pixelSize: Screen.height / 25
            onEditingFinished: dirEditRoot.editingFinished()
        }
    }
    Rectangle {
        height: parent.height
        width: deleteButton.width * 3
        color: "lightgrey"
        border.width: 1
        border.color: "black"
        ComboBox {
            model: GameDataModel {}
            textRole: "placeTitle"
            currentIndex: GameDataBase.getIndexOf(targetId)
            anchors.centerIn: parent
            height: parent.height - 4
            width: parent.width - 4
            onActivated: {
                dirEditRoot.targetId = GameDataBase.getIdAt(currentIndex)
            }
        }
    }
    Button {
        id: deleteButton
        height: dirEditBox.height
        width: height
        text: "-"
        font.pixelSize: inputField.font.pixelSize * 0.8
        onClicked: dirEditRoot.removeFromDataBase()
    }
}
