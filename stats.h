#ifndef STATS_H
#define STATS_H
#include <QGraphicsTextItem>

class Stats: public QGraphicsTextItem
{
public:
    Stats(int savedScore, int lvl);
    void decreaseHealth();
    void increaseScore(int sc);
    int lives;
    int score;
    int lvl;
};

#endif // STATS_H


