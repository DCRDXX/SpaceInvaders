#ifndef BULLET_H
#define BULLET_H

#include <QObject>
#include <QTimer>

class Bullet: public QObject
{
    Q_OBJECT
    Q_PROPERTY(double x READ get_x WRITE set_x NOTIFY x_change)
    Q_PROPERTY(double y READ get_y WRITE set_y NOTIFY y_change)

public:
    Bullet(QObject* parent = nullptr);

    double get_x();

    double get_y();

    void set_x(double value);

    void set_y(double value);

signals:
    void x_change();
    void y_change();

public slots:
    void update_bullet();

private:
    double _x;
    double _y;
    double _y_speed;
    QTimer _timer;
};
#endif
