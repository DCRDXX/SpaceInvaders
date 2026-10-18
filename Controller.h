#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>
#include <QQmlListProperty>
#include <vector>
#include "Bullet.h"
#include "Enemy.h"

class Controller: public QObject
{
    Q_OBJECT
    Q_PROPERTY(double x READ get_x WRITE set_x NOTIFY x_change)
    Q_PROPERTY(double y READ get_y WRITE set_y NOTIFY y_change)
    Q_PROPERTY(QQmlListProperty<Bullet> bullets READ get_bullets NOTIFY bullet_change)
    Q_PROPERTY(QQmlListProperty<Enemy> enemies READ get_enemies NOTIFY enemy_change)

public:
    Controller(QObject* parent = nullptr);

    double get_x();

    double get_y();

    void set_x(double value);

    void set_y(double value);

    Q_INVOKABLE void move_left();
    
    Q_INVOKABLE void move_right();

    Q_INVOKABLE void apply_thrust();

    Q_INVOKABLE void fire_bullet();

    Q_INVOKABLE void create_enemy();

    QQmlListProperty<Bullet> get_bullets();

    QQmlListProperty<Enemy> get_enemies();
    
public slots:
    void update_state();
    void delete_bullet(Bullet* bullet);
signals:
    void x_change();
    void y_change();
    void bullet_change();
    void enemy_change();
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
    QTimer _timer_enemy;
    QList<Bullet*> _bullet_list;
    QList<Enemy*> _enemy_list;
};

#endif
