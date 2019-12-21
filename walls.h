#ifndef WALLS_H
#define WALLS_H

#include <QObject>
#include <QGraphicsRectItem>
#include <QBrush>

#define cellsize 30

class Walls: public QObject, public QGraphicsRectItem{
    Q_OBJECT
public:
    Walls(int i, int j){
        setRect(i*cellsize, j*cellsize, cellsize,cellsize);
        QBrush brush;
        brush.setColor(Qt::darkBlue);
        brush.setStyle(Qt::SolidPattern);
        setBrush(brush);
    }
};
#endif // WALLS_H
