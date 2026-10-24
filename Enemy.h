#ifndef ENEMY_H
#define ENEMY_H

#include <QObject>
#include <QTimer>

class Enemy: public QObject
{
    Q_OBJECT
    Q_PROPERTY(double x READ get_x WRITE set_x NOTIFY x_change)
    Q_PROPERTY(double y READ get_y WRITE set_y NOTIFY y_change)
    Q_PROPERTY(int _index READ get_index WRITE set_index NOTIFY index_change)    

public:
    Enemy(QObject* parent = nullptr);

    double get_x();

    double get_y();

    void set_x(double value);

    void set_y(double value);

    int get_index();

    void set_index(int value);
signals:
    void x_change();
    void y_change();
    void index_change();

public slots:
    void update_enemy();

private:
    double _x;
    double _y;
    int _index;
    double _y_speed;
    QTimer _timer;
};

#endif
