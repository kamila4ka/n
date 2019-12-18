#ifndef STATS_H
#define STATS_H
#include <QGraphicsTextItem>

class Stats: public QGraphicsTextItem
{
public:
    Stats(int savedScore);
    void decreaseHealth();
    void increaseScore(int sc);
    int lives;
    int score;
};

#endif // STATS_H


