#include "zombie.h"

Zombie::Zombie(QWidget* parent) : Object(parent)
{
    this->frozen_sound->setLoops(QSound::Infinite);
}

Zombie::~Zombie()
{
    delete this->frozen_sound;
}

void Zombie::act()
{

}

void Zombie::hit(int damage, bool silence)
{

}

void Zombie::ice()
{

}

//Type: 0 for Common Zombie
//      1 for Flag Zombie
//      2 for Cone Zombie
//      3 for Bucket Zombie
//      4 for Shield Zombie
zCommonZombie::zCommonZombie(QWidget* parent, int type) : Zombie(parent)
{
    switch (QRandomGenerator::global()->bounded(2))
    {
    case 0:
        this->walk = new QMovie(":/Zombies/rc/Zombie.gif");
        this->frozen = new QMovie(":/Zombies/rc/frozen_Zombie.gif");
        this->frozen->setSpeed(50);
        break;
    case 1:
        this->walk = new QMovie(":/Zombies/rc/Zombie_2.gif");
        this->frozen = new QMovie(":/Zombies/rc/Zombie_2_frozen.gif");
        this->frozen->setSpeed(50);
        break;
    }
    this->attack = new QMovie(":/Zombies/rc/ZombieAttack.gif");
    this->frozen_attack = new QMovie(":/Zombies/rc/frozen_ZombieAttack.gif");
    this->frozen_attack->setSpeed(50);
    this->paused = new QMovie(":/Zombies/rc/Zombie_0.gif");
    this->frozen_paused = new QMovie(":/Zombies/rc/frozen_Zombie_0.gif");
    this->frozen_paused->setSpeed(50);
    this->score = 50;
    switch (type)
    {
    case 0:
        this->prop = false;
        this->iron = false;
        this->offset = 75;
        break;
    case 1:
        this->prop = false;
        this->iron = false;
        this->offset = 90;
        delete this->walk;
        delete this->attack;
        this->walk = new QMovie(":/Zombies/rc/ZombieFlag.gif");
        this->frozen = new QMovie(":/Zombies/rc/frozen_ZombieFlag.gif");
        this->frozen->setSpeed(50);
        this->attack = new QMovie(":/Zombies/rc/ZombieFlagAttack.gif");
        this->frozen_attack = new QMovie(":/Zombies/rc/frozen_ZombieFlagAttack.gif");
        this->frozen->setSpeed(50);
        this->paused = new QMovie(":/Zombies/rc/FlagZombie_0.gif");
        this->frozen_paused = new QMovie(":/Zombies/rc/frozen_FlagZombie_0.gif");
        this->frozen_paused->setSpeed(50);
        break;
    case 2:
        this->prop = true;
        this->iron = false;
        this->prop_strength = 200;
        this->prop_walk = new QMovie(":/Zombies/rc/ZombieCone.gif");
        this->frozen = new QMovie(":/Zombies/rc/frozen_ZombieCone.gif");
        this->frozen->setSpeed(50);
        this->prop_attack = new QMovie(":/Zombies/rc/ZombieConeAttack.gif");
        this->frozen_attack = new QMovie(":/Zombies/rc/frozen_ZombieConeAttack.gif");
        this->frozen_attack->setSpeed(50);
        this->prop_paused = new QMovie(":/Zombies/rc/ZombieCone_0.gif");
        this->frozen_paused = new QMovie(":/Zombies/rc/frozen_ZombieCone_0.gif");
        this->frozen_paused->setSpeed(50);
        this->offset = 90;
        this->score = 75;
        break;
    case 3:
        this->prop = true;
        this->iron = true;
        this->prop_strength = 400;
        this->prop_walk = new QMovie(":/Zombies/rc/ZombieBucket.gif");
        this->frozen = new QMovie(":/Zombies/rc/frozen_ZombieBucket.gif");
        this->frozen->setSpeed(50);
        this->prop_attack = new QMovie(":/Zombies/rc/ZombieBucketAttack.gif");
        this->frozen_attack = new QMovie(":/Zombies/rc/frozen_ZombieBucketAttack.gif");
        this->frozen_attack->setSpeed(50);
        this->prop_paused = new QMovie(":/Zombies/rc/ZombieBucket_0.gif");
        this->frozen_paused = new QMovie(":/Zombies/rc/frozen_ZombieBucket_0.gif");
        this->frozen_paused->setSpeed(50);
        this->offset = 70;
        this->score = 100;
        break;
    case 4:
        this->prop = true;
        this->iron = true;
        this->shield = true;
        this->prop_strength = 400;
        this->prop_walk = new QMovie(":/Zombies/rc/ZombieShield.gif");
        this->prop_attack = new QMovie(":/Zombies/rc/ZombieShieldAttack.gif");
        this->prop_paused = new QMovie(":/Zombies/rc/ZombieShield_0.gif");
        this->offset = 60;
        this->score = 150;
        break;
    }
    this->speed = 0.25;
    this->strength = 200;
    this->xpos = 950;
    if (this->prop)
    {
        //prop_walk->setScaledSize(this->size());
        this->setMovie(this->prop_walk);
        this->walk->start();
        this->prop_walk->start();
        this->attack->start();
        this->prop_attack->start();
        this->frozen->setSpeed(50);
        this->frozen->start();
        this->frozen_attack->start();
        this->frozen_paused->start();
        this->paused->start();
        this->prop_paused->start();
    }
    else
    {
        //walk->setScaledSize(this->size());
        this->setMovie(this->walk);
        this->walk->start();
        this->attack->start();
        this->frozen->setSpeed(50);
        this->frozen_attack->setSpeed(50);
        this->frozen_paused->setSpeed(50);
        this->frozen->start();
        this->frozen_attack->start();
        this->frozen_paused->start();
        this->paused->start();
    }
    this->show();
}

