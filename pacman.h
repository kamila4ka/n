#ifndef PACMAN_H
#define PACMAN_H

#include <QObject>
#include <QGraphicsEllipseItem>
#include "map.h"
#include <QTimer>

class Pacman: public QObject, public QGraphicsEllipseItem{
    Q_OBJECT
public:
    Pacman(int i, int j, Map* map);
    ~Pacman();
    void check();
    int getx(){ return _x;}
    int gety(){ return _y;}
    QTimer* timer;
    bool powerful;
//    int points;
    void keyPressEvent(QKeyEvent* event);
public slots:
    void move();
    void change();
private:
    int _x;
    int _y;
    int pdir;
    int nextDir;
    bool canMove(int dir);
    Map* map;
};

#endif // PACMAN_H
