#include "ghost.h"
#include <QBrush>
#include <iostream>
#include "node.h"
#include <QDebug>
#include <QColor>
#include <queue>
#include "game.h"

#define cellsize 30
#define step 10


using namespace std;

extern Game* game;

Ghost::~Ghost(){
    delete timer;
}
Ghost::Ghost(int i, int j, int color, int lvl, Map* map, Pacman* pacman):
    QGraphicsRectItem(i*cellsize, j*cellsize, cellsize, cellsize){
    homeX=_x=i*cellsize;
    homeY=_y=j*cellsize;
    this->map=map;
    this->lvl=lvl;
    pac=pacman;
    dir=0;
    QBrush brush;
    color=color%4+1;
    switch(color){
        case 1:
            brush.setColor(Qt::green);
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
    timer=new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(update()));
    timer->start(100);

    scared=false;
}

void Ghost::update(){
    QList<QGraphicsItem*> colliding_items = collidingItems();
    for (int i = 0, n = colliding_items.size(); i < n; ++i){
        if (typeid(*(colliding_items[i])) == typeid(Pacman)){
            if(pac->powerful){
                int idx = game->ghosts.indexOf(this);
                game->ghosts.remove(idx);
                delete colliding_items[i];
            }
            else{
                game->stats->decreaseHealth();
                _x=homeX;
                _y=homeY;
                dir=0;
                setPos(0,0);
            }
        }
    }
    if(abs(_x/30 - pac->getx()/30) + abs(_y/30 - pac->gety()/30) < 3+lvl*4){
        if(scared){
            runAway();
        }
        else{
            if(count% (cellsize/step)==0){
                setDirection(); // found pacman
            }
            ++count;
        }
    }
    else{
        count=0;
        if(!canMove(dir)){
            setRandomDirection();
        }
    }
    move();
}

void Ghost::setRandomDirection(){    
    srand(time(nullptr));
    dir=(rand()%1003) %4 + 1;
    while(!canMove(dir)){
        ++dir;
        if(dir>4){
            dir-=4;
        }
    }
}

void Ghost::runAway(){
   int maxDir=0; int maxDist=0;
   int pX=pac->getx()/30; int pY=pac->gety()/30;
   int nX; int nY;
   nX=_x/30-1; nY=_y/30;
   if(abs(nX-pX)+abs(nY-pY) > maxDist
      && canMove(1)){
       maxDist = abs(nX-pX)+abs(nY-pY);
       maxDir=1;
   }
   nX+=2;
   if(abs(nX-pX)+abs(nY-pY) > maxDist
      && canMove(2)){
       maxDist = abs(nX-pX)+abs(nY-pY);
       maxDir=2;
   }
   --nX; ++nY;
   if(abs(nX-pX)+abs(nY-pY) > maxDist
      && canMove(3)){
       maxDist = abs(nX-pX)+abs(nY-pY);
       maxDir=3;
   }
   nY-=2;
   if(abs(nX-pX)+abs(nY-pY) > maxDist
      && canMove(4)){
       maxDist = abs(nX-pX)+abs(nY-pY);
       maxDir=4;
   }
   dir=maxDir;
}

void Ghost::setDirection(){
    Node ghost((_x)/cellsize,(_y)/cellsize);
    Node pacman(pac->getx()/cellsize, pac->gety()/cellsize);
    dir=Dkstra(ghost, pacman);
}

bool Ghost::canMove(int newDir){
    switch (newDir) {
    case 0:
        return false;

    case 1:
        if(_x-step<0)
            return true;
        if(map->map[(_x-step)/cellsize][_y/cellsize]!='w'&& (_y%cellsize==0) )
            return true;
        return false;
    case 2:
        if(570 - step - cellsize - _x<=0)
            return true;
        if(map->map[(_x + cellsize + step-1)/cellsize][_y/cellsize]!='w' && (_y%cellsize==0))
            return true;
        return false;
    case 3:
        if(map->map[_x/cellsize][(_y-step)/cellsize]!='w' && _x%cellsize == 0)
            return true;
        return false;
    case 4:
        if(map->map[_x/cellsize][(_y + cellsize + step-1)/cellsize]!='w' && _x%cellsize == 0)
            return true;
        return false;
    default:
        return false;
    }
}


void Ghost::move(){

    switch (dir) {

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
            if ((560-cellsize-_x)<=0) {
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

        case 3:
            if(canMove(3)){
                setY(y()-step);
                _y-=step;
            }
            break;

        case 4:
            if(canMove(4)){
                setY(y()+step);
                _y+=step;
            }
            break;
        }
}



void Ghost::makePath(std::array<std::array<Node, 21>,19> graph, QVector<Node>& path, Node goal){
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
    graph[_x/cellsize][_y/cellsize].distance=0;
    graph[_x/cellsize][_y/cellsize].parentX=graph[_x/cellsize][_y/cellsize].parentY=0;
    Node current=graph[_x/cellsize][_y/cellsize];
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
    makePath(graph, path, goal);
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
