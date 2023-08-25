#include "City.h"
#include "Residential.h"
#include <iostream>
#include <vector>
#include <string>
using namespace std;

    // constructor
    City::City(){
        change_I = false;
        change_R = false; 
        change_C = false;
    }

    // initialization
    void City::init(vector<vector<char>> regionMap, string refreshR, string time){
        region = regionMap;
        region_static = regionMap;
        refresh = refreshR;
        timeMax = time;

        timestep = 0;
    }
    
    bool City::isAdjPower(int row, int col){
        // returns whether an adjacent value is a power source
        /*
            This if statement tests all 8 neighbors in this pattern:
                1   2   3
                4   -   6
                7   8   9
        */
        if ((region[row-1 ][col-1 ] == 'T') ||
        (region[row-1 ][col] == 'T') ||
        (region[row-1 ][col+1 ] == 'T') ||
        (region[row][col-1] == 'T') ||
        (region[row][col+1 ] == 'T') || 
        (region[row+1][col-1] == 'T') ||
        (region[row+1][col] == 'T') ||
        (region[row+1][col+1] == 'T')){
            return true;
        }


        return false;
    }

    int City::isAdjPop(int row, int col, int pop){
        // search all adj nodes for # >= pop
        // searches in same pattern from isAdjPower
        int count = 0; //count of all adj nodes that meet criteria
        
        /*
            Assesses each adjacent node and,
            if the value satisfies the adjacency population
            search, it increments count
        */
        if ((region[row-1 ][col-1 ] >= pop) &&
            (isdigit(region[row-1][col-1])))  {
                count++;
        }

        if ((region[row-1 ][col] >= pop) &&
            (isdigit(region[row-1][col])))  {
                count++;
        }

        if ((region[row-1 ][col+1 ] >= pop) &&
            (isdigit(region[row-1][col+1])))  {
                count++;
        }

        if ((region[row][col-1] >= pop) &&
            (isdigit(region[row][col-1])))  {
                count++;
        }

        if ((region[row][col+1 ] >= pop) &&
            (isdigit(region[row][col+1])))  {
                count++;
        }

        if ((region[row+1][col-1] >= pop) &&
            (isdigit(region[row+1][col-1])))  {
                count++;
        }
        if ((region[row+1][col] >= pop) &&
            (isdigit(region[row+1][col])))  {
                count++;
        }
        
        if ((region[row+1][col+1] >= pop) &&
            (isdigit(region[row+1][col+1])))  {
                count++;
        }
        
        // Returns count of the number of adjacent nodes >= pop
        return count;
    }

    void City::display(){
        for(int row=0; row<region.size(); row++){               // Iterate through row
            for(int col=0; col<region[0].size(); col++){        // Iterate through node in a row
                cout << region[row][col] << "  ";               // Print node data
            }
            cout << endl;
        }
    }

    void City::printArea(int colS, int rowS, int colE, int rowE) {
        for(int row = rowS; row <= rowE; row++){                 // Iterate through row
            for(int col = colS; col <= colE; col++){          // Iterate through node in a row
                cout << region[row][col] << "  ";               // Print node data
            }
            cout << endl;
        }
    }

    void City::setRegion(vector<vector<char>> layout){
        region = layout;
    }

    void City::setRegion_static(vector<vector<char>> layout){
        region_static = layout;
    }


    
