#ifndef COINS_H
#define COINS_H

#include <QGraphicsEllipseItem>
#include <QBrush>

#define cellsize 30

class Coins: public QGraphicsEllipseItem{
public:
        Coins(int i, int j): QGraphicsEllipseItem(i*cellsize+14, j*cellsize+14, 3, 3){
        //setPos(x()+14, y()+14);
        QBrush brush;
        brush.setColor(Qt::yellow);
        brush.setStyle(Qt::SolidPattern);
        setBrush(brush);     
    }
};

#endif // COINS_H
