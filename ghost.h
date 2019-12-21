#ifndef GHOST_H
#define GHOST_H

#include <QObject>
#include <QGraphicsItem>
#include <QGraphicsPixmapItem>
#include <QTimer>
#include "map.h"
#include "pacman.h"
#include <QVector>
#include "node.h"
#include <array>
#include <QGraphicsRectItem>

class Pacman;

class Ghost: public QObject, public QGraphicsRectItem{
    Q_OBJECT
public:
    Ghost(int i, int j, int color, int lvl, Map* map, Pacman* pacman);
    ~Ghost();
    int Dkstra(Node player, Node goal);
    void makePath(std::array<std::array<Node, 21>,19> graph, QVector<Node>& path, Node goal);
    Node minDistance(std::array<std::array<Node, 21>,19> graph, Node curNode);
    void move();
    void setDirection();
    void check();
    bool canMove(int dir);
    void setRandomDirection();
    void runAway();
    bool scared;
    QTimer* timer;

    int dir;

    int homeX;
    int homeY;
    int _x;
    int _y;
public slots:
    void update();

private:
    int count;
    QPixmap left, right, up, down;
    bool moving;
 //   int dir;
    int lvl;
    Map* map;
    Pacman* pac;
};

#endif // GHOST_H
