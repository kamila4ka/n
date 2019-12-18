#ifndef HEALTH_H
#define HEALTH_H

#include <QGraphicsTextItem>
#include <QFont>

class Health: public QGraphicsTextItem{
public:
    Health(): QGraphicsTextItem(){
        lives = 3;
        setPlainText(QString("Lives: ") + QString::number(lives)); //
        setDefaultTextColor(Qt::yellow);
        setFont(QFont("times",16));
    }
    void decrease(){
        if(lives>0){
            --lives;
        }
        setPlainText(QString("Lives: ") + QString::number(lives));
    }
    int lives;
};

#endif // HEALTH_H
