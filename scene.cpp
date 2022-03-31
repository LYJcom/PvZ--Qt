#include "scene.h"
#include <QMessageBox>

Scene::Scene(QWidget* parent) : Object(parent)
{

}

Scene::~Scene()
{
    while (!Zombies.empty())
    {
        delete Zombies[0];                 //delete QList
        Zombies.removeAt(0);
    }
    while (!Plants.empty())
    {
        delete Plants[0];
        Plants.removeAt(0);
    }
    while (!FlyingObjects.empty())
    {
        delete FlyingObjects[0];
        FlyingObjects.removeAt(0);
    }
    while (!Anims.empty())
    {
        delete Anims[0];
        Anims.removeAt(0);
    }
    while (!Bonuses.empty())
    {
        delete Bonuses[0];
        Bonuses.removeAt(0);
    }
    while (!Cards.empty())
    {
        delete Cards[0];
        Cards.removeAt(0);
    }
    if (!(this->backgroundMusic == nullptr)) delete this->backgroundMusic;
    if (!(this->SunFront == nullptr)) delete this->SunFront;
    if (!(this->SunBack == nullptr)) delete this->SunBack;
    if (!(this->sunback == nullptr)) delete this->sunback;
    if (!(this->timer == nullptr)) delete this->timer;
    if (!(this->ScoreFront == nullptr)) delete this->ScoreFront;
    if (!(this->Score == nullptr)) delete this->Score;
    if (!(this->ScoreBack == nullptr)) delete this->ScoreBack;
    if (!(this->scoreback == nullptr)) delete this->scoreback;
    if (!(this->Menu == nullptr)) delete this->Menu;
    if (!(this->menu == nullptr)) delete this->menu;
    if (!(this->Note == nullptr)) delete this->Note;
    if (!(this->note == nullptr)) delete this->note;
}

void Scene::mouseMoveEvent(QMouseEvent* event)
{
    m = event->pos();
    if (this->currentCard != nullptr)
    {
        this->currentCard->move(m + QPoint(-40, 1));
    }
}

void Scene::mousePressEvent(QMouseEvent *event)
{
    QPoint m_cell = this->getCell(); //获取光标位置（行列）
    if (event->button() == Qt::LeftButton) //按下左键
    {
        if ((m_cell.x() > -1) && (this->currentCard != nullptr)) //已选中植物状态
        {
            if(this->currentCard->pumpkin)
            {
                for (int i = 0; i < Plants.count(); i++)
                {
                    if ((Plants[i]->pumpkin) && (Plants[i]->raw == m_cell.y()) && (Plants[i]->column == m_cell.x()) && this->currentCard->plantIndex > 0)
                    {
                        return;
                    }
                }
            }
            else
            {
                for (int i = 0; i < Plants.count(); i++)
                {
                    if (!(Plants[i]->pumpkin) && (Plants[i]->raw == m_cell.y()) && (Plants[i]->column == m_cell.x()) && this->currentCard->plantIndex > 0)
                    {
                        return;
                    }
                }
            }
            QSound::play(":/Sound/rc/Place.wav");
            this->currentCard->setGeometry(0, 0, 90, 60);
            this->currentCard->move(this->currentPos);
            this->currentCard->setMovie(this->currentCard->anim0);
            if(!this->currentCard->shovel)
                this->currentCard->frontText->show();
            this->putPlant(m_cell);
        }
    }
    else
    {
        if (this->currentCard != nullptr)
        {
            this->currentCard->setGeometry(0, 0, 90, 60);
            this->currentCard->move(this->currentPos);
            this->currentCard->setMovie(this->currentCard->anim0);
            if(!this->currentCard->shovel)
                this->currentCard->frontText->show();
        }
        this->currentCard = nullptr;
    }
}
QPoint Scene::getCell()
{
    if (this->rect.contains(this->m))
    {
        return QPoint((this->m.x() - this->rect.left()) / this->cellSize.x(),
                      (this->m.y() - this->rect.top()) / this->cellSize.y());
    }
    else
    {
        return QPoint(-1, -1);
    }
}

