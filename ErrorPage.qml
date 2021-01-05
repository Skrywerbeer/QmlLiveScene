import QtQuick 2.0

Rectangle {
    id: root

    property alias message: errorMsg.text

    width: 400
    height: 300
    color: "black"

    Text {
        id: errorMsg

        anchors.fill: parent
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        wrapMode: Text.WordWrap
        color: "white"
    }
}
