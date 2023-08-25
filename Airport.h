#include <vector>
#include <iostream>
using namespace std;



class Airport{
private:
    int startCol;
    int startRow;
    int endCol;
    int endRow;
    int workers;
    int oldEndMapRow;
    int oldEndMapCol;
    vector<vector<char>> region;
    int i_growthTime;
    int i_growthTime_static;
    int worker_coefficient;

public:
    Airport(vector<vector<char>>);

    vector<vector<char>> build(vector<vector<char>> region, int availWorkers); // function for building 

    vector<vector<char>> buildRoadAndPower(vector<vector<char>>);

    vector<vector<char>> simulation(vector<vector<char>> region, int availWorkers); // function that calls

    vector<vector<char>> allocate(vector<vector<char>>);

    int getNewWorkers();

};


