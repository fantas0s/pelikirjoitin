import QtQuick 2.0
import QtQuick.Window 2.2
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.2
import GameDataBase 1.0

RowLayout {
    id: dirEditRoot
    signal removeFromDataBase()
    property string text: "jonnekin"
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
            anchors.centerIn: parent
            width: parent.width - 10
            text: dirEditRoot.text
            font.pixelSize: Screen.height / 25
        }
    }
    Rectangle {
        height: parent.height
        width: deleteButton.width * 3
        color: "lightgrey"
        border.width: 1
        border.color: "black"
        Button {
            text: GameDataBase.title(targetId)
            anchors.centerIn: parent
            height: parent.height - 4
            width: parent.width - 4
        }
    }
    Button {
        id: deleteButton
        height: dirEditBox.height
        width: height
        text: "-"
        onClicked: dirEditRoot.removeFromDataBase()
    }
}
