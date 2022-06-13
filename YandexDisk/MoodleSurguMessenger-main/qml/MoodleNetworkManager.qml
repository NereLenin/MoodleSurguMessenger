import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.12
import QtQuick.Window 2.15

Window {
    width: 340
    height: 400
    visible: true
    title:"MoodleMessenger"

    Item {

    id: mainItem
    anchors.fill: parent
    width: 340
    height: 400



    StackView {
        id: stackView
        objectName: "mainStack"
        x: 0
        width: 340
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: toolBar.bottom
        anchors.bottom: parent.bottom
        anchors.topMargin: 1
        initialItem: "CheckConnection.qml"

        function pushPage(pageUrl: string){
                push(pageUrl);
            }
        function popPage(){
                pop();
            }
        function clear(){
                clear();
            }

    }

    ToolBar {
        id: toolBar
        y: 0
        height: parent.height/12
        anchors.left: parent.left
        anchors.right: parent.right
        Material.background: "#0070B9"


        ToolButton {
            id: drawerToolButton
            width: 48
            text: qsTr("\u2630")
            anchors.left: parent.left
            anchors.top: parent.top
            anchors.bottom: parent.bottom

            onClicked:{
                drawer.position ? drawer.close() : drawer.open()
            }


        }


        ToolButton {
            id: toolButton
            x: 54
            y: 0
            width: 51
            height: 40
            text: qsTr("")
            anchors.left: drawerToolButton.right
            anchors.top: parent.top
            anchors.bottom: parent.bottom

            Image {
                        anchors.fill: parent
                        source: "qrc:/qml/images/bell.png"
                        anchors.margins: 8
                        fillMode: Image.PreserveAspectFit
                    }
            }

        Text {
            id: titleText
            color: "#ffffff"
            text: qsTr(stackView.currentItem.title)
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            font.pointSize: 22
            style: Text.Normal

            minimumPointSize: 2

            fontSizeMode: Text.Fit
            anchors.left: toolButton.right
            anchors.right: toolButton1.left
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            anchors.leftMargin: 10
            anchors.rightMargin: 10
        }

        ToolButton {
            id: toolButton1
            width: 51
            height: 40
            text: qsTr("")
            anchors.right: parent.right
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 0
            anchors.topMargin: 0

            Image {
                        anchors.fill: parent
                        source: "qrc:/qml/images/search.png"
                        anchors.margins: 8
                        fillMode: Image.PreserveAspectFit
                    }
            }
}


    Drawer {
        id: drawer
        y: toolBar.height
        width: parent.width * 0.33
        height: parent.height
        //visible: (stackView.currentItem.title === "Соединение с Moodle")||(stackView.currentItem.title === "Авторизация с Moodle")||(stackView.currentItem.title === "Загрузка данных")

        Column {
            anchors.fill: parent

            ItemDelegate {
                text: qsTr("Диалоги")
                width: parent.width
                onClicked: {
                    //stackView.clear()
                    //stackView.push("ConversationsList.qml")
                    appEngine.openConversations();
                    drawer.close()

                }
            }

            /*
            ItemDelegate {
                text: qsTr("По курсам")
                width: parent.width
                onClicked: {
                    //stackView.clear()
                    stackView.push("CourseList.ui.qml")
                    drawer.close()
            }}

           ItemDelegate {
                text: qsTr("Диалог")
                width: parent.width
                onClicked: {
                    //stackView.clear()
                     stackView.push("Conversation.ui.qml")
                     drawer.close()
            }
           }

                ItemDelegate {
                     text: qsTr("Авторизация")
                     width: parent.width
                     onClicked: {
                         //stackView.clear()
                          stackView.push("Authorization.ui.qml")
                          drawer.close()
                 }
                 }
                     ItemDelegate {
                          text: qsTr("Проверить подключение")
                          width: parent.width
                          onClicked: {
                              //stackView.clear()
                               stackView.push("CheckConnection.ui.qml")
                               drawer.close()
                      }}
                          ItemDelegate {
                               text: qsTr("Загрузить Диалоги")
                               width: parent.width
                               onClicked: {
                                   //stackView.clear()
                                    stackView.push("DialogLoad.ui.qml")
                                    drawer.close()
                           }}
                               ItemDelegate {
                                    text: qsTr("По курсам")
                                    width: parent.width
                                    onClicked: {
                                        //stackView.clear()
                                         stackView.push("CourseList.ui.qml")
                                         drawer.close()
                                }
            }
            */
        }

    }
}

}

/*##^##
Designer {
    D{i:0;formeditorZoom:0.9}
}
##^##*/
