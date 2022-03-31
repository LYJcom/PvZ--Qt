#ifndef OBJECT_H
#define OBJECT_H

#include <QLabel>
#include <QMovie>
#include <QMouseEvent>

class Scene;

class Object : public QLabel
{
    Q_OBJECT
public:
    explicit Object(QWidget* parent = 0);
    bool alive = true;
    virtual void act()=0;
    int strength = 1;
    Scene* scene;
};

#endif // OBJECT_H
