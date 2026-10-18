import QtQuick

Rectangle
{
    id: enemy
    width: 50
    height: 50
    color: "blue"
    x: model.x
    y: model.y
}