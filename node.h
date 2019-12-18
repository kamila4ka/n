#ifndef NODE_H
#define NODE_H
#include "map.h"

class Node
{
public:
    Node();
    Node(int x, int y);
    bool isToTheLeft(const Node& node);
    bool isToTheRight(const Node& node);
    bool isHigher(const Node& node);
    bool isAdjacent(const Node& node);
    bool isAWall(Map* map);
    bool isVisited();
    void visit();
    void assignParent(Node newParent);

    bool operator==(Node &node);

    int x;
    int y;
    int parentX;
    int parentY;
    int distance;
private:
    bool visited;
};

#endif // NODE_H
