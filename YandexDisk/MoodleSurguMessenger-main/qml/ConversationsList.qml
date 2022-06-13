import QtQuick 2.15
import QtQuick.Controls 2.15

Rectangle {
    id: parentRectangle
    width: 300
    height: 500

    anchors.fill: parent

    property string title: "Все диалоги"

    ListView {
        id: listView
        anchors.fill: parent

        model: conversationsModel
        delegate: ConversationItem {
            id: convItem
            anchors.right: parent.right
            anchors.left: parent.left
            anchors.leftMargin: 20
            anchors.rightMargin: 20

            height: parentRectangle.height / 6

            fullName: name
            msgText: lastMsgText
            profileImgPath: "images/logo.png"
            msgTime:lastMsgTime

            Button{
                anchors.fill: parent
                Material.background: "#00000000"
                Material.foreground: "#00000000"

                onClicked: {
                    appEngine.openConversation(convID);
                }
            }
        }

        //visible: false
    }
}

/*##^##
Designer {
    D{i:0;formeditorZoom:1.5}
}
##^##*/

