import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12
import ViewModel 1.0
import QtQuick.Dialogs 1.2
import QtQuick.Shapes 1.12


Window {
    width: 1100
    height: 500
    visible: true
    title: qsTr("Client app")
    minimumWidth: 1000
    minimumHeight: 400

    readonly property int deafMargin: 10
    readonly property color panelColor: "#17212B"
    readonly property color lightPanelColor: "DodgerBlue"
    readonly property color bubbleColor: "#87CEFA"
    readonly property color darkBubbleColor: "#4682B4"
    readonly property color bgColor: "#0E1621"
    readonly property color textColor: "white"

    color: bgColor

    ViewModel {
        id: viewModel
//        onAddMessageToChat: (message) => {
//                                chatWindow.text += message + "\n";
//                            }
    }

    Item {
        anchors.fill: parent
        ColumnLayout {
            id:mainLayout
            anchors.fill: parent
            anchors.leftMargin: 20
            anchors.rightMargin: 20
            anchors.topMargin: 10
            anchors.bottomMargin: 10
            spacing: 10
            RowLayout {
                id:topRowLay
                Layout.fillWidth: true
                Label {
                    width: lbl_textName.contentWidth
                    Text {
                        id: lbl_textName
                        color: textColor
                        text: "Your Name:"
                        font.pixelSize: 18
                    }
                }
                TextEditRect {
                    id:nameRect
                    Layout.minimumWidth: 200
                    height: connectToServer.height
                    tipText: "write your Name"
                }

                Label {
                    width: lbl_textIP.contentWidth
                    Text {
                        id: lbl_textIP
                        color: textColor
                        text: "IP:"
                        font.pixelSize: 18
                    }
                }
                TextEditRect {
                    id: ipRect
                    Layout.minimumWidth: 150
                    height: nameRect.height
                    fieldText: "127.0.0.1"
                }

                Label {
                    width: lbl_textPort.contentWidth
                    Text {
                        id: lbl_textPort
                        color: textColor
                        text: "port:"
                        font.pixelSize: 18
                    }
                }
                TextEditRect {
                    id: portRect
                    Layout.minimumWidth: 150
                    height: nameRect.height
                    fieldText: "3228"
                }
                StylishButton {
                    id:connectToServer
                    text: "Connect to server!"
                    onClicked: {
                        if (viewModel.isConnect()) {
                            messageDialog.visible = true;
                            messageDialog.text = "Вы уже подключены к серверу";
                            return;
                        }
                        if(nameRect.fieldText === "") {
                            messageDialog.visible = true;
                            messageDialog.text = "Перед подключением надо задать имя, очевидно";
                            return;
                        }
                        if(ipRect.fieldText === "")
                        {
                            messageDialog.visible = true;
                            messageDialog.text = "Перед подключением надо задать IP или имя хоста, очевидно...";
                            return;
                        }
                        if(portRect.fieldText === "")
                        {
                            messageDialog.visible = true;
                            messageDialog.text = "ну естественно, перед подключением надо задать порт сервера";
                            return;
                        }
                        viewModel.connectToServer(nameRect.fieldText, ipRect.fieldText, portRect.fieldText);
                        nameRect.enabled = false;
                    }
                }

                StylishButton {
                    id:disconnectFromServer
                    text: "Disconnect!"
                    onClicked: {
                        if (!viewModel.isConnect()) {
                            messageDialog.visible = true;
                            messageDialog.text = "Вы и так отключены от сервера, е мае";
                            return;
                        }
                        nameRect.enabled = true;
                        viewModel.disconnectFromServer();
                    }
                }
            }

            Rectangle {
                border.width: 1
                Layout.fillHeight: true
                Layout.fillWidth: true
                color: bgColor

                ListView {
                    id: listView
                    anchors.fill: parent
                    spacing: deafMargin
                    model: viewModel.messagesModel
                    ScrollBar.vertical: ScrollBar { id:scroll }

                    delegate: Rectangle {
                        height: 60
                        anchors.margins: deafMargin*2
                        width: parent.width
                        color: panelColor
                        border.color: panelColor
                        radius: 6

                        Text {
                            id: textName
                            anchors.left: parent.left
                            anchors.verticalCenter: parent.verticalCenter
                            anchors.margins: deafMargin
                            text: model.name
                            color: textColor
                            font.pixelSize: 20
                        }

                        MyBlueTriangle {
                            id: blueTriangle
                            isAnotherClient: model.name === nameRect.fieldText ? true : false
                        }

                        Rectangle {
                            width: textName.text === "" || model.name === nameRect.fieldText ?
                                       parent.width - deafMargin : parent.width - textName.contentWidth - deafMargin*3 - 5
                            anchors.margins: deafMargin/2
                            anchors.top: parent.top
                            anchors.right: parent.right
                            anchors.bottom: parent.bottom
                            color: model.name === nameRect.fieldText ? lightPanelColor : darkBubbleColor
                            radius: 7
                            Text {
                                id:textLine
                                anchors.margins: deafMargin
                                anchors.left: parent.left
                                anchors.right: parent.right
                                anchors.verticalCenter: parent.verticalCenter
                                text: model.line
                                color: textColor
                                font.pixelSize: 24
                                verticalAlignment: Text.AlignVCenter
                                //horizontalAlignment: Text.AlignHCenter
                                horizontalAlignment: textName.text === "" ? Text.AlignHCenter : Text.AlignLeft ;
                            }

                            Text {
                                id:textTime
                                color: textColor
                                anchors.margins: deafMargin / 2
                                anchors.bottom: parent.bottom
                                anchors.right: parent.right
                                text: model.time
                                font.pixelSize: 12
                            }
                        }
                    }
                }
            }

            RowLayout {
                id: bottomRowLay
                Layout.fillWidth: true
                spacing: 10

                function pressedSendMessage(){
                    if (viewModel.isConnect())
                        viewModel.sendMessage(newMessage.fieldText);
                    else
                    {
                        messageDialog.visible = true;
                        messageDialog.text = "это уже не смешно";
                    }
                    newMessage.fieldText = "";
                }

                TextEditRect {
                    id: newMessage
                    height: sendMessageButton.height
                    Layout.minimumWidth: 400
                    tipText: "write a message"

                    Keys.onPressed: {
                            if (event.key === Qt.Key_Return) {
                                event.accepted = true;
                                bottomRowLay.pressedSendMessage();
                            }
                        }
                }

                StylishButton {
                    id:sendMessageButton
                    Layout.minimumWidth: 100
                    text: "Send"
                    font.pixelSize: 18
                    onClicked: {
                        bottomRowLay.pressedSendMessage();
                    }
                }
            }
        }

        MessageDialog {
            id: messageDialog
            visible: false
            modality: Qt.WindowModal
            title: "Ошибка действия"
        }
    }
}