void Scene::removeDeath()
{
    int p = 0;
    while (p < Plants.count())
    {
        if (!(Plants[p]->alive))
        {
            delete (Plants[p]);
            Plants.removeAt(p);
        }
        else
        {
            p++;
        }
    }
    for (int i = 0; i < 6; i++)
    {
        this->hasEnemy[i] = false;
    }
    p = 0;
    while (p < Zombies.count())
    {
        if (!(Zombies[p]->alive))
        {
            delete (Zombies[p]);
            Zombies.removeAt(p);
        }
        else
        {
            this->hasEnemy[Zombies[p]->raw] = true;
            p++;
        }
    }
    p = 0;
    while (p < FlyingObjects.count())
    {
        if (!(FlyingObjects[p]->alive))
        {
            delete (FlyingObjects[p]);
            FlyingObjects.removeAt(p);
        }
        else
        {
            p++;
        }
    }
    p = 0;
    while (p < Anims.count())
    {
        if (!(Anims[p]->alive))
        {
            delete (Anims[p]);
            Anims.removeAt(p);
        }
        else
        {
            p++;
        }
    }
    p = 0;
    while (p < Bonuses.count())
    {
        if (!(Bonuses[p]->alive))
        {
            delete (Bonuses[p]);
            Bonuses.removeAt(p);
        }
        else
        {
            p++;
        }
    }
}

void Scene::act()
{
    Object* i;
    foreach(i, Zombies)
    {
        i->act();
    }
    foreach(i, Plants)
    {
        i->act();
    }
    foreach(i, FlyingObjects)
    {
        i->act();
    }
    foreach(i, Anims)
    {
        i->act();
    }
    foreach(i, Bonuses)
    {
        i->act();
    }
    foreach(i, Cards)
    {
        i->act();
    }
}

void Scene::createZombie()
{
    if (this->threat < 15000)
    {
        this->threat ++;
    }
    if (this->Zombies.count() < (this->threat / 1200))
    {
        if (this->threat < 5000)
        {
            this->putZombie(QRandomGenerator::global()->bounded(5), 0);
        }
        else
        {
            this->putZombie(QRandomGenerator::global()->bounded(5), QRandomGenerator::global()->bounded(9));
        }
    }
}

void Scene::judge()
{
    if (this->TimerLose > 1)
    {
        this->TimerLose --;
    }
    else
    {
        if (this->TimerLose == 1)
        {
            emit toTitle();
        }
        else
        {
            Zombie* zombie;
            foreach(zombie, Zombies)
            {
                if (zombie->x() + zombie->offset < 180)
                {
                    this->currentCard = nullptr;
                    while (!Cards.empty())
                    {
                        delete Cards[0];
                        Cards.removeAt(0);
                    }
                    this->SunBack->hide();
                    this->SunFront->hide();
                    this->move(0, 0);
                    this->TimerLose = 100;
                    return;
                }
            }
        }
    }
}

void Scene::uiSetup()
{

}

void Scene::putPlant(QPoint t_cell)
{
    Plant* plant;
    switch (this->currentCard->plantIndex)
    {
    case 0: //铲子
        for (int i = 0; i < Plants.count(); i++)
        {
            if ((Plants[i]->raw == t_cell.y()) && (Plants[i]->column == t_cell.x()))
            {
                delete Plants[i];
                Plants.removeAt(i);
                this->currentCard->move(this->currentPos);
                this->currentCard = nullptr;
                return;
            }
        }
        this->currentCard = nullptr;
        return;
        break;
    case 1:
        plant = new zSunFlower(this);
        break;
    case 2:
        plant = new zPeaShooter(this);
        break;
    case 3:
        plant = new zWallNut(this);
        break;
    case 4:
        plant = new zRepeater(this);
        break;
    case 5:
        //plant = new zPotatoMine(this);
        plant = new zPumpKin(this);
        break;
    case 6:
        //plant = new zFireTree(this);
        plant = new zTallNut(this);
        break;
    case 7:
        plant = new zCherryBomb(this);
        break;
    case 8:
        plant = new zIcePeaShooter(this);
        break;
    case 9:
        //plant = new zMushroom(this);
        plant = new zGarlic(this);
        break;
    case 10:
        plant = new zSquash(this);
    }
    if(this->currentCard->plantIndex == 10) //窝瓜
        plant->setGeometry(this->rect.x() + this->cellSize.x() * t_cell.x(), this->rect.y() - 150 + this->cellSize.y() * t_cell.y(), 100, 230);
    else if(this->currentCard->plantIndex == 6) //高坚果
        plant->setGeometry(this->rect.x() + 5 + this->cellSize.x() * t_cell.x(), this->rect.y() - 30 + this->cellSize.y() * t_cell.y(), 100, 120);
    else if(this->currentCard->plantIndex == 5) //南瓜头
        plant->setGeometry(this->rect.x() + 5 + this->cellSize.x() * t_cell.x(), this->rect.y() - 60 + this->cellSize.y() * t_cell.y(), 100, 230);
    else
        plant->setGeometry(this->rect.x() + 10 + this->cellSize.x() * t_cell.x(), this->rect.y() - 15 + this->cellSize.y() * t_cell.y(), 120, 100);
    //plant->setGeometry(this->rect.x() + 10 + this->cellSize.x() * t_cell.x(), this->rect.y() - 15 + this->cellSize.y() * t_cell.y(), 120, 230);
    Plant* pump;
    foreach(pump, this->Plants)
    {
        if(pump->pumpkin && pump->raw == t_cell.y() && pump->column == t_cell.x())
        {
            plant->stackUnder(pump);
            break;
        }
    }
    plant->raw = t_cell.y();
    plant->column = t_cell.x();
    this->Plants.append(plant);
    this->sunPoint -= this->currentCard->sunPoint;
    this->currentCard->frame = this->currentCard->frame_max;
    this->currentCard = nullptr;
}

