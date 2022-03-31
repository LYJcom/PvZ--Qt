#ifndef BONUS_H
#define BONUS_H

#include <QWidget>
#include <QMovie>
#include <QMouseEvent>

#include "object.h"
#include "scene.h"

class Bonus : public Object
{
public:
    Bonus(QWidget* parent = 0);
    virtual void act();
};

class zSun : public Bonus
{
public:
    zSun(QWidget* parent = 0);
    ~zSun();
    void act();
    int frame;
    float level, speed, accelerate, x_speed = 0;
protected:
    void mousePressEvent(QMouseEvent *event);
private:
    QMovie* anim = new QMovie(":/Bonus/rc/Sun.gif");
};

class zSunFall : public Bonus
{
public:
    zSunFall(QWidget* parent = 0);
    ~zSunFall();
    void act();
    int frame;
    float level, speed; //落点高度、下落速度
protected:
    void mousePressEvent(QMouseEvent *event);
private:
    QMovie* anim = new QMovie(":/Bonus/rc/Sun.gif");
};

#endif // BONUS_H
