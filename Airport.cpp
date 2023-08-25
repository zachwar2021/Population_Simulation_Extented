#include <vector>
#include <iostream>
#include <random>
#include "Airport.h"
#include <math.h>
using namespace std;



Airport::Airport(vector<vector<char>> region){
    i_growthTime = rand() % 3 + 3; // number between 3 and 5
    i_growthTime_static = i_growthTime;
    workers = 0; // airport employees
    worker_coefficient = floor(i_growthTime * 1.75);

}

/*Allocate adds a 3X5 block to the left of the map using push_back 
to a new temp vector. Then pushes that back onto a temp 2d vecotr 
of chars of the original region map creating new rows then returns 
the temp 2d vector
The function has one paramiter of a 2d vector of chars
and returns a 3d vector of chars
*/
vector<vector<char>> Airport::allocate(vector<vector<char>> region){ // initializes the area, allocates space
// Zach
    // find closest power line/power plant
    // pick space and allocate 3x5 space like this:
    /*
    @ @ @ @ @
    @ @ x @ @     x = employees
    @ @ @ @ @
    */
    startRow = 0;
    startCol = region[1].size()+1;
    endRow = startRow+2;
    endCol = startCol+2;

    vector<vector<char>> regionTemp;
    vector<char> temp;

    /*
    this loop controls how the underconstruction airport is
    added as well as a buffer zone in between the last region
    and the new airport
    */
    for(int x=0; x<region[1].size();x++)
    {
        temp = region[x];
        temp.push_back(' ');
        if(x < 3)
        {
            temp.push_back('U');
            temp.push_back('U');
            temp.push_back('U');
            temp.push_back('U');
            temp.push_back('U');
        }
        else{
            temp.push_back(' ');
            temp.push_back(' ');
            temp.push_back(' ');
            temp.push_back(' ');
            temp.push_back(' ');
        }
        regionTemp.push_back(temp);
    }

    //this is setting class variables with the new temp
    //region and returning temp region
    startRow = 0;
    startCol = regionTemp[0].size()-5;
    oldEndMapCol = region[0].size()-1;
    oldEndMapRow = region.size()-1;
    endRow = startRow+2;
    endCol = startCol+2;
    return regionTemp;

    //unused code will be deleted when finale revison is turned in
    //commented just in case we need to use later
    /*
    int i_lastPowerLineRow = 0;
    int i_lastPowerLineCol = 0;

    for(int x=0; x < region.size(); x++)
    {
        for(int y=0; y < region[x].size(); y++)
        {
            if(region[x][y] == 'T')
            {
                i_lastPowerLineRow = x;
                i_lastPowerLineCol = y;
            }
        }
    }
    //have to test to see if it works and builds airport and add more if for the length of the 
    //airport
    if(region[i_lastPowerLineRow][i_lastPowerLineCol+1] == ' ')
    {
        startRow = i_lastPowerLineRow;
        startCol = i_lastPowerLineCol+1;
    }
    else if(region[i_lastPowerLineRow+1][i_lastPowerLineCol+1] == ' ')
    {
        startRow = i_lastPowerLineRow+1;
        startCol = i_lastPowerLineCol+1;
    }
    else if(region[i_lastPowerLineRow+1][i_lastPowerLineCol] == ' ')
    {
        startRow = i_lastPowerLineRow+1;
        startCol = i_lastPowerLineCol;
    }
    else if(region[i_lastPowerLineRow+1][i_lastPowerLineCol-1] == ' ')
    {
        startRow = i_lastPowerLineRow+1;
        startCol = i_lastPowerLineCol-1;
    }
    else if(region[i_lastPowerLineRow][i_lastPowerLineCol-1] == ' ')
    {
        startRow = i_lastPowerLineRow;
        startCol = i_lastPowerLineCol-1;
    }
    else if(region[i_lastPowerLineRow-1][i_lastPowerLineCol-1] == ' ')
    {
        startRow = i_lastPowerLineRow-1;
        startCol = i_lastPowerLineCol-1;
    }
    else if(region[i_lastPowerLineRow-1][i_lastPowerLineCol] == ' ')
    {
        startRow = i_lastPowerLineRow-1;
        startCol = i_lastPowerLineCol;
    }
    else if(region[i_lastPowerLineRow-1][i_lastPowerLineCol+1] == ' ')
    {
        startRow = i_lastPowerLineRow-1;
        startCol = i_lastPowerLineCol+1;
    }
    else{
        cout<<"Could not find a open span of cells"<<endl;
    }*/
}

