import QtQuick

Rectangle
{
    id: bullet
    width: 10
    height: 30
    color: "Transparent"
    x: model.x
    y: model.y

    Image
    {
        anchors.fill: parent
        source: "qrc:/player/bullet.png"
    }
}