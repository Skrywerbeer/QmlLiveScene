import QtQuick 2.15

Rectangle {
    id: root

    signal close
    signal reload

    width: childrenRect.width
    height: childrenRect.height
    color: "lightgrey"

    Column {
        Button {
            id: closeBtn
            icon: "qrc:/icons/close.svg"
            onPressed: root.close()
        }
        Button {
            id: reloadBtn
            icon: "qrc:/icons/reload.svg"
            onPressed: root.reload()
        }
    }
}
