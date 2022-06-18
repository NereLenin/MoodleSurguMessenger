import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Shapes 1.15
import QtQuick.Controls.Material 2.12

Rectangle {
    id: rectangle
    width: 300
    height: 500
    anchors.fill: parent

    property string title: "Загрузка данных"

    Shape {
        anchors.fill: image

        layer.enabled: true
        layer.samples: 4

        ShapePath {
            strokeColor: "#0063b9"
            strokeWidth: 5

            capStyle: ShapePath.FlatCap
            PathAngleArc {
                id: loadCirclePathAngle
                centerX: image.width / 2
                centerY: image.height / 2

                radiusX: image.width < image.height ? image.width / 2.1 : image.height / 2.1
                radiusY: radiusX

                startAngle: 90
                sweepAngle: 30
            }
        }

        NumberAnimation {

            target: loadCirclePathAngle
            id: circleAnimation
            property: "sweepAngle"
            duration: 5000
            to: 360
            running: true

            onFinished:
            {
                appEngine.openConversations();
            }
        }
    }

    Image {

        id: image1
        x: (image.x + (image.width / 2)) - width / 2
        y: (image.y + (image.height / 2)) - height / 2

        width: (image.width < image.height ? image.width / 2.2 : image.height / 2.2) * 2
        height: width

        source: "images//profilefoto.png"
        fillMode: Image.PreserveAspectFit
        visible: !circleAnimation.running
    }

    Image {
        id: image
        x: 44
        y: 119
        width: 230
        height: 230
        anchors.fill: parent
        source: circleAnimation.running ? "images//logo.png" : "images//emptylogo.png"
        anchors.rightMargin: 40
        anchors.leftMargin: 40
        anchors.bottomMargin: 180
        anchors.topMargin: 40
        fillMode: Image.PreserveAspectFit
    }

    Text {
        id: text1
        height: 67
        color: "#0063b9"
        text: qsTr("Добро пожаловать,\n ") + appEngine.myFullName
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: image.bottom

        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        maximumLineCount: 3
        font.weight: Font.Normal
        font.pointSize: 24
        minimumPointSize: 8
        minimumPixelSize: 8
        fontSizeMode: Text.Fit
        anchors.rightMargin: 40
        anchors.leftMargin: 40
        anchors.bottomMargin: 0
        anchors.topMargin: 10
    }

    Text {
        id: text2
        height: 54
        color: "#808080"
        width: text1.width * 0.5

        text: qsTr("Загрузка данных")

        anchors.top: text1.bottom
        anchors.horizontalCenter: text1.horizontalCenter

        font.pointSize: 18
        anchors.topMargin: 10
        minimumPixelSize: 8
        minimumPointSize: 8

        fontSizeMode: Text.Fit
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        maximumLineCount: 3
    }

    BusyIndicator {
        id: busyIndicator
        x: 233
        y: 396
        Material.accent: "#0063b9"
        anchors.left: text2.right
        anchors.verticalCenter: text2.verticalCenter
        height: text2.height * 0.7
        width: height
    }
}

/*##^##
Designer {
    D{i:0;formeditorZoom:0.9}
}
##^##*/

