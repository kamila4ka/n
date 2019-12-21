#include "button.h"
#include <QBrush>
#include <QTimer>
#include <QFont>

#define screensize 800

Button::Button(QString name){
    setRect(screensize/4, screensize/3, screensize/2, screensize/3);
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(Qt::darkBlue);
    setBrush(brush);
    // draw the text
    text = new QGraphicsTextItem(name,this);
    int xPos = 330;
    int yPos = 360;
    text->setPos(xPos,yPos);
    text->setDefaultTextColor(Qt::white);
    text->setFont(QFont("times",30));
}



void Button::mousePressEvent(QGraphicsSceneMouseEvent *event){
    emit clicked();
}
