#include "stats.h"

#include <QFont>

Stats::Stats(int savedScore, int lvl): QGraphicsTextItem(){

    lives = 3;     score = savedScore;      this->lvl=lvl;
    setPlainText(QString("Lives: ") + QString::number(lives) + QString(".        ")
                 + QString("Score: ") + QString::number(score) + QString(".        ")
                 + QString("Level: ") + QString::number(lvl) + QString("."));
    setDefaultTextColor(Qt::white);
    setFont(QFont("times",16));

}

void Stats::decreaseHealth(){
    if(lives>0){
        --lives;
    }
    setPlainText(QString("Lives: ") + QString::number(lives) +QString(".        ")
                 + QString("Score: ") + QString::number(score) + QString(".        ")
                 + QString("Level: ") + QString::number(lvl) + QString("."));
}

void Stats::increaseScore(int sc){
    score+=sc;
    setPlainText(QString("Lives: ") + QString::number(lives) +QString(".        ")
                 + QString("Score: ") + QString::number(score) + QString(".        ")
                 + QString("Level: ") + QString::number(lvl) + QString("."));
}
