#include "coins.h"
#include "QPainter"
#include <QBrush>

Coins::Coins(): QGraphicsEllipseItem(){}
Coins::Coins(const Coins& coin): QGraphicsEllipseItem(){
    *this=coin;
};

Coins& Coins::operator=(const Coins&){
    return *this;
};

void Coins::paint(int x, int y){
    this->setPos(x,y);
    QPainter painter;
    painter.drawEllipse(x,y, 10,10);
    QBrush brush;
    brush.setColor(Qt::yellow);
    painter.setBrush(brush);
};

void Coins::paintSuper(int x, int y){
    this->setPos(x,y);
    QPainter painter;
    painter.drawEllipse(x,y, 15, 15);
    QBrush brush;
    brush.setColor(Qt::yellow);
    painter.setBrush(brush);
}
