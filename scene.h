#ifndef SCENE_H
#define SCENE_H

//#define SOUND

#include <QLabel>
#include <QPushButton>
#include <QMovie>
#include <QTimer>
#include <QDebug>
#include <QMouseEvent>
#include <QKeyEvent>
#include <QRandomGenerator>
#include <QSound>

#include "object.h"
#include "plant.h"
#include "zombie.h"
#include "bullet.h"
#include "anim.h"
#include "bonus.h"
#include "card.h"

class Object;
class Plant;
class Zombie;
class Bullet;
class Anim;
class Bonus;
class Card;

class Scene : public Object
{
    Q_OBJECT
public:
    explicit Scene(QWidget* parent = 0);
    ~Scene();
    QPoint getCell();

    QList<Zombie*> Zombies;
    QList<Plant*> Plants;
    QList<Bullet*> FlyingObjects;
    QList<Anim*> Anims;
    QList<Bonus*> Bonuses;
    QList<Card*> Cards;

    QPoint m;
    QPoint cellSize = QPoint(1, 1);
    QRect rect = QRect(0, 0, 1, 1);
    QRect screen = QRect(170, 0, 900, 600);

    QTimer* timer = nullptr;
    QSound* backgroundMusic = nullptr;
    QLabel* SunFront = new QLabel(this);
    QLabel* SunBack = new QLabel(this);
    QMovie* sunback = new QMovie(":/Interface/rc/SunBack.png");        //backgroud of value of sun

    QLabel* ScoreFront = new QLabel(this);
    QLabel* Score = new QLabel(this);
    QLabel* ScoreBack = new QLabel(this);
    QMovie* scoreback = new QMovie(":/Interface/rc/ScoreBoard.png");

    QLabel* Help = new QLabel(this);
    QLabel* Menu = new QLabel(this);
    QMovie* menu = new QMovie(":/Interface/rc/Menu.png");
    QLabel* Note = new QLabel(this);
    QMovie* note = new QMovie(":/Interface/rc/ZombieNote.png");

    void removeDeath(); //remove dead item
    void act();
    void createZombie();
    void judge();
    virtual void uiSetup();
    void putPlant(QPoint t_cell);
    void putZombie(int raw, int type);

    bool hasEnemy[6];
    int sunPoint = 50;
    int tempSunPoint;
    int threat = 0;
    int score = 0;
    int TimerLose = 0;
    Card* currentCard = nullptr;
    QPoint currentPos;
    bool shouldstop = false;
protected:
    void mouseMoveEvent(QMouseEvent* event);
    void mousePressEvent(QMouseEvent* event);
signals:
    void toTitle();
    void toLawn();
    //void toDarkLawn();
};

class zLawnScene : public Scene
{
    Q_OBJECT
public:
    explicit zLawnScene(QWidget* parent = 0);
    ~zLawnScene();
protected:
    void keyPressEvent(QKeyEvent *event);
private:
    QMovie* background = new QMovie(":/Background/rc/background1.jpg");
    QPushButton* exit = new QPushButton(this);
    QPoint cell;
    void uiSetup();
private slots:
    void onTimer();
    void leave();
};

class zEndScene : public Scene
{
    Q_OBJECT
public:
    explicit zEndScene(QWidget* parent = 0);
    ~zEndScene();
private:
    QMovie* background = new QMovie(":/Background/rc/background1.jpg");
    QLabel* Dave = new QLabel(this);
    QMovie* Dave_1 = new QMovie(":/Interface/rc/Dave_move.gif");
    QMovie* Dave_2 = new QMovie(":/Interface/rc/Dave.gif");
private slots:
    void onTimer();
};


class zStartScreen : public Scene
{
    Q_OBJECT
public:
    explicit zStartScreen(QWidget* parent = 0);
    ~zStartScreen();
private:
    QMovie* background = new QMovie(":/Background/rc/PvZ.jpg");
    QWidget* front = new QWidget(this);
    int frame = 100;
private slots:
    void onTimer();
};





class zStartScene : public Scene
{
    Q_OBJECT
public:
    explicit zStartScene(QWidget* parent = 0);
    ~zStartScene();
private:
    QMovie* background = new QMovie(":/Background/rc/Title.jpg");
    QMovie* lawn = new QMovie(":/Interface/rc/zombatar_background_crazydave.png");
    QMovie* dark = new QMovie(":/Interface/rc/zombatar_background_menu.png");
    QLabel* btn1 = new QLabel(this);
    QLabel* btn2 = new QLabel(this);
    QLabel* title = new QLabel(this);
    QLabel* UserName = new QLabel(this);
    QLabel* BestTime = new QLabel(this);
protected:
    void mousePressEvent(QMouseEvent *event);
};












class zDarkScene : public Scene
{
    Q_OBJECT
public:
    explicit zDarkScene(QWidget* parent = 0);
    ~zDarkScene();
protected:
    void keyPressEvent(QKeyEvent *event);
private:
    QMovie* background = new QMovie(":/Background/rc/background2.jpg");
    QPushButton* exit = new QPushButton(this);
    QPoint cell;
    void uiSetup();
private slots:
    void onTimer();
    void leave();
};

#endif // SCENE_H
