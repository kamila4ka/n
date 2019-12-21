#include "game.h"
#include <QGraphicsView>
#include <cmath>
#include <QKeyEvent>
#include <QTimer>
#include <QBrush>
#include <QDebug>
#include "coins.h"
#include "powerball.h"
#include <iostream>
#include <QWidget>
#include <QTime>
#include <QThread>

using namespace std;

Game::Game()
{
    map = new Map();
    points=0; gamePlayed=false;
    lvl=0;
    scene = new QGraphicsScene();
    scene->setSceneRect(0,0,800,800);
    view = new QGraphicsView();
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setFixedSize(800,800);
    view->setScene(scene);
    scene->setBackgroundBrush(Qt::black);
    scene->setFocus();
    view->show();
    startPage();
}

Game::~Game()
{
    delete map;
    delete scene;
    delete view;
}

void Game::drawLevel(){

    pac = new Pacman(9, 10, map);
    scene->addItem(pac);
    try{
        for(int i=0; i<map->map.size(); ++i){
            for(int j=0; j<map->map[0].size(); ++j){
                if(map->map[i][j]=='h' || map->map[i][j]=='g'){
                    Coins* coin = new Coins(i, j);
                    scene->addItem(coin);
                    coins.push_back(coin);
                }
                if(map->map[i][j]=='w'){
                    Walls* block = new Walls(i, j);
                    scene->addItem(block);
                    walls.push_back(block);
                }
                if(map->map[i][j]=='g'){
                    Ghost* ghost = new Ghost(i, j, ghosts.size()+1, lvl, map, pac);
                    scene->addItem(ghost);
                    ghosts.push_back(ghost);
                }
                if(map->map[i][j]=='p'){
                    Powerball* pb = new Powerball(i, j);
                    scene->addItem(pb);
                    pbs.push_back(pb);
                }
            }
        }
    }
    catch(...){
        qDebug() << "BITCH";
    }
    stats=new Stats(points, lvl);
    stats->setPos(0,650);
    scene->addItem(stats);
    gamePlayed=true;
    timer=new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(check()));
    timer->start(100);

}

void Game::startPage(){
    //if we haven't played a game yet,
    //  there's nothing to delete.
    if(gamePlayed){
        delete gameOver;
        delete score;
        points=0;
        lvl=0;
    }
    gamePlayed=false;
    button = new Button("PLAY");
    connect(button, SIGNAL(clicked()), this, SLOT(nextLevel()));
    scene->addItem(button);
}


void Game::check(){
    if(isGameLost()){
        gameLost();
        QTimer::singleShot(3000, this, SLOT(startPage()));
    }
    else if(isGameWon()){
        gameWon();
        QTimer::singleShot(3000, this, SLOT(nextLevel()));
    }
}

bool Game::isGameLost(){
    if(stats->lives==0){
        return true;
    }
    else{
        return false;
    }
}

bool Game::isGameWon(){
    //if pacman ate all the coins or ghosts, the level is passed.
    if((coins.empty() && pbs.empty()) || ghosts.empty()){
        return true;
    }
    else{
        return false;
    }
}

void Game::gameLost(){
    points+=stats->score;
    try{
    timer->stop();
    disconnect(timer, SIGNAL(timeout()), this, SLOT(check()));
    delete timer;
    for(int i=0; i<ghosts.size(); ++i){
        disconnect(ghosts[i]->timer, SIGNAL(timeout()), ghosts[i], SLOT(update()));
        ghosts[i]->timer->stop();
        delete ghosts[i];
    }
    ghosts.clear();
    }
    catch(...){
        qDebug() << "FUCK FUCK FUCK";
    }
    pac->clearFocus();
    pac->disconnect(pac->timer, SIGNAL(timeout()), pac, SLOT(move()));
    pac->timer->stop();
    delete pac;
    if(!walls.empty()){
        for(int i=0; i<walls.size(); ++i){
            delete walls[i];
        }
    }
    walls.clear();
    if(!coins.empty()){
        for(int i=0; i<coins.size(); ++i){
            delete coins[i];
        }
    }
    coins.clear();
    if(!pbs.empty()){
        for(int i=0; i<pbs.size(); ++i){
            delete pbs[i];
        }
    }
    pbs.clear();
    delete stats;
    gameOver = new QGraphicsTextItem;
    gameOver->setPos(180,250);
    gameOver->setFont(QFont("times",40));
    gameOver->setDefaultTextColor(Qt::red);
    gameOver->setPlainText("GAME OVER");
    scene->addItem(gameOver);
    score = new QGraphicsTextItem;
    score->setPos(190,430);
    score->setFont(QFont("times",30));
    score->setDefaultTextColor(Qt::white);
    score->setPlainText("Your score: "+ QString::number(points));
    scene->addItem(score);
}

void Game::gameWon(){
    points+=stats->score;

    timer->stop();
    disconnect(timer, SIGNAL(timeout()), this, SLOT(check()));
    delete timer;

    pac->clearFocus();
    pac->disconnect(pac->timer,SIGNAL(timeout()),pac,SLOT(move()));
    delete pac->timer;
    delete pac;
    timer->stop();
    for(int i=0; i<ghosts.size(); ++i){
        ghosts[i]->disconnect(ghosts[i]->timer,SIGNAL(timeout()),ghosts[i],SLOT(update()));
        ghosts[i]->timer->stop();
        delete ghosts[i]->timer;
        delete ghosts[i];
    }
    for(int i=0; i<walls.size(); ++i){
        delete walls[i];
    }
    for(int i=0; i<coins.size();++i){
        delete coins[i];
    }
    for(int i=0; i<pbs.size(); ++i){
        delete pbs[i];
    }
    delete stats;
    delete timer;

    levelWon = new QGraphicsTextItem;
    levelWon->setPos(180,250);
    levelWon->setFont(QFont("times",40));
    levelWon->setDefaultTextColor(Qt::white);
    levelWon->setPlainText("YOU WON");
    scene->addItem(levelWon);
    score = new QGraphicsTextItem;
    score->setPos(190,430);
    score->setFont(QFont("times",30));
    score->setDefaultTextColor(Qt::white);
    score->setPlainText("Your score: "+ QString::number(points));
    scene->addItem(score);
}


void Game::nextLevel(){
    if(gamePlayed){
        delete levelWon;
        delete score;
    }
    delete button;
    ++lvl;
    map->createMap(lvl);
    drawLevel();
}
