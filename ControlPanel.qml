import QtQuick 2.0
import QtQuick.Controls 2.2
import QtQuick.Dialogs 1.2

Item {
    id: item1
    width: 1050
    height: 150

    Text {
        id: name0
        text: qsTr("Intergral:")
        font.pointSize: 30
        anchors.horizontalCenterOffset: -231
        anchors.verticalCenter: parent.verticalCenter
        anchors.verticalCenterOffset: -33
        anchors.horizontalCenter: parent.horizontalCenter
    }

    SpinBox {
        id: spinBox0
        width: 120
        font.pointSize: 18
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
        anchors.verticalCenterOffset: -33
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
        font.pointSize: 18
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
        anchors.verticalCenterOffset: 20
        font.pointSize: 30
        anchors.horizontalCenterOffset: -245
        anchors.verticalCenter: parent.verticalCenter
        anchors.horizontalCenter: parent.horizontalCenter
    }

    Label {
        id: label
        text: ControlPanelModule.measureLength
        anchors.verticalCenter: name1.verticalCenter
        anchors.left: name1.right
        anchors.leftMargin: 5
        font.pointSize: 30
    }

    Text {
        id: name2
        text: qsTr("Real Length:")
        font.pointSize: 30
        anchors.horizontalCenterOffset: 72
        anchors.verticalCenter: parent.verticalCenter
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenterOffset: 20
    }

    Label {
        id: label2
        text: ControlPanelModule.realLength
        anchors.verticalCenter: name2.verticalCenter
        anchors.left: name2.right
        anchors.leftMargin: 20
        font.pointSize: 30
    }

    Text {
        id: name5
        text: qsTr("Poly Pixels:")
        font.pointSize: 30
        anchors.left: name2.left
        anchors.verticalCenter: parent.verticalCenter
        //anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenterOffset: 60
    }

    Label {
        id: label3
        text: ControlPanelModule.polyValue
        anchors.verticalCenter: name5.verticalCenter
        anchors.left: name5.right
        anchors.leftMargin: 20
        font.pointSize: 30
    }



    Button {
        id: button
        width: 150
        text: qsTr("Close")
        anchors.left: saveButton.left
        font.pointSize: 30
        focusPolicy: Qt.NoFocus
        opacity: 0.8
        anchors.verticalCenter: name1.verticalCenter
        onClicked: {
            ControlPanelModule.closeDevice()
            Qt.quit()
        }
    }

    Button {
        id: saveButton
        width: 150
        text: qsTr("save RAW")
        anchors.right: name0.left
        anchors.rightMargin: 37
        font.pointSize: 30
        focusPolicy: Qt.NoFocus
        opacity: 0.8
        anchors.verticalCenter: name0.verticalCenter
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
