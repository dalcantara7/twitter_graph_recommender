//------------------------------------------------------------------------------------------------
//
// File: node.h
// Author: ECE 275 Spring 2016
// Date: April 14, 2016
//
// Description:
//
//------------------------------------------------------------------------------------------------

#ifndef NODE_H
#define NODE_H

#include <vector>
#include <string>
#include "edge.h"

using namespace std;

class Node {
private:
    int followers; //count for number of followers
    bool visited; //used for depth first search and calculating centrality
   
public:
    Node(); //default constructor
   Node(string account); //
   // Other public methods go here.
    //Setters and Getters
    string getAccount() const;
    string account;  // Label for node
    int getNumFollowers() const;
    vector<Edge*> getFollowingList();
    vector<Edge*> getFollowersList();
    vector<Edge*> _followingList;    // Adjacency list (only stores the edges that lead to
    vector<Edge*> _followersList; //Adjacency list
    void setAccountName(string accountName);
    
    void incNumFollowers(); //increments number of followers
    
    bool operator<(const Node& rhs) const; //overloaded operator for nodes

};

#endif

//------------------------------------------------------------------------------------------------


