//classes and public functions. 
#include <iostream>
#include <vector>

using namespace std;

class Commercial
{
    private:
    vector<vector<char>> vvc_workingVector;
    vector<vector<char>> vvc_shapshotVector;
    // bool b_testingMode;
    bool b_powerAdj;
    int i_availableWorkers;
    int i_generalPop;
    int i_products;
    int i_commercialStartX;
    int i_commercialStartY;
    int i_commercialEndX;
    int i_commercialEndY;
    int i_commercialXLength;
    int i_commercialYLength;
    int i_powerX;
    int i_powerY;

    public:
    Commercial(vector<vector<char>> map);

    void findCommercialZone();
    void powerAdj();
    bool numAdj(int* cords, int givinX, int givinY, char key, int numNeeded);

    int getAvailWorker(); //Do these need to be void or int?????? are we returning something??????
    int getAvailGood();
    int getGenPop();
    vector<vector<char>> deleteWorker(int c,vector<vector<char>> regionMap);
    int getCellPop(int x, int y);
    int* nextCell(int, int);
    int simulation(int i_availableWorkers, int i_products, vector<vector<char>> region);
    int regionSearch(int user_startRow, int user_startCol, int user_endRow, int user_endCol);

    void printArea();
    vector<vector<char>> getRegion();
};
