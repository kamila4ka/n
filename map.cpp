#include "map.h"
#include <QColor>
#include <QGraphicsRectItem>
#include <QGraphicsEllipseItem>
#include <cstdlib>
#include <QDebug>
#include <iostream>

using namespace std;

Map::Map(){}

void Map::createMap(int lvl){
    points=0;
    QVector<QVector<int>> _map(labirinth[0].size(), QVector<int>(labirinth.size(), 0));
    srand(time(nullptr));
    for(int i=0; i<labirinth[0].size(); ++i){
        for(int j=0; j<labirinth.size(); ++j){
            _map[i][j]=labirinth[j][i];
            if(_map[i][j]==0){
                ++points;
            }
        }
    }
    int gi=0, gj=0, ci, cj, pi, pj;
    for(int i=0; i<3+lvl; ++i){
        if (i%3==0){
            gi= rand() % 2+2;
            gj= 0;
        }
        else if(i%3==1){
            gi= rand() % 2 +9;
            gj= 0;
        }

        else if(i%3==2){
            gi= rand() % 2+2;
            gj= 0;
        }
        do{
            ++gj;
        }
        while(_map[gi][gj]!=0);
        _map[gi][gj]=2;
    }
    for(int i=0; i<3; ++i){
        ci= rand() % 17+2;
        do{
            cj= rand() % 15+2;
        }
        while(_map[ci][cj]!=0);
        _map[ci][cj]=3;
    }

    points+=3;
    pi= rand() % 17+2;
    do{
        pj= rand() % 15+2;
    }
    while(_map[pi][pj]!=0);
    _map[pi][pj]=4;

    map=_map;
}





