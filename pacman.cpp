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

#define cellsize 30
#define step 10

using namespace std;

extern Game* game;

Pacman::~Pacman(){
    delete timer;
}

Pacman::Pacman(int i, int j, Map* map): QGraphicsEllipseItem(i*cellsize, j*cellsize, cellsize, cellsize){
    QBrush brush;
    brush.setColor(Qt::yellow);
    brush.setStyle(Qt::SolidPattern);
    setBrush(brush);
    setFlag(QGraphicsItem::ItemIsFocusable);
    setFocus();
    this->map=map;
    powerful=false;
    _x=i*cellsize; _y=j*cellsize;
    pdir=nextDir=0;
    timer=new QTimer(this);
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
        if (typeid(*(colliding_items[i])) == typeid(Coins)){
            scene()->removeItem(colliding_items[i]);
            int idx = game->coins.indexOf(dynamic_cast<Coins*>(colliding_items[i]));
            game->coins.remove(idx);
            delete colliding_items[i];
            game->stats->increaseScore(1);
        }
        else if(typeid(*(colliding_items[i])) == typeid(Powerball)){
            scene()->removeItem(colliding_items[i]);
            int idx = game->pbs.indexOf(dynamic_cast<Powerball*>(colliding_items[i]));
            game->pbs.remove(idx);
            delete colliding_items[i];
            game->stats->increaseScore(3);
            powerful=true;
            for(int i=0; i<game->ghosts.size();++i){
                game->ghosts[i]->scared=true;
            }
            QBrush brush;
            brush.setColor(Qt::red);
            brush.setStyle(Qt::SolidPattern);
            setBrush(brush);
            timer->setInterval(40);
            QTimer::singleShot(3000, this, SLOT(change()));
        }
        else if(typeid(*(colliding_items[i])) == typeid(Ghost)){
            if(powerful){
                int idx = game->ghosts.indexOf(dynamic_cast<Ghost*>(colliding_items[i]));
                game->ghosts.remove(idx);
                delete colliding_items[i];
            }
        }
    }
}

void Pacman::move(){
//    cout << " "<< map->map[_x/cellsize][_y/cellsize-'w']<< endl <<map->map[_x/cellsize-'w'][_y/cellsize]
//    << map->map[_x/cellsize][_y/cellsize+'w']<< map->map[_x/cellsize+'w'][_y/cellsize] << endl;
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
        if ((_x-step)<0) {
            setX(x()+560);
            _x=560+_x;
        }
        else{
            if(canMove(1)){
                setX(x()-step);
                _x-=step;
            }
        }
        break;

    case 2:
        if ((570-step-cellsize-_x)<=0) {
            setX(x()-550);
            _x=_x-550;
        }
        else{
            if(canMove(2)){
                setX(x()+step);
                _x+=step;
                }
            }
        break;

    case 3: if(canMove(3)){
        setY(y()-step);
        _y-=step;
        }
        break;
    case 4: if(canMove(4)){
        setY(y()+step);
        _y+=step;
        }
        break;
    }
    check();
}

bool Pacman::canMove(int dir){
    switch (dir) {
    case 1:
        if(_x-step<0 && _y %cellsize == 0 && (_y%cellsize == 0))
            return true;
        if(map->map[(_x-step)/cellsize][_y/cellsize]!='w'
                && _y %cellsize == 0)
            return true;
        return false;
    case 2:
        if(570-step-cellsize-_x<=0 && (_y%cellsize == 0))
            return true;
        if(map->map[(_x+step+cellsize-1)/cellsize][_y/cellsize]!='w' && (_y%cellsize == 0))
            return true;
        return false;
    case 3:
        if(map->map[_x/cellsize][(_y-step)/cellsize]!='w' && _x%cellsize == 0)
            return true;
        return false;
    case 4:
        if(map->map[_x/cellsize][(_y+cellsize+step-1)/cellsize]!='w' && _x%cellsize == 0)
            return true;
        return false;
    }
}

void Pacman::change(){
    QBrush brush;
    brush.setColor(Qt::yellow);
    brush.setStyle(Qt::SolidPattern);
    setBrush(brush);
    powerful=false;
    for(int i=0; i<game->ghosts.size();++i){
        game->ghosts[i]->scared=false;
    }
    timer->setInterval(100);
}

