import QtQuick 2.0
import QtQuick.Window 2.2

EditBox {
    id: dirEditRoot
    property string text: "jonnekin"
    color: "lightgray"
    height: inputField.font.pixelSize + 10
    width: 100
    TextInput {
        id: inputField
        anchors.centerIn: parent
        width: parent.width - 10
        text: dirEditRoot.text
        font.pixelSize: Screen.height / 25
    }
}
