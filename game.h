#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QGraphicsView>
#include "ghost.h"
#include "map.h"
#include "pacman.h"
#include "stats.h"
#include <QWidget>
#include <QKeyEvent>
#include <QGraphicsTextItem>
#include <powerball.h>
#include "button.h"
#include "walls.h"

class Pacman;
class Ghost;

class Game: public QGraphicsView{
    Q_OBJECT

public:
    Game();
    ~Game();

    void drawLevel();
    void gameWon();
    void gameLost();
    bool isGameLost();
    bool isGameWon();

    Stats* stats;
    QVector<Ghost*> ghosts;
    QVector<Coins*> coins;
    QVector<Powerball*> pbs;
public slots:
    void check();
    void nextLevel();
    void startPage();

private:
    int points;
    QVector<QVector<int>> myMap;
    int lvl;
    QGraphicsTextItem* gameOver; QGraphicsTextItem* score;
    QGraphicsTextItem* levelWon; // for cutscenes
    Map* map;
    Pacman* pac;
    Button* button;

    QVector<Walls*> walls;
    QTimer* timer;
    QGraphicsView* view;
    QGraphicsScene* scene;
    bool gamePlayed;
};

#endif // MAINWINDOW_H
