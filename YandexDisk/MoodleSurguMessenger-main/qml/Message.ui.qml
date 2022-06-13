import QtQuick 2.15
import QtQuick.Controls 2.15


/*
  Поскольку заранее мы не знаем сколько места нужно выделить для сообщения
  в ListView мы расчитываем его исходя из размера экрана.
  Сначала передаем в этот модуль размер экрана - screenHeight
  Затем по нему расчитываем шрифт, расчитываем размер текста и элементов и тд.
  Возвращаем найденное значение через realSize
  Выделяем место
  */
Item {
    id: root
    width: 400
    height: 150

    anchors.left: parent.left
    anchors.right: parent.right

    property string msgText: "Какой то текст сообщения..."
    property string profileImgPath: "images/profilefoto.png"
    property string createTime: "25.07.1997 11:22"
    property bool isMyMessage: false

    property real screenHeight: parent.height

    //необходимый размер равен - высоте до аватарки + высоте рамки вокруг текста+ высоте текста времени создания
    property real realSize: 10 + lastMessageBorder.height + textTime.height

    Image {
        id: imageprofile
        x: 0
        y: 10 //отодвигаем сверху от последнего сообщения на 10

        //аватарки будут занимать 1/10 экрана
        height: screenHeight / 10
        width: height

        source: profileImgPath
        anchors.verticalCenterOffset: 0
        fillMode: Image.PreserveAspectFit

        anchors.left: parent.left
        visible: !isMyMessage
    }

    Rectangle {
        id: lastMessageBorder

        anchors.fill: textLastMessage
        anchors.leftMargin: -20
        anchors.rightMargin: -10
        anchors.topMargin: -10
        anchors.bottomMargin: -10

        //для своих и чужих сообщений разные цвета
        color: isMyMessage ? "#cc0070b9" : "#800070b9"
        radius: 6
    }

    Text {
        id: textLastMessage
        color: "#ffffff"
        text: qsTr(msgText)

        anchors.left: imageprofile.right
        anchors.right: root.right
        anchors.top: imageprofile.top

        font.pixelSize: screenHeight / 35
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignLeft

        lineHeightMode: Text.ProportionalHeight
        wrapMode: Text.WordWrap
        maximumLineCount: 10000

        minimumPointSize: 5
        minimumPixelSize: 6

        fontSizeMode: Text.FixedSize
        font.capitalization: Font.MixedCase

        anchors.rightMargin: 20
        anchors.leftMargin: 30
        anchors.topMargin: 10
        anchors.bottomMargin: 10

        //устанавливаем высоту текста по его содержимому
        height: contentHeight
    }

    Text {
        id: textTime

        //Размер шрифта внутри подбирается под размер текста, при таком пармаетре норм
        height: imageprofile.height / 4
        text: qsTr(createTime)

        anchors.top: lastMessageBorder.bottom
        anchors.right: lastMessageBorder.right
        anchors.left: lastMessageBorder.left

        anchors.topMargin: 5
        anchors.leftMargin: 5
        anchors.rightMargin: 5

        horizontalAlignment: isMyMessage ? Text.AlignRight : Text.AlignLeft

        font.pointSize: 24
        minimumPointSize: 8
        fontSizeMode: Text.Fit
    }
}

/*##^##
Designer {
    D{i:0;formeditorZoom:2}
}
##^##*/

