#include "pacman.h"
#include <QBrush>
#include "coins.h"
#include <QGraphicsScene>
#include <QList>
#include <iostream>
#include <QDebug>
#include "powerball.h"
#include "game.h"
#include "ghost.h"

using namespace std;

extern Game* game;
Pacman::Pacman(int i, int j, Map* map): QGraphicsEllipseItem(i*30, j*30, 30, 30){
    QBrush brush;
    brush.setColor(Qt::yellow);
    brush.setStyle(Qt::SolidPattern);
    setBrush(brush);
    setFlag(QGraphicsItem::ItemIsFocusable);
    setFocus();
    this->map=map;
    _x=i*30; _y=j*30;
    points=pdir=nextDir=0;
    state=0;
    timer=new QTimer();
    connect(timer,SIGNAL(timeout()),this,SLOT(move()));
    timer->start(100);
}
void Pacman::keyPressEvent(QKeyEvent *event){
    if(event->key() == Qt::Key_Left){
        nextDir=1;
    }
    else if(event->key() == Qt::Key_Right){
        nextDir=2;
    }
    else if(event->key() == Qt::Key_Up){
        nextDir=3;
    }
    else if(event->key() == Qt::Key_Down){
        nextDir=4;
    }
}
void Pacman::check(){
    QList<QGraphicsItem*> colliding_items = collidingItems();
    for (int i = 0, n = colliding_items.size(); i < n; ++i){
        if (typeid(*(colliding_items[i])) == typeid(Coins)){ // edit later
            scene()->removeItem(colliding_items[i]);
            delete colliding_items[i];
            game->stats->increaseScore(1);
            --game->pointsCounter;
        }
        else if(typeid(*(colliding_items[i])) == typeid(Powerball)){
            scene()->removeItem(colliding_items[i]);
            delete colliding_items[i];
            game->stats->increaseScore(3);
            --game->pointsCounter;
            timer->setInterval(40);
            QTimer::singleShot(1000, this, SLOT(change()));
        }
        else if(typeid(*(colliding_items[i])) == typeid(Ghost)){
            game->stats->decreaseHealth();
        }
    }
}

void Pacman::move(){
//    cout << " "<< map->map[_x/30][_y/30-1]<< endl <<map->map[_x/30-1][_y/30]
//    << map->map[_x/30][_y/30+1]<< map->map[_x/30+1][_y/30] << endl;
    if(canMove(nextDir)){
        pdir=nextDir;
    }
    switch (pdir) {
    case 0:
        if(nextDir!=0){
            pdir=nextDir;
        }
        break;
    case 1:
        if ((_x-10)<0 && (_y%30 == 0)) {
            setX(x()+560);
            _x=560+_x;
        }
        else{
            if(map->map[(_x-10)/30][(_y)/30]!=1 && (_y%30==0)){
                setX(x()-10);
                _x-=10;
            }
        }
        break;

    case 2:
        if ((560-30-_x)<=0 && (_y%30 == 0)) {
            setX(x()-550);
            _x=_x-550;
        }
        else{
            if(map->map[(_x+30)/30][(_y)/30]!=1
                    && (_y%30 == 0)){
                setX(x()+10);
                _x+=10;
                }
            }
        break;

    case 3: if(map->map[_x/30][(_y-10)/30]!=1 && _x%30 == 0){
        setY(y()-10);
        _y-=10;
        }
        break;
    case 4: if(map->map[_x/30][(_y+31)/30]!=1 && _x%30 == 0){
        setY(y()+10);
        _y+=10;
        }
        break;
    }
    check();
}
/*
    if(map->map[_x/30][(_y-10)/30]!=1)
        return true;
    return false;
case 4:
    if(map->map[_x/30][(_y+40)/30]!=1)
*/

bool Pacman::canMove(int dir){
    switch (dir) {
    case 1:
        if(_x-10<0 && _y %30 == 0)
            return true;
        if(map->map[(_x-10)/30][_y/30]!=1
                && _y %30 == 0)
            return true;
        return false;
    case 2:
        if(560-30-_x<=0)
            return true;
        if(map->map[(_x+40)/30][_y/30]!=1)
            return true;
        return false;
    case 3:
        if(map->map[_x/30][(_y-10)/30]!=1)
            return true;
        return false;
    case 4:
        if(map->map[_x/30][(_y+40)/30]!=1)
            return true;
        return false;
    }
}

void Pacman::change(){
    timer->setInterval(100);
}

