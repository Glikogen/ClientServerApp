import QtQuick 2.12
import QtQuick.Layouts 1.12
import QtQuick.Controls 2.12

Item {
    Layout.fillWidth: true
    property alias fieldText: field.text
    property alias tipText: field.placeholderText
    Rectangle {
        anchors.fill: parent
        border.width: 1
        color: panelColor
        TextField {
            id:field
            anchors.fill: parent
            font.pixelSize: 18
            verticalAlignment: TextEdit.AlignVCenter
            selectByMouse: true
            leftPadding: 5
            color: textColor
            placeholderTextColor: textColor
            background: Rectangle {
                color: panelColor
            }
        }
    }
}