zCommonZombie::~zCommonZombie()
{
    delete this->walk;
    delete this->attack;
    delete this->paused;
    delete this->frozen;
    delete this->frozen_attack;
    delete this->frozen_paused;
}

void zCommonZombie::act()
{
    this->raise();
    Zombie* zombie;
    foreach(zombie, this->scene->Zombies)
    {
        if(zombie->raw == this->raw + 1)
            this->stackUnder(zombie);
    }
    Plant* plant;
    foreach(plant, this->scene->Plants)
    {
        if(plant->raw == this->raw + 1)
            this->stackUnder(plant);
    }
    if(this->iced)
    {

        frozen_cnt += 20;
        if(frozen_cnt >= frozen_time)
        {
            this->iced = false;
            this->speed *= 2;
            frozen_cnt = 0;
#ifdef SOUND
            frozen_sound->stop();
#endif
            eatFrame_max /= 2;
        }
    }
    if(this->garlic)
    {
        this->xpos -= 0.1;
        this->move(this->xpos, this->y() + target);
        move_cnt++;
        if(move_cnt >= 100)
        {
            move_cnt = 0;
            garlic = false;
            target = 0;
            if(this->iced)
                this->setMovie(this->frozen);
            else if(this->prop)
                this->setMovie(this->prop_walk);
            else
                this->setMovie(this->walk);
        }
        return;
    }
    foreach (plant, this->scene->Plants)
    {
        //if ((qAbs(plant->x() - this->x() - 55 - this->offset) < 40) && ((this->raw) == (plant->raw)) && (this->alive))
        if (this->x() + 100 - plant->x() > 0 && this->x() + offset - plant->x() - 55 < 0 && ((this->raw) == (plant->raw)) && (this->alive))
        {
            if (this->eatFrame <= 0)
            {
#ifdef SOUND
                QSound::play(":/Sound/rc/Eat.wav");
#endif
                this->eatFrame = eatFrame_max;
            }
            this->eatFrame --;
            if (this->prop)
            {
                this->setMovie(this->prop_attack);
                if(this->iced)
                    this->setMovie(this->frozen_attack);
            }
            else
            {
                this->setMovie(this->attack);
                if(this->iced)
                    this->setMovie(this->frozen_attack);
            }
            Plant* pump;
            foreach(pump, this->scene->Plants)
            {
                if(pump->pumpkin && pump->raw == plant->raw && pump->column == plant->column)
                {
                    pump->hit(1);
                    return;
                }
            }
            plant->hit(1);
            if(plant->garlic)
            {
                if(this->iced)
                    this->setMovie(this->frozen_paused);
                else if(this->prop)
                    this->setMovie(this->prop_paused);
                else
                    this->setMovie(this->paused);
                this->garlic = true;
                if(plant->raw == 0)
                    this->target = 1;
                else if(plant->raw == 4)
                    this->target = -1;
                else
                {
                    switch (QRandomGenerator::global()->bounded(2))
                    {
                    case 0:
                        this->target =  1;
                        break;
                    case 1:
                        this->target =  -1;
                        break;
                    }
                }
                this->raw += target;
            }
            return;
        }
    }
    if (this->prop)
    {
        this->setMovie(this->prop_walk);
        if(this->iced)
            this->setMovie(this->frozen);
    }
    else
    {
        this->setMovie(this->walk);
        if(this->iced)
            this->setMovie(this->frozen);
    }
    this->xpos -= this->speed;
    this->move(this->xpos, this->y());

}

