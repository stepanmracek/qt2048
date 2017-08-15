import QtQuick 2.0

Item {
    id: field
    focus: true

    Keys.onLeftPressed: {
        game.playerMove(0);
        game.computerMove();
    }

    Keys.onRightPressed: {
        game.playerMove(1);
        game.computerMove();
    }

    Keys.onUpPressed: {
        game.playerMove(2);
        game.computerMove();
    }

    Keys.onDownPressed: {
        game.playerMove(3);
        game.computerMove();
    }

    Rectangle {
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter

        width: parent.width > parent.height ? parent.height : parent.width
        height: width

        GridView {
            id: gridView
            boundsBehavior: Flickable.StopAtBounds
            anchors.fill: parent
            anchors.margins: 10

            cellWidth: gridView.width / game.size()
            cellHeight: gridView.height / game.size()

            delegate: Item {
                width: gridView.cellWidth
                height: gridView.cellHeight

                Rectangle {
                    anchors.fill: parent
                    anchors.margins: 2
                    color: value > 0 ? "#80ff0000" : "#40000000"
                    radius: 10

                    Text {
                        anchors.horizontalCenter: parent.horizontalCenter
                        anchors.verticalCenter: parent.verticalCenter
                        text: value > 0 ? value : ""
                        horizontalAlignment: Text.AlignHCenter
                        verticalAlignment: Text.AlignVCenter
                        font.pixelSize: parent.height / 2
                    }
                }
            }
            model: game
        }


    }

}
