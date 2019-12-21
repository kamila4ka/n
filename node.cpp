#include "node.h"
#include <cmath>
#include "map.h"

Node::Node(){
    this->visited=false;
}

Node::Node(int x, int y){
    this->x=x;
    this->y=y;
    this->visited=false;
}


bool Node::operator==(Node &node){
    if(x==node.x && y==node.y){
        return true;
    }
    else{
        return false;
    }
}


void Node::assignParent(Node newParent){
    this->parentX=newParent.x;
    this->parentY=newParent.y;
}

bool Node::isAWall(Map* map){
    return map->map[x][y]=='w';
}

bool Node::isToTheLeft(const Node& node){
    return this->x < node.x;
}

bool Node::isToTheRight(const Node& node){
    return this->x > node.x;
}

bool Node::isHigher(const Node& node){
    return this->y < node.y;
}

bool Node::isVisited(){
    return visited;
}

//bool Node::isAdjacent(const Node& node){
//    if((this->x==node.x && abs(this->y - node.y)==1)
//       ||(this->y==node.y && abs(this->x - node.x)==1)){
//        return true;
//    }
//    else
//        return false;
//}

void Node::visit(){
    visited=true;
}

