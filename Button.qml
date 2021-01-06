import QtQuick 2.15

Rectangle {
    id: root

    property alias icon: img.source

    signal pressed

    width :48
    height: 48
    color: "steelblue"
    border {width: 2; color: "grey"}
    state: "Released"

    Image {
        id: img
        anchors.centerIn: root
        width: 32
        height: 32
    }
    MouseArea {
        anchors.fill: parent
        onPressed: root.state = "Pressed"
        onReleased: {
            if (containsMouse)
                root.pressed()
            root.state = "Released"
        }
    }

    states: [
        State {
            name: "Released"
            PropertyChanges {
                target: root
                color: "steelblue"
            }
        },
        State {
            name: "Pressed"
            PropertyChanges {
                target: root
                color: "lightsteelblue"
            }
        }
    ]
    transitions: [
        Transition {
            from: "*"
            to: "*"
            ColorAnimation {duration: 100}
        }

    ]
}
