#include "plant.h"

Plant::Plant(QWidget *parent) : Object(parent)
{

}

void Plant::act()
{

}

void Plant::hit(int damage)
{
    this->strength -= damage;
    if (this->strength <= 0)
    {
        this->alive = false;
    }
}



zPeaShooter::zPeaShooter(QWidget *parent) : Plant(parent)
{
    this->setMovie(anim);
    anim->start();
    this->show();
    this->TimerShoot_max = 50;
    this->TimerShoot = this->TimerShoot_max;
    this->strength = 200;
}

void zPeaShooter::act()
{
    Zombie* zombie;
    foreach(zombie, this->scene->Zombies)
    {
        if(zombie->raw == this->raw + 1)
        {
            this->stackUnder(zombie);
            break;
        }
    }
    foreach(zombie, this->scene->Zombies)
    {
        if(zombie->raw == this->raw)
        {
            this->stackUnder(zombie);
            break;
        }
    }
    Plant* plant;
    foreach(plant, this->scene->Plants)
    {
        if(plant->raw == this->raw + 1)
        {
            this->stackUnder(plant);
            break;
        }
    }
    if (this->TimerShoot <= 0)
    {
        bool shoot = false;
        Zombie* zombie;
        foreach(zombie, scene->Zombies)
        {
            if(zombie->raw == this->raw && zombie->x() + zombie->offset + 64 >= this->x() + 50)
            {
                shoot = true;
                break;
            }
        }
        //if (!(scene->hasEnemy[this->raw]))
        if(!shoot)
        {
            this->TimerShoot = QRandomGenerator::global()->bounded(20);// not to shoot too many peas in a single timer event
            return;
        }
        this->TimerShoot = this->TimerShoot_max;
        Pea* pea = new Pea(scene);
        pea->setGeometry(this->x() + 20, this->y() + 15 - (QRandomGenerator::global()->bounded(5)), 80, 40);
        pea->raw = this->raw;
        scene->FlyingObjects.append(pea);
    }
    else
    {
        this->TimerShoot --;
    }
}

zPeaShooter::~zPeaShooter()
{
    delete this->anim;
}



zSunFlower::zSunFlower(QWidget *parent) : Plant(parent)
{
    this->setMovie(anim);
    anim->start();
    this->show();
    this->TimerSun_max = 500;
    this->TimerSun = QRandomGenerator::global()->bounded(this->TimerSun_max);
    this->strength = 200;
}

void zSunFlower::act()
{
    Zombie* zombie;
    foreach(zombie, this->scene->Zombies)
    {
        if(zombie->raw == this->raw + 1)
        {
            this->stackUnder(zombie);
            break;
        }
    }
    foreach(zombie, this->scene->Zombies)
    {
        if(zombie->raw == this->raw)
        {
            this->stackUnder(zombie);
            break;
        }
    }
    Plant* plant;
    foreach(plant, this->scene->Plants)
    {
        if(plant->raw == this->raw + 1)
        {
            this->stackUnder(plant);
            break;
        }
    }
    if (this->TimerSun <= 0)
    {
        this->TimerSun = this->TimerSun_max;
        zSun* sun = new zSun(scene);
        sun->setGeometry(this->x(), this->y() + 15 - (QRandomGenerator::global()->bounded(5)), 80, 80);
        sun->level = this->y() + 40;
        scene->Bonuses.append(sun);
        //QSound::play(":/Sounds/rc/PeaHit.wav");
    }
    else
    {
        this->TimerSun --;
    }
}

zSunFlower::~zSunFlower()
{
    delete this->anim;
}



zWallNut::zWallNut(QWidget *parent) : Plant(parent)
{
    this->setMovie(anim);
    anim->start();
    anim_1->start();
    anim_2->start();
    this->show();
    this->strength = 1200;
}

