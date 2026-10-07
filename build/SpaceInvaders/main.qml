import QtQuick

Window {
    width: 1280
    height: 720
    visible: true
    title: qsTr("Hello World!")

    Rectangle {
        id: move
        width: 50
        height: 50
        color: "red"
        x: control.x
        y: control.y
        focus: true

        Keys.onPressed: (event) => {
            if (event.key === Qt.Key_Left) {
               control.move_left()
            }
            if (event.key === Qt.Key_Right) {
               control.move_right()
            }
            if (event.key === Qt.Key_Up) {
               move.y -= 10
            }
            if (event.key === Qt.Key_Down) {
               move.y += 10
            }

        }
        
    }
}
