#pragma once
#ifndef BFSNODE_H
#define BFSNODE_H
#include "Globals.h"
class BfsNode
{
public:
    BfsNode();
    BfsNode(string name,string parent, int level);
    string name,parent;
    int level,indx;
};

#endif // BFSNODE_H