void zWallNut::act()
{
    Zombie* zombie;
    foreach(zombie, this->scene->Zombies)
    {
        if(zombie->raw == this->raw + 1)
        {
            this->stackUnder(zombie);
            break;
        }
    }
    foreach(zombie, this->scene->Zombies)
    {
        if(zombie->raw == this->raw)
        {
            this->stackUnder(zombie);
            break;
        }
    }
    Plant* plant;
    foreach(plant, this->scene->Plants)
    {
        if(plant->raw == this->raw + 1)
        {
            this->stackUnder(plant);
            break;
        }
    }
    if ((this->strength < 800) && (this->strength >= 400))
    {
        this->setMovie(anim_1);
    }
    if (this->strength < 400)
    {
        this->setMovie(anim_2);
    }
}

zWallNut::~zWallNut()
{
    delete this->anim;
    delete this->anim_1;
    delete this->anim_2;
}

zTallNut::zTallNut(QWidget *parent) : Plant(parent)
{
    tallnut = true;
    this->setMovie(anim);
    anim->start();
    anim_1->start();
    anim_2->start();
    this->show();
    this->strength = 2400;
}

void zTallNut::act()
{
    Zombie* zombie;
    foreach(zombie, this->scene->Zombies)
    {
        if(zombie->raw == this->raw + 1)
        {
            this->stackUnder(zombie);
            break;
        }
    }
    foreach(zombie, this->scene->Zombies)
    {
        if(zombie->raw == this->raw)
        {
            this->stackUnder(zombie);
            break;
        }
    }
    Plant* plant;
    foreach(plant, this->scene->Plants)
    {
        if(plant->raw == this->raw + 1)
        {
            this->stackUnder(plant);
            break;
        }
    }
    if ((this->strength < 1600) && (this->strength >= 800))
    {
        this->setMovie(anim_1);
    }
    if (this->strength < 800)
    {
        this->setMovie(anim_2);
    }
}

zTallNut::~zTallNut()
{
    delete this->anim;
    delete this->anim_1;
    delete this->anim_2;
}

zRepeater::zRepeater(QWidget *parent) : Plant(parent)
{
    this->setMovie(anim);
    anim->start();
    this->show();
    this->TimerShoot_max = 50;
    this->TimerShoot = this->TimerShoot_max;
    this->strength = 200;
}

void zRepeater::act()
{
    Zombie* zombie;
    foreach(zombie, this->scene->Zombies)
    {
        if(zombie->raw == this->raw + 1)
        {
            this->stackUnder(zombie);
            break;
        }
    }
    foreach(zombie, this->scene->Zombies)
    {
        if(zombie->raw == this->raw)
        {
            this->stackUnder(zombie);
            break;
        }
    }
    Plant* plant;
    foreach(plant, this->scene->Plants)
    {
        if(plant->raw == this->raw + 1)
        {
            this->stackUnder(plant);
            break;
        }
    }
    if (this->TimerShoot <= 0) //第二发
    {
        bool shoot = false;
        Zombie* zombie;
        foreach(zombie, scene->Zombies)
        {
            if(zombie->raw == this->raw && zombie->x() + zombie->offset + 64 >= this->x() + 50)
            {
                shoot = true;
                break;
            }
        }
        //if (!(scene->hasEnemy[this->raw]))
        if(!shoot)
        {
            this->TimerShoot = QRandomGenerator::global()->bounded(20);// not to shoot too many peas in a single timer event
            return;
        }
        this->TimerShoot = this->TimerShoot_max;
        Pea* pea = new Pea(scene);
        pea->setGeometry(this->x() + 20, this->y() + 15 - (QRandomGenerator::global()->bounded(5)), 80, 40);
        pea->raw = this->raw;
        scene->FlyingObjects.append(pea);
    }
    else if (this->TimerShoot == 5) //第一发
    {
        bool shoot = false;
        Zombie* zombie;
        foreach(zombie, scene->Zombies)
        {
            if(zombie->raw == this->raw && zombie->x() + zombie->offset + 64 >= this->x() + 50)
            {
                shoot = true;
                break;
            }
        }
        //if (!(scene->hasEnemy[this->raw]))
        if(!shoot)
        {
            this->TimerShoot = QRandomGenerator::global()->bounded(20);// not to shoot too many peas in a single timer event
            return;
        }
        Pea* pea = new Pea(scene);
        pea->setGeometry(this->x() + 20, this->y() + 15 - (QRandomGenerator::global()->bounded(5)), 80, 40);
        pea->raw = this->raw;
        scene->FlyingObjects.append(pea);
        this->TimerShoot --;
    }
    else
    {
        this->TimerShoot --;
    }
}

