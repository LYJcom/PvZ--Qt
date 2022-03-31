#ifndef PLANT_H
#define PLANT_H

#include <QLabel>
#include <QMovie>
#include <QDebug>
#include <QMouseEvent>

#include "object.h"
#include "scene.h"
#include "bullet.h"

//Base Class

class Plant : public Object
{
    Q_OBJECT
public:
    Plant(QWidget* parent = 0);
    virtual void act();
    virtual void hit(int damage);
    int raw, column;
    bool pumpkin = false;
    bool tallnut = false;
    bool garlic = false;
    bool damage = true;
};

//Pea Shooter

class zPeaShooter : public Plant
{
    Q_OBJECT
public:
    zPeaShooter(QWidget* parent = 0);
    ~zPeaShooter();
    void act();
private:
    QMovie* anim = new QMovie(":/Plants/rc/Peashooter.gif");
    int TimerShoot, TimerShoot_max;
};

//SunFlower

class zSunFlower : public Plant
{
    Q_OBJECT
public:
    zSunFlower(QWidget* parent = 0);
    ~zSunFlower();
    void act();
private:
    QMovie* anim = new QMovie(":/Plants/rc/SunFlower.gif");
    int TimerSun, TimerSun_max;
};

//WallNut

class zWallNut : public Plant
{
    Q_OBJECT
public:
    zWallNut(QWidget* parent = 0);
    ~zWallNut();
    void act();
private:
    QMovie* anim = new QMovie(":/Plants/rc/WallNut.gif");
    QMovie* anim_1 = new QMovie(":/Plants/rc/Wallnut_1.gif");
    QMovie* anim_2 = new QMovie(":/Plants/rc/Wallnut_2.gif");
};

//TallNut

class zTallNut : public Plant
{
    Q_OBJECT
public:
    zTallNut(QWidget* parent = 0);
    ~zTallNut();
    void act();
private:
    QMovie* anim = new QMovie(":/Plants/rc/TallNut.gif");
    QMovie* anim_1 = new QMovie(":/Plants/rc/TallNut_1.gif");
    QMovie* anim_2 = new QMovie(":/Plants/rc/TallNut_2.gif");
};

//Repeater

class zRepeater : public Plant
{
    Q_OBJECT
public:
    zRepeater(QWidget* parent = 0);
    ~zRepeater();
    void act();
private:
    QMovie* anim = new QMovie(":/Plants/rc/Repeater.gif");
    int TimerShoot, TimerShoot_max;
};

class zPotatoMine : public Plant
{
    Q_OBJECT
public:
    zPotatoMine(QWidget* parent = 0);
    ~zPotatoMine();
    void act();
private:
    QMovie* anim = new QMovie(":/Plants/rc/PotatoMine_1.gif");
    QMovie* anim_1 = new QMovie(":/Plants/rc/PotatoMine.gif");
    int TimerGrow;
};

class zFireTree : public Plant
{
    Q_OBJECT
public:
    zFireTree(QWidget* parent = 0);
    ~zFireTree();
    void act();
private:
    QMovie* anim = new QMovie(":/Plants/rc/FireTree.gif");
};

class zGarlic : public Plant
{
    Q_OBJECT
public:
    zGarlic(QWidget* parent = 0);
    ~zGarlic();
    void act();
private:
    QMovie* anim = new QMovie(":/Plants/rc/Garlic.gif");
    QMovie* anim_1 = new QMovie(":/Plants/rc/Garlic_1.gif");
    QMovie* anim_2 = new QMovie(":/Plants/rc/Garlic_2.gif");
};

class zCherryBomb : public Plant
{
    Q_OBJECT
public:
    zCherryBomb(QWidget* parent = 0);
    ~zCherryBomb();
    void act();
private:
    QMovie* anim = new QMovie(":/Plants/rc/CherryBomb.gif");
    int TimerBoom;
};


class zIcePeaShooter : public Plant
{
    Q_OBJECT
public:
    zIcePeaShooter(QWidget* parent = 0);
    ~zIcePeaShooter();
    void act();
private:
    QMovie* anim = new QMovie(":/Plants/rc/IcePeaShooter.gif");
    int TimerShoot, TimerShoot_max;
};


class zMushroom : public Plant
{
    Q_OBJECT
public:
    zMushroom(QWidget* parent = 0);
    ~zMushroom();
    void act();
private:
    QMovie* anim = new QMovie(":/Plants/rc/Mushroom.gif");
    int TimerShoot, TimerShoot_max;
};

//PumpKin

class zPumpKin : public Plant
{
    Q_OBJECT
public:
    zPumpKin(QWidget* parent = 0);
    ~zPumpKin();
    void act();
private:
    QMovie* anim = new QMovie(":/Plants/rc/PumpKin_1.gif");
    QMovie* anim_0 = new QMovie(":/Plants/rc/PumpKin_whole.gif");
    QMovie* anim_1 = new QMovie(":/Plants/rc/PumpKinDamage_1.gif");
    QMovie* anim_2 = new QMovie(":/Plants/rc/PumpKinDamage_2.gif");
};

//Squash

class zSquash : public Plant
{
    Q_OBJECT
public:
    zSquash(QWidget* parent = 0);
    ~zSquash();
    void act();
private:
    bool go = false;
    int direction;
    int move_cnt = 0;
    QMovie* anim = new QMovie(":/Plants/rc/Squash.gif");
    QMovie* anim_attack = new QMovie(":/Plants/rc/SquashAttack.gif");
};

#endif // PLANT_H