void zCommonZombie::hit(int damage, bool silence)
{
    if (damage >= 200)
    {
        this->alive = false;
        this->scene->score += this->score;
        Anim* death_anim = new BurnDie(scene);
        death_anim->setGeometry(this->x() - 30, this->y() + 25, 180, 150);
        this->scene-> Anims.append(death_anim);
        if (!(this->prop_walk == nullptr))
        {
            delete this->prop_walk;
        }
        if (!(this->prop_attack == nullptr))
        {
            delete this->prop_attack;
        }
        if (!(this->prop_paused == nullptr))
        {
            delete this->prop_paused;
        }
        return;
    }
#ifdef SOUND
    if (!silence)
    {
        if(this->iron && this->prop)
            QSound::play(":/Sound/rc/ShieldHit.wav");
        else
            QSound::play(":/Sound/rc/PeaHit.wav");
    }
#endif
    if (this->prop)
    {
        this->prop_strength -= damage;
        if (this->prop_strength <= 0)
        {
            this->prop = false;
            this->xpos += 15; //gif偏移量(= 90-75)
            this->act();
            this->setMovie(this->walk);
            this->walk->start();
            delete this->prop_walk;
            delete this->prop_attack;
            delete this->prop_paused;
            this->prop_walk = nullptr;
            this->prop_attack = nullptr;
            this->prop_paused = nullptr;
            this->shield = false;
            delete this->frozen;
            delete this->frozen_attack;
            delete this->frozen_paused;
            this->frozen = new QMovie(":/Zombies/rc/frozen_Zombie.gif");
            this->frozen->setSpeed(50);
            this->frozen_attack = new QMovie(":/Zombies/rc/frozen_ZombieAttack.gif");
            this->frozen_attack->setSpeed(50);
            this->frozen_paused = new QMovie(":/Zombies/rc/frozen_Zombie_0.gif");
            this->frozen_paused->setSpeed(50);
            this->frozen_attack->start();
            this->frozen_paused->start();
            this->frozen->start();
        }
    }
    else
    {
        this->strength -= damage;
    }
    if (this->strength <= 0)
    {
        this->alive = false;
        this->scene->score += this->score;
        if(this->iced)
        {
            Anim* death_anim = new frozen_ZombieDie(scene);
            death_anim->setGeometry(this->x() - 30, this->y() + 25, 180, 150);
            this->scene->Anims.append(death_anim);
            Anim* death_head = new frozen_ZombieHead(scene);
            death_head->setGeometry(this->x() + 50, this->y() + 25, 180, 200);
            this->scene->Anims.append(death_head);
        }
        else
        {
            Anim* death_anim = new ZombieDie(scene);
            death_anim->setGeometry(this->x() - 30, this->y() + 25, 180, 150);
            this->scene->Anims.append(death_anim);
            Anim* death_head = new ZombieHead(scene);
            death_head->setGeometry(this->x() + 50, this->y() + 25, 180, 200);
            this->scene->Anims.append(death_head);
        }
    }
}

void zCommonZombie::ice()
{
    if ((!iced) && (!shield))
    {
        this->iced = true;
        this->speed /= 2;
        eatFrame_max *= 2;
#ifdef SOUND
        this->frozen_sound->play();
#endif
    }
    this->frozen_cnt = 0;
}



zPoleZombie::zPoleZombie(QWidget* parent) : Zombie(parent)
{
    this->setMovie(this->run);
    this->run->start();
    this->walk->start();
    this->attack->start();
    this->paused->start();
    this->frozen_1->setSpeed(50);
    this->frozen_2->setSpeed(50);
    this->frozen_attack->setSpeed(50);
    this->frozen_paused->setSpeed(50);
    this->frozen_1->start();
    this->frozen_2->start();
    this->frozen_attack->start();
    this->frozen_paused->start();
    this->speed = 0.5;
    this->strength = 200;
    this->xpos = 950;
    this->show();
    this->offset = 180;
    this->score = 100;
}

