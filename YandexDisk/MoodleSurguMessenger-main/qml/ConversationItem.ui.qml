import QtQuick 2.15
import QtQuick.Controls 2.15

Item {
    id: root
    x: 0
    y: 0
    width: 400
    height: 150

    property string fullName: "Пользователь Фамилия Отчество"
    property string msgText: "Текст значица последнего сообщения в диалоге значица..."
    property string profileImgPath: "images/profilefoto.png"
    property string msgTime: "00-00-00"

    Image {
        id: imageprofile
        x: 0
        y: 0

        height: parent.height / 1.5
        width: height

        source: profileImgPath
        anchors.verticalCenterOffset: 0
        fillMode: Image.PreserveAspectFit

        anchors.verticalCenter: parent.verticalCenter
        anchors.left: parent.left
    }

    Text {
        id: textFullName
        height: imageprofile.height / 3
        text: qsTr(fullName)
        anchors.left: imageprofile.right
        anchors.right: parent.right
        anchors.top: imageprofile.top
        font.pixelSize: parent.height / 6

        minimumPointSize: 8
        minimumPixelSize: 8
        fontSizeMode: Text.FixedSize
        font.capitalization: Font.MixedCase
        anchors.topMargin: -(height / 3)
        anchors.rightMargin: 10
        anchors.leftMargin: 30
    }

    Text {
        id: textLastMessage
        height: imageprofile.height / 2
        color: "#808080"
        text: msgText
        anchors.left: imageprofile.right
        anchors.right: parent.right
        anchors.top: textFullName.bottom
        font.pixelSize: parent.height / 6
        verticalAlignment: Text.AlignVCenter
        lineHeight: 1
        wrapMode: Text.WordWrap

        minimumPointSize: 5
        minimumPixelSize: 6
        fontSizeMode: Text.FixedSize
        font.capitalization: Font.MixedCase
        anchors.topMargin: 10
        anchors.rightMargin: 10
        anchors.leftMargin: 30
    }

    Text {
        id: textTime
        height: imageprofile.height / 4.5
        text: msgTime
        anchors.right: root.right

        anchors.top: textLastMessage.bottom

        horizontalAlignment: Text.AlignRight

        font.pointSize: 24
        minimumPointSize: 8
        minimumPixelSize: 8
        fontSizeMode: Text.Fit
        font.capitalization: Font.MixedCase
        //anchors.rightMargin: 20
    }

    Rectangle {
        id: line
        height: 1
        color: "#200070b9"
        anchors.left: root.left
        anchors.right: root.right
        anchors.bottom: root.bottom
    }
}

/*##^##
Designer {
    D{i:0;formeditorZoom:1.25}
}
##^##*/

