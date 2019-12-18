#include "stats.h"

#include <QFont>

Stats::Stats(int savedScore): QGraphicsTextItem(){
    lives = 3;     score = savedScore;
    setPlainText(QString("Lives: ") + QString::number(lives) +QString("     ")
                 + QString("Score: ") + QString::number(score));
    setDefaultTextColor(Qt::white);
    setFont(QFont("times",16));

}

void Stats::decreaseHealth(){
    if(lives>0){
        --lives;
    }
    setPlainText(QString("Lives: ") + QString::number(lives) +QString("     ")
                 + QString("Score: ") + QString::number(score));
}

void Stats::increaseScore(int sc){
    score+=sc;
    setPlainText(QString("Lives: ") + QString::number(lives) +QString("     ")
                 + QString("Score: ") + QString::number(score));
}
