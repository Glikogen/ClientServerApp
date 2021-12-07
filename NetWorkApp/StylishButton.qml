import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12

Button {
    text: "A button"
    font.pixelSize: 18
    id: control
    Layout.fillWidth: true
    background: Rectangle {
        implicitWidth: 100
        implicitHeight: 25
        color: bubbleColor
        border.width: control.activeFocus ? 2 : 1
        border.color: "CornflowerBlue"
        radius: 4
        gradient: Gradient {
            GradientStop { position: 0 ; color: control.pressed ? bubbleColor : darkBubbleColor }
            GradientStop { position: 1 ; color: control.pressed ? bubbleColor : darkBubbleColor }
        }
    }
}
