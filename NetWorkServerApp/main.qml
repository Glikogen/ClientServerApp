import QtQuick 2.12
import ViewModel 1.0
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12
import QtQuick.Controls.Styles 1.4
import QtQuick.Dialogs 1.2
import Qt.labs.platform 1.0

Window {
    width: 1000
    height: 700
    visible: true
    title: qsTr("Server app")
    minimumHeight: 700
    minimumWidth: 1000

    ViewModel {
        id: serverData
        onAddMessagetoChat: (message) => {
                                chatWindow.text += message + "\n";
                            }
    }

    Item {
        id:background
        anchors.fill: parent
        ColumnLayout {
            id:mainColLay
            anchors.fill: parent
            spacing: 10
            anchors.margins: 10
            RowLayout {
                id:topRowLay
                Layout.fillWidth: true
                spacing: 10
                Label {
                    text: "Server Name:"
                    font.pixelSize: 18
                }

                TextEditRect {
                    id: nameRect
                    height: openServerButton.height
                }

                Label {
                    text: "Port:"
                    font.pixelSize: 18
                }

                TextEditRect {
                    id: portRect
                    height: openServerButton.height
                    fieldText: "3228"
                }

                StylishButton {
                    id:openServerButton
                    text: "Open"
                    Layout.fillWidth: false
                    onClicked: {
                        if (serverData.isOpen) {
                            messageDialog.visible = true;
                            messageDialog.text = "Сервер уже запущен";
                            return;
                        }

                        if (nameRect.textField === "")
                        {
                            messageDialog.visible = true;
                            messageDialog.text = "Введите имя сервера перед открытием!";
                            return;
                        }
                        if (portRect.fieldText === "")
                        {
                            messageDialog.visible = true;
                            messageDialog.text = "Введите номер порта перед открытием сервера!"
                            return;
                        }
                        serverData.openServer(nameRect.fieldText, portRect.fieldText);
                    }
                }

                StylishButton {
                    id:closeServerButton
                    text: "Close"
                    Layout.fillWidth: false
                    onClicked: {
                        if (!serverData.isOpen) {
                            messageDialog.visible = true;
                            messageDialog.text = "Сервер и так уже отключен!";
                            return;
                        }

                        serverData.closeServer()
                    }
                }
            }

            RowLayout {
                spacing: 10
                Rectangle {
                    id:chatWindowRect
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    border.width: 1
                    Layout.minimumWidth: background.width / 5 * 3 - 20
                    Rectangle {
                        id:headerChat
                        anchors.left: parent.left
                        anchors.right: parent.right
                        height: 50
                        border.width: 1
                        color: "lightgreen"
                        Label {
                            x: 20
                            id: lblChatHeader
                            anchors.verticalCenter: parent.verticalCenter
                            text: "Chat Window:"
                            font.pixelSize: 18
                        }
                    }
                    Rectangle {
                        id:bodyChat
                        anchors.top: headerChat.bottom
                        anchors.left: parent.left
                        anchors.right: parent.right
                        anchors.bottom: parent.bottom
                        border.width: 1
                        ScrollView {
                            id:scroll
                            anchors.fill: parent
                            TextArea {
                                id: chatWindow
                                anchors.fill: parent
                                font.pixelSize: 18
                                readOnly: true
                            }
                        }
                    }
                }

                Rectangle {
                    id: clientsRect
                    Layout.fillHeight: true
                    Layout.fillWidth:  true
                    Layout.minimumWidth: background.width / 5 * 2 - 40
                    Rectangle {
                        id:clientsListHead
                        anchors.left: parent.left
                        anchors.right: parent.right
                        height: 50
                        border.width: 1
                        color: "lightpink"
                        Label {
                            x: 20
                            id: lblclientsHeader
                            anchors.verticalCenter: parent.verticalCenter
                            text: "Clients list:"
                            font.pixelSize: 18
                        }
                    }
                    Rectangle {
                        id:clientsListBody
                        anchors.top: clientsListHead.bottom
                        anchors.left: parent.left
                        anchors.right: parent.right
                        anchors.bottom: parent.bottom
                        border.width: 1

                        StylishButton {
                            id: disconnectClient
                            text: "Disconnect this client"
                            font.pixelSize: 18
                            anchors.left: parent.left
                            anchors.right: parent.right
                            anchors.bottom: parent.bottom
                            anchors.margins: 1
                            onClicked: {
                                if(clientsList.count == 0) return;
                                serverData.forcedClientDisconnect(clientsList.currentIndex);
                            }
                        }

                        ListView {
                            id: clientsList
                            anchors.top: parent.top
                            anchors.left: parent.left
                            anchors.right: parent.right
                            anchors.bottom: disconnectClient.top

                            Component {
                                id:clientsDelegate
                                Item {
                                    width: clientsListBody.width
                                    height: textName.height
                                    Column {
                                        Text {
                                            id: textName
                                            text: model.display
                                            font.pixelSize: 24
                                        }
                                    }

                                    MouseArea {
                                        anchors.fill: parent
                                        hoverEnabled: true
                                        onClicked: {
                                            clientsList.currentIndex = index
                                        }
                                    }
                                }
                            }

                            model: serverData.clientsListModel
                            delegate: clientsDelegate
                            focus: true
                            highlight: Rectangle { color: "lightsteelblue"; }
                        }
                    }
                }
            }

            RowLayout {
                spacing: 50

                StylishButton {
                    id:clearChat
                    text: "Clear Chat"
                    onClicked: {
                        chatWindow.text = "";
                    }
                }

                StylishButton {
                    id:chooseDirectory
                    text: "choose directory to save messages..."
                    onClicked: {
                        folderDialog.visible = true;
                    }
                }

                FolderDialog{
                    id: folderDialog
                    visible: false
                    modality: Qt.WindowModal
                    title: "Select file"
                    onAccepted: {
                        serverData.chooseFolderToSaveChat(currentFolder);
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
