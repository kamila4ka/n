#ifndef WALLS_H
#define WALLS_H

#include <QObject>
#include <QGraphicsRectItem>
#include <QBrush>

class Walls: public QObject, public QGraphicsRectItem{
    Q_OBJECT
public:
    Walls(int i, int j){
        setRect(i*30, j*30, 30,30);
        QBrush brush;
        brush.setColor(Qt::blue);
        brush.setStyle(Qt::SolidPattern);
        setBrush(brush);
    }
};
#endif // WALLS_H
