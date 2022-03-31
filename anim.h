#ifndef ANIM_H
#define ANIM_H

#include <QWidget>
#include <QMovie>

#include "object.h"
#include "scene.h"

class Anim : public Object
{
public:
    Anim(QWidget* parent = 0);
    void act();
    int frame;
};

class PeaHit : public Anim
{
public:
    PeaHit(QWidget* parent = 0);
    ~PeaHit();
private:
    QMovie* anim = new QMovie(":/Anims/rc/PeaHit.gif");
};

class SnowHit :public Anim
{
public:
    SnowHit(QWidget* parent = 0);
    ~SnowHit();
private:
    QMovie* anim = new QMovie(":/Anims/rc/SnowPeaHit.gif");
};


class zFire : public Anim
{
public:
    zFire(QWidget* parent = 0);
    ~zFire();
private:
    QMovie* anim = new QMovie(":/Anims/rc/Fire.gif");
};

class ZombieDie : public Anim
{
public:
    ZombieDie(QWidget* parent = 0);
    ~ZombieDie();
private:
    QMovie* anim = new QMovie(":/Anims/rc/ZombieDie.gif");
};

class frozen_ZombieDie : public Anim
{
public:
    frozen_ZombieDie(QWidget* parent = 0);
    ~frozen_ZombieDie();
private:
    QMovie* anim = new QMovie(":/Anims/rc/frozen_ZombieDie.gif");
};

class BurnDie : public Anim
{
public:
    BurnDie(QWidget* parent = 0);
    ~BurnDie();
private:
    QMovie* anim = new QMovie(":/Anims/rc/BurnDie.gif");
};

class ZombieHead : public Anim
{
public:
    ZombieHead(QWidget* parent = 0);
    ~ZombieHead();
private:
    QMovie* anim = new QMovie(":/Anims/rc/ZombieHead.gif");
};

class frozen_ZombieHead : public Anim
{
public:
    frozen_ZombieHead(QWidget* parent = 0);
    ~frozen_ZombieHead();
private:
    QMovie* anim = new QMovie(":/Anims/rc/frozen_ZombieHead.gif");
};

class zMashedPotato : public Anim
{
public:
    zMashedPotato(QWidget* parent = 0);
    ~zMashedPotato();
private:
    QMovie* anim = new QMovie(":/Anims/rc/PotatoMine_mashed.gif");
};

class Boom : public Anim
{
public:
    Boom(QWidget* parent = 0);
    ~Boom();
private:
    QMovie* anim = new QMovie(":/Anims/rc/Boom.gif");
};

class BoxZombieBoom : public Anim
{
public:
    BoxZombieBoom(QWidget* parent = 0);
    ~BoxZombieBoom();
private:
    QMovie* anim = new QMovie(":/Anims/rc/BoxZombieBoom.gif");
};

class zPoleZombieDie : public Anim
{
public:
    zPoleZombieDie(QWidget* parent = 0);
    ~zPoleZombieDie();
private:
    QMovie* anim = new QMovie(":/Anims/rc/PoleZombieDie.gif");
};

class zfrozen_PoleZombieDie : public Anim
{
public:
    zfrozen_PoleZombieDie(QWidget* parent = 0);
    ~zfrozen_PoleZombieDie();
private:
    QMovie* anim = new QMovie(":/Anims/rc/frozen_PoleZombieDie.gif");
};

class zPoleZombieHead : public Anim
{
public:
    zPoleZombieHead(QWidget* parent = 0);
    ~zPoleZombieHead();
private:
    QMovie* anim = new QMovie(":/Anims/rc/PoleZombieHead.gif");
};

class zfrozen_PoleZombieHead : public Anim
{
public:
    zfrozen_PoleZombieHead(QWidget* parent = 0);
    ~zfrozen_PoleZombieHead();
private:
    QMovie* anim = new QMovie(":/Anims/rc/frozen_PoleZombieHead.gif");
};

class zNewsDie : public Anim
{
public:
    zNewsDie(QWidget* parent = 0);
    ~zNewsDie();
private:
    QMovie* anim = new QMovie(":/Anims/rc/NewsDie.gif");
};

class zfrozen_NewsDie : public Anim
{
public:
    zfrozen_NewsDie(QWidget* parent = 0);
    ~zfrozen_NewsDie();
private:
    QMovie* anim = new QMovie(":/Anims/rc/frozen_NewsZombieDie.gif");
};

class zNewsHead : public Anim
{
public:
    zNewsHead(QWidget* parent = 0);
    ~zNewsHead();
private:
    QMovie* anim = new QMovie(":/Anims/rc/NewsHead.gif");
};

class zfrozen_NewsHead : public Anim
{
public:
    zfrozen_NewsHead(QWidget* parent = 0);
    ~zfrozen_NewsHead();
private:
    QMovie* anim = new QMovie(":/Anims/rc/frozen_NewsHead.gif");
};

#endif // ANIM_H
