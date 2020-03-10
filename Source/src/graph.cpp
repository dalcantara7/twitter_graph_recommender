//------------------------------------------------------------------------------------------------
//
// File: graph.cpp
// Author: ECE 275 Spring 2016
// Date: April 14, 2016
//
// Description:
//
//------------------------------------------------------------------------------------------------



//------------------------------------------------------------------------------------------------

#include <string>
#include <sstream>
#include <iostream>
#include <stdio.h>
#include <vector>
#include <string>
#include <cctype>
#include <algorithm>


#include "graph.h"
#include "edge.h"


int Graph::ReadInputsFromFile() {
    unsigned int i = 0;
    int numPasses = 0; //variable to check for empty test file only on the first iteration
    
    if (_inputFileName != NULL) { //checks if filename is valid
        _inputFile.open(_inputFileName);
        
        if (_inputFile.good()) { //checks if it is good
            if (_inputFile.is_open()) { //checks that it is valid
                while (!_inputFile.eof()) {
                    string account1; //variable to store account name
                    string account2;
                    
                    _inputFile >> account1; //read into variable
                    _inputFile >> account2;
                    
                    if(numPasses == 0 && (account1 == "" || account2 == "")) //case for empty test file
                        return -1; //returns error
                    
                    for (i = 0; i < account1.size() - 1; i++) { //check for alphanumeric excludes "_"
                        if (!isalnum(account1[i])) {
                            if (account1[i] == 95) {} //actual part that excludes "_"
                            else if (account1 == "") { //special case for weird empty account name at end of file
                                return 0;
                            }
                            else //if account name is not alpha numeric and was not labeled that becuase of an underscore
                                return -1; //integer to represent invalid file
                        }
                    }
                    
                    for (i = 0; i < account2.size() - 1; i++) { //check for alphanumeric excludes "_"
                        if (!isalnum(account2[i])) {
                            if (account2[i] == 95) {} //actual part that excludes "_"
                            else if (account2 == "") { //special case for weird empty account name at end of file
                                return 0;
                            }
                            else //if account name is not alpha numeric and was not labeled that becuase of an underscore
                                return -1; //integer to represent invalid file
                        }
                    }
                    
                    if (AccountExists(account1) == -1) { //if the account does not exist
                        Node *tempNode = new Node(account1); //create a node for it
                        _nodez.push_back(tempNode); //put it into the vector
                    }
                    if (AccountExists(account2) == -1) { //same as above but ofr account2
                        Node *tempNode2 = new Node(account2);
                        _nodez.push_back(tempNode2);
                    }
                    if(AccountExists(account1) != -1 && AccountExists(account2) != -1) { //if both accounts already exist
                        Edge *followerEdge; //create following edge
                        Edge *followingEdge; //create followers edge
                        followerEdge = new Edge(_nodez.at(AccountExists(account2)));
                        _nodez.at(AccountExists(account1))->_followersList.push_back(followerEdge); //puts edge into edge vector for that account
                        _nodez.at(AccountExists(account1))->incNumFollowers(); //increment followers
                        followingEdge = new Edge(_nodez.at(AccountExists(account1))); //puts edge into edge vector for that account
                        _nodez.at(AccountExists(account2))->_followingList.push_back(followingEdge);
                        ++numPasses;
                    }
                }
            }
        }
    }
    _inputFile.close(); //close input file
    
    return 0; //tells main that everything is fine
}


void Graph::WriteOutputsToFile(string account) { //writes outputs to file
    if (_outputFileName != NULL) { //checks if filename is valid
        _outputFile.open(_outputFileName); //opens file
        
        if (_outputFile.good()) { //checks that file is good
            if (_outputFile.is_open()) { //checks that file is open
                _outputFile << "Looking for new accounts for " << account << " (" << AnalyzeNode(account) << ") to follow" << endl; //writes output statement
                vector<Node> reccommendations; //list for reccommendations
                reccommendations = CalcCentrality(account); //sets reccommendations
                
                if (account == "") {} //case for accounts with no characters
                else { //lower cases all reccommendations for sorting
                    for (unsigned int i = 0; i < reccommendations.size(); i++) {
                        for (unsigned int j = 0; j < reccommendations.at(i).getAccount().size(); j++)
                            reccommendations.at(i).account[j] = tolower(reccommendations.at(i).getAccount()[j]);
                    }
                }
                sort(reccommendations.begin(), reccommendations.end()); //sorts reccomendations
            
                for (unsigned int i = 0; i < reccommendations.size(); ++i) { //writes reccommendations to output file
                    _outputFile << reccommendations.at(i).getAccount() << " (" << reccommendations.at(i).getNumFollowers() << ")" << endl;
                }
                reccommendations.at(i). << 
                    
                }
            }
        }
    }
    _outputFile.close(); //closes file
}

