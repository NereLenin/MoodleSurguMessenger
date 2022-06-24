import QtQuick 2.15
import QtQuick.Controls 2.15

Rectangle {
    id: parentRectangle
    width: 300
    height: 500

    anchors.fill: parent

    property string title: "Все диалоги"

    property bool searchOpenAnimation: false
    property bool searchCloseAnimation: false
    property bool isSearchOpen: searchBar.visible


    ListView {
        visible: true
        id: listView

        anchors.top: searchBar.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom

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
                    appEngine.searchConvs(searchText.text)
                }
                else
                {
                    appEngine.updateConvs()
                    listView.positionViewAtBeginning()
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
                    appEngine.searchConvs(searchText.text)
                }
                else
                {
                    appEngine.updateConvs()
                    listView.positionViewAtBeginning()
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
                searchText.forceActiveFocus();
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
}

/*##^##
Designer {
    D{i:0;formeditorZoom:1.5}
}
##^##*/

