#include <iostream>
#include <vector>
#include <string>
#include <fstream>
using namespace std;

class City{
friend class Residential;
private:
    // vector of vector setups
    vector<vector<char>> region_static;     // This WILL NOT change
    vector<vector<char>> region;            // changing region layout 

/*
    Measures whether or not change has occurred.
    These are each function's RETURN
*/
    bool change_I;
    bool change_R;
    bool change_C;

    int timestep; // tracks number of timesteps

/*
    Config file information
*/
    string refresh;
    string timeMax;


public:
    // initialize functions
    City();

    void init(vector<vector<char>> regionMap, string refreshR, string time);
    
    bool isAdjPower(int row, int col);

    int isAdjPop(int row, int col, int pop);

    void display();

    void printArea(int colS, int rowS, int colE, int rowE);

    void setRegion(vector<vector<char>> regionMap);

    void setRegion_static(vector<vector<char>> layout);
};