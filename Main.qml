import QtQuick
import androidnotifier

Window {
    width: 640
    height: 480
    visible: true
    title: qsTr("Hello World")

    TextInput {
        id: _textInput

        anchors.centerIn: parent
        width: parent.width * 0.5
        onVisibleChanged: if (visible) forceActiveFocus()
        onAccepted: NotificationClient.notification = text
    }

    Rectangle {
        id: _underline

        anchors {
            left: _textInput.left
            right: _textInput.right
            bottom: _textInput.bottom
        }
        height: 1
        color: 'black'
    }
}
