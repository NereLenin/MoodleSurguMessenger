import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.12

Rectangle {
    id: parentRectangle
    width: 300
    height: 500

    anchors.fill: parent

    property string title: currentConversation.name

    ListView {
        id: listView
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.leftMargin: 20
        anchors.rightMargin: 20

        height: parent.height * 0.8

        model: messagesModel
        delegate: Message {
            //id: deligateMessage
            screenHeight: parentRectangle.height

            height: realSize + 10

            msgText: msgContent
            createTime: msgTime
            //profileImgPath: path

            isMyMessage: isMsgMine
        }

        //visible: false
        currentIndex: count - 1
    }

    Rectangle {
        id: textRectangle
        anchors.left: listView.left
        anchors.right: listView.right
        anchors.top: listView.bottom
        anchors.bottom: parent.bottom
        anchors.topMargin: 30
        anchors.bottomMargin: 0

        ScrollView {
            id: textScrollView
            anchors.fill: textRectangle
            anchors.rightMargin: textRectangle.width / 9

            ScrollBar.vertical.policy: (textArea.height > textRectangle.height) ? ScrollBar.AlwaysOn : ScrollBar.AlwaysOff
            TextArea {
                id: textArea
                placeholderText: qsTr("Введите сообщение...")

                anchors.fill: textRectangle
                anchors.margins: 10

                wrapMode: Text.WrapAnywhere
                selectByMouse: true
                font.pixelSize: parentRectangle.height / 35

                Material.accent: "#0070B9"
            }
        }

        Label {
            id: sendMsgLabel

            anchors.top: textRectangle.top
            anchors.bottom: textRectangle.bottom
            anchors.right: textRectangle.right
            anchors.left: textScrollView.right

            font.pixelSize: parentRectangle.height / 10

            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter

            Material.foreground: "#0070B9"

            //text: qsTr("\u276F")
            text: qsTr("\u00BB")

            Button{
                anchors.fill: parent
                Material.background: "#00000000"
                Material.foreground: "#00000000"

                onClicked: {
                    console.log(currentConversation.name)
                    console.log(currentConversation.convID)


                    if(textArea.text!=="")
                    {
                        appEngine.sendMessage(currentConversation.convID,textArea.text);
                        appEngine.openConversation(currentConversation.convID);
                    }
                }
            }
        }
    }

    Rectangle {
        id: line
        height: 2
        color: "#200070b9"
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: textRectangle.top
    }


    /*##^##
Designer {
    D{i:0;formeditorZoom:1.5}
}
##^##*/
}
