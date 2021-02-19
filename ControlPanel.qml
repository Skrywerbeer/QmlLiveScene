import QtQuick 2.15

Rectangle {
    id: root

    signal close
    signal move
    signal reload

    width: childrenRect.width
    height: childrenRect.height
    color: "lightgrey"

    Column {
        Button {
            id: closeBtn
            icon: "qrc:/icons/close.png"
            onPressed: root.close()
        }
        Button {
            id: moveBtn
            icon: "qrc:/icons/move.png"
            onPressed: root.move()
        }

        Button {
            id: reloadBtn
            icon: "qrc:/icons/reload.png"
            onPressed: root.reload()
        }
    }
}
