import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Shapes 1.15
import QtQuick.Controls.Material 2.12

Rectangle {
    id: rectangle
    width: 300
    height: 500
    anchors.fill: parent

    property string title: "Авторизация"

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
        anchors.bottomMargin: 258
        anchors.topMargin: 20
        fillMode: Image.PreserveAspectFit
    }

    TextField {
        id: loginTextField
        x: 43
        y: 292
        width: 137
        height: (parent.height - (image.height + image.anchors.topMargin)) / 5
        anchors.left: image.left
        anchors.right: image.right
        anchors.bottom: passwordTextField.top
        anchors.bottomMargin: 5

        Material.accent: "#0070B9"
        //networkManager.SetLogin("vladislavyakubchick");
        //networkManager.SetPassword("RmTeERuL");
        text: "vladislavyakubchick"

        placeholderText: qsTr("Логин")
    }

    TextField {
        id: passwordTextField
        x: 43
        y: 348
        width: 137
        height: (parent.height - (image.height + image.anchors.topMargin)) / 5
        anchors.left: image.left
        anchors.right: image.right
        anchors.bottom: rememberMecheckBox.top
        anchors.bottomMargin: 5
        text: "RmTeERuL"
        Material.accent: "#0070B9"

        placeholderText: qsTr("Пароль")
    }

    CheckBox {
        id: rememberMecheckBox
        x: 15
        y: 392
        width: 151
        height: (parent.height - (image.height + image.anchors.topMargin)) / 5

        anchors.left: image.left
        anchors.right: image.right
        anchors.bottom: admitButton.top
        anchors.bottomMargin: 10
        Material.accent: "#0070B9"

        text: qsTr("Запомнить меня")
    }

    Button {
        id: admitButton
        x: 20
        y: 438
        height: (parent.height - (image.height + image.anchors.topMargin)) / 5
        anchors.left: image.left
        anchors.right: image.right
        anchors.bottom: parent.bottom
        font.capitalization: Font.MixedCase
        anchors.bottomMargin: 20
        Material.background: "#007CCD"
        Material.foreground: "#FFFFFF"
        text: qsTr("Войти")

        onClicked: {
            if(appEngine.authorisation(loginTextField.text, passwordTextField.text))
            {
                //startLoad
                appEngine.startLoadDialog();
                console.log("Аутоежжиризовался")
            }
            else{
                console.log("Косяк братишка, косяк")
            }
        }
    }
}
