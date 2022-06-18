import QtQuick 2.15
import QtQuick.Controls 2.15

Rectangle {
    id: parentRectangle
    width: 300
    height: 500

    anchors.fill: parent

    property string title: "Название курса"

    ListView {
        id: listView
        anchors.fill: parent

        model: ListModel {
            ListElement {
                name: "605-51"
                text: "Анька, Дима, Айсель, Лев ..."
                path: "images/profilefoto.png"
            }

            ListElement {
                name: "605-71"
                text: "Ира, Даша, Наиль, Сеня ..."
                path: "images/profilefoto.png"
            }
            ListElement {
                name: "605-51"
                text: "Анька, Дима, Айсель, Лев ..."
                path: "images/profilefoto.png"
            }

            ListElement {
                name: "605-71"
                text: "Ира, Даша, Наиль, Сеня ..."
                path: "images/profilefoto.png"
            }
        }
        delegate: ConversationItem {
            id: convItem
            anchors.right: parent.right
            anchors.left: parent.left
            anchors.leftMargin: 20
            anchors.rightMargin: 20

            height: parentRectangle.height / 6

            fullName: name
            msgText: text
            profileImgPath: path
        }

        //visible: false
    }
}

/*##^##
Designer {
    D{i:0;formeditorZoom:1.5}
}
##^##*/

