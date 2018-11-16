import QtQuick 2.0
import QtQuick.Controls 2.2
import QtQuick.Dialogs 1.2
import QtQuick.Layouts 1.3

Item {
    id: item1

    GridLayout {
        id: gridLayout
        anchors.leftMargin: 20
        anchors.topMargin: 20
        anchors.rightMargin: 20
        anchors.bottomMargin: 20
        rows: 2
        columns: 6
        anchors.fill: parent

        Text {
            id: nameIntergral
            text: qsTr("Intergral:")
            font.pointSize: 30
            Layout.row: 1
            Layout.column: 1
        }

        SpinBox {
            id: spinBoxIntergral
            width: 120
            stepSize: 1
            font.pointSize: 18
            editable: true
            Layout.row: 1
            Layout.column: 2
            from: 1
            to: 100
            value: 1
            onValueChanged: {
                ControlPanelModule.setIntergral(spinBoxIntergral.value)
            }
        }

        Text {
            id: nameThreshold
            text: qsTr("Threshold:")
            font.pointSize: 30
            Layout.row: 1
            Layout.column: 3
        }

        SpinBox {
            id: spinBoxThreshold
            editable: true
            font.pointSize: 18
            Layout.row: 1
            Layout.column: 4
            from: 1000
            to: 70000
            value: 30000
            stepSize: 1000
            onValueChanged: {
                ControlPanelModule.updateThresholdValue(spinBoxThreshold.value);
            }
        }

            Button {
                id: buttonClose
                width: 150
                text: qsTr("Close")
                font.pointSize: 30
                focusPolicy: Qt.NoFocus
                opacity: 0.8
                Layout.row: 1
                Layout.column: 5
                onClicked: {
                    ControlPanelModule.closeDevice()
                    Qt.quit()
                }
            }

            Button {
                id: buttonSave
                width: 150
                text: qsTr("save RAW")
                font.pointSize: 30
                focusPolicy: Qt.NoFocus
                opacity: 0.8
                Layout.row: 1
                Layout.column: 6
                onClicked: {
                    fileDialog.visible = true

                }
            }

        Text {
            id: nameCount
            text: qsTr("Count:")
            font.pointSize: 30
            Layout.row: 2
            Layout.column: 1
        }

        Label {
            id: label
            text: ControlPanelModule.measureLength
            Layout.row: 2
            Layout.column: 2
            //anchors.left: nameCount.right
            //anchors.leftMargin: 5
            font.pointSize: 30
        }

        Text {
            id: nameRealLength
            text: qsTr("Real Length:")
            font.pointSize: 30
            Layout.row: 2
            Layout.column: 3
        }

        Label {
            id: labelRealLength
            text: ControlPanelModule.realLength
            Layout.row: 2
            Layout.column: 4
            //anchors.left: nameRealLength.right
            //anchors.leftMargin: 5
            font.pointSize: 30
        }

        Text {
            id: namePolyPixels
            text: qsTr("Poly Pixels:")
            font.pointSize: 30
            Layout.row: 2
            Layout.column: 5
        }

        Label {
            id: labelPolyValue
            text: ControlPanelModule.polyValue
            Layout.row: 2
            Layout.column: 6
            //anchors.left: namePolyPixels.right
            //anchors.leftMargin: 5
            font.pointSize: 30
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

/*##^## Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
 ##^##*/
