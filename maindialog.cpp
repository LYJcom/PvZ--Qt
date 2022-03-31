#include "maindialog.h"
#include<QFile>
#include<QTextStream>
#include<QInputDialog>
#include<QString>
#include<QApplication>
#include<QtDebug>
#include <QMessageBox>

mainDialog::mainDialog(QWidget *parent) :
    QDialog(parent)
{
    //setWindowIcon(QIcon(QStringLiteral(":/Interface/rc/mainlogo.png")));
    this->setMouseTracking(true);                //track mouse when mouse isn`t pressed
    this->setFixedSize(800, 600); //窗口大小，禁止缩放
    scene = new zStartScreen(this);
    connect(this->scene, SIGNAL(toTitle()), this, SLOT(startLawn()));
}

mainDialog::~mainDialog()
{
    delete ui;
}

void mainDialog::startLawn()
{
    this->setFixedSize(900, 600);
    this->score = scene->score;
    delete scene;                            //remember to delete !!!
    scene = new zLawnScene(this);
    connect(this->scene, SIGNAL(toTitle()), this, SLOT(SetName()));
}



void mainDialog::back()
{
    //this->setFixedSize(800, 600);
    this->setFixedSize(900, 600);
    this->score = scene->score;
    delete scene;
    //scene = new zStartScene(this);
    //scene = new zLawnScene(this);
    //connect(this->scene, SIGNAL(toLawn()), this, SLOT(startLawn()));
    //connect(this->scene, SIGNAL(toDarkLawn()), this, SLOT(startDark()));
    connect(this->scene, SIGNAL(toTitle()), this, SLOT(SetName()));
}

void mainDialog::SetName()
{
    this->score = scene->score;
    if(!(this->scene == nullptr))
        delete scene;
    scene = new zEndScene(this);

    connect(this, SIGNAL(toRanking()), this, SLOT(ShowRanking()));

    bool bOK = false;
    QString Name = QInputDialog::getText(this, "GameOver", "留下尊姓大名？", QLineEdit::Normal, "你的名字", &bOK);

    while(bOK && Name.isEmpty())
    {
        bOK = false;
        Name = QInputDialog::getText(this, "GameOver", "留下尊姓大名？", QLineEdit::Normal, "你的名字", &bOK);
    }

    QFile f("/Users/apple/Qt/Qt Project/None_sound/data.txt");
    if(!f.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug() << "0::Open failed!" << Qt::endl;
    }
    QTextStream in(&f);
    QString str;
    int s;
    while(!in.atEnd())
    {
        in >> str >> s;
        qDebug() << str << ": " << s;
        database.append(qMakePair(str, s));
    }
    f.close();

    if(bOK && !Name.isEmpty())
    {
        database.append(qMakePair(Name, score));
    }
    std::sort(database.begin(), database.end(), [](QPair<QString, int> a, QPair<QString, int> b){ return a.second > b.second; });
    QFile f2("/Users/apple/Qt/Qt Project/None_sound/data.txt");
    if(!f2.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        qDebug() << "Open failed!" << Qt::endl;
    }
    QTextStream txtOutput(&f2);
    QVector<QPair<QString, int> > :: iterator it;
    for(it = database.begin(); it != database.end(); it++)
        if(it->first != "")
            txtOutput << it->first << ' ' << it->second << Qt::endl;
    f2.close();
    emit toRanking();
}

void mainDialog::ShowRanking()
{
    QMessageBox msgBox;
    QString str;
    str += "                 历史排行榜\n\n名字\t\t得分\n\n";
    QVector<QPair<QString, int> > :: iterator it; int i;
    for(i = 0, it = database.begin(); it != database.end() && i < 10; it++, i++)
    {
        if(it->first != "")
        {
            str += it->first;
            str += "\t\t";
            str += QString::number(it->second);
            str += "\n\n";
        }
    }
    msgBox.setText(str);
    msgBox.exec();
    delete scene;
    qApp->quit();
}
