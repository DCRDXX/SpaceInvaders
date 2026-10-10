#include "Controller.h"

Controller::Controller(QObject* parent): _x(1280/2-25), _y(720-70), _x_speed(10), _x_min(0), _x_max(1280), _y_min(0), _y_max(670), _gravity(0.5), _thrust(-15)
{
    connect(&_timer, &QTimer::timeout, this, &Controller::update_state);
    _timer.start(16);
}


