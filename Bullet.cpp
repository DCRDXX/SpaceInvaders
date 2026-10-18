#include "Controller.h"
#include "Bullet.h"

Bullet::Bullet(Controller* controller, QObject* parent): _x(1280/2-5), _y(720-80), _y_speed(-10)
{
    connect(&_timer, &QTimer::timeout, this, &Bullet::update_bullet);
    _timer.start(16);

    connect(this, &Bullet::bullet_destroyed, controller, &Controller::delete_bullet);
}

double Bullet::get_x()
{
    return _x;
}

double Bullet::get_y()
{
    return _y;
}

void Bullet::set_x(double value)
{
    if (_x != value)
    {
        _x = value;
        emit x_change();
    }
}

void Bullet::set_y(double value)
{
    if (_y != value)
    {
        _y = value;
        emit y_change();
    }
}

void Bullet::update_bullet()
{
    set_y(_y + _y_speed);
    if (_y < 0)
    {
        emit bullet_destroyed(this);
    }
}
