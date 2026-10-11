#include "Controller.h"

Controller::Controller(QObject* parent): _x(1280/2-25), _y(720-70), _x_speed(10), _x_min(0), _x_max(1280), _y_min(0), _y_max(670), _gravity(0.5), _thrust(-15)
{
    connect(&_timer, &QTimer::timeout, this, &Controller::update_state);
    _timer.start(16);
}

double Controller::get_x()
{
    return _x;
}

double Controller::get_y()
{
    return _y;
}

void Controller::set_x(double value)
{
    if (_x != value)
    {
        _x = value;
        emit x_change();
    }
}

void Controller::set_y(double value)
{
    if (_y != value)
    {
        _y = value;
        emit y_change();
    }
}

void Controller::move_left()
{
    if (_x - _x_speed <= _x_min)
    {
        set_x(_x_min);
    }
    else
    {
        set_x(_x - _x_speed);
    }
}

void Controller::move_right()
{
    if (_x +  _x_speed >= _x_max - 50)
    {
        set_x(_x_max - 50);
    }
    else
    {
        set_x(_x + _x_speed);
    }
}

void Controller::apply_thrust()
{
    _y_speed = _thrust;
    if (_y < _y_max/1.5)
    {
        _y_speed = 0;
    }
}

void Controller::update_state()
{
    _y += _y_speed;
    _y_speed += _gravity;
    if (_y > _y_max)
    {
        _y = _y_max;
    }

    emit y_change();
}

QQmlListProperty<Bullet> Controller::get_bullets()
{
    return QQmlListProperty<Bullet>(this, &_bullet_list);
}
    
void Controller::fire_bullet()
{
    Bullet* new_bullet = new Bullet();
    new_bullet->set_x(_x);
    new_bullet->set_y(_y);
    _bullet_list.append(new_bullet);
    emit bullet_change();
}
