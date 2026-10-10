#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>
#include <QTimer>

class Controller: public QObject
{
    Q_OBJECT
    Q_PROPERTY(double x READ get_x WRITE set_x NOTIFY x_change)
    Q_PROPERTY(double y READ get_y WRITE set_y NOTIFY y_change)

public:
    Controller(QObject* parent = nullptr);

    double get_x()
    {
        return _x;
    }

    double get_y()
    {
        return _y;
    }

    void set_x(double value)
    {
        if (_x != value)
        {
            _x = value;
            emit x_change();
        }
    }

    void set_y(double value)
    {
        if (_y != value)
        {
            _y = value;
            emit y_change();
        }
    }

    Q_INVOKABLE void move_left()
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
    
    Q_INVOKABLE void move_right()
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

    Q_INVOKABLE void apply_thrust()
    {
        _y_speed = _thrust;
        if (_y < _y_max/1.5)
        {
            _y_speed = 0;
        }
    }

public slots:
    void update_state()
    {
        _y += _y_speed;
        _y_speed += _gravity;
        if (_y > _y_max)
        {
            _y = _y_max;
        }

        emit y_change();
    }
    
signals:
    void x_change();
    void y_change();
private:
    double _x;
    double _y;
    double _x_speed;
    double _x_min;
    double _x_max;
    double _y_min;
    double _y_max;
    double _y_speed;
    double _gravity;
    double _thrust;
    QTimer _timer;
};

#endif
