//------------------------------------------------------------------------------------------------
//
// File: node.cpp
// Author: ECE 275 Spring 2016
// Date: April 14, 2016
//
// Description:
//
//------------------------------------------------------------------------------------------------



//------------------------------------------------------------------------------------------------

#include "node.h"
#include "graph.h"

#include <string>
#include <sstream>
#include <iostream>
#include <stdio.h>
#include <vector>
#include <string>
#include <string.h>
#include <cctype>
#include <stack>

Node::Node() { //default constructor
    this->account = "NULL";
    this->followers = 0;
    this->visited = false;
}
Node::Node(string account) { //specific constructor
    this->account = account;
    this->followers = 0;
    this->visited = false;
}

void Node::incNumFollowers() { //increments number of followers
    this->followers++;
}

//Setters and Getters
int Node::getNumFollowers() const {
    return this->followers;
}

string Node::getAccount() const{
    return this->account;
}

void Node::setAccountName(string accountName) {
    this->account = accountName;
}

vector<Edge*> Node::getFollowingList() {
    return this->_followingList;
}

vector<Edge*> Node::getFollowersList() {
    return this->_followersList;
}

// Overloaded < operator for Node objects
bool Node::operator<(const Node& rhs) const {
    if (rhs.getNumFollowers() < getNumFollowers())
        return true;
    else if (rhs.getNumFollowers() == getNumFollowers() && getAccount() < rhs.getAccount())
        return true;
    else
        return false;
}

