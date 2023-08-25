#include <iostream>

#include "PlaneCrash.h"

using namespace std;

PlaneCrashfunc::PlaneCrashfunc(){crash = 0;}

//simulates plane crash between 1-10 chances   
bool PlaneCrashfunc::ChanceOfPlaneCrash(bool airportBuilt)
{
    srand (time(NULL));
    crash = rand() % 10 + 1;

    if (airportBuilt = true)
    {
        if (crash == 2)
        {
            return true;
        }
        return false;
    } 
    else
    {
        return false;
    }
}

//Hits the town in a random spot 
//Add impact of crash onto region map inside simulation 
int* PlaneCrashfunc::sim(vector<vector<char>> region)
{
    bool cell_change = false;
    int cout = 0; 
    int yBound = region[0].size();
    int xBound = region.size();
   
    srand (time(NULL));
    static int coords[2];
    coords[1]= rand() % yBound;//ycoord
    coords[0]= rand() % xBound;//xcoord

    return coords;
} 