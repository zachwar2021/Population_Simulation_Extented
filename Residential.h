#include <iostream>
#include <vector>
#include <string>
#include <fstream>
using namespace std;



class Residential{
private:
// Variables representing start and end index of Residential region
    int startRow;
    int startCol;
    int endRow;
    int endCol;
// 2D vectors which hold the region layout
    vector<vector<char>> region_static; // changes once per iteration
    vector<vector<char>> region; // changes constantly throughout simulation
    vector<vector<char>> empMap; // 2D vector to fill as a record of employment type for population in cell

public:
    Residential(vector<vector<char>> layout);
    vector<vector<char>> getRegion();
    int resSim(vector<vector<char>> layout);
    int resAirportSim(vector<vector<char>> layout);
    bool isAdjPower(int row, int col);
    int isAdjPop(int row, int col, int pop);
    int regionSearch(int user_startRow, int user_startCol, int user_endRow, int user_endCol);
    vector<vector<char>> assignJobs(int population, char x);    //Places job assignments for population in 2D vector of employment to be returned
};