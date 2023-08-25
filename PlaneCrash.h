#include <iostream>
#include <ctype.h>
#include <vector>
#include <random>

using namespace std;

class PlaneCrashfunc{
    private:
    int crash;

    public:
    PlaneCrashfunc();
    bool ChanceOfPlaneCrash(bool airportBuilt);
    int* sim(vector<vector<char>> region);
    
};