import QtQuick 2.6
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3
import QtQuick.Window 2.2

Item {
    id: placeEditorRoot
    property int idToView: 0
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
            height: leftButton.height
            width: placeEditorRoot.width
            DirectionEditor {
                id: leftButton
                text: "vasemmalle"
                width: placeEditorRoot.width / 4
            }
            DirectionEditor {
                id: upButton
                text: "eteenpäin"
                width: placeEditorRoot.width / 4
            }
            DirectionEditor {
                id: downButton
                text: "taaksepäin"
                width: placeEditorRoot.width / 4
            }
            DirectionEditor {
                id: rightButton
                text: "oikealle"
                width: placeEditorRoot.width / 4
            }
        }
    }
}
