#ifndef POWERBALL_H
#define POWERBALL_H
#include <QGraphicsEllipseItem>
#include <QBrush>
class Powerball: public QGraphicsEllipseItem{
public:
    Powerball(int i, int j): QGraphicsEllipseItem(i*30+13, j*30+13, 5, 5){
        QBrush brush;
        brush.setColor(Qt::yellow);
        brush.setStyle(Qt::SolidPattern);
        setBrush(brush);
    }
};

#endif // POWERBALL_H
