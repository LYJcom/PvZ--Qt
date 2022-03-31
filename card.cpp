#include "card.h"

Card::Card(QWidget* parent) : Object(parent)
{
    this->setCursor(Qt::PointingHandCursor);

    frontText = new QLabel(this);
    frontText->setText("50");
    //frontText->setGeometry(70, 50, 30, 18);
    frontText->setGeometry(60, 40, 27, 18);
    frontText->setFont(QFont("黑体", 15));
    frontText->setStyleSheet("color:black;background:yellow");
    frontText->setAlignment(Qt::AlignHCenter);
    frontText->show();
    back = new QWidget(this);
    back->setStyleSheet("background-color: rgba(0, 0, 0, 50%);");
    back->show();
    back->raise();
    front = new QWidget(this);
    front->setStyleSheet("background-color: rgba(0, 0, 0, 50%);");
    front->show();
    front->raise();
    this->show();
    this->raise();
}

void Card::act()
{
    //this->setGeometry(125, 40 + 50 * id, 90, 60);
    if (this->frame > 0)
    {
        this->frame --;
    }
    this->transFront();
    this->raise();
}

void Card::setIndex(int index)
{
    id = index;
    this->setGeometry(125, 40 + 50 * index, 90, 60);
    //this->setGeometry(125, 40 + 60 * index, 105, 80); //卡片大小
}

void Card::transFront() //阴影遮盖
{
    //front->setGeometry(0, 16, 100, 54 * this->frame / this->frame_max);
    front->setGeometry(0, 9, 87, 54 * this->frame / this->frame_max);
    if (scene->sunPoint >= this->sunPoint)
    {
        back->setGeometry(0, 0, 0, 0);
    }
    else
    {
        //back->setGeometry(0, 16, 100, 54);
        back->setGeometry(0, 9, 87, 54);
    }
}

void Card::mousePressEvent(QMouseEvent* event)
{
    if (scene->currentCard != nullptr)
    {
        scene->currentCard->setGeometry(0, 0, 90, 60);
        scene->currentCard->move(scene->currentPos);
        scene->currentCard->setMovie(scene->currentCard->anim0);
        if(!this->scene->currentCard->shovel)
            scene->currentCard->frontText->show();
    }
    if (event->button() == Qt::LeftButton)
    {
        if (this->front->height() > 0)
        {
            QSound::play(":/Sound/rc/NotEnoughSun.wav");
            scene->currentCard = nullptr;
            return;
        }
        if (this->scene->sunPoint < this->sunPoint)
        {
            QSound::play(":/Sound/rc/NotEnoughSun.wav");
            scene->currentCard = nullptr;
            return;
        }
        QSound::play(":/Sound/rc/CardSelected.wav");
        scene->currentPos = this->pos();
        scene->currentCard = this;
        switch(this->plantIndex)
        {
        case 1: case 2: case 3: case 4: case 8:
            this->setGeometry(125, 40 + 60 * id, 75, 75); //卡片预览大小
            break;
        case 6:
            this->setGeometry(125, 40 + 60 * id, 105, 120); //卡片预览大小
            break;
        case 7:
            this->setGeometry(125, 40 + 60 * id, 112, 81); //卡片预览大小
            break;
        case 10:
            this->setGeometry(125, 40 + 60 * id, 100, 90); //卡片预览大小
        default:
            break;
        }
        this->setMovie(this->anim1);
        this->frontText->hide();
    }
    else
    {
        scene->currentCard = nullptr;
        this->setGeometry(125, 40 + 60 * id, 105, 80); //卡片大小
        this->setMovie(this->anim0);
        if(!this->shovel)
            scene->currentCard->frontText->show();
    }
}

Card::~Card()
{
    delete (this->back);
    delete (this->front);
    delete (this->frontText);
}

zSunFlowerCard::zSunFlowerCard(QWidget* parent) : Card(parent)
{
    anim0 = new QMovie(":/Cards/rc/card_Sunflower.png");
    anim1 = new QMovie(":/Cards/rc/SunFlower_0.gif");
    this->setMovie(anim0);
    anim0->start();
    anim1->start();
    this->frontText->setText("50");
    this->frame_max = 100;
    this->frame = 100;
    this->plantIndex = 1;
    this->sunPoint = 50;
}