void Scene::putZombie(int raw, int type)
{
    Zombie* zombie;
    switch(type)
    {
    case 0:
        zombie = new zCommonZombie(this, 0);
        break;
    case 1:
        zombie = new zCommonZombie(this, 1);
        break;
    case 2:
        zombie = new zCommonZombie(this, 2);
        break;
    case 3:
        zombie = new zCommonZombie(this, 3);
        break;
    case 4:
        zombie = new zCommonZombie(this, 4);
        break;
    case 5:
        zombie = new zPoleZombie(this);
        break;
    case 6:
        zombie = new zNewsZombie(this);
        break;
    case 7:
        zombie = new zCatapultZombie(this);
        break;
    case 8:
        zombie = new zBoxZombie(this);
        break;
    }
    zombie->raw = raw;
    //zombie->setGeometry(950, zombie->raw * 100 - 25, 340, 200);
    zombie->setGeometry(950, zombie->raw * 100 - 25, 350, 200);
    this->Zombies.append(zombie);
}


zLawnScene::zLawnScene(QWidget* parent) : Scene(parent)
{
    this->setMouseTracking(true);
    this->grabKeyboard();              //limit keyboard input

    backgroundMusic = new QSound(":/Sound/rc/GameBackgroundMusic.wav");
    backgroundMusic->setLoops(QSound::Infinite);
    this->setGeometry(-120, 0, 1400, 600);
    this->cellSize = QPoint(81, 100);
    this->rect = QRect(250, 85, 729, 500);
    this->setMovie(this->background);
    this->background->start();
    this->show();
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(onTimer()));
    timer->start(20);
    this->uiSetup();
}

zLawnScene::~zLawnScene()
{
    delete this->background;
}

