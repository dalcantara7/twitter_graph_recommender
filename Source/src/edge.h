//------------------------------------------------------------------------------------------------
//
// File: edge.h
// Author: ECE 275 Spring 2016
// Date: April 14, 2016
//
// Description:
//
//------------------------------------------------------------------------------------------------

#ifndef EDGE_H
#define EDGE_H

#include <vector>
#include <string>

using namespace std;

//------------------------------------------------------------------------------------------------

class Node; // This is a forward class declaration that defines that a class named
            // Node exists elsewhere. This declaration allows us to use Node*
            // within the Edge class, becuase all pointers have the same size.

//------------------------------------------------------------------------------------------------

class Edge {
private:
    Node* destNode;     //Adjacent node
   
public:
    Edge(); //default constructor
   Edge(Node* destNode); //specific constructor
   //Getters
    Node* GetDestNode() const;
};

#endif

//------------------------------------------------------------------------------------------------