zSunFlowerCard::~zSunFlowerCard()
{
    delete this->anim0;
    delete this->anim1;
}

zPeaShooterCard::zPeaShooterCard(QWidget* parent) : Card(parent)
{
    anim0 = new QMovie(":/Cards/rc/card_PeaShooter.png");
    anim1 = new QMovie(":/Cards/rc/PeaShooter_0.gif");
    this->setMovie(anim0);
    anim0->start();
    anim1->start();
    this->frontText->setText("100");
    this->frame_max = 100;
    this->frame = 100;
    this->plantIndex = 2;
    this->sunPoint = 100;
}

zPeaShooterCard::~zPeaShooterCard()
{
    delete this->anim0;
    delete this->anim1;
}

zWallNutCard::zWallNutCard(QWidget* parent) : Card(parent)
{
    anim0 = new QMovie(":/Cards/rc/card_WallNut.png");
    anim1 = new QMovie(":/Cards/rc/WallNut_0.gif");
    this->setMovie(anim0);
    anim0->start();
    anim1->start();
    this->frontText->setText("50");
    this->frame_max = 500;
    this->frame = 500;
    this->plantIndex = 3;
    this->sunPoint = 50;
}

zWallNutCard::~zWallNutCard()
{
    delete this->anim0;
    delete this->anim1;
}

zTallNutCard::zTallNutCard(QWidget* parent) : Card(parent)
{
    anim0 = new QMovie(":/Cards/rc/card_TallNut.png");
    anim1 = new QMovie(":/Cards/rc/TallNut_0.gif");
    this->setMovie(anim0);
    anim0->start();
    anim1->start();
    this->frontText->setText("125");
    this->frame_max = 500;
    this->frame = 500;
    this->plantIndex = 6;
    this->sunPoint = 125;
}

zTallNutCard::~zTallNutCard()
{
    delete this->anim0;
    delete this->anim1;
}

zRepeaterCard::zRepeaterCard(QWidget* parent) : Card(parent)
{
    anim0 = new QMovie(":/Cards/rc/card_Repeater.png");
    anim1 = new QMovie(":/Cards/rc/Repeater_0.gif");
    this->setMovie(anim0);
    anim0->start();
    anim1->start();
    this->frontText->setText("200");
    this->frame_max = 100;
    this->frame = 100;
    this->plantIndex = 4;
    this->sunPoint = 200;
}

zRepeaterCard::~zRepeaterCard()
{
    delete this->anim0;
    delete this->anim1;
}

zPotatoMineCard::zPotatoMineCard(QWidget* parent) : Card(parent)
{
    anim0 = new QMovie(":/Cards/rc/card_PotatoMine.png");
    anim1 = new QMovie(":/Cards/rc/PotatoMine_0.gif");
    this->setMovie(anim0);
    anim0->start();
    anim1->start();
    this->frontText->setText("25");
    this->frame_max = 500;
    this->frame = 500;
    this->plantIndex = 5;
    this->sunPoint = 25;
}

zPotatoMineCard::~zPotatoMineCard()
{
    delete this->anim0;
    delete this->anim1;
}

zFireTreeCard::zFireTreeCard(QWidget* parent) : Card(parent)
{
    anim0 = new QMovie(":/Cards/rc/card_FireTree.png");
    anim1 = new QMovie(":/Cards/rc/TorchWood_0.gif");
    this->setMovie(anim0);
    anim0->start();
    anim1->start();
    this->frontText->setText("175");
    this->frame_max = 300;
    this->frame = 300;
    this->plantIndex = 6;
    this->sunPoint = 175;
}

zFireTreeCard::~zFireTreeCard()
{
    delete this->anim0;
    delete this->anim1;
}

