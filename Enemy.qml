import QtQuick

Rectangle
{
    id: enemy
    width: 50
    height: 50
    color: "Transparent"
    x: model.x
    y: model.y

    property var enemyPng : [
        "qrc:/enemy/enemy1.png",
        "qrc:/enemy/enemy2.png",
        "qrc:/enemy/enemy3.png",
        "qrc:/enemy/enemy4.png",
        "qrc:/enemy/enemy5.png"
    ]

    Image
    {
        anchors.fill: parent
        source: enemyPng[model._index]
    }
}