void zLawnScene::uiSetup()
{
    backgroundMusic->play();
    SunBack->setGeometry(120, 0, 123, 34);
    sunback->setScaledSize(SunBack->size());
    sunback->start();
    SunBack->show();
    SunBack->setMovie(sunback);
    SunFront->setGeometry(164, 6, 65, 30);
    SunFront->setFont(QFont("黑体", 20, QFont::Bold));
    SunFront->setText("50");
    SunFront->setStyleSheet("color:black");
    SunFront->setAlignment(Qt::AlignHCenter);
    SunFront->show();
    SunFront->raise(); //移到重叠画面顶部

    ScoreBack->setGeometry(510, 0, 200, 50);
    scoreback->setScaledSize(ScoreBack->size());
    scoreback->start();
    ScoreBack->show();
    ScoreBack->setMovie(scoreback);
    Score->setGeometry(520, 13, 100, 30);
    Score->setFont(QFont("黑体", 20, QFont::Bold));
    Score->setText("SCORE:");
    Score->setStyleSheet("color:black");
    Score->setAlignment(Qt::AlignHCenter);
    Score->show();
    Score->raise(); //移到重叠画面顶部
    ScoreFront->setGeometry(600, 10, 100, 30);
    ScoreFront->setFont(QFont("黑体", 25, QFont::Bold));
    ScoreFront->setText("0");
    ScoreFront->setStyleSheet("color:black");
    ScoreFront->setAlignment(Qt::AlignHCenter);
    ScoreFront->show();
    ScoreFront->raise(); //移到重叠画面顶部

    Help->setGeometry(420, 423, 300, 100);
    Help->setFont(QFont("黑体", 50, QFont::Bold));
    Help->setText("空格键继续");
    Help->setStyleSheet("color:black");
    Help->setAlignment(Qt::AlignHCenter);
    Help->hide();
    Menu->setGeometry(370, 100, 400, 400);
    menu->setScaledSize(Menu->size());
    menu->start();
    Menu->hide();
    Menu->setMovie(menu);
    Note->setGeometry(405, 180, 330, 220);
    note->setScaledSize(Note->size());
    note->start();
    Note->hide();
    Note->setMovie(note);

    exit->setGeometry(950, 0, 60, 60);
    exit->setFlat(true);
    exit->setIcon(QIcon(":/Interface/rc/Leave.png"));
    exit->setIconSize(QSize(60,60));
    exit->setStyleSheet("background: transparent");
    exit->setCursor(Qt::PointingHandCursor);
    connect(exit, SIGNAL(clicked()), this, SLOT(leave()));
    exit->show();
    exit->raise();
    Card *card = new zSunFlowerCard(this);
    card->setIndex(0);
    Cards.append(card);
    Card *card_2 = new zPeaShooterCard(this);
    card_2->setIndex(1);
    Cards.append(card_2);
    Card *card_3 = new zWallNutCard(this);
    card_3->setIndex(2);
    Cards.append(card_3);
    Card *card_4 = new zIcePeaShooterCard(this);
    card_4->setIndex(3);
    Cards.append(card_4);
    Card *card_5 = new zRepeaterCard(this);
    card_5->setIndex(4);
    Cards.append(card_5);
    Card *card_6 = new zPumpKinCard(this);
    card_6->setIndex(5);
    Cards.append(card_6);
    /*Card *card_6 = new zPotatoMineCard(this);
    card_6->setIndex(5);
    Cards.append(card_6);
    Card *card_7 = new zFireTreeCard(this);
    card_7->setIndex(6);
    Cards.append(card_7);*/
    Card *card_7 = new zCherryBombCard(this);
    card_7->setIndex(6);
    Cards.append(card_7);
    Card *card_8 = new zTallNutCard(this);
    card_8->setIndex(7);
    Cards.append(card_8);
    Card *card_9 = new zGarlicCard(this);
    card_9->setIndex(8);
    Cards.append(card_9);
    Card *card_10 = new zSquashCard(this);
    card_10->setIndex(9);
    Cards.append(card_10);

    Card *shovel = new zShovel(this);
    Cards.append(shovel);
}

void zLawnScene::keyPressEvent(QKeyEvent *event)
{
    switch(event->key())
    {
    case Qt::Key_1:
        this->putZombie(QRandomGenerator::global()->bounded(5), 0);
        break;
    case Qt::Key_2:
        this->putZombie(QRandomGenerator::global()->bounded(5), 1);
        break;
    case Qt::Key_3:
        this->putZombie(QRandomGenerator::global()->bounded(5), 2);
        break;
    case Qt::Key_4:
        this->putZombie(QRandomGenerator::global()->bounded(5), 3);
        break;
    case Qt::Key_5:
        this->putZombie(QRandomGenerator::global()->bounded(5), 4);
        break;
    case Qt::Key_6:
        this->putZombie(QRandomGenerator::global()->bounded(5), 5);
        break;
    case Qt::Key_7:
        this->putZombie(QRandomGenerator::global()->bounded(5), 6);
        break;
    case Qt::Key_8:
        this->sunPoint += 100;
        break;
    case Qt::Key_9:
        this->putZombie(QRandomGenerator::global()->bounded(5), 8);
        break;
    case Qt::Key_0:
        this->putZombie(QRandomGenerator::global()->bounded(5), 7);
        break;
    case Qt::Key_Escape:
        emit toTitle();
        break;
    case Qt::Key_Space:
        if(shouldstop)
        {
            this->Menu->hide();
            this->Help->hide();
            this->Note->hide();
            this->shouldstop = false;
        }
        else
        {
            this->Menu->show();
            this->Menu->raise();
            this->Help->show();
            this->Help->raise();
            this->Note->show();
            this->Note->raise();
            this->shouldstop = true;
        }
        break;
    }
}

