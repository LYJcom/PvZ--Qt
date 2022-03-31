#ifndef BULLET_H
#define BULLET_H

#include <QWidget>
#include <QMovie>

#include "object.h"
#include "scene.h"
#include "anim.h"
#include "plant.h"

class Bullet : public Object
{
public:
    Bullet(QWidget* parent = 0);
    virtual void act(){}
    int raw;
    bool canFire = false;
};

class Pea : public Bullet
{
public:
    Pea(QWidget* parent = 0);
    ~Pea();
    void act();
private:
    QMovie* anim = new QMovie(":/FlyingObjects/rc/Pea.gif");
    int speed;
};

class FirePea : public Bullet
{
public:
    FirePea(QWidget* parent = 0);
    ~FirePea();
    void act();
private:
    QMovie* anim = new QMovie(":/FlyingObjects/rc/PeaFire.gif");
    int speed;
};

class IcePea : public Bullet
{
public:
    IcePea(QWidget* parent = 0);
    ~IcePea();
    void act();
private:
    QMovie* anim = new QMovie(":/FlyingObjects/rc/PeaIce.gif");
    int speed;
};

class zMush : public Bullet
{
public:
    zMush(QWidget* parent = 0);
    ~zMush();
    void act();
private:
    QMovie* anim = new QMovie(":/FlyingObjects/rc/Mush.gif");
    int speed;
    int TimerFly;
};

class Ball : public Bullet
{
public:
    Ball(QWidget* parent = 0);
    ~Ball();
    void act();
    void setTarget(int x);
    //void setTargetPlant(zPlant* p);
private:
    QMovie* anim = new QMovie(":/FlyingObjects/rc/BasketBall.gif");
    //Plant* target_plant = nullptr;
    int speed;
    int target;
    int height;
    int speed_max;
    int speed_y;
};

#endif // BULLET_H