zRepeater::~zRepeater()
{
    delete this->anim;
}



zPotatoMine::zPotatoMine(QWidget *parent) : Plant(parent)
{
    this->setMovie(anim);
    anim->start();
    anim_1->start();
    this->show();
    this->strength = 200;
    this->TimerGrow = 800;
}

void zPotatoMine::act()
{
    Zombie* zombie;
    foreach(zombie, this->scene->Zombies)
    {
        if(zombie->raw == this->raw + 1)
        {
            this->stackUnder(zombie);
            break;
        }
    }
    foreach(zombie, this->scene->Zombies)
    {
        if(zombie->raw == this->raw)
        {
            this->stackUnder(zombie);
            break;
        }
    }
    Plant* plant;
    foreach(plant, this->scene->Plants)
    {
        if(plant->raw == this->raw + 1)
        {
            this->stackUnder(plant);
            break;
        }
    }
    if (this->TimerGrow > 0)
    {
        this->TimerGrow --;
    }
    else
    {
        this->setMovie(anim_1);
        Zombie* zombie;
        foreach (zombie, this->scene->Zombies)
        {
            if ((qAbs(zombie->x() - this->x() + zombie->offset + 50) < 40) && ((this->raw) == (zombie->raw)))
            {
                if (this->alive)
                {
                    Anim* mashedPotato = new zMashedPotato(scene);
                    mashedPotato->setGeometry(this->x() - 40, this->y(), 150, 100);
                    this->scene->Anims.append(mashedPotato);
                }
                this->alive = false;
                zombie->hit(1200);
            }
        }
    }
}

zPotatoMine::~zPotatoMine()
{
    delete this->anim;
    delete this->anim_1;
}



zFireTree::zFireTree(QWidget *parent) : Plant(parent)
{
    this->setMovie(anim);
    anim->start();
    this->show();
    this->strength = 300;
}

void zFireTree::act()
{
    Zombie* zombie;
    foreach(zombie, this->scene->Zombies)
    {
        if(zombie->raw == this->raw + 1)
        {
            this->stackUnder(zombie);
            break;
        }
    }
    foreach(zombie, this->scene->Zombies)
    {
        if(zombie->raw == this->raw)
        {
            this->stackUnder(zombie);
            break;
        }
    }
    Plant* plant;
    foreach(plant, this->scene->Plants)
    {
        if(plant->raw == this->raw + 1)
        {
            this->stackUnder(plant);
            break;
        }
    }
    int i = 0;
    while (i < scene->FlyingObjects.count())
    {
        Bullet* obj = scene->FlyingObjects[i];
        if (obj->canFire && (obj->raw == this->raw) && (qAbs(this->x() - obj->x() - 10) < 20))
        {
            FirePea* firepea = new FirePea(scene);
            firepea->setGeometry(obj->x(), obj->y(), 80, 40);
            firepea->raw = obj->raw;
            scene->FlyingObjects.append(firepea);
            delete obj;
            scene->FlyingObjects.removeAt(i);
        }
        else
        {
            i++;
        }
    }
}

zFireTree::~zFireTree()
{
    delete this->anim;
}