void zLawnScene::onTimer()
{
    while(this->shouldstop)
    {
        QCoreApplication::processEvents();
    }
    this->removeDeath();
    this->act();
    this->SunFront->setText(QString::number(this->sunPoint));
    this->ScoreFront->setText(QString::number(this->score));
    this->createZombie();
    if (QRandomGenerator::global()->bounded(777) < 1)
    {
        Bonus* sun = new zSunFall(this);
        Bonuses.append(sun);
    }
    this->exit->raise();
    this->judge();
}

void zLawnScene::leave()
{
    emit toTitle();
}





zEndScene::zEndScene(QWidget* parent) : Scene(parent)
{
    backgroundMusic = new QSound(":/Sound/rc/Loonboon.wav");
    backgroundMusic->setLoops(QSound::Infinite);
    backgroundMusic->play();

    this->setGeometry(-120, 0, 1400, 600);
    this->cellSize = QPoint(81, 100);
    this->rect = QRect(250, 85, 729, 500);
    this->setMovie(this->background);
    this->background->start();
    this->show();

    Dave->setGeometry(100, 100, 309, 519);
    Dave_1->setScaledSize(Dave->size());
    Dave_2->setScaledSize(Dave->size());
    Dave_1->start();
    Dave_2->start();
    Dave->setMovie(Dave_1);
    Dave->show();

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(onTimer()));
    timer->start(20);
}
zEndScene::~zEndScene()
{
    delete this->background;
    delete this->Dave;
    delete this->Dave_1;
    delete this->Dave_2;
}

void zEndScene::onTimer()
{
    if (this->Dave_1->currentFrameNumber() >= (this->Dave_1->frameCount() - 1))
    {
        this->Dave_1->stop();
        Dave->setMovie(Dave_2);
    }
}






























zDarkScene::zDarkScene(QWidget* parent) : Scene(parent)
{
    this->setMouseTracking(true);
    this->grabKeyboard();              //limit keyboard input

    this->setGeometry(-120, 0, 1400, 600);
    this->cellSize = QPoint(81, 100);
    this->rect = QRect(250, 85, 729, 500);
    this->setMovie(this->background);
    this->background->start();
    this->show();
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(onTimer()));
    timer->start(20);
    this->uiSetup();
}

zDarkScene::~zDarkScene()
{
    delete this->background;
}

void zDarkScene::uiSetup()
{
    SunBack->setGeometry(120, 0, 123, 34);
    sunback->start();
    SunBack->show();
    SunBack->setMovie(sunback);
    SunFront->setGeometry(160, 0, 65, 30);
    SunFront->setFont(QFont("Calibri", 16));
    SunFront->setText("50");
    SunFront->setAlignment(Qt::AlignHCenter);
    SunFront->show();
    SunFront->raise();
    exit->setGeometry(950, 0, 60, 60);
    exit->setFlat(true);
    exit->setIcon(QIcon(":/Interface/rc/Leave.png"));
    exit->setIconSize(QSize(60,60));
    exit->setStyleSheet("background: transparent");
    exit->setCursor(Qt::PointingHandCursor);
    connect(exit, SIGNAL(clicked()), this, SLOT(leave()));
    exit->show();
    exit->raise();
    Card *card = new zSunFlowerCard(this);
    card->setIndex(1);
    Cards.append(card);
    Card *card_2 = new zPeaShooterCard(this);
    card_2->setIndex(2);
    Cards.append(card_2);
    Card *card_3 = new zWallNutCard(this);
    card_3->setIndex(3);
    Cards.append(card_3);
    Card *card_4 = new zRepeaterCard(this);
    card_4->setIndex(5);
    Cards.append(card_4);
    Card *card_5 = new zPotatoMineCard(this);
    card_5->setIndex(6);
    Cards.append(card_5);
    Card *card_6 = new zFireTreeCard(this);
    card_6->setIndex(7);
    Cards.append(card_6);
    Card *card_7 = new zCherryBombCard(this);
    card_7->setIndex(8);
    Cards.append(card_7);
    Card *card_8 = new zIcePeaShooterCard(this);
    card_8->setIndex(4);
    Cards.append(card_8);
    Card *card_9 = new zMushroomCard(this);
    card_9->setIndex(0);
    Cards.append(card_9);
    Card *shovel = new zShovel(this);
    Cards.append(shovel);
    //this->music = new QSound(":/music/rc/Scene2.wav");
    //this->music->setLoops(-1);
    //this->music->play();
}

