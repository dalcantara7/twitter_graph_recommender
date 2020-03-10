//------------------------------------------------------------------------------------------------
//
// File: edge.cpp
// Author: ECE 275 Spring 2016
// Date: April 14, 2016
//
// Description:
//
//------------------------------------------------------------------------------------------------



//------------------------------------------------------------------------------------------------

#include "edge.h"

Edge::Edge() { //default constructor
    this->destNode = NULL;
    
}

Edge::Edge(Node* destNode) { //specific constructor
    this->destNode = destNode;
    
}

//getters

Node* Edge::GetDestNode() const{
    return this->destNode;
}