int Graph::AnalyzeNode(string account) { //analyzes specific node
    int followers = 0;
    
    followers = _nodez.at(AccountExists(account))->getNumFollowers(); //returns number of follower
    
    return followers;
}

vector<Node*> Graph::getNodez() const { //getter for node vector
    return this->_nodez;
}

int Graph::AccountExists(string accountName) { //checks if account exists
    unsigned int i = 0;
    int index = -1; //default if account doesn't exist
    
    if (_nodez.size() != 0) { //special case for when the vector is empty
    for (i = 0; i < _nodez.size(); ++i) { //checks all nodes for if account exists
        if (accountName == _nodez.at(i)->getAccount()) { //if found returns index to account
            index = i;
            return index;
    }
    }
    }

    return index; //else returns -1 to indicate account doesn't exist yet
}

void Graph::CreateEmptyFile() { //creates empty file
    
    if (_outputFileName != NULL) { //checks if file name is valid
        _outputFile.open(_outputFileName); //opens file
        
        if (_outputFile.good()) { //checks that file is good
            if (_outputFile.is_open()) { //checks if file is open
                _outputFile << ""; //writes nothing
            }
        }
    }
    _outputFile.close(); //closes file
    
}

vector<Node> Graph::CalcCentrality(string rootAccount) { //function to calculate reccommendations
    vector<Node> toRecommend; //vector to store reccomendations
    unsigned int i = 0;
    unsigned int j = 0;
    unsigned int k = 0;
    
    for (i = 0; i < getNodez().at(AccountExists(rootAccount))->_followingList.size(); ++i) { //basically the search algorithm
        Node tempNode = *getNodez().at(AccountExists(rootAccount))->_followingList.at(i)->GetDestNode(); //variable to store current node for pushback
        for (j = 0; j < tempNode._followingList.size(); ++j) { //iterates through all adjacent nodes
            Node tempNode2 = *tempNode._followingList.at(j)->GetDestNode(); //variable to store current node for pushback
            for (k = 0; k < tempNode2._followingList.size(); ++k) { //iterates through all adjacent nodes
                Node tempNode3 = *tempNode2._followingList.at(k)->GetDestNode(); //variable to store current node for pushback
                if (AlreadyFollowing(getNodez().at(AccountExists(rootAccount)), tempNode3) == false) { //checks if already following
                    if (AccountExistsReccommendations(tempNode3.getAccount(), toRecommend) == -1) //checks if already in reccommendations list
                        toRecommend.push_back(tempNode3); //pushes node into vector
                }
            }
            if (AlreadyFollowing(getNodez().at(AccountExists(rootAccount)), tempNode2) == false) { //checks if already following
                if (AccountExistsReccommendations(tempNode2.getAccount(), toRecommend) == -1) //checks if already in reccommendations list
                    toRecommend.push_back(tempNode2); //pushes node into vector
            }
        }
        if (AlreadyFollowing(getNodez().at(AccountExists(rootAccount)), tempNode) == false) { //checks if already following
            if (AccountExistsReccommendations(tempNode.getAccount(), toRecommend) == -1) //checks if already in reccommendations list
                toRecommend.push_back(tempNode); //pushes node into vector
        }
    }
    return toRecommend;
}

int Graph::AccountExistsReccommendations(string accountName, vector<Node> recommendations) { //checks if account exists
    unsigned int i = 0;
    int index = -1; //default if account doesn't exist
    
    if (recommendations.size() != 0) { //special case for when the vector is empty
        for (i = 0; i < recommendations.size(); ++i) { //checks all nodes for if account exists
            if (accountName == recommendations.at(i).getAccount()) { //if found returns index to account
                index = i;
                return index;
            }
        }
    }
    
    return index; //else returns -1 to indicate account doesn't exist yet
}


bool Graph::AlreadyFollowing(Node* rootAccount, Node account) { //checks if root node is already following the current node
    unsigned int i = 0;
    
    for (i = 0; i < getNodez().at(AccountExists(rootAccount->getAccount()))->getFollowingList().size(); ++i) { //iterates through list
        if (account.getAccount() == rootAccount->getFollowingList().at(i)->GetDestNode()->getAccount()) //check
            return true;
        if (rootAccount->getAccount() == account.getAccount()) //checks if the reccommendatio is the root itself
            return true;
    }
    return false;
}

