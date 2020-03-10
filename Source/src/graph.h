//------------------------------------------------------------------------------------------------
//
// File: graph.h
// Author: ECE 275 Spring 2016
// Date: April 14, 2016
//
// Description:
//
//------------------------------------------------------------------------------------------------

#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <iostream>
#include <fstream>

#include "node.h"

using namespace std;

class Graph {
private:
   // Using a vector (or other ADT) of Node* ensure the Graph maintains a single
   // copy of each Node. The Edge class also contains a pointer to a Node, which points to
   // to the nodes in the graph. This way all pointers to the Node are the same node
   // and not a copy of the nodes. So, we can stored temporary values within the nodes when
   // we implement various graph algorithms
   vector<Node*> _nodez;
    char *_inputFileName;
    char *_outputFileName;
    ifstream _inputFile;
    ofstream _outputFile;
   
public:
   // Other public methods go here.
    Graph () {}; //default constructor
    Graph (char *_filename1, char *_outfilename1) : _inputFileName(_filename1), _outputFileName(_outfilename1) {}; //constructor for initializing files
    int ReadInputsFromFile(); //reads inputs
    void WriteOutputsToFile(string account); //writes output
    void CreateEmptyFile(); //creates empty file for invalid file
    int AnalyzeNode(string account); //analyzes specific node
    
    int AccountExists(string accountName); //checks if account exists
    int AccountExistsReccommendations(string accountName, vector<Node> recommendations); //checks  if accounts exists in reccommendations list
    bool AlreadyFollowing(Node* rootAccount, Node account); //checks if root node is already following
    vector<Node> CalcCentrality(string account); //finds reccommendations
    
    vector<Node*> getNodez() const; //getter for nodes list
};

#endif

//------------------------------------------------------------------------------------------------


