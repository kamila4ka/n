#include "map.h"
#include <QColor>
#include <QGraphicsRectItem>
#include <QGraphicsEllipseItem>
#include <cstdlib>
#include <QDebug>
#include <iostream>

using namespace std;

Map::Map(){
    QVector<QVector<char>> _map(labirinth[0].size(), QVector<char>(labirinth.size(), 0));
    for(int i=0; i<labirinth[0].size(); ++i){
        for(int j=0; j<labirinth.size(); ++j){
            _map[i][j]=labirinth[j][i];
            if(_map[i][j]==0){
            }
        }
    }
    map=_map;
}

void Map::createMap(int lvl){
    srand(time(nullptr));
    for(int i=0; i<lvl-1; ++i){
        int newX;
        int newY;
        while(map[newX][newY]!='h'){
            newX = rand() %19;
            newY = rand() %21;
        }
        map[newX][newY]='g';
    }
}






