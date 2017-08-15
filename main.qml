import QtQuick 2.6
import QtQuick.Window 2.2

Window {
    id: window
    visible: true
    width: 320
    height: 240
    title: qsTr("Hello World")

    Text {
        id: score
        height: parent.height / 10
        text: qsTr("Score: ") + game.score
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignHCenter
        anchors.top: parent.top
        anchors.right: parent.right
        anchors.left: parent.left
        font.pixelSize: height / 2
    }

    Game {
        anchors.top: score.bottom
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        anchors.left: parent.left
    }
}
