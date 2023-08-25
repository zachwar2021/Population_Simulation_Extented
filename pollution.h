#include <iostream>
#include <string>
#include <vector>
#include <ctype.h>

using namespace std;

class Pollution{
    //x is rows
    //y is columns
    private:
    
    vector<vector<string>> region; // this one won't be altered; will be used for reference
    vector<vector<string>> regionPolluted;
    vector<vector<char>> c_regionPolluted;


    int numPollution;
    
    int colS, rowS, colE, rowE;
    //int cordies[4] = {1,0,3,2};


    public:
    //constructor
    Pollution(int* cordies, vector<vector<string>>);

    void pollutionDisplay();//display function

    int getNumPollution();//getter

    //called the find value function to compare strings against each other, then calls the set pollution funciton to adjust value if needed
    void spreadPollution(int,int);

    //this function should call the spreadpollution function, it also tallies the value of pollution
    void polluteArea();

    //changes the contets of the string to an appropriate pollution value
    void setPollution(int,int,int,int);

    //returns an integer value from the string given, or zero if there is no integer
    int findvalue(int row, int col);
    //prints the 2d string vector regionPolluted
    //void printPollution();
    //idk if i need this
    int regionSearch(int user_startRow, int user_startCol, int user_endRow, int user_endCol);

    //this function should take in coordinates and add pollution to the tile, then spread to nearby tiles.
    void crashPollution(int row, int col);

};