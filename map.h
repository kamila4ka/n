#ifndef MAP_H
#define MAP_H

#include <QObject>
#include <QGraphicsRectItem>
#include <QPainter>
#include <QGraphicsScene>
#include "coins.h"

class Map: public QObject, public QGraphicsRectItem{
    Q_OBJECT
public:
    Map();
    QVector<QVector<char>> map;
    void createMap(int lvl);
private:    
    QVector<QVector<char>> labirinth={
        {'w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w'},
        {'w','g','h','h','h','h','h','h','h','h','h','h','p','h','h','h','h','g','w'},
        {'w','h','w','w','h','w','w','w','h','w','h','w','w','w','h','w','w','h','w'},
        {'w','p','w','w','h','w','w','w','h','w','h','w','w','w','h','w','w','h','w'},
        {'w','h','h','h','h','h','h','h','h','h','h','h','h','h','h','h','h','h','w'},
        {'w','h','w','w','h','w','h','w','w','w','w','w','h','w','h','w','w','h','w'},
        {'w','h','h','h','h','w','h','h','h','w','h','h','h','w','h','h','h','h','w'},
        {'w','w','w','w','h','w','w','w','h','w','h','w','w','w','h','w','w','w','w'},
        {'w','w','w','w','h','w','h','h','h','h','h','h','h','w','h','w','w','w','w'},
        {'w','w','w','w','h','w','h','w','w','h','w','w','h','w','h','w','w','w','w'},
        {'h','h','h','h','h','h','h','w','h','o','h','w','h','w','h','h','p','h','h'},
        {'w','w','w','w','h','w','h','w','w','w','w','w','h','w','h','w','w','w','w'},
        {'w','w','w','w','h','w','h','h','h','h','h','h','h','w','h','w','w','w','w'},
        {'w','w','w','w','h','w','w','w','h','w','h','w','w','w','h','w','w','w','w'},
        {'w','h','h','h','h','w','h','h','h','w','h','h','h','w','h','h','h','h','w'},
        {'w','p','w','w','h','w','h','w','w','w','w','w','h','w','h','w','w','h','w'},
        {'w','h','h','h','h','h','h','h','h','h','h','h','h','h','h','h','h','h','w'},
        {'w','h','w','w','h','w','w','w','h','w','h','w','w','w','h','w','w','h','w'},
        {'w','h','w','w','h','w','w','w','h','w','h','w','w','w','h','w','w','h','w'},
        {'w','g','h','h','h','h','h','h','p','h','h','h','h','h','h','h','h','g','w'},
        {'w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w'}};
    // w = wall
    // h = hallway
    // g = ghost
    // p = powerball
};

#endif // MAP_H
