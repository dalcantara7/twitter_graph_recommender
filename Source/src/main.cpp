//------------------------------------------------------------------------------------------------
//
// File: main.cpp
// Author: ECE 275 Spring 2016
// Date: April 14, 2016
//
// Description:
//
//------------------------------------------------------------------------------------------------

#include <iostream>
#include <cstdlib>
#include <cstdio>
#include "graph.h"

//------------------------------------------------------------------------------------------------

using namespace std;

//------------------------------------------------------------------------------------------------

int main(int argc, char *argv[]) {
    
    if (argc != 4) { //usage statement
        cout << "sna inputFile userName outputFile" << endl;
        return EXIT_FAILURE;
    }
    
    Graph twitterAccounts(argv[1], argv[3]); //instantiates input and output files
    int isGoodFile = 0; //variable for good file type
    
    isGoodFile = twitterAccounts.ReadInputsFromFile(); //handles all the reading of files and also checks if file is valid
    if (isGoodFile == -1) { //if file is invalid
        twitterAccounts.CreateEmptyFile(); //create empty file
        return EXIT_SUCCESS; //end program
    }
    twitterAccounts.AnalyzeNode(argv[2]); //else analyzes node
    twitterAccounts.WriteOutputsToFile(argv[2]); //write output
   
   return 0;
}

//------------------------------------------------------------------------------------------------
