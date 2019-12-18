#include "button.h"
#include <QBrush>
#include <QTimer>
#include <QFont>

Button::Button(QString name){
    setRect(0,0,400,100);
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(Qt::darkBlue);
    setBrush(brush);
    // draw the text
    text = new QGraphicsTextItem(name,this);
    int xPos = rect().width()/2 - text->boundingRect().width()/2;
    int yPos = rect().height()/2 - text->boundingRect().height()/2;
    text->setPos(xPos,yPos);
    text->setDefaultTextColor(Qt::white);
    text->setFont(QFont("times",30));
//    QTimer* btimer =new QTimer();
//    connect(btimer,SIGNAL(timeout()),this,SLOT(deleteButton()));
//    btimer->start(2000);
}



void Button::mousePressEvent(QGraphicsSceneMouseEvent *event){
    emit clicked();
}
