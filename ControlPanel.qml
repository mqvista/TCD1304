import QtQuick 2.0
import QtQuick.Controls 2.2
import QtQuick.Dialogs 1.2
import QtQuick.Layouts 1.3

Item {
    id: item1

    GridLayout {
        id: gridLayout
        anchors.leftMargin: 20
        anchors.topMargin: 10
        anchors.rightMargin: 20
        anchors.bottomMargin: 10
        columns: 5
        anchors.fill: parent

        Item {
            id: item1_1
            Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
            Layout.columnSpan: 1
            implicitWidth: 220
            implicitHeight: nameIntergral.height

            Text {
                id: nameIntergral
                text: qsTr("Intergral:")
                anchors.verticalCenter: parent.verticalCenter
                font.pointSize: 18
            }

            SpinBox {
                id: spinBoxIntergral
                width: 100
                anchors.left: nameIntergral.right
                anchors.leftMargin: 5
                anchors.verticalCenter: parent.verticalCenter
                wheelEnabled: true
                stepSize: 1
                font.pointSize: 16
                editable: true
                from: 1
                to: 100
                value: 1
                onValueChanged: {
                    ControlPanelModule.setIntergral(spinBoxIntergral.value)
                }
            }
        }


        Item {
            id: item1_2
            Layout.columnSpan: 1
            implicitWidth: 280
            implicitHeight: nameThreshold.height

            Text {
                id: nameThreshold
                text: qsTr("Threshold:")
                font.pointSize: 18
                anchors.verticalCenter: parent.verticalCenter

            }

            SpinBox {
                id: spinBoxThreshold
                width: 160
                wheelEnabled: true
                anchors.left: nameThreshold.right
                anchors.leftMargin: 5
                anchors.verticalCenter: parent.verticalCenter
                editable: true
                font.pointSize: 16
                from: 1000
                to: 70000
                value: 30000
                stepSize: 1000
                onValueChanged: {
                    ControlPanelModule.updateThresholdValue(spinBoxThreshold.value);
                }
            }

        }

        Button {
            id: buttonClose
            width: 120
            text: qsTr("Close")
            font.pointSize: 18
            focusPolicy: Qt.NoFocus
            opacity: 0.8
            onClicked: {
                ControlPanelModule.closeDevice()
                Qt.quit()
            }
        }

        Button {
            id: buttonOpen
            width: 120
            text: qsTr("Open")
            font.pointSize: 18
            focusPolicy: Qt.NoFocus
            opacity: 0.8
            onClicked: {
            }
        }

        Button {
            id: buttonSave
            width: 120
            text: qsTr("Save")
            font.pointSize: 18
            focusPolicy: Qt.NoFocus
            opacity: 0.8
            onClicked: {
                fileDialog.visible = true
            }
        }

        Item {
            id: item2_1
            Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
            Layout.columnSpan: 1
            implicitWidth: 220
            implicitHeight: nameCount.height

            Text {
                id: nameCount
                text: qsTr("Count:")
                anchors.verticalCenter: parent.verticalCenter
                font.pointSize: 18
            }

            Label {
                id: label
                text: ControlPanelModule.measureLength
                anchors.left: nameCount.right
                anchors.leftMargin: 5
                anchors.verticalCenter: parent.verticalCenter
                font.pointSize: 18
            }
        }

        Item {
            id: item2_2
            Layout.columnSpan: 1
            implicitWidth: 220
            implicitHeight: nameRealLength.height

            Text {
                id: nameRealLength
                text: qsTr("Real Length:")
                anchors.verticalCenter: parent.verticalCenter
                font.pointSize: 18
            }

            Label {
                id: labelRealLength
                text: ControlPanelModule.realLength
                anchors.left: nameRealLength.right
                anchors.leftMargin: 5
                anchors.verticalCenter: parent.verticalCenter
                font.pointSize: 18
            }
        }

        Item {
            id: item2_3
            Layout.columnSpan: 2
            implicitWidth: 220
            implicitHeight: namePolyPixels.height

            Text {
                id: namePolyPixels
                text: qsTr("Poly Pixels:")
                anchors.verticalCenter: parent.verticalCenter
                font.pointSize: 18
            }

            Label {
                id: labelPolyValue
                text: ControlPanelModule.polyValue
                anchors.left: namePolyPixels.right
                anchors.leftMargin: 5
                anchors.verticalCenter: parent.verticalCenter
                font.pointSize: 18
            }
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