zCherryBombCard::zCherryBombCard(QWidget* parent) : Card(parent)
{
    anim0 = new QMovie(":/Cards/rc/card_CherryBomb.png");
    anim1 = new QMovie(":/Cards/rc/CherryBomb_0.gif");
    this->setMovie(anim0);
    anim0->start();
    anim1->start();
    this->frontText->setText("150");
    this->frame_max = 500;
    this->frame = 500;
    this->plantIndex = 7;
    this->sunPoint = 150;
}

zCherryBombCard::~zCherryBombCard()
{
    delete this->anim0;
    delete this->anim1;
}

zIcePeaShooterCard::zIcePeaShooterCard(QWidget* parent) : Card(parent)
{
    anim0 = new QMovie(":/Cards/rc/card_IcePeaShooter.png");
    anim1 = new QMovie(":/Cards/rc/SnowPea_0.gif");
    this->setMovie(anim0);
    anim0->start();
    anim1->start();
    this->frontText->setText("175");
    this->frame_max = 100;
    this->frame = 100;
    this->plantIndex = 8;
    this->sunPoint = 175;
}

zIcePeaShooterCard::~zIcePeaShooterCard()
{
    delete this->anim0;
    delete this->anim1;
}

zMushroomCard::zMushroomCard(QWidget* parent) : Card(parent)
{
    anim0 = new QMovie(":/Cards/rc/card_Mushroom.png");
    anim1 = new QMovie(":/Cards/rc/card_Mushroom.png");
    this->setMovie(anim0);
    anim0->start();
    anim1->start();
    this->frontText->setText("0");
    this->frame_max = 300;
    this->frame = 300;
    this->plantIndex = 9;
    this->sunPoint = 0;
}

zMushroomCard::~zMushroomCard()
{
    delete this->anim0;
    delete this->anim1;
}


zPumpKinCard::zPumpKinCard(QWidget* parent) : Card(parent)
{
    this->pumpkin = true;
    anim0 = new QMovie(":/Cards/rc/card_PumpKin.png");
    anim1 = new QMovie(":/Cards/rc/PumpKin_0.gif");
    this->setMovie(anim0);
    anim0->start();
    anim1->start();
    this->frontText->setText("125");
    this->frame_max = 500;
    this->frame = 500;
    this->plantIndex = 5;
    this->sunPoint = 125;
}

zPumpKinCard::~zPumpKinCard()
{
    delete this->anim0;
    delete this->anim1;
}

zGarlicCard::zGarlicCard(QWidget* parent) : Card(parent)
{
    anim0 = new QMovie(":/Cards/rc/card_Garlic.png");
    anim1 = new QMovie(":/Cards/rc/Garlic_0.gif");
    this->setMovie(anim0);
    anim0->start();
    anim1->start();
    this->frontText->setText("50");
    this->frame_max = 125;
    this->frame = 125;
    this->plantIndex = 9;
    this->sunPoint = 50;
}

zGarlicCard::~zGarlicCard()
{
    delete this->anim0;
    delete this->anim1;
}

zSquashCard::zSquashCard(QWidget* parent) : Card(parent)
{
    anim0 = new QMovie(":/Cards/rc/card_Squash.png");
    anim1 = new QMovie(":/Cards/rc/Squash_0.gif");
    this->setMovie(anim0);
    anim0->start();
    anim1->start();
    this->frontText->setText("50");
    this->frame_max = 125;
    this->frame = 125;
    this->plantIndex = 10;
    this->sunPoint = 50;
}

zSquashCard::~zSquashCard()
{
    delete this->anim0;
    delete this->anim1;
}

zShovel::zShovel(QWidget* parent) : Card(parent)
{
    this->shovel = true;
    anim0 = new QMovie(":/Cards/rc/Shovel.png");
    anim1 = new QMovie(":/Cards/rc/Shovel.png");
    this->setMovie(anim0);
    this->setGeometry(250, 5, 76, 34);
    anim0->start();
    anim1->start();
    this->frontText->setText("");
    this->frame_max = 1;
    this->frame = 0;
    this->plantIndex = 0;
    this->sunPoint = 0;
    this->id = -1;
    this->front->hide();
    this->back->hide();
    this->frontText->hide();
}

zShovel::~zShovel()
{
    delete this->anim0;
    delete this->anim1;
}