zGarlic::zGarlic(QWidget *parent) : Plant(parent)
{
    this->garlic = true;
    this->setMovie(anim);
    anim->start();
    anim_1->start();
    anim_2->start();
    this->show();
    this->strength = 240;
}

void zGarlic::act()
{
    Zombie* zombie;
    foreach(zombie, this->scene->Zombies)
    {
        if(zombie->raw == this->raw + 1)
        {
            this->stackUnder(zombie);
            break;
        }
    }
    foreach(zombie, this->scene->Zombies)
    {
        if(zombie->raw == this->raw)
        {
            this->stackUnder(zombie);
            break;
        }
    }
    Plant* plant;
    foreach(plant, this->scene->Plants)
    {
        if(plant->raw == this->raw + 1)
        {
            this->stackUnder(plant);
            break;
        }
    }
    if ((this->strength < 200) && (this->strength >= 100))
    {
        this->setMovie(anim_1);
    }
    if (this->strength < 100)
    {
        this->setMovie(anim_2);
    }
}

zGarlic::~zGarlic()
{
    delete this->anim;
    delete this->anim_1;
    delete this->anim_2;
}

zCherryBomb::zCherryBomb(QWidget *parent) : Plant(parent)
{
    this->setMovie(anim);
    anim->start();
    this->show();
    this->TimerBoom = 12;
    this->strength = 2000;
    this->damage = false;
}

void zCherryBomb::act()
{
    Plant* plant;
    foreach(plant, this->scene->Plants)
    {
        if(plant->raw == this->raw + 1)
        {
            this->stackUnder(plant);
            break;
        }
    }
    if (this->TimerBoom > 0)
    {
        this->TimerBoom --;
    }
    else
    {
        Zombie* zombie;
        foreach (zombie, this->scene->Zombies)
        {
            if ((qAbs(zombie->x() - this->x() + zombie->offset + 50) < 140) && (qAbs(this->raw - zombie->raw) <= 1))
            {
                zombie->hit(1200);
            }
        }
        Anim* boom = new Boom(scene);
        boom->setGeometry(this->x() - 60, this->y() - 50, 200, 150);
        scene->Anims.append(boom);
        this->alive = false;
    }
}

zCherryBomb::~zCherryBomb()
{
    delete this->anim;
}



zIcePeaShooter::zIcePeaShooter(QWidget *parent) : Plant(parent)
{
    this->setMovie(anim);
    anim->start();
    this->show();
    this->TimerShoot_max = 50;
    this->TimerShoot = this->TimerShoot_max;
    this->strength = 200;
}

void zIcePeaShooter::act()
{
    Zombie* zombie;
    foreach(zombie, this->scene->Zombies)
    {
        if(zombie->raw == this->raw + 1)
        {
            this->stackUnder(zombie);
            break;
        }
    }
    foreach(zombie, this->scene->Zombies)
    {
        if(zombie->raw == this->raw)
        {
            this->stackUnder(zombie);
            break;
        }
    }
    Plant* plant;
    foreach(plant, this->scene->Plants)
    {
        if(plant->raw == this->raw + 1)
        {
            this->stackUnder(plant);
            break;
        }
    }
    if (this->TimerShoot <= 0)
    {
        bool shoot = false;
        Zombie* zombie;
        foreach(zombie, scene->Zombies)
        {
            if(zombie->raw == this->raw && zombie->x() + zombie->offset + 64 >= this->x() + 50)
            {
                shoot = true;
                break;
            }
        }
        //if (!(scene->hasEnemy[this->raw]))
        if(!shoot)
        {
            this->TimerShoot = QRandomGenerator::global()->bounded(20);// not to shoot too many peas in a single timer event
            return;
        }
        this->TimerShoot = this->TimerShoot_max;
        IcePea* pea = new IcePea(scene);
        pea->setGeometry(this->x() + 20, this->y() + 15 - (QRandomGenerator::global()->bounded(5)), 80, 40);
        pea->raw = this->raw;
        scene->FlyingObjects.append(pea);
    }
    else
    {
        this->TimerShoot --;
    }
}

