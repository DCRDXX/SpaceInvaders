#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>

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
        if (_x - _speed <= _min_x)
        {
            set_x(_min_x);
        }
        else
        {
            set_x(_x - _speed);
        }
    }
    
    Q_INVOKABLE void move_right()
    {
        if (_x +  _speed >= _max_x - 50)
        {
            set_x(_max_x - 50);
        }
        else
        {
            set_x(_x + _speed);
        }
    }

signals:
    void x_change();
    void y_change();
private:
    double _x;
    double _y;
    double _speed;
    double _min_x;
    double _max_x;
    double _min_y;
    double _max_y;
};

#endif