zPoleZombie::~zPoleZombie()
{
    delete this->walk;
    delete this->attack;
    delete this->run;
    delete this->jump_1;
    delete this->jump_2;
    delete this->paused;
    delete this->frozen_1;
    delete this->frozen_2;
    delete this->frozen_attack;
    delete this->frozen_paused;
    delete this->frozen_jump_1;
    delete this->frozen_jump_2;
}

void zPoleZombie::act()
{
    this->raise();
    Zombie* zombie;
    foreach(zombie, this->scene->Zombies)
    {
        if(zombie->raw == this->raw + 1)
            this->stackUnder(zombie);
    }
    Plant* plant;
    foreach(plant, this->scene->Plants)
    {
        if(plant->raw == this->raw + 1)
            this->stackUnder(plant);
    }

    if(this->iced)
    {
        frozen_cnt += 20;
        if(frozen_cnt >= frozen_time)
        {
            this->iced = false;
            this->speed *= 2;
            frozen_cnt = 0;
#ifdef SOUND
            frozen_sound->stop();
#endif
            eatFrame_max /= 2;
        }
    }
    if(this->garlic)
    {
        this->xpos -= 0.1;
        this->move(this->xpos, this->y() + target);
        move_cnt++;
        if(move_cnt >= 100)
        {
            move_cnt = 0;
            garlic = false;
            target = 0;
            this->setMovie(this->walk);
            if(this->iced)
                this->setMovie(this->frozen_2);
        }
        return;
    }

    if (this->jumping_1)
    {
        if(this->iced)
        {
            if (this->frozen_jump_2->currentFrameNumber() >= (this->jump_2->frameCount() - 1))
            {
                this->jump_2->stop();
                this->jumping_1 = false;
                this->is_jumping = false;
                this->speed /= 2;
            }
        }
        else
        {
            if (this->jump_2->currentFrameNumber() >= (this->jump_2->frameCount() - 1))
            {
                this->jump_2->stop();
                this->jumping_1 = false;
                this->is_jumping = false;
                this->speed /= 2;
            }
        }
        return;
    }
    else if ((this->jumping) && !(this->jumping_1))
    {
        if(this->iced && (this->frozen_jump_1->currentFrameNumber() == (this->frozen_jump_1->frameCount() - 1)))
        {
            this->frozen_jump_1->stop();
            this->setMovie(this->frozen_jump_2);
            this->frozen_jump_2->start();

            if(this->success)
                this->xpos -= 110;
            //else
                //this->xpos -= 40;
            this->move(this->xpos, this->y());
            this->jumping_1 = true;
            this->jumping = false;
            return;
        }
        else if(!(this->iced) && (this->jump_1->currentFrameNumber() == (this->jump_1->frameCount() - 1)) && !(this->jumping_1))
        {
            this->jump_1->stop();
            this->setMovie(this->jump_2);
            this->jump_2->start();

            if(this->success)
                this->xpos -= 110;
            //else
                //this->xpos -= 15;
            this->move(this->xpos, this->y());
            this->jumping_1 = true;
            this->jumping = false;
            return;
        }
    }

    if (this->jumping)
    {
        return;
    }
    foreach (plant, this->scene->Plants)
    {
        if (this->x() + this->offset - plant->x() + 20 > 0 && this->x() + offset - plant->x() - 55 < 0 && ((this->raw) == (plant->raw)) && (this->alive))
        //if ((qAbs(plant->x() - this->x() - 55 - this->offset) < 40) && ((this->raw) == (plant->raw)) && (this->alive))
        {
            Plant* tallnut;
            foreach(tallnut, this->scene->Plants)
            {
                if(tallnut->tallnut && tallnut->raw == plant->raw && tallnut->column == plant->column)
                {
                    success = false;
                    break;
                }
            }
            if (this->pole)
            {
                this->pole = false;
                this->jumping = true;
                this->is_jumping = true;
                if(this->iced)
                {
                    this->setMovie(this->frozen_jump_1);
                    this->frozen_jump_1->start();
                }
                else
                {
                    this->setMovie(this->jump_1);
                    this->jump_1->start();
                }
                return;
            }
            else
            {
                if (this->eatFrame <= 0)
                {
#ifdef SOUND
                    QSound::play(":/Sound/rc/Eat.wav");
#endif
                    this->eatFrame = eatFrame_max;
                }
                this->eatFrame --;
                this->setMovie(this->attack);
                if(this->iced)
                    this->setMovie(this->frozen_attack);
                Plant* pump;
                foreach(pump, this->scene->Plants)
                {
                    if(pump->pumpkin && pump->raw == plant->raw && pump->column == plant->column)
                    {
                        pump->hit(1);
                        return;
                    }
                }
                plant->hit(1);
                if(plant->garlic)
                {
                    this->setMovie(this->paused);
                    if(this->iced)
                        this->setMovie(this->frozen_paused);
                    this->garlic = true;
                    if(plant->raw == 0)
                        this->target = 1;
                    else if(plant->raw == 4)
                        this->target = -1;
                    else
                    {
                        switch (QRandomGenerator::global()->bounded(2))
                        {
                        case 0:
                            this->target =  1;
                            break;
                        case 1:
                            this->target =  -1;
                            break;
                        }
                    }
                    this->raw += target;
                }
                return;
            }
        }
    }
    if (this->pole)
    {
        this->setMovie(this->run);
        if(this->iced)
            this->setMovie(this->frozen_1);
    }
    else
    {
        this->setMovie(this->walk);
        if(this->iced)
            this->setMovie(this->frozen_2);
    }
    this->xpos -= this->speed;
    this->move(this->xpos, this->y());
}

