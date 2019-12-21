#ifndef POWERBALL_H
#define POWERBALL_H
#include <QGraphicsEllipseItem>
#include <QBrush>

#define cellsize 30


class Powerball: public QGraphicsEllipseItem{
public:
    Powerball(int i, int j): QGraphicsEllipseItem(i*cellsize+11, j*cellsize+11, 7, 7){
        QBrush brush;
        brush.setColor(Qt::red);
        brush.setStyle(Qt::SolidPattern);
        setBrush(brush);
    }
};

#endif // POWERBALL_H