zIcePeaShooter::~zIcePeaShooter()
{
    delete this->anim;
}



zMushroom::zMushroom(QWidget *parent) : Plant(parent)
{
    this->setMovie(anim);
    anim->start();
    this->show();
    this->TimerShoot_max = 50;
    this->TimerShoot = this->TimerShoot_max;
    this->strength = 100;
}

void zMushroom::act()
{
    Zombie* zombie;
    foreach(zombie, this->scene->Zombies)
    {
        if(zombie->raw == this->raw + 1)
        {
            this->stackUnder(zombie);
            break;
        }
    }
    foreach(zombie, this->scene->Zombies)
    {
        if(zombie->raw == this->raw)
        {
            this->stackUnder(zombie);
            break;
        }
    }
    Plant* plant;
    foreach(plant, this->scene->Plants)
    {
        if(plant->raw == this->raw + 1)
        {
            this->stackUnder(plant);
            break;
        }
    }
    if (this->TimerShoot <= 0)
    {
        if (!(scene->hasEnemy[this->raw]))
        {
            this->TimerShoot = QRandomGenerator::global()->bounded(20);// not to shoot too many peas in a single timer event
            return;
        }
        this->TimerShoot = this->TimerShoot_max;
        zMush* mush = new zMush(scene);
        mush->setGeometry(this->x() + 20, this->y()+ 55 - (QRandomGenerator::global()->bounded(5)), 80, 40);
        mush->raw = this->raw;
        scene->FlyingObjects.append(mush);
    }
    else
    {
        this->TimerShoot --;
    }
}

zMushroom::~zMushroom()
{
    delete this->anim;
}


zPumpKin::zPumpKin(QWidget *parent) : Plant(parent)
{
    this->pumpkin = true;
    this->setMovie(anim_0);
    anim->start();
    anim_0->start();
    anim_1->start();
    anim_2->start();
    this->show();
    this->strength = 1200;
}

void zPumpKin::act()
{
    Zombie* zombie;
    foreach(zombie, this->scene->Zombies)
    {
        if(zombie->raw == this->raw + 1)
        {
            this->stackUnder(zombie);
            break;
        }
    }
    foreach(zombie, this->scene->Zombies)
    {
        if(zombie->raw == this->raw)
        {
            this->stackUnder(zombie);
            break;
        }
    }
    Plant* plant;
    foreach(plant, this->scene->Plants)
    {
        if(plant->raw == this->raw + 1)
        {
            this->stackUnder(plant);
            break;
        }
    }
    if(this->strength >= 800)
    {
        Plant* plant;
        foreach(plant, this->scene->Plants)
        {
            if(!(plant->pumpkin) && plant->raw == this->raw && plant->column == this->column)
            {
                this->setMovie(anim);
                return;
            }
        }
        this->setMovie(anim_0);
    }
    else if ((this->strength < 800) && (this->strength >= 400))
    {
        this->setMovie(anim_1);
    }
    else if (this->strength < 400)
    {
        this->setMovie(anim_2);
    }
}

zPumpKin::~zPumpKin()
{
    delete this->anim;
    delete this->anim_1;
    delete this->anim_2;
}

zSquash::zSquash(QWidget *parent) : Plant(parent)
{
    this->setMovie(anim);
    anim->start();
    anim_attack->start();
    this->show();
    this->strength = 2000;
    this->damage = false;
}

