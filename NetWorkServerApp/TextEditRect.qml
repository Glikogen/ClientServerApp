import QtQuick 2.12
import QtQuick.Layouts 1.12

Item {
    Layout.fillWidth: true
    property alias fieldText: field.text
    Rectangle {
        anchors.fill: parent
        border.width: 1
        color: "transparent"
        TextInput {
            id:field
            anchors.fill: parent
            font.pixelSize: 18
            verticalAlignment: TextEdit.AlignVCenter
            selectByMouse: true
            leftPadding: 5
        }
    }
}