void zPoleZombie::hit(int damage, bool silence)
{
    if (damage >= 200)
    {
        this->alive = false;
        Anim* death_anim = new BurnDie(scene);
        death_anim->setGeometry(this->x() - 20 + this->offset, this->y() + 25, 180, 150);
        this->scene->Anims.append(death_anim);
        return;
    }
#ifdef SOUND
    if (!silence)
    {
        QSound::play(":/Sound/rc/PeaHit.wav");
    }
#endif
    this->strength -= damage;
    if (this->strength <= 0)
    {
        this->alive = false;
        if(this->iced)
        {
            Anim* death_anim = new zfrozen_PoleZombieDie(scene);
            death_anim->setGeometry(this->x() - 30, this->y(), 300, 200);
            this->scene->Anims.append(death_anim);
            Anim* death_head = new zfrozen_PoleZombieHead(scene);
            death_head->setGeometry(this->x(), this->y() - 50, 300, 300);
            this->scene->Anims.append(death_head);
        }
        else
        {
            Anim* death_anim = new zPoleZombieDie(scene);
            death_anim->setGeometry(this->x() - 30, this->y(), 300, 200);
            this->scene->Anims.append(death_anim);
            Anim* death_head = new zPoleZombieHead(scene);
            death_head->setGeometry(this->x(), this->y() - 50, 300, 300);
            this->scene->Anims.append(death_head);
        }
    }
}

void zPoleZombie::ice()
{
    if (!iced)
    {
        this->iced = true;
        this->speed /= 2;
        eatFrame_max *= 2;
#ifdef SOUND
        this->frozen_sound->play();
#endif
    }
    this->frozen_cnt = 0;
}



zNewsZombie::zNewsZombie(QWidget* parent) : Zombie(parent)
{
    this->shield = true;
    this->setMovie(this->paper_walk);
    this->paper_walk->start();
    this->walk->start();
    this->attack->start();
    this->paper_attack->start();
    this->frozen->setSpeed(50);
    this->frozen_attack->setSpeed(50);
    this->frozen_paused->setSpeed(50);
    this->frozen->start();
    this->frozen_attack->start();
    this->frozen_paused->start();
    this->paused_1->start();
    this->paused_2->start();
    this->speed = 0.25;
    this->strength = 200;
    this->paper_strength = 50;
    this->xpos = 950;
    this->show();
    this->offset = 20;
    this->score = 150;
    this->eatFrame_max = 27;
}

zNewsZombie::~zNewsZombie()
{
    delete this->walk;
    delete this->attack;
    delete this->paper_walk;
    delete this->paper_attack;
    delete this->lose_paper;
    delete this->paused_1;
    delete this->paused_2;
    delete this->frozen;
    delete this->frozen_attack;
    delete this->frozen_paused;
}

