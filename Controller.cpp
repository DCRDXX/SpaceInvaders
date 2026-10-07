#include "Controller.h"

Controller::Controller(QObject* parent): _x(1280/2-25), _y(720-70), _speed(10), _min_x(0), _max_x(1280), _min_y(0), _max_y(720) {}

