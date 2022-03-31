#include "bullet.h"

Bullet::Bullet(QWidget* parent) : Object(parent)
{

}

Pea::Pea(QWidget* parent) : Bullet(parent)
{
    this->setMovie(anim);
    anim->start();
    this->show();
    //this->speed = 10;
    this->speed = 8;
    this->canFire = true;
}

void Pea::act()
{
    this->raise();
    if (!(this->scene->screen.contains(this->pos())))
    {
        this->alive = false;
    }
    this->move(this->x() + this->speed , this->y());
    Zombie* zombie;
    foreach (zombie, this->scene->Zombies)
    {
        //if ((qAbs(zombie->x() - this->x() + zombie->offset + 60) < 20) && ((this->raw) == (zombie->raw)) && (this->alive))
        if (!(zombie->is_jumping) && this->x() + 20 >= zombie->x() + zombie->offset && this->x() < zombie->x() + zombie->offset + 40 && ((this->raw) == (zombie->raw)) && (this->alive))
        {
            this->alive = false;
            Anim* pea_anim = new PeaHit(scene);
            pea_anim->setGeometry(this->x() + 20, this->y(), 40, 40);
            this->scene->Anims.append(pea_anim);
            zombie->hit(10);
            return;
        }
    }
}

Pea::~Pea()
{
    delete this->anim;
}



FirePea::FirePea(QWidget* parent) : Bullet(parent)
{
    this->setMovie(anim);
    anim->start();
    this->show();
    this->speed = 10;
}

void FirePea::act()
{
    this->raise();
    if (!(this->scene->screen.contains(this->pos())))
    {
        this->alive = false;
    }
    this->move(this->x() + this->speed , this->y());
    Zombie* zombie;
    foreach (zombie, this->scene->Zombies)
    {
        if (!(zombie->is_jumping) && this->x() + 20 >= zombie->x() + zombie->offset && this->x() < zombie->x() + zombie->offset + 40 && ((this->raw) == (zombie->raw)) && (this->alive))
        //if ((qAbs(zombie->x() - this->x() + zombie->offset + 60) < 20) && ((this->raw) == (zombie->raw)) && (this->alive))
        {
            this->alive = false;
            Anim* pea_anim = new zFire(scene);
            pea_anim->setGeometry(this->x() + 20, this->y(), 40, 40);
            this->scene->Anims.append(pea_anim);
            zombie->hit(10);
            Zombie* zombie_2;
            foreach (zombie_2, this->scene->Zombies)
            {
                if ((qAbs(zombie_2->x() - this->x() + zombie_2->offset + 60) < 60) && ((this->raw) == (zombie_2->raw)))
                {
                    zombie_2->hit(10, true);
                }
            }
            return;
        }
    }
}

FirePea::~FirePea()
{
    delete this->anim;
}



IcePea::IcePea(QWidget* parent) : Bullet(parent)
{
    this->setMovie(anim);
    anim->start();
    this->show();
    this->speed = 10;
    this->canFire = true;
}

void IcePea::act()
{
    this->raise();
    if (!(this->scene->screen.contains(this->pos())))
    {
        this->alive = false;
    }
    this->move(this->x() + this->speed , this->y());
    Zombie* zombie;
    foreach (zombie, this->scene->Zombies)
    {
        if (!(zombie->is_jumping) && this->x() + 20 >= zombie->x() + zombie->offset && this->x() < zombie->x() + zombie->offset + 40 && ((this->raw) == (zombie->raw)) && (this->alive))
        //if ((qAbs(zombie->x() - this->x() + zombie->offset + 60) < 20) && ((this->raw) == (zombie->raw)) && (this->alive))
        {
            this->alive = false;
            Anim* pea_anim = new SnowHit(scene);
            pea_anim->setGeometry(this->x() + 20, this->y(), 40, 40);
            this->scene->Anims.append(pea_anim);
            zombie->ice();
            zombie->hit(10);
            return;
        }
    }
}

IcePea::~IcePea()
{
    delete this->anim;
}


zMush::zMush(QWidget* parent) : Bullet(parent)
{
    this->setMovie(anim);
    anim->start();
    this->show();
    this->speed = 12;
    this->canFire = false;
    this->TimerFly = 22;
}

void zMush::act()
{
    this->raise();
    this->TimerFly --;
    if (this->TimerFly < 0)
    {
        this->alive = false;
    }
    if (!(this->scene->screen.contains(this->pos())))
    {
        this->alive = false;
    }
    this->move(this->x() + this->speed , this->y());
    Zombie* zombie;
    foreach (zombie, this->scene->Zombies)
    {
        if (!(zombie->is_jumping) && this->x() + 20 >= zombie->x() + zombie->offset && this->x() < zombie->x() + zombie->offset + 40 && ((this->raw) == (zombie->raw)) && (this->alive))
        //if ((qAbs(zombie->x() - this->x() + zombie->offset + 60) < 20) && ((this->raw) == (zombie->raw)) && (this->alive))
        {
            this->alive = false;
            zombie->hit(10);
            return;
        }
    }
}

zMush::~zMush()
{
    delete this->anim;
}

Ball::Ball(QWidget* parent) : Bullet(parent)
{
    this->setMovie(anim);
    anim->start();
    this->show();
    this->speed = 12;
    this->canFire = false;
    this->height = ((this->x() - target) / 2) * ((this->x() - target) / 2) / 400;
    this->speed_max = ((this->x() - target) / 2) * 10;
    this->speed_y = this->speed_max;
}

void Ball::setTarget(int x)
{
    target = x;
}

//void Ball::setTargetPlant(Plant* p)
//{
    //target_plant = p;
//}

void Ball::act()
{
    this->raise();
    if (!(this->scene->screen.contains(this->pos())))
    {
        this->alive = false;
    }
    if(this->x() <= this->target)
    {
        Plant* plant;
        foreach(plant, this->scene->Plants)
        {
            if(plant->x() + 20 == this->target && plant->raw == this->raw)
            {
                Plant* pumpkin;
                foreach(pumpkin, this->scene->Plants)
                {
                    if(pumpkin->pumpkin && pumpkin->raw == plant->raw && pumpkin->column == plant->column)
                    {
                        pumpkin->hit(50);
                        this->alive = false;
                        return;
                    }
                }
                plant->hit(50);
                this->alive = false;
                return;
            }
        }

    }
    //this->move(this->x() - speed, this->y() + speed_y);
    //this->speed_y -= 20;
    this->move(this->x() - speed, this->y());
}

Ball::~Ball()
{
    delete this->anim;
}