void zSquash::act()
{
    this->raise();
    Zombie* zombie;
    foreach(zombie, this->scene->Zombies)
    {
        if(zombie->raw == this->raw + 1)
        {
            this->stackUnder(zombie);
            break;
        }
    }
    Plant* plant;
    foreach(plant, this->scene->Plants)
    {
        if(plant->raw == this->raw + 1)
        {
            this->stackUnder(plant);
            break;
        }
    }
    if(this->go)
    {
        this->move(this->x() + 10*direction, this->y());
        move_cnt++;
        if(move_cnt >= 35)
        {
            this->alive = false;
            foreach(zombie, this->scene->Zombies)
            {
                switch(this->direction)
                {
                case -1:
                    if(zombie->catapult && zombie->raw == this->raw && this->x() - 20 <= zombie->x() + zombie->offset + 100 && this->x() + 100 + 20 >= zombie->x() + zombie->offset + 100)
                    {
                       zombie->alive = false;
                       this->scene->score += zombie->score;
                       break;
                    }
                    else if(zombie->raw == this->raw && this->x() - (zombie->x() + zombie->offset) < 100 && this->x() - zombie->x() - zombie->offset >= 33)
                    {
                       zombie->alive = false;
                       this->scene->score += zombie->score;
                    }
                    break;
                case 1:
                    if(zombie->catapult && zombie->raw == this->raw && this->x() - 20 <= zombie->x() + zombie->offset + 100 && this->x() + 100 + 20 >= zombie->x() + zombie->offset + 100)
                    {
                       zombie->alive = false;
                       this->scene->score += zombie->score;
                       break;
                    }
                    else if(zombie->raw == this->raw && this->x() - zombie->x() - zombie->offset > -100 && this->x() - zombie->x() - zombie->offset <= -33)
                    {
                       zombie->alive = false;
                       this->scene->score += zombie->score;
                    }
                    break;
                case 0:
                    if(zombie->catapult && zombie->raw == this->raw && this->x() - 20 <= zombie->x() + zombie->offset + 100 && this->x() + 100 + 20 >= zombie->x() + zombie->offset + 100)
                    {
                       zombie->alive = false;
                       this->scene->score += zombie->score;
                       break;
                    }
                    else if(zombie->raw == this->raw && this->x() - zombie->x() - zombie->offset >= -33 && this->x() - zombie->x() - zombie->offset <= 33)
                    {
                        zombie->alive = false;
                        this->scene->score += zombie->score;
                    }
                    break;
                }
            }
        }
    }
    foreach(zombie, this->scene->Zombies)
    {
        if(zombie->raw == this->raw && zombie->catapult)
        {
            if(this->x() >= zombie->x() + zombie->offset + 100 && this->x() - 100 < zombie->x() + zombie->offset + 100)
            {
                this->go = true;
                this->direction = -1;
                this->setMovie(anim_attack);
                break;
            }
            else if(this->x() + 100 <= zombie->x() + zombie->offset + 100 && this->x() + 180 > zombie->x() + zombie->offset + 100)
            {
                this->go = true;
                this->direction = 1;
                this->setMovie(anim_attack);
                break;
            }
            else if(this->x() <= zombie->x() + zombie->offset + 100 && this->x() + 100 >= zombie->x() + zombie->offset + 100)
            {
                this->go = true;
                this->direction = 0;
                this->setMovie(anim_attack);
                break;
            }
        }
        if(zombie->raw == this->raw && this->x() - (zombie->x() + zombie->offset) < 100 && this->x() - zombie->x() - zombie->offset >= 33)
        {
            this->go = true;
            this->direction = -1;
            this->setMovie(anim_attack);
        }
        else if(zombie->raw == this->raw && this->x() - zombie->x() - zombie->offset > -100 && this->x() - zombie->x() - zombie->offset <= -33)
        {
            this->go = true;
            this->direction = 1;
            this->setMovie(anim_attack);
        }
        else if(zombie->raw == this->raw && this->x() - zombie->x() - zombie->offset >= -33 && this->x() - zombie->x() - zombie->offset <= 33)
        {
            this->go = true;
            this->direction = 0;
            this->setMovie(anim_attack);
        }
    }
}

zSquash::~zSquash()
{
    delete this->anim;
    delete this->anim_attack;
}

