import QtQuick
import QtQuick.Layouts
Window
{
    width: 1280
    height: 720
    visible: true
    title: qsTr("Hello World!")

    Rectangle
    {
        id: game_over_lay
        anchors.fill: parent
        color: "black"
        visible: false
        opacity: 0.8
        z:1

        ColumnLayout
        {
            spacing: 20
            anchors.centerIn: parent
            Text
            {
                id: game_over
                text: qsTr("Game Over")
                color: "white"
                anchors.horizontalCenter: parent.horizontalCenter
            }
            
            RowLayout
            {       
                spacing: 20
                Rectangle
                {
                    id: restart
                    color: "grey"
                    width: 300
                    height: 35
                    Text
                    {
                        text: qsTr("restart")
                        color: "white"
                        anchors.centerIn: parent
                     }

                     MouseArea
                     {
                        anchors.fill: parent
                        hoverEnabled: true
                        onEntered:
                        {
                            restart.color = "lightgrey"
                        }
                        onExited:
                        {
                            restrat.color = "gray"
                        }
                        onClicked:
                        {
                            control.restart_game();
                            game_over_lay.visible = false;
                            move.focus = true
                        }
                    }
                }

                Rectangle
                {
                    id: close
                    color: "grey"
                    width: 300
                    height: 35
                    Text
                    {
                        text: qsTr("close")
                        color: "white"
                        anchors.centerIn: parent
                    }
                    
                    MouseArea
                    {
                        anchors.fill: parent
                        hoverEnabled: true
                        onEntered:
                        {
                            close.color = "lightgrey"
                        }
                        onExited:
                        {
                            close.color = "gray"
                        }
                        onClicked:
                        {
                            Qt.quit()
                        }
                    }
                }            
            }
        }
    }

    Connections
    {
        target: control

        function onGameOver()
        {
            game_over_lay.visible = true
            move.focus = false
        }
    }

    Rectangle
    {
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
               control.apply_thrust()
            }
            if (event.key === Qt.Key_Space) {
               control.fire_bullet()
            }
        }

        Keys.onReleased: (event) => {
            if (event.key === Qt.Key_Left) {
               control.move_left_stop()
            }
            if (event.key === Qt.Key_Right) {
               control.move_right_stop()
            }
        }
    }

    Text
    {
        text: "score: " + control.score
        color: "black"
        x: 50
        y: 50
    }
      

    Repeater
    {
        model: control.bullets
        delegate: Bullet{}
    }

    Repeater
    {
        model: control.enemies
        delegate: Enemy{}
    }
}
