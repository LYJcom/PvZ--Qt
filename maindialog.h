#ifndef MAINDIALOG_H
#define MAINDIALOG_H

#include <QDialog>
#include <QMouseEvent>
#include <QVector>
#include <QPair>
#include <algorithm>

#include "scene.h"

/*bool cmp(QPair<QString, int> p1, QPair<QString, int> p2)
{
    return p1.second > p2.second;
}*/
namespace Ui {
class mainDialog;
}

class mainDialog : public QDialog
{
    Q_OBJECT

public:
    explicit mainDialog(QWidget *parent = 0);
    Scene* scene;
    QVector<QPair<QString, int> > database;
    int score;
    ~mainDialog();
protected:

private:
    Ui::mainDialog *ui;
public slots:
    void startLawn();
    //void startDark();
    void back();
    void SetName();
    void ShowRanking();
signals:
    void toRanking();
};

#endif // MAINDIALOG_H
