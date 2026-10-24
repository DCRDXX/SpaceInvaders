#include "Enemy.h"

Enemy::Enemy(QObject* parent): _x(rand() % 1270), _y(0), _y_speed(1)
{
    _index = rand() % 5;
    connect(&_timer, &QTimer::timeout, this, &Enemy::update_enemy);
    _timer.start(50);
}

double Enemy::get_x()
{
    return _x;
}

double Enemy::get_y()
{
    return _y;
}

void Enemy::set_x(double value)
{
    if (_x != value)
    {
        _x = value;
        emit x_change();
    }
}

void Enemy::set_y(double value)
{
    if (_y != value)
    {
        _y = value;
        emit y_change();
    }
}

int Enemy::get_index()
{
    return _index;
}

void Enemy::set_index(int value)
{
    if (_index != value)
    {
        _index = value;
        emit index_change();
    }    
}

void Enemy::update_enemy()
{
    set_y(_y + _y_speed);
}
