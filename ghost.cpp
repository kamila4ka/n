#include "ghost.h"
#include <QBrush>
#include <iostream>
#include "node.h"
#include <QDebug>
#include <QColor>
#include <queue>

using namespace std;

extern Game* game;

Ghost::Ghost(int i, int j, int color, Map* map, Pacman* pacman): QGraphicsRectItem(i*30, j*30, 30, 30){
    this->map=map;
    pac=pacman;

    _x=i*30; _y=j*30;
    _dir=0;
    QBrush brush;
    color=color%4+1;
    switch(color){
        case 1:
            brush.setColor(Qt::red);
            break;
        case 2:
            brush.setColor(Qt::cyan);
            break;
        case 3:
            brush.setColor(Qt::magenta);
            break;
        case 4:
            brush.setColor(QColor("#ffb6c1"));
            break;
    }
    brush.setStyle(Qt::SolidPattern);
    setBrush(brush);
    count=0;
    timer=new QTimer();
    connect(timer,SIGNAL(timeout()),this,SLOT(update()));
    timer->start(100);
}

void Ghost::update(){

    if(!(_x/30==pac->getx()/30 && _y/30==pac->gety()/30)){
        if(count%3==0){
            setDirection();
        }
        move();
    }
    ++count;
}

void Ghost::setDirection(){
    Node ghost((_x)/30,(_y)/30);
    Node pacman(pac->getx()/30, pac->gety()/30);
    _dir=Dkstra(ghost, pacman);
}
/*if(!moving)
 * setDirection;
 * if(moving)
 * if(canMove(currentDirection))
    keepMoving;
  else
    setDirection;
*/

//bool Ghost::canMove(){
//    switch (_dir) {
//    case 1:
//        if(_x-10<0 && _y %30 == 0)
//            return true;
//        if(map->map[(_x-10)/30][_y/30]!=1
//                && _y %30 == 0)
//            return true;
//        return false;
//    case 2:
//        if(560-30-_x<=0)
//            return true;
//        if(map->map[(_x+40)/30][_y/30]!=1)
//            return true;
//        return false;
//    case 3:
//        if(map->map[_x/30][(_y-10)/30]!=1)
//            return true;
//        return false;
//    case 4:
//        if(map->map[_x/30][(_y+40)/30]!=1)
//            return true;
//        return false;
//    }
//}


void Ghost::move(){


    if(!(_x/30==int(x())/30 && _y/30==int(y()))/30){
        qDebug() << "HUITA";
    }
    switch (_dir) {
    case 0: break;
    case 1://left
        if ((_x-10)<0) {
            setX(x()+570);
            _x=570-10+_x;
        }
        else{
                setX(x()-10);
                _x-=10;
        }
        break;

    case 2:
        if ((560-30-_x)<=0 /*&& (_y%30 == 0)*/) {
            setX(x()-560+10);
            _x=_x-560+10;
        }
        else{
            setX(x()+10);
            _x+=10;
        }
        break;

    case 3:
        setY(y()-10);
        _y-=10;        
        break;
    case 4:
        setY(y()+10);
        _y+=10;
        break;
    }
}



void Ghost::makePath(std::array<std::array<Node, 21>,19> graph,QVector<Node>& path, Node current, Node goal){
    Node it;
    for(it=graph[goal.x][goal.y]; !(it.parentX==0&&it.parentY==0) ; it=graph[it.parentX][it.parentY]){
        path.push_back(it);
    }
}

int Ghost::Dkstra(Node player, Node goal) {
    std::array<std::array<Node,21>,19> graph;
    if(player==goal){
        return 0;
    }
    for(int i=0; i<19; ++i){
        for(int j=0; j<21; ++j){
            graph[i][j].x=i; graph[i][j].y=j;
            graph[i][j].distance=100;
            graph[i][j].parentX=graph[i][j].parentY=0;
        }
    }
    graph[_x/30][_y/30].distance=0;
    graph[_x/30][_y/30].parentX=graph[_x/30][_y/30].parentY=0;
    Node current=graph[_x/30][_y/30];
    queue<Node> frontier;
    frontier.push(current);
    int count=0;
    while(!frontier.empty()){
        ++count;
        current=frontier.front();
        frontier.pop();

        if(current==goal){
            break;
        }

        current.visit();
        int i=current.x-1; int j=current.y;
        if(i<0){ i+=19;}
        if(i>=0 && i<19 && j>=0 && j<21)
        if(graph[i][j].isVisited()==false
           &&!graph[i][j].isAWall(map)
           &&graph[i][j].distance > (current.distance + 1)){
            graph[i][j].distance = current.distance + 1;
            graph[i][j].assignParent(current);
            frontier.push(graph[i][j]);
        }

        i=current.x+1; j=current.y;
        if(i>=19){ i-=19;}
        if(i>=0 && i<19 && j>=0 && j<21)
        if(graph[i][j].isVisited()==false
           &&!graph[i][j].isAWall(map)
           &&graph[i][j].distance > (current.distance + 1)){
            graph[i][j].distance = current.distance + 1;
            graph[i][j].assignParent(current);
            frontier.push(graph[i][j]);
        }

        i=current.x; j=current.y-1;
        if(i>=0 && i<19 && j>=0 && j<21)
        if(graph[i][j].isVisited()==false
           &&!graph[i][j].isAWall(map)
           &&graph[i][j].distance > (current.distance + 1)){
            graph[i][j].distance = current.distance + 1;
            graph[i][j].assignParent(current);
            frontier.push(graph[i][j]);

        }

        i=current.x; j=current.y+1;
        if(i>=0 && i<19 && j>=0 && j<21)
        if(graph[i][j].isVisited()==false
           &&!graph[i][j].isAWall(map)
           &&graph[i][j].distance > (current.distance + 1)){
            graph[i][j].distance = current.distance + 1;
            graph[i][j].assignParent(current);
            frontier.push(graph[i][j]);
        }      
    }
    QVector<Node> path;
    makePath(graph, path, graph[_x/30][_y/30], goal);
    int dir=0;
    if(!path.isEmpty()){
        Node next = path.back();
        if(player.isToTheRight(next)){
            dir=1;
        }
        else if(player.isToTheLeft(next)){
            dir=2;
        }
        else if(player.isHigher(next)){
                dir=4;
        }
        else{
            dir=3;
        }
    }
    path.clear();
    return dir;
}
