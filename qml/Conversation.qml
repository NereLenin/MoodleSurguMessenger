import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.12

Rectangle {
    id: parentRectangle
    width: 300
    height: 500

    anchors.fill: parent

    property string title: currentConversation.name

    property bool searchOpenAnimation: false
    property bool searchCloseAnimation: false
    property bool isSearchOpen: searchBar.visible

    ListView {
        id: listView
        anchors.top: searchBar.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.leftMargin: 20
        anchors.rightMargin: 20

        height: (parent.height-searchBar.height) * 0.8


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
        id: searchBar
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: parent.right

        height: 0
        visible: false
        //color: "#200070b9"

        Rectangle {
            id: searchline
            height: 2
            color: "#200070b9"
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.top: searchBar.bottom
            anchors.leftMargin: 5
            anchors.rightMargin: 5
        }

        Button{
            id: searchButton
            anchors.top: searchBar.top
            anchors.right: parent.right
            anchors.bottom: searchBar.bottom

            anchors.leftMargin: 2
            anchors.rightMargin: 10
            anchors.topMargin: 5
            anchors.bottomMargin: 5
            width: 50

            Material.background: "#00000000"
            Material.foreground: "#00000000"

                Rectangle{
                    id: searchButtonBackgound
                    anchors.fill: parent
                    color: "#8d0070b9"
                    anchors.topMargin: 5
                    anchors.bottomMargin: 5
                    radius:3
                        Image {
                            id: searchButtonIcon
                            anchors.fill: parent
                            source: "qrc:/qml/images/search.png"
                            fillMode: Image.PreserveAspectFit
                        }

                }

            onClicked:
            {
                if(searchText.text !== "")
                {
                    appEngine.searchMessage(currentConversation.convID, searchText.text)
                }
                else
                {
                    appEngine.updateConv(currentConversation.convID)
                    listView.positionViewAtEnd()
                }
            }

        }

        TextField
        {

            id: searchText
            anchors.top: parent.top
            anchors.left: parent.left
            anchors.bottom: parent.bottom

            anchors.right: searchButton.left
            anchors.leftMargin: 10
            anchors.rightMargin: 10

            font.pixelSize: parentRectangle.height / 35
            selectByMouse: true
            placeholderText: "Текст поиска..."
            Material.accent: "#0070B9"

            onTextChanged:
            {
                if(searchText.text !== "")
                {
                    appEngine.searchMessage(currentConversation.convID, searchText.text)
                }
                else
                {
                    appEngine.updateConv(currentConversation.convID)
                    listView.positionViewAtEnd()
                }

            }
        }

        NumberAnimation {
            id: openSearchBarAnimation
            target: searchBar
            property: "height"
            duration: 300
            from: 0
            to: parent.height/12
            running: searchOpenAnimation
            onStarted:
            {
                searchBar.visible = true;

            }
            onFinished:
            {
                searchBar.height = parent.height/12
                searchOpenAnimation = false
                searchText.forceActiveFocus()
            }
        }
        NumberAnimation {
            id: closeSearchBarAnimation
            target: searchBar
            property: "height"
            duration: 300
            to: 0
            running: searchCloseAnimation
            onStarted:
            {
                searchText.text = "";
                searchText.focus = false;
            }
            onFinished:
            {
                searchCloseAnimation = false
                searchBar.visible=false
            }
        }
    }
    //end searchBar

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
                    //console.log(currentConversation.name)
                    //console.log(currentConversation.convID)


                    if(textArea.text!=="")
                    {
                        appEngine.sendMessage(currentConversation.convID,textArea.text);
                        appEngine.openConversation(currentConversation.convID);
                        listView.currentIndex = listView.count -1;
                    }
                }
            }
        }


        /*
        NumberAnimation {
            id: openSendBarAnimation
            target: textRectangle
            property: "height"
            duration: 300
            to: parentRectangle.height - (listView.y+listView.height)
            running: false
            onStarted:
            {
                textRectangle.visible = true;
            }
            onFinished:
            {
                textRectangle.anchors.top = listView.bottom
                //searchBar.height = parent.height/12
                //searchOpenAnimation = false
            }
        }
        NumberAnimation {
            id: closeSendBarAnimation
            target: textRectangle
            property: "height"
            duration: 300
            to: 0
            running: false
            onFinished:
            {
                textRectangle.visible=false

                listView.anchors.bottom = textRectangle.top
            }
        }


    */
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