void zNewsZombie::act()
{
    this->raise();
    Zombie* zombie;
    foreach(zombie, this->scene->Zombies)
    {
        if(zombie->raw == this->raw + 1)
            this->stackUnder(zombie);
    }
    Plant* plant;
    foreach(plant, this->scene->Plants)
    {
        if(plant->raw == this->raw + 1)
            this->stackUnder(plant);
    }
    if(this->iced)
    {
        frozen_cnt += 20;
        if(frozen_cnt >= frozen_time)
        {
            this->iced = false;
            this->speed *= 2;
            frozen_cnt = 0;
#ifdef SOUND
            frozen_sound->stop();
#endif
            eatFrame_max /= 2;
        }
    }
    if(this->garlic)
    {
        this->xpos -= 0.1;
        this->move(this->xpos, this->y() + target);
        move_cnt++;
        if(move_cnt >= 100)
        {
            move_cnt = 0;
            garlic = false;
            target = 0;
            if(this->paper)
                this->setMovie(this->paper_walk);
            else
            {
                this->setMovie(this->walk);
                if(this->iced)
                    this->setMovie(this->frozen);
            }
        }
        return;
    }
    if (this->angrying)
    {
        if (this->lose_paper->currentFrameNumber() >= (this->lose_paper->frameCount() - 1))
        {
            this->lose_paper->stop();
            this->angrying = false;
            this->speed *= 2;
        }
        return;
    }
    foreach (plant, this->scene->Plants)
    {
        if ((qAbs(plant->x() - this->x() - 55 - this->offset) < 40) && ((this->raw) == (plant->raw)) && (this->alive))
        {
            if (this->angrying)
            {
                return;
            }
            else
            {
                if (this->eatFrame <= 0)
                {
#ifdef SOUND
                    QSound::play(":/Sound/rc/Eat.wav");
#endif
                    this->eatFrame = eatFrame_max;
                }
                this->eatFrame --;
                if (this->paper)
                {
                    this->setMovie(this->paper_attack);
                    Plant* pump;
                    foreach(pump, this->scene->Plants)
                    {
                        if(pump->pumpkin && pump->raw == plant->raw && pump->column == plant->column)
                        {
                            pump->hit(1);
                            return;
                        }
                    }
                    plant->hit(1);
                    if(plant->garlic)
                    {
                        if(this->paper)
                            this->setMovie(this->paused_1);
                        else
                            this->setMovie(this->paused_2);
                        this->garlic = true;
                        if(plant->raw == 0)
                            this->target = 1;
                        else if(plant->raw == 4)
                            this->target = -1;
                        else
                        {
                            switch (QRandomGenerator::global()->bounded(2))
                            {
                            case 0:
                                this->target =  1;
                                break;
                            case 1:
                                this->target =  -1;
                                break;
                            }
                        }
                        this->raw += target;
                    }
                }
                else
                {
                    this->setMovie(this->attack);
                    if(this->iced)
                        this->setMovie(this->frozen_attack);
                    Plant* pump;
                    foreach(pump, this->scene->Plants)
                    {
                        if(pump->pumpkin && pump->raw == plant->raw && pump->column == plant->column)
                        {
                            pump->hit(1);
                            return;
                        }
                    }
                    plant->hit(2);
                    if(plant->garlic)
                    {
                        if(this->paper)
                            this->setMovie(this->paused_1);
                        else
                        {
                            this->setMovie(this->paused_2);
                            if(this->iced)
                                this->setMovie(this->frozen_paused);
                        }
                        this->garlic = true;
                        if(plant->raw == 0)
                            this->target = 1;
                        else if(plant->raw == 4)
                            this->target = -1;
                        else
                        {
                            switch (QRandomGenerator::global()->bounded(2))
                            {
                            case 0:
                                this->target =  1;
                                break;
                            case 1:
                                this->target =  -1;
                                break;
                            }
                        }
                        this->raw += target;
                    }
                }
                return;
            }
        }
    }
    if (this->paper)
    {
        this->setMovie(this->paper_walk);
    }
    else
    {
        this->setMovie(this->walk);
        if(this->iced)
            this->setMovie(this->frozen);
    }
    this->xpos -= this->speed;
    this->move(this->xpos, this->y());
}

void zNewsZombie::hit(int damage, bool silence)
{
    if (damage >= 200)
    {
        this->alive = false;
        this->scene->score += this->score;
        Anim* death_anim = new BurnDie(scene);
        death_anim->setGeometry(this->x() - 20 + this->offset, this->y() + 25, 180, 150);
        this->scene->Anims.append(death_anim);
        return;
    }
#ifdef SOUND
    if (!silence)
    {
        QSound::play(":/Sound/rc/PeaHit.wav");
    }
#endif
    if (this->paper)
    {
        this->paper_strength -= damage;
        if (this->paper_strength <= 0)
        {
            this->paper = false;
            this->angrying = true;
            this->setMovie(this->lose_paper);
            this->lose_paper->start();
            this->shield = false;
        }
    }
    else
    {
        this->strength -= damage;
        if (this->strength <= 0)
        {
            this->alive = false;
            this->scene->score += this->score;
            if(this->iced)
            {
                Anim* death_anim = new zfrozen_NewsDie(scene);
                death_anim->setGeometry(this->x() - 30, this->y() + 25, 180, 150);
                this->scene->Anims.append(death_anim);
                Anim* death_head = new zfrozen_NewsHead(scene);
                death_head->setGeometry(this->x() + 50, this->y() + 25, 180, 200);
                this->scene->Anims.append(death_head);
            }
            else
            {
                Anim* death_anim = new zNewsDie(scene);
                death_anim->setGeometry(this->x() - 30, this->y() + 25, 180, 150);
                this->scene->Anims.append(death_anim);
                Anim* death_head = new zNewsHead(scene);
                death_head->setGeometry(this->x() + 50, this->y() + 25, 180, 200);
                this->scene->Anims.append(death_head);
            }
        }
    }
}

