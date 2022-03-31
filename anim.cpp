#include "Anim.h"

Anim::Anim(QWidget* parent) : Object(parent)
{

}

void Anim::act()
{
    if ((this->frame) > 0)
    {
        this->frame --;
    }
    else
    {
        this->alive = false;
    }
}

PeaHit::PeaHit(QWidget* parent) : Anim(parent)
{
    this->setMovie(anim);
    anim->start();
    this->show();
    this->frame = 2;
}

PeaHit::~PeaHit()
{
    delete (this->anim);
}

SnowHit::SnowHit(QWidget* parent) : Anim(parent)
{
    this->setMovie(anim);
    anim->start();
    this->show();
    this->frame = 2;
}

SnowHit::~SnowHit()
{
    delete (this->anim);
}

zFire::zFire(QWidget* parent) : Anim(parent)
{
    this->setMovie(anim);
    anim->start();
    this->show();
    this->frame = 2;
}

zFire::~zFire()
{
    delete (this->anim);
}


ZombieDie::ZombieDie(QWidget* parent) : Anim(parent)
{
    this->setMovie(anim);
    anim->start();
    this->show();
    this->frame = 50;
}

ZombieDie::~ZombieDie()
{
    delete (this->anim);
}

frozen_ZombieDie::frozen_ZombieDie(QWidget* parent) : Anim(parent)
{
    this->setMovie(anim);
    anim->start();
    this->show();
    this->frame = 50;
}

frozen_ZombieDie::~frozen_ZombieDie()
{
    delete (this->anim);
}

BurnDie::BurnDie(QWidget* parent) : Anim(parent)
{
    this->setMovie(anim);
    anim->start();
    this->show();
    this->frame = 85;
}

BurnDie::~BurnDie()
{
    delete (this->anim);
}

ZombieHead::ZombieHead(QWidget* parent) : Anim(parent)
{
    this->setMovie(anim);
    anim->start();
    this->show();
    this->frame = 40;
}

ZombieHead::~ZombieHead()
{
    delete (this->anim);
}

frozen_ZombieHead::frozen_ZombieHead(QWidget* parent) : Anim(parent)
{
    this->setMovie(anim);
    anim->start();
    this->show();
    this->frame = 40;
}

frozen_ZombieHead::~frozen_ZombieHead()
{
    delete (this->anim);
}

zMashedPotato::zMashedPotato(QWidget* parent) : Anim(parent)
{
    this->setMovie(anim);
    anim->start();
    this->show();
    this->frame = 20;
}

zMashedPotato::~zMashedPotato()
{
    delete (this->anim);
}

Boom::Boom(QWidget* parent) : Anim(parent)
{
    this->setMovie(anim);
    anim->start();
    this->show();
    this->frame = 40;
}

Boom::~Boom()
{
    delete (this->anim);
}

BoxZombieBoom::BoxZombieBoom(QWidget* parent) : Anim(parent)
{
    this->setMovie(anim);
    anim->start();
    this->show();
    this->frame = 40;
}

BoxZombieBoom::~BoxZombieBoom()
{
    delete (this->anim);
}

zPoleZombieDie::zPoleZombieDie(QWidget* parent) : Anim(parent)
{
    this->setMovie(anim);
    anim->start();
    this->show();
    this->frame = 50;
}

zPoleZombieDie::~zPoleZombieDie()
{
    delete (this->anim);
}

zfrozen_PoleZombieDie::zfrozen_PoleZombieDie(QWidget* parent) : Anim(parent)
{
    this->setMovie(anim);
    anim->start();
    this->show();
    this->frame = 50;
}

zfrozen_PoleZombieDie::~zfrozen_PoleZombieDie()
{
    delete (this->anim);
}

zPoleZombieHead::zPoleZombieHead(QWidget* parent) : Anim(parent)
{
    this->setMovie(anim);
    anim->start();
    this->show();
    this->frame = 40;
}

zPoleZombieHead::~zPoleZombieHead()
{
    delete (this->anim);
}

zfrozen_PoleZombieHead::zfrozen_PoleZombieHead(QWidget* parent) : Anim(parent)
{
    this->setMovie(anim);
    anim->start();
    this->show();
    this->frame = 40;
}

zfrozen_PoleZombieHead::~zfrozen_PoleZombieHead()
{
    delete (this->anim);
}

zNewsDie::zNewsDie(QWidget* parent) : Anim(parent)
{
    this->setMovie(anim);
    anim->start();
    this->show();
    this->frame = 50;
}

zNewsDie::~zNewsDie()
{
    delete (this->anim);
}

zfrozen_NewsDie::zfrozen_NewsDie(QWidget* parent) : Anim(parent)
{
    this->setMovie(anim);
    anim->start();
    this->show();
    this->frame = 50;
}

zfrozen_NewsDie::~zfrozen_NewsDie()
{
    delete (this->anim);
}

zNewsHead::zNewsHead(QWidget* parent) : Anim(parent)
{
    this->setMovie(anim);
    anim->start();
    this->show();
    this->frame = 40;
}

zNewsHead::~zNewsHead()
{
    delete (this->anim);
}

zfrozen_NewsHead::zfrozen_NewsHead(QWidget* parent) : Anim(parent)
{
    this->setMovie(anim);
    anim->start();
    this->show();
    this->frame = 40;
}

zfrozen_NewsHead::~zfrozen_NewsHead()
{
    delete (this->anim);
}
