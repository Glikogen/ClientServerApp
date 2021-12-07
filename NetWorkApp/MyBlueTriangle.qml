import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12
import ViewModel 1.0
import QtQuick.Dialogs 1.2
import QtQuick.Shapes 1.12

Shape {
    id:blueTriangle
    width: 20
    height: 20
    property bool isAnotherClient: false
    anchors.verticalCenter: isAnotherClient == false ? textName.verticalCenter : parent.BottomRight
    anchors.left: isAnotherClient == false ? textName.right : parent.right
    anchors.right: isAnotherClient == false ? textName.right : parent.right
    anchors.top: isAnotherClient == false ? textName.verticalCenter : parent.bottom
        anchors.rightMargin: isAnotherClient == false ? 0 : deafMargin*3
    anchors.leftMargin: isAnotherClient == false ? deafMargin : -deafMargin*2
    anchors.topMargin: isAnotherClient == false ? -deafMargin : 0
    visible: textName.text === "" ? false : true
    rotation: isAnotherClient == false ? 0 : 270;
    ShapePath {
        fillColor: isAnotherClient == false ? darkBubbleColor : lightPanelColor
        strokeColor: darkBubbleColor
        strokeWidth: 1
        startX: 0
        startY: 10
        PathLine { x:10; y:0 }
        PathLine { x:10; y:20 }
        PathLine { x:0; y:10 }
    }
}
