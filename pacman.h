#ifndef PACMAN_H
#define PACMAN_H

#include <QObject>
#include <QGraphicsEllipseItem>
#include "map.h"
#include "game.h"
#include <QTimer>

class Pacman: public QObject, public QGraphicsEllipseItem{
    Q_OBJECT
public:
    Pacman(int i, int j, Map* map);
    void check();
    int getx(){ return _x;}
    int gety(){ return _y;}
    QTimer* timer;
    int points;
    int nextDir;
    void keyPressEvent(QKeyEvent* event);

public slots:
    void move();
    void change();
private:
    int _x;
    int _y;
    int pdir;
    int state; // ==1 if consumed superball
    bool canMove(int dir);
    Map* map;
};

#endif // PACMAN_H
