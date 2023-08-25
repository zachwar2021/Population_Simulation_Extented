//#ifndef INDUSTRIAL_H
//#define INDUSTRIAL_H

#include <iostream>
#include <vector>
#include <ctype.h>
#include <stdlib.h>

using namespace std;

class Industrial
{
    //x is rows
    //y is columns
    private:
    vector<vector<char>> vvc_workingVector;
    vector<vector<char>> vvc_shapshotVector;
    int i_availableWorkers;
    int i_products; //Max amount is 1*cellPop
    int i_generalPop; //AKA workers
    bool b_powerAdj;
    // bool b_testingMode;
    int i_industrialStartX;
    int i_industrialStartY;
    int i_industrialXLength;
    int i_industrialYLength;
    int i_powerX;
    int i_powerY;

    public:
    Industrial(vector<vector<char>>);

    int getNumAvailableWorkers();
    int getNumProducts();
    int getgeneralPop();
    vector<vector<char>> deleteWorker(int,vector<vector<char>>);
    int getCellPop(int, int);
    int* getIndustrialZoneCord();

    void setNumAvailableWorkers(int);

    void findIndustrialZone();
    void powerAdj();
    int* nextCell(int, int);
    bool numAdj(int*, int, int, char, int);
    vector<vector<char>> simulation();

    void printArea();

    void setWorkingVector(vector<vector<char>>);
    int regionSearch(int, int, int, int);
    int getLargest();
};

//#endif