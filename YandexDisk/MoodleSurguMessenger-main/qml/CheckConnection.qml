import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Shapes 1.15

Rectangle {
    id: rectangle
    width: 300
    height: 500
    anchors.fill: parent

    property string title: "Соединение с Moodle"

    Shape {
        anchors.fill: image
        // multisample, decide based on your scene settings
        layer.enabled: true
        layer.samples: 4

        ShapePath {
            id: myShapePath
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
            property: "sweepAngle"
            duration: 5000
            to: 360
            running: true
            //easing.type: Easing.InOutQuad
            onFinished:
            {
                if(appEngine.isConnection())
                {
                    //startAuthorisation
                    console.log("All right internrut!");
                    appEngine.startAuthorisation();
                }
                else
                {
                     myShapePath.strokeColor = "#FF0000";
                    text1.color = "#FF0000";
                    text1.text = "Ошибка соединения с moodle";
                }

            }
        }
    }

    Image {
        id: image
        x: 44
        y: 119
        width: 230
        height: 230
        anchors.fill: parent
        source: "images//logo.png"
        anchors.rightMargin: 20
        anchors.leftMargin: 20
        anchors.bottomMargin: 80
        anchors.topMargin: 20
        fillMode: Image.PreserveAspectFit
    }

    Text {
        id: text1
        color: "#0063b9"
        text: qsTr("Установка соединения с сайтом")
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: image.bottom
        anchors.bottom: parent.bottom
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        font.weight: Font.Normal
        font.pointSize: 24
        minimumPointSize: 8
        minimumPixelSize: 8
        fontSizeMode: Text.Fit
        anchors.rightMargin: 20
        anchors.leftMargin: 20
        anchors.bottomMargin: 0
        anchors.topMargin: 0
    }
}

/*##^##
Designer {
    D{i:0;formeditorZoom:0.9}
}
##^##*/