void zDarkScene::keyPressEvent(QKeyEvent *event)
{
    switch(event->key())
    {
    case Qt::Key_1:
        this->putZombie(QRandomGenerator::global()->bounded(5), 0);
        break;
    case Qt::Key_2:
        this->putZombie(QRandomGenerator::global()->bounded(5), 1);
        break;
    case Qt::Key_3:
        this->putZombie(QRandomGenerator::global()->bounded(5), 2);
        break;
    case Qt::Key_4:
        this->putZombie(QRandomGenerator::global()->bounded(5), 3);
        break;
    case Qt::Key_5:
        this->putZombie(QRandomGenerator::global()->bounded(5), 4);
        break;
    case Qt::Key_6:
        this->putZombie(QRandomGenerator::global()->bounded(5), 5);
        break;
    case Qt::Key_7:
        this->putZombie(QRandomGenerator::global()->bounded(5), 6);
        break;
    case Qt::Key_8:
        this->sunPoint += 100;
        break;
    case Qt::Key_9:
        //this->threat = 6001;
        break;
    case Qt::Key_Escape:
        emit toTitle();
        break;
    }
}

void zDarkScene::onTimer()
{
    this->removeDeath();
    this->act();
    this->createZombie();
    this->exit->raise();
    this->SunFront->setText(QString::number(this->sunPoint));
    this->judge();
}

void zDarkScene::leave()
{
    emit toTitle();
}



zStartScene::zStartScene(QWidget* parent) : Scene(parent)
{
    this->setGeometry(0, 0, 800, 600);
    this->setMovie(this->background);
    this->background->start();
    this->show();
    btn1->setStyleSheet("QLabel{border: 5px solid #000000;} QLabel:hover{border:10px solid #EE0000;}");
    btn2->setStyleSheet("QLabel{border: 5px solid #000000;} QLabel:hover{border:10px solid #EE0000;}");
    btn1->setMovie(lawn);
    lawn->start();
    btn2->setMovie(dark);
    dark->start();
    btn1->setGeometry(120, 205, 180, 180);
    btn2->setGeometry(500, 205, 180, 180);
    btn1->show();
    btn2->show();
    title->setText("Select a Scene");
    title->setGeometry(290, 0, 240, 100);
    title->setFont(QFont("Consolas", 18));
    title->show();


}

zStartScene::~zStartScene()
{
    delete this->background;
    delete this->lawn;
    delete this->dark;
    delete this->btn1;
    delete this->btn2;
    delete this->title;
}


void zStartScene::mousePressEvent(QMouseEvent *event)
{
    if (QRect(120, 205, 180, 180).contains(event->pos()))
    {
        emit toLawn();
    }
    if (QRect(500, 205, 180, 180).contains(event->pos()))
    {
        //emit toDarkLawn();
    }
}



zStartScreen::zStartScreen(QWidget* parent) : Scene(parent)
{
    this->setGeometry(0, 0, 800, 600);
    this->setMovie(this->background);
    this->background->start();
    this->show();
    this->front->setGeometry(0, 0, 800, 600);
    this->front->show();
    this->front->setStyleSheet("background: rgba(0,0,0,1)");
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(onTimer()));
    timer->start(20);
}

zStartScreen::~zStartScreen()
{
    delete this->background;
    delete this->front;
}

void zStartScreen::onTimer()
{
    if (frame > 0)
    {
        frame --;
        if (frame > 50)
        {
            this->front->setStyleSheet("background: rgba(0,0,0," + QString::number((frame - 50) / 50.0) +")");
        }
        if (frame < 30)
        {
            this->front->setStyleSheet("background: rgba(0,0,0," + QString::number((30 - frame) / 30.0) +")");
        }
    }
    else
    {
        emit toTitle();
    }
}
