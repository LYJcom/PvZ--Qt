#ifndef ZOMBIE_H
#define ZOMBIE_H

#include <QLabel>
#include <QMovie>
#include <QDebug>
#include <QMouseEvent>
#include<QRandomGenerator>

#include "object.h"
#include "scene.h"
#include "bullet.h"
#include "plant.h"

//Base Class

class Zombie : public Object
{
    Q_OBJECT
public:
    Zombie(QWidget* parent = 0);
    ~Zombie();
    virtual void act();
    virtual void hit(int damage, bool silence = false);
    virtual void ice();
    int raw;
    int offset = 0;
    int eatFrame = 0;
    int eatFrame_max = 25;
    bool iced = false;
    bool shield = false;
    float speed;
    bool garlic = false;
    int target;
    int move_cnt = 0;
    bool catapult = false;
    bool is_jumping = false;
    int frozen_cnt = 0;
    int frozen_time = 8000;
    int score; //击杀得分
    QSound* frozen_sound = new QSound(":/Sound/rc/frozen.wav");
};

class zCommonZombie : public Zombie
{
    Q_OBJECT
public:
    zCommonZombie(QWidget* parent = 0, int type = 0);
    ~zCommonZombie();
    void act();
    void hit(int damage, bool silence = false);
    void ice();
private:
    QMovie* walk = nullptr;
    QMovie* attack = nullptr;
    QMovie* paused = nullptr;
    QMovie* prop_walk = nullptr;
    QMovie* prop_attack = nullptr;
    QMovie* prop_paused = nullptr;
    QMovie* frozen = nullptr;
    QMovie* frozen_attack = nullptr;
    QMovie* frozen_paused = nullptr;
    bool prop, iron;
    int prop_strength;
    float xpos;
};

class zPoleZombie : public Zombie
{
    Q_OBJECT
public:
    zPoleZombie(QWidget* parent = 0);
    ~zPoleZombie();
    void act();
    void hit(int damage, bool silence = false);
    void ice();
private:
    QMovie* walk = new QMovie(":/Zombies/rc/PoleZombieWalk.gif");
    QMovie* attack = new QMovie(":/Zombies/rc/PoleZombieAttack.gif");
    QMovie* run = new QMovie(":/Zombies/rc/PoleZombie.gif");
    QMovie* jump_1 = new QMovie(":/Zombies/rc/PoleZombieJump.gif");
    QMovie* jump_2 = new QMovie(":/Zombies/rc/PoleZombieJump2.gif");
    QMovie* paused = new QMovie(":/Zombies/rc/PoleZombie_0.gif");
    QMovie* frozen_1 = new QMovie(":/Zombies/rc/frozen_PoleZombie.gif");
    QMovie* frozen_2 = new QMovie(":/Zombies/rc/frozen_PoleZombieWalk.gif");
    QMovie* frozen_jump_1 = new QMovie(":/Zombies/rc/frozen_PoleZombieJump.gif");
    QMovie* frozen_jump_2 = new QMovie(":/Zombies/rc/frozen_PoleZombieJump2.gif");
    QMovie* frozen_attack = new QMovie(":/Zombies/rc/frozen_PoleZombieAttack.gif");
    QMovie* frozen_paused = new QMovie(":/Zombies/rc/frozen_PoleZombie_0.gif");
    bool pole = true;
    bool success = true;
    bool jumping = false, jumping_1 = false;
    float xpos;
};

class zNewsZombie : public Zombie
{
    Q_OBJECT
public:
    zNewsZombie(QWidget* parent = 0);
    ~zNewsZombie();
    void act();
    void hit(int damage, bool silence = false);
    void ice();
private:
    QMovie* walk = new QMovie(":/Zombies/rc/NewsWalk.gif");
    QMovie* attack = new QMovie(":/Zombies/rc/NewsAttack.gif");
    QMovie* paper_walk = new QMovie(":/Zombies/rc/NewsWalk_1.gif");
    QMovie* paper_attack = new QMovie(":/Zombies/rc/NewsAttack_1.gif");
    QMovie* lose_paper = new QMovie(":/Zombies/rc/NewsLost.gif");
    QMovie* paused_1 = new QMovie(":/Zombies/rc/NewsZombie_0.gif");
    QMovie* paused_2 = new QMovie(":/Zombies/rc/NewsZombie_none_0.gif");
    QMovie* frozen = new QMovie(":/Zombies/rc/frozen_NewsWalk.gif");
    QMovie* frozen_attack = new QMovie(":/Zombies/rc/frozen_NewsZombieAttack.gif");
    QMovie* frozen_paused = new QMovie(":/Zombies/rc/frozen_NewsZombie_0.gif");
    bool paper = true;
    bool angrying = false;
    float xpos;
    int paper_strength;
};

class zCatapultZombie : public Zombie
{
    Q_OBJECT
public:
    zCatapultZombie(QWidget* parent = 0);
    ~zCatapultZombie();
    void act();
    void hit(int damage, bool silence = false);
private:
    QMovie* walk = new QMovie(":/Zombies/rc/CatapultZombie.gif");
    float xpos;
    int num = 20; //篮球数
    int speed_shoot = 100;
    int speed_cnt = 0;
    bool none_target = true;
    int target;
};

class zBoxZombie : public Zombie
{
    Q_OBJECT
public:
    zBoxZombie(QWidget* parent = 0);
    ~zBoxZombie();
    void act();
    void hit(int damage, bool silence = false);
    void ice();
private:
    QMovie* walk = new QMovie(":/Zombies/rc/BoxZombie.gif");
    QMovie* attack = new QMovie(":/Zombies/rc/BoxZombieAttack.gif");
    QMovie* paused = new QMovie(":/Zombies/rc/BoxZombie_0.gif");
    QMovie* frozen = new QMovie(":/Zombies/rc/frozen_BoxZombie.gif");
    QMovie* frozen_attack = new QMovie(":/Zombies/rc/frozen_BoxZombieAttack.gif");
    QMovie* frozen_paused = new QMovie(":/Zombies/rc/frozen_BoxZombie_0.gif");
    QMovie* open_box = new QMovie(":/Zombies/rc/OpenBox.gif");
    float xpos;
    bool opening = false;
};


#endif // ZOMBIE_H