void zNewsZombie::ice()
{
    if (!iced && !shield)
    {
        this->iced = true;
        this->speed /= 2;
        eatFrame_max *= 2;
#ifdef SOUND
        this->frozen_sound->play();
#endif
    }
    this->frozen_cnt = 0;
}

zCatapultZombie::zCatapultZombie(QWidget* parent) : Zombie(parent)
{
    this->shield = true;
    this->setMovie(this->walk);
    this->walk->start();
    this->speed = 0.25;
    this->strength = 400;
    this->xpos = 950;
    this->show();
    this->offset = 80;
    this->catapult = true;
    this->score = 300;
}

zCatapultZombie::~zCatapultZombie()
{
    delete this->walk;
}

void zCatapultZombie::act()
{
    this->raise();
    Zombie* zombie;
    foreach(zombie, this->scene->Zombies)
    {
        if(zombie->raw == this->raw + 1)
            this->stackUnder(zombie);
    }
    Plant* plant;
    foreach(plant, this->scene->Plants)
    {
        if(plant->raw == this->raw + 1)
            this->stackUnder(plant);
    }
    foreach(plant, this->scene->Plants)
    {
        if(qAbs(plant->x() - this->x() - 55 - this->offset) < 60 && this->raw == plant->raw && this->alive && plant->damage)
        {
            plant->alive = false;
        }
    }
    none_target = true;
    int flag = 0;
    for(int i = 0; i < 6; i++)
    {
        foreach(plant, this->scene->Plants)
        {
            if(plant->alive && plant->raw == this->raw && plant->x() < this->x() + this->offset && plant->column == i)
            {
                none_target = false;
                target = plant->x() + 20;
                flag = 1;
                break;
            }
        }
        if(flag)
            break;
    }


    if(this->x() >= 600 || this->num <= 0 || none_target)
    {
        this->xpos -= speed;
        this->move(this->xpos, this->y());
        return;
    }


    if(!none_target)
    {
        speed_cnt++;
        if(speed_cnt >= speed_shoot)
        {
            speed_cnt = 0;
            Ball* ball = new Ball(this->scene);
            ball->setGeometry(this->x() + this->offset, this->y() + 120, 60, 60);
            ball->setTarget(target);
            ball->raw = this->raw;
            this->scene->FlyingObjects.append(ball);
            num--;
        }
    }
}

void zCatapultZombie::hit(int damage, bool silence)
{
    if (damage >= 200)
    {
        this->alive = false;
        this->scene->score += this->score;
        Anim* death_anim = new BurnDie(scene);
        death_anim->setGeometry(this->x() + 60, this->y() + 25, 180, 150);
        this->scene->Anims.append(death_anim);
        return;
    }
#ifdef SOUND
    if (!silence)
    {
        QSound::play(":/Sound/rc/ShieldHit.wav");
    }
#endif
    this->strength -= damage;
    if (this->strength <= 0)
    {
        this->alive = false;
        this->scene->score += this->score;
    }
}

zBoxZombie::zBoxZombie(QWidget* parent) : Zombie(parent)
{
    this->setMovie(this->walk);
    this->walk->start();
    this->attack->start();
    this->frozen->setSpeed(50);
    this->frozen_attack->setSpeed(50);
    this->frozen_paused->setSpeed(50);
    this->frozen->start();
    this->frozen_attack->start();
    this->frozen_paused->start();
    this->paused->start();
    this->speed = 0.25;
    this->strength = 6400;
    this->xpos = 950;
    this->show();
    this->offset = 60;
    this->score = 300;
}

