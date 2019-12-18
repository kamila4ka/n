#ifndef SCORE_H
#define SCORE_H

#include <QGraphicsTextItem>
#include <QFont>

class Score: public QGraphicsTextItem{
public:
    Score(): QGraphicsTextItem(){
        score = 0;
        setPlainText(QString("Score: ") + QString::number(score)); // Score: 0
        setDefaultTextColor(Qt::yellow);
        setFont(QFont("times",16));
    }
    void increase(int sc){
        score+=sc;
        setPlainText(QString("Score: ") + QString::number(score));
    }
    int score;
};

#endif // SCORE_H
