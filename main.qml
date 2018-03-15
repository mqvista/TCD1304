import QtQuick 2.10
import QtQuick.Window 2.10
//import QtQuick.Controls 2.3

Window {
    id: window
    visible: true
    width: 1024
    height: 768
    title: qsTr("Hello World")

    ScopeView {
        id: scopeView
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        anchors.right: parent.right
        anchors.left: parent.left
        height: window.height
    }
}
