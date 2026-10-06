#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>

class Controller: public QObject
{
    Q_OBJECT
    Q_PROPERTY(double x READ get_x WRITE set_x NORIFY x_change)
    Q_PROPERTY(double y READ get_y WRITE set_y NORIFY y_change)

public:
    Controller(QObject* parent = nullptr);

    double get_x()
    {
        return _x;
    }

    double get_x()
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
        set_x(m_x - _speed);
    }
    
    Q_INVOKABLE void move_right()
    {
        set_x(m_x + _speed);
    }

singals:
    void x_change();
    void y_change();
private:
    double _x;
    double _y;
    double _speed;
};

#endif
