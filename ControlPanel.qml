import QtQuick 2.0
import QtQuick.Controls 2.2
import QtQuick.Dialogs 1.2

Item {
    id: item1
    width: 1050
    height: 100

    Text {
        id: name0
        text: qsTr("Intergral:")
        font.pointSize: 30
        anchors.horizontalCenterOffset: -230
        anchors.verticalCenter: parent.verticalCenter
        anchors.verticalCenterOffset: -20
        anchors.horizontalCenter: parent.horizontalCenter
    }

    SpinBox {
        id: spinBox0
        width: 120
        editable: true
        anchors.left: name0.right
        anchors.leftMargin: 5
        anchors.verticalCenter: name0.verticalCenter
        from: 1
        to: 100
        value: 1
        onValueChanged: {
            ControlPanelModule.setIntergral(spinBox0.value)
        }
    }


    Text {
        id: name
        text: qsTr("Threshold:")
        anchors.verticalCenterOffset: -20
        font.pointSize: 30
        anchors.horizontalCenterOffset: 100
        anchors.verticalCenter: parent.verticalCenter
        anchors.horizontalCenter: parent.horizontalCenter
    }

    SpinBox {
        id: spinBox
        editable: true
        anchors.left: name.right
        anchors.leftMargin: 5
        anchors.verticalCenter: name.verticalCenter
        from: 1000
        to: 70000
        value: 25000
        onValueChanged: {
            ControlPanelModule.updateThresholdValue(spinBox.value);
        }
    }

    Text {
        id: name1
        text: qsTr("Count:")
        anchors.verticalCenterOffset: 35
        font.pointSize: 30
        anchors.horizontalCenterOffset: -245
        anchors.verticalCenter: parent.verticalCenter
        anchors.horizontalCenter: parent.horizontalCenter
    }

    Label {
        id: label
        text: ControlPanelModule.measureLength
        anchors.verticalCenter: parent.verticalCenter
        anchors.verticalCenterOffset: 35
        anchors.left: name1.right
        anchors.leftMargin: 5
        font.pointSize: 30
    }

    Text {
        id: name2
        text: qsTr("Pixels")
        font.pointSize: 30
        anchors.horizontalCenterOffset: 72
        anchors.verticalCenter: parent.verticalCenter
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenterOffset: 35
    }

    Text {
        id: name3
        text: qsTr("*")
        font.pointSize: 30
        anchors.leftMargin: 10
        anchors.verticalCenter: parent.verticalCenter
        anchors.verticalCenterOffset: 35
        anchors.left: name2.right
    }

    TextField {
        id: textField
        width: 100
        height: 40
        text: qsTr("1")
        font.pointSize: 25
        font.family: "Tahoma"
        anchors.left: name3.right
        anchors.leftMargin: 10
        anchors.verticalCenter: parent.verticalCenter
        anchors.verticalCenterOffset: 35
    }

    Text {
        id: name4
        text: qsTr("=")
        font.pointSize: 30
        anchors.leftMargin: 10
        anchors.verticalCenter: parent.verticalCenter
        anchors.verticalCenterOffset: 35
        anchors.left: textField.right
    }

    Label {
        id: label2
        text: ControlPanelModule.realLength
        anchors.verticalCenter: parent.verticalCenter
        anchors.verticalCenterOffset: 35
        anchors.left: name4.left
        anchors.leftMargin: 20
        font.pointSize: 30
    }

    Button {
        id: button
        width: 150
        text: qsTr("Close")
        font.pointSize: 30
        focusPolicy: Qt.NoFocus
        opacity: 0.8
        anchors.left: parent.left
        anchors.leftMargin: 50
        anchors.verticalCenter: parent.verticalCenter
        anchors.verticalCenterOffset: 35
        onClicked: {
            ControlPanelModule.closeDevice()
            Qt.quit()
        }
    }

    Button {
        id: saveButton
        width: 150
        text: qsTr("save RAW")
        anchors.verticalCenterOffset: -20
        font.pointSize: 30
        focusPolicy: Qt.NoFocus
        opacity: 0.8
        anchors.left: parent.left
        anchors.leftMargin: 50
        anchors.verticalCenter: parent.verticalCenter
        onClicked: {
            fileDialog.visible = true

        }
    }

    FileDialog {
        id: fileDialog
        title: "Please choose to save"
        folder: shortcuts.home
        selectExisting: false
        onAccepted:
        {
            ControlPanelModule.saveData(fileDialog.fileUrls)
            //console.log("You chose: " + fileDialog.fileUrl)
        }
        onRejected:
        {
            console.log("Canceled")
        }
    }
}