/*buildRoadAndPower is the function that finds an existing road and powerline
and builds a new road and powerline out to the under construction airport.
This should be called before building the airport starts because you need a road 
get to the job site
it has one paramiter of a 2d vector of chars and returns a 2d vector of chars
*/
vector<vector<char>> Airport::buildRoadAndPower(vector<vector<char>> region)
{
    int powerStartRow = 0;
    int powerStartCol = 0;
    int roadStartRow = 0;
    int roadStartCol = 0;
    int powerRowDiff;
    int powerColDiff; 
    int roadRowDiff; 
    int roadColDiff; 
    bool powerFound=false;
    bool roadFound=false;
    /*first finds the rearest power station or power line from top
    to bottom then right to left. This way we dont have to go through 
    every element to find the last instance. Once it has found one of 
    the two it sets two int variables to its x and y coordinates for 
    later in the function. This happens for both power and road.*/
    for(int y=oldEndMapCol; y>=0;y--)
    {
        for(int x=0;x<region.size();x++)
        {            
            if(region[x][y] == 'T' || region[x][y] == 'P' || region[x][y] == '#')
            {
                if(!powerFound)
                {
                    powerStartRow = x;
                    powerStartCol = y;
                    powerFound=true;
                }
                
            }
            if(region[x][y] == '-' || region[x][y] == '#')
            {
                if(!roadFound)
                {
                    roadStartRow = x;
                    roadStartCol = y;
                    roadFound=true;
                }
                
            }
        }
    }
    /*Dont remember what this does*/
    if(powerStartCol == 0 && powerStartRow == 0)
    {
        int lastT = 0;
        for(int x=0;x<region.size();x++)
        {
            if(region[0][x] == 'T' || region[0][x] == 'P')
            {
                lastT = x;
            }
        }
        powerStartRow = 0;
        powerStartCol = 0;
    }
    
    /*this finds and sets the number of spaces between the airport and 
    the starting point for row and col for both power and road*/
    if(powerStartRow <= 2)
        powerRowDiff = 0;
    else
        powerRowDiff = powerStartRow-(startRow+3);
    if(roadStartRow <= 2)
        roadRowDiff = 0;
    else
        roadRowDiff = roadStartRow-(startRow+3);
    
    powerColDiff = startCol-(powerStartCol+1);
    roadColDiff = startCol-(roadStartCol);
    
    //power
    /*these two for loops are for creating new powerlines off of
    an existing powerline or power plant. First it builts powerlines
    accross from left to right and then up if needed*/
    for(int y=1 ;y<=powerColDiff;y++)
    {
        region[powerStartRow][powerStartCol+y] = 'T';
    }
    for(int x=1; x<=powerRowDiff;x++)
    {
        region[powerStartRow+x][powerStartCol] = 'T';
    }

    //road
    /*these two for loops are for creating new roads off of
    an existing roadt. First it builts roads accross from 
    left to right and then up if needed. It also checks to 
    see if the cell has a powerline in it, and if so it places a #*/
    for(int y=1; y<=roadColDiff;y++)
    {
        if(region[roadStartRow][roadStartCol+y]== 'T')
        {
            region[roadStartRow][roadStartCol+y]= '#';
        }
        else
        {
            region[roadStartRow][roadStartCol+y] = '-';
        }
    }
    for(int x=1; x<=roadRowDiff;x++)
    {
        if(region[roadStartRow-x][roadStartCol+roadColDiff] == 'T')
        {
            region[roadStartRow-x][roadStartCol+roadColDiff] = '#';
        }
        else
        {
            region[roadStartRow-x][roadStartCol+roadColDiff] = '-';
        }
    }

    return region;
}

vector<vector<char>> Airport::build(vector<vector<char>> region, int availWorkers){ // function for building, runs until fully built
    
    if (availWorkers){
        workers += 1;
    } else {
        return region;
    }
    
    region[startRow+1][startCol+2] = 1 + (region[startRow+1][startCol+2] - '0'); // increments cell worker pop

    // decrement to signal how close to being built it is
    i_growthTime--;
    int newWorkers = 1;
    return region;
}

vector<vector<char>> Airport::simulation(vector<vector<char>> region, int availWorkers){ // function that grows airport, calls build
    workers = 0;

    if(i_growthTime){
        region = build(region, availWorkers);

        return region;
    } else { // if its done building
        if ((workers<= worker_coefficient) && availWorkers){ // if more workers can be hired and there are available employees
            workers++;
            region[startRow+1][startCol+2] = 1 + (region[startRow+1][startCol+2] - '0'); // increments cell worker pop
            int workers = 1;
        }
    }




        

    // goods production



    return region;
}

int Airport::getNewWorkers(){
    return workers;
}

