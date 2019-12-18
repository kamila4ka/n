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
    Ghost(int i, int j, int color, Map* map, Pacman* pacman);

    int Dkstra(Node player, Node goal);
    void makePath(std::array<std::array<Node, 21>,19> graph, QVector<Node>& path, Node current, Node goal);
    Node minDistance(std::array<std::array<Node, 21>,19> graph, Node curNode);
    void move();
    void setDirection();
    void check();
    bool canMove();

    QTimer* timer;


    int homeX;
    int homeY;

public slots:
    void update();

private:
    int count;
    QPixmap left, right, up, down;
    bool moving;
    int _x;
    int _y;
    int _dir;
    Map* map;
    Pacman* pac;
};

#endif // GHOST_H