zBoxZombie::~zBoxZombie()
{
    delete this->walk;
    delete this->attack;
    delete this->paused;
    delete this->frozen;
    delete this->frozen_attack;
    delete this->frozen_paused;
}

void zBoxZombie::act()
{
    this->raise();
    Zombie* zombie;
    foreach(zombie, this->scene->Zombies)
    {
        if(zombie->raw == this->raw + 1)
            this->stackUnder(zombie);
    }
    Plant* plant;
    foreach(plant, this->scene->Plants)
    {
        if(plant->raw == this->raw + 1)
            this->stackUnder(plant);
    }
    if(this->iced)
    {
        frozen_cnt += 20;
        if(frozen_cnt >= frozen_time)
        {
            this->iced = false;
            this->speed *= 2;
            frozen_cnt = 0;
#ifdef SOUND
            frozen_sound->stop();
#endif
            eatFrame_max /= 2;
        }
    }
    int coin = QRandomGenerator::global()->bounded(300);
    if(!coin && this->x() <= 800)
    {
        this->setMovie(open_box);
        this->open_box->start();
        this->opening = true;
    }
    if(opening)
    {
        if (this->open_box->currentFrameNumber() >= (this->open_box->frameCount() - 1))
        {
            this->open_box->stop();
            this->alive = false;
            this->scene->score += this->score;
            Anim* boom = new BoxZombieBoom(scene);
            boom->setGeometry(this->x(), this->y() - 50, 306, 300);
            scene->Anims.append(boom);
            foreach(plant, this->scene->Plants)
            {
                if((qAbs(this->x() - plant->x() + this->offset + 50) < 140) && (qAbs(plant->raw - this->raw) <= 1))
                {
                    plant->alive = false;
                }
            }
            return;
        }
        return;
    }
    if(this->garlic)
    {
        this->xpos -= 0.1;
        this->move(this->xpos, this->y() + target);
        move_cnt++;
        if(move_cnt >= 100)
        {
            move_cnt = 0;
            garlic = false;
            target = 0;
            this->setMovie(this->walk);
            if(this->iced)
                this->setMovie(this->frozen);
        }
        return;
    }

    foreach (plant, this->scene->Plants)
    {
        if ((qAbs(plant->x() - this->x() - 55 - this->offset) < 40) && ((this->raw) == (plant->raw)) && (this->alive))
        {
            if (this->eatFrame <= 0)
            {
#ifdef SOUND
                QSound::play(":/Sound/rc/Eat.wav");
#endif
                this->eatFrame = eatFrame_max;
            }
            this->eatFrame --;

            this->setMovie(this->attack);
            if(this->iced)
                this->setMovie(this->frozen_attack);
            Plant* pump;
            foreach(pump, this->scene->Plants)
            {
                if(pump->pumpkin && pump->raw == plant->raw && pump->column == plant->column)
                {
                    pump->hit(1);
                    return;
                }
            }
            plant->hit(1);
            if(plant->garlic)
            {
                this->setMovie(this->paused);
                if(this->iced)
                    this->setMovie(this->frozen_paused);
                this->garlic = true;
                if(plant->raw == 0)
                    this->target = 1;
                else if(plant->raw == 4)
                    this->target = -1;
                else
                {
                    switch (QRandomGenerator::global()->bounded(2))
                    {
                    case 0:
                        this->target =  1;
                        break;
                    case 1:
                        this->target =  -1;
                        break;
                    }
                }
                this->raw += target;
            }

            return;
        }
    }

    this->setMovie(this->walk);
    if(this->iced)
        this->setMovie(this->frozen);

    this->xpos -= this->speed;
    this->move(this->xpos, this->y());
}

void zBoxZombie::hit(int damage, bool silence)
{
    if (damage >= 200)
    {
        this->alive = false;
        this->scene->score += this->score;
        Anim* death_anim = new BurnDie(scene);
        death_anim->setGeometry(this->x() + 60, this->y() + 25, 180, 150);
        this->scene->Anims.append(death_anim);
        return;
    }
#ifdef SOUND
    if (!silence)
    {
        QSound::play(":/Sound/rc/PeaHit.wav");
    }
#endif
    this->strength -= damage;
    if (this->strength <= 0)
    {
        this->alive = false;
        this->scene->score += this->score;
    }
}

void zBoxZombie::ice()
{
    if (!iced)
    {
        this->iced = true;
        this->speed /= 2;
        eatFrame_max *= 2;
#ifdef SOUND
        this->frozen_sound->play();
#endif
    }
    this->frozen_cnt = 0;
}
