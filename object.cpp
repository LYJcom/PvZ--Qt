#include "object.h"

Object::Object(QWidget *parent) : QLabel(parent)
{
    this->setMouseTracking(true);
    this->scene = (Scene*)this->parent();
}
