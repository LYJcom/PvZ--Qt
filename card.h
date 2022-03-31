#ifndef CARD_H
#define CARD_H

#include <QLabel>
#include <QMovie>
#include <QMouseEvent>

#include "object.h"
#include "scene.h"

class Card : public Object
{
public:
    Card(QWidget* parent = 0);
    ~Card();
    int plantIndex;
    int id;
    int sunPoint = 50;
    int frame_max = 1, frame = 1;
    virtual void act();
    QWidget* front;
    QWidget* back;
    QLabel* frontText;
    QMovie* anim0;
    QMovie* anim1;
    void setIndex(int index);
    void transFront();
    bool pumpkin = false;
    bool shovel = false;
protected:
    void mousePressEvent(QMouseEvent* event);
};

class zSunFlowerCard : public Card
{
public:
    zSunFlowerCard(QWidget* parent = 0);
    ~zSunFlowerCard();
};

class zPeaShooterCard : public Card
{
public:
    zPeaShooterCard(QWidget* parent = 0);
    ~zPeaShooterCard();
};

class zWallNutCard : public Card
{
public:
    zWallNutCard(QWidget* parent = 0);
    ~zWallNutCard();
};

class zTallNutCard : public Card
{
public:
    zTallNutCard(QWidget* parent = 0);
    ~zTallNutCard();
};

class zRepeaterCard: public Card
{
public:
    zRepeaterCard(QWidget* parent = 0);
    ~zRepeaterCard();
};

class zPotatoMineCard: public Card
{
public:
    zPotatoMineCard(QWidget* parent = 0);
    ~zPotatoMineCard();
};

class zFireTreeCard: public Card
{
public:
    zFireTreeCard(QWidget* parent = 0);
    ~zFireTreeCard();
};

class zCherryBombCard: public Card
{
public:
    zCherryBombCard(QWidget* parent = 0);
    ~zCherryBombCard();
};

class zIcePeaShooterCard: public Card
{
public:
    zIcePeaShooterCard(QWidget* parent = 0);
    ~zIcePeaShooterCard();
};

class zMushroomCard : public Card
{
public:
    zMushroomCard(QWidget* parent = 0);
    ~zMushroomCard();
};

class zShovel : public Card
{
public:
    zShovel(QWidget* parent = 0);
    ~zShovel();
};

class zPumpKinCard : public Card
{
public:
    zPumpKinCard(QWidget* parent = 0);
    ~zPumpKinCard();
};

class zGarlicCard : public Card
{
public:
    zGarlicCard(QWidget* parent = 0);
    ~zGarlicCard();
};

class zSquashCard : public Card
{
public:
    zSquashCard(QWidget* parent = 0);
    ~zSquashCard();
};

#endif // CARD_H
