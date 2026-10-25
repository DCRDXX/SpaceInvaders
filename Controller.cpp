#include "Controller.h"

Controller::Controller(QObject* parent): _x(1280/2-25), _y(720-70), _x_speed(10), _x_min(0), _x_max(1280), _y_min(0), _y_max(670), _gravity(0.5), _thrust(-15), _score(0)
{
    _move_left = false;
    _move_right = false;
    connect(&_timer, &QTimer::timeout, this, &Controller::update_state);
    _timer.start(16);

    connect(&_timer_enemy, &QTimer::timeout, this, &Controller::create_enemy);
    _timer_enemy.start(1000 + rand() % 2000);

    connect(&_timer_move, &QTimer::timeout, this, &Controller::update_move);
    _timer_move.start(16);
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

int Controller::get_score()
{
    return _score;
}

void Controller::set_score(int value)
{
    _score = value;
    emit score_change();
}    

void Controller::move_left()
{
    _move_left = true;
}

void Controller::move_right()
{
    _move_right = true;
}

void Controller::move_left_stop()
{
    _move_left = false;
}

void Controller::move_right_stop()
{
    _move_right = false;
}

void Controller::apply_thrust()
{
    _y_speed = _thrust;
    if (_y < _y_max/1.5)
    {
        _y_speed = 0;
    }
}

void Controller::restart_game()
{
    for (Enemy* enemy : _enemy_list)
    {
        delete enemy;
    }
    _enemy_list.clear();

    for (Bullet* bullet : _bullet_list)
    {
        delete bullet;
    }
    _bullet_list.clear();

    _move_left = false;
    _move_right = false;
    _score = 0;
    
    bullet_change();
    enemy_change();

    set_x(1280/2-25);
    set_y(720-20);
}

void Controller::update_state()
{
    _y += _y_speed;
    _y_speed += _gravity;
    if (_y > _y_max)
    {
        _y = _y_max;
    }
    check_collision();
    check_over();
    emit y_change();
}

void Controller::update_move()
{
    if (_move_left && _move_right)
    {
        return;
    }
    if (_move_left && _x - _x_speed > _x_min)
    {
        set_x(_x - _x_speed);
    }
    if (_move_right && _x + _x_speed < _x_max)
    {
        set_x(_x + _x_speed);
    }
}

QQmlListProperty<Bullet> Controller::get_bullets()
{
    return QQmlListProperty<Bullet>(this, &_bullet_list);
}

QQmlListProperty<Enemy> Controller::get_enemies()
{
    return QQmlListProperty<Enemy>(this, &_enemy_list);
}
    
void Controller::fire_bullet()
{
    Bullet* new_bullet = new Bullet(this);
    new_bullet->set_x(_x+23);
    new_bullet->set_y(_y-20);
    _bullet_list.append(new_bullet);
    emit bullet_change();
}

void Controller::create_enemy()
{
    Enemy* new_enemy = new Enemy();
    new_enemy->set_x(rand() % 1230);
    new_enemy->set_y(-50);
    _enemy_list.append(new_enemy);
    _timer_enemy.start(1000 + rand() % 2000);
    emit enemy_change();
}

void Controller::delete_bullet(Bullet* bullet)
{
    int index = _bullet_list.indexOf(bullet);
    if (index != -1)
    {
        delete _bullet_list[index];
        _bullet_list.removeAt(index);
        emit bullet_change();
        qInfo() << "bullet changed";
    }
}

void Controller::delete_enemy(Enemy* enemy)
{
    int index = _enemy_list.indexOf(enemy);
    if (index != -1)
    {
        delete _enemy_list[index];
        _enemy_list.removeAt(index);
        emit enemy_change();
        qInfo() << "enemy changed";
    }
}

void Controller::check_collision()
{
    for (int i = _bullet_list.size() - 1; i >= 0; i--)
    {
        Bullet* bullet = _bullet_list[i];
        for (int j = _enemy_list.size() - 1; j >= 0; j--)
        {
            Enemy* enemy = _enemy_list[j];

            double bullet_left = bullet->get_x();
            double bullet_right = bullet->get_x() + 10;
            double bullet_top = bullet->get_y();
            double bullet_bottom = bullet->get_y() + 30;

            double enemy_left = enemy->get_x();
            double enemy_right = enemy->get_x() + 50;
            double enemy_top = enemy->get_y();
            double enemy_bottom = enemy->get_y() + 50;
           
            if (bullet_right > enemy_left && bullet_left < enemy_right &&
            bullet_bottom > enemy_top && bullet_top < enemy_bottom)
            {
                delete_bullet(bullet);
                delete_enemy(enemy);
                set_score(get_score() + 10);
                break;
            }
        }
    }
}

void Controller::check_over()
{
    for(Enemy* enemy : _enemy_list)
    {
        double enemy_left = enemy->get_x();
        double enemy_right = enemy->get_x() + 50;
        double enemy_top = enemy->get_y();
        double enemy_bottom = enemy->get_y() + 50;

        double player_left = get_x();
        double player_right = get_x() + 50;
        double player_top = get_y();
        double player_bottom = get_y() + 50;

        if (player_right > enemy_left && player_left < enemy_right &&
        player_bottom > enemy_top && player_top < enemy_bottom ||
        enemy_bottom > 720)
        {
            emit gameOver();
            qInfo() << "game over";
            break;
        }
    }
}
