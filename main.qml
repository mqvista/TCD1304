import QtQuick 2.10
import QtQuick.Window 2.10
import QtQuick.Controls 2.3

Window {
    id: window
    visible: true
    width: 1024
    height: 768
    title: qsTr("TCD1304 Tester")

    ControlPanel {
        id: controlPanel
        anchors.top: parent.top
        anchors.bottom: scopeView.top
        anchors.right: parent.right
        anchors.left: parent.left
        height: window.height * 0.2
    }

    ScopeView {
        id: scopeView
        anchors.top: controlPanel.bottom
        anchors.bottom: parent.bottom
        anchors.right: parent.right
        anchors.left: parent.left
    }
}
