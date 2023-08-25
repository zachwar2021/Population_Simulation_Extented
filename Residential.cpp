#include <iostream>
#include <vector>
#include <string>
#include "City.h"
#include "Residential.h"
using namespace std;


/*
    Reidential Constructor:
      ~Takes 2D vector of the initial region layout
      ~Finds start and end index of Residential region; saves to class
*/
Residential::Residential(vector<vector<char>> layout){

    // two member variables for managing changing 
    region_static = layout;
    region = layout;

    // bools that manage whether or not the index values have been found
    bool startFound = false;
    bool endFound = false;

    // detect R boundaries:
    for(int row=0; (row < region.size()) && (endFound == false); row++){             // iterate through row and col respectively
        for (int col=0; (col < region[0].size()) && (endFound == false); col++){     // to find starting index

            if(!startFound){
                if(region_static[row][col] == 'R'){
                    startRow = row;
                    startCol = col;
                    startFound = true;
                }
            }

            if(startFound){ // if start index has been identified

                for(int c_index = col; !endFound; c_index++){
                    if (region_static[row][c_index] != 'R'){
                        endCol = c_index-1;
                        endFound = true;
                    } else if (c_index+1 == region_static[0].size()){    // identifies if the row backs to an edge in the matrix
                        endCol = c_index;
                        endFound = true;
                    }
                }

                endFound = false; // resets to find row
                
                for(int r_index=startRow; !endFound; r_index++){

                    if (region_static[r_index][col]  != 'R'){
                        endRow = r_index-1;
                        endFound = true;

                    } else if (r_index+1 == region_static.size()){    // identifies if the row backs to an edge in the matrix
                        endRow = r_index;
                        endFound = true;
                    } 
                }
            }

        }
    }

}



/*
    getRegion:
      ~Takes nothing
      ~Returns the member 2D vector storing region data
*/
vector<vector<char>> Residential::getRegion(){
    return region_static;
}



/*
    resSim:
      ~Takes a 2D vector representing current region state
      ~Returns an int representing number of workers added this iteration
      ~Adds population according to these rules, in this order:
        * increment cell if: cell population = 0 AND, is adjacent to power OR to a populated cell
        * increment cell if: cell population = (1 or 2 or 3 or 4) AND
*/
int Residential::resSim( vector<vector<char>> layout){

    // iterate through R field

    // count will update total and available workers in main
    int count=0;
    region = layout;


    for (int row=startRow; row<=endRow; row++){      // iterate through row and col respectively
        for (int col=startCol; col<=endCol; col++){
            bool cell_change = false; // local variable to ensure that a cell does not get adjusted twice

            // if cell pop = 0
            if(region_static[row][col] == 'R'){
                if(isAdjPower(row, col) || (isAdjPop(row, col, 1))){    // if adjacent to a powerline
                    region[row][col] = '1';   
                    //empMap[row][col].push_back('U');    //record Unemployed worker into employment map when worker generated
                    empMap[row].push_back('U');
                    cell_change = true;                 //essentially all generated new workers are unemployed by default
                    count++;
                }
            }

            if (!cell_change ){ // if no change has occurred in this cell yet

                // case variable is the value of the cell
                switch(region_static[row][col]){
                    case '1':
                        if (isAdjPop(row, col, 1) >1){
                            region[row][col]++;
                            empMap[row].push_back('U');    //record Unemployed worker into employment map when worker generated
                            count++;                            //essentially all generated new workers are unemployed by default
                        }
                        break;
                    
                    case '2':
                        if (isAdjPop(row, col, 2) >= 4){
                            region[row][col]++;
                            empMap[row].push_back('U');    //record Unemployed worker into employment map when worker generated
                            count++;                            //essentially all generated new workers are unemployed by default
                        }
                        break;

                    case '3':
                        if (isAdjPop(row, col, 3) >= 6){
                            region[row][col]++;
                            empMap[row].push_back('U');    //record Unemployed worker into employment map when worker generated
                            count++;                            //essentially all generated new workers are unemployed by default
                        }
                        break;

                    case '4':
                        if (isAdjPop(row, col, 4) >= 8){
                            region[row][col]++;
                            empMap[row].push_back('U');    //record Unemployed worker into employment map when worker generated
                            count++;                            //essentially all generated new workers are unemployed by default
                        }
                        break;

                }
            }
        }
    }
    
    // Update region_static
    region_static = region;


    return count;
}


int Residential::resAirportSim( vector<vector<char>> layout){

    // iterate through R field

    // count will update total and available workers in main
    int count=0;
    region = layout;


    for (int row=startRow; row<=endRow; row++){      // iterate through row and col respectively
        for (int col=startCol; col<=endCol; col++){
            bool cell_change = false; // local variable to ensure that a cell does not get adjusted twice

            // if cell pop = 0
            if(region_static[row][col] == 'R'){
                if(isAdjPower(row, col) || (isAdjPop(row, col, 1))){    // if adjacent to a powerline
                    region[row][col] = '1';   
                    //empMap[row][col].push_back('U');    //record Unemployed worker into employment map when worker generated
                    empMap[row].push_back('U');
                    cell_change = true;                 //essentially all generated new workers are unemployed by default
                    count++;
                }
            }

            if (!cell_change ){ // if no change has occurred in this cell yet

                // case variable is the value of the cell
                switch(region_static[row][col]){
                    case '1':
                        if (isAdjPop(row, col, 1) >1){
                            region[row][col]++;
                            empMap[row].push_back('U');    //record Unemployed worker into employment map when worker generated
                            count++;                            //essentially all generated new workers are unemployed by default
                        }
                        break;
                    
                    case '2':
                        if (isAdjPop(row, col, 2) >= 2){//changed from 4 to 2
                            region[row][col]++;
                            empMap[row].push_back('U');    //record Unemployed worker into employment map when worker generated
                            count++;                            //essentially all generated new workers are unemployed by default
                        }
                        break;

                    case '3':
                        if (isAdjPop(row, col, 3) >= 4){//changed from 6 to 4
                            region[row][col]++;
                            empMap[row].push_back('U');    //record Unemployed worker into employment map when worker generated
                            count++;                            //essentially all generated new workers are unemployed by default
                        }
                        break;

                    case '4':
                        if (isAdjPop(row, col, 4) >= 6){//changed from 8 to 6
                            region[row][col]++;
                            empMap[row].push_back('U');    //record Unemployed worker into employment map when worker generated
                            count++;                            //essentially all generated new workers are unemployed by default
                        }
                        break;

                }
            }
        }
    }
    
    // Update region_static
    region_static = region;


    return count;
}



/*
    isAdjPower:
      ~Takes int row and int column value for the cell to be searched
      ~Systematically searches adjacent cells, adjusting for searching border values
      ~Returns bool stating whether it IS adjacent (1) or IS NOT adjacent (0) to power
*/
bool Residential::isAdjPower(int row, int col){

    // if not a border cell 
    if(((row+1) < region.size()) &&
       ((row-1) >= 0) &&
       ((col+1) < region[0].size()) &&
       ((col-1) >= 0)){
        if ((region_static[row-1 ][col-1 ] == 'T') || 
            (region_static[row-1 ][col] == 'T') ||
            (region_static[row-1 ][col+1 ] == 'T') || 
            (region_static[row][col-1] == 'T') ||
            (region_static[row][col+1 ] == 'T') || 
            (region_static[row+1][col-1] == 'T') ||
            (region_static[row+1][col] == 'T') ||
            (region_static[row+1][col+1] == 'T')){
            return true;
        }
    } else if((row-1 < 0) && (col-1 < 0)){ // if cell is in top left
        if ((region_static[row][col+1 ] == 'T') || 
            (region_static[row+1][col] == 'T') ||
            (region_static[row+1][col+1] == 'T')){
            return true;
        }
    } else if ((row-1 < 0) && (col+1 < region[0].size())){ // if cell is in top right
        if ((region_static[row][col-1] == 'T') ||
            (region_static[row+1][col-1] == 'T') ||
            (region_static[row+1][col] == 'T')){
            return true;
        }
    } else if (((row+1) < region.size()) && (col-1 < 0)){ // if cell is in bottom left
        if ((region_static[row-1 ][col] == 'T') ||
            (region_static[row-1 ][col+1 ] == 'T') || 
            (region_static[row][col+1 ] == 'T')){
            return true;
        }
    } else if (((row+1) < region.size()) && ((col+1) < region[0].size())){ // if cell is in  bottom right
        if ((region_static[row-1 ][col-1 ] == 'T') || 
            (region_static[row-1 ][col] == 'T') ||
            (region_static[row][col-1] == 'T')){
            return true;
        }
    } else if ((row+1) >= region.size()){  // if cell is in bottom row
        if ((region_static[row-1 ][col-1 ] == 'T') || 
            (region_static[row-1 ][col] == 'T') ||
            (region_static[row-1 ][col+1 ] == 'T') || 
            (region_static[row][col-1] == 'T') ||
            (region_static[row][col+1 ] == 'T')){
            return true;
        }
    } else if ((row-1) < 0){  // if cell is in top row
        if ((region_static[row][col-1] == 'T') ||
            (region_static[row][col+1 ] == 'T') || 
            (region_static[row+1][col-1] == 'T') ||
            (region_static[row+1][col] == 'T') ||
            (region_static[row+1][col+1] == 'T')){
            return true;
        }
    } else if ((col+1) >= region[0].size()){  // if cell is in rightmost column
        if ((region_static[row-1 ][col-1 ] == 'T') || 
            (region_static[row-1 ][col] == 'T') ||
            (region_static[row][col-1] == 'T') ||
            (region_static[row+1][col-1] == 'T') ||
            (region_static[row+1][col] == 'T')){
                return true;
            }
    } else if ((col-1) < 0){  // if cell is in leftmost column
        if((region_static[row-1 ][col] == 'T') ||
           (region_static[row-1 ][col+1 ] == 'T') || 
           (region_static[row][col+1 ] == 'T') || 
           (region_static[row+1][col] == 'T') ||
           (region_static[row+1][col+1] == 'T')){
            return true;
        }
    }

    // if none is true, then: 
    return false;
}



/*
    isAdjPop:
      ~Takes int row and column value for cell, as well as a population value to be searched for
      ~Adds 1 to count for each adjacent cell that is equal to or greater than int pop
      ~Returns integer count for each qualifying neighbor
*/
int Residential::isAdjPop(int row, int col, int pop){
    int count = 0; //count of all adj nodes that meet criteria
    
    // if not a border cell 
    if(((row+1) < region_static.size()) &&
       ((row-1) >= 0) &&
       ((col+1) < region_static[0].size()) &&
       ((col-1) >= 0)){
        if ((region_static[row-1 ][col-1 ]-'0' >= pop) &&
            (isdigit(region_static[row-1][col-1])))  {
                count++;
        }

        if ((region_static[row-1 ][col]-'0' >= pop) &&
            (isdigit(region_static[row-1][col])))  {
                count++;
        }

        if ((region_static[row-1 ][col+1 ]-'0' >= pop) &&
            (isdigit(region_static[row-1][col+1])))  {
                count++;
        }

        if ((region_static[row][col-1]-'0' >= pop) &&
            (isdigit(region_static[row][col-1])))  {
                count++;
        }

        if ((region_static[row][col+1 ]-'0' >= pop) &&
            (isdigit(region_static[row][col+1])))  {
                count++;
        }

        if ((region_static[row+1][col-1]-'0' >= pop) &&
            (isdigit(region_static[row+1][col-1])))  {
                count++;
        }
        if ((region_static[row+1][col]-'0' >= pop) &&
            (isdigit(region_static[row+1][col])))  {
                count++;
        }//
        
        if ((region_static[row+1][col+1]-'0' >= pop) &&
            (isdigit(region_static[row+1][col+1])))  {
                count++;
        }
    } else if((row-1 < 0) && (col-1 < 0)){  // if cell is in top left
        if ((region_static[row][col+1 ]-'0' >= pop) &&
            (isdigit(region_static[row][col+1])))  {
                count++;
        }
        
        if ((region_static[row+1][col]-'0' >= pop) &&
            (isdigit(region_static[row+1][col])))  {
                count++;
        }
        
        if ((region_static[row+1][col+1]-'0' >= pop) &&
            (isdigit(region_static[row+1][col+1])))  {
                count++;
        }
    } else if ((row-1 < 0) && (col+1 < region_static[0].size())){  // if cell is in top right
        if ((region_static[row][col-1]-'0' >= pop) &&
            (isdigit(region_static[row][col-1])))  {
                count++;
        }

        if ((region_static[row+1][col-1]-'0' >= pop) &&
            (isdigit(region_static[row+1][col-1])))  {
                count++;
        }

        if ((region_static[row+1][col]-'0' >= pop) &&
            (isdigit(region_static[row+1][col])))  {
                count++;
        }
    } else if (((row+1) < region_static.size()) && (col-1 < 0)){ // if cell is in bottom left
        if ((region_static[row-1 ][col]-'0' >= pop) &&
            (isdigit(region_static[row-1][col])))  {
                count++;
        }

        if ((region_static[row-1 ][col+1 ]-'0' >= pop) &&
            (isdigit(region_static[row-1][col+1])))  {
                count++;
        }

        if ((region_static[row][col+1 ]-'0' >= pop) &&
            (isdigit(region_static[row][col+1])))  {
                count++;
        }
    } else if (((row+1) < region_static.size()) && ((col+1) < region_static[0].size())){ // if cell is in  bottom right
        if ((region_static[row-1 ][col-1 ]-'0' >= pop) &&
            (isdigit(region_static[row-1][col-1])))  {
                count++;
        }

        if ((region_static[row-1 ][col]-'0' >= pop) &&
            (isdigit(region_static[row-1][col])))  {
                count++;
        }

        if ((region_static[row][col-1]-'0' >= pop) &&
            (isdigit(region_static[row][col-1])))  {
                count++;
        }
    } else if ((row+1) >= region_static.size()){  // if cell is in bottom row
        if ((region_static[row-1 ][col-1 ]-'0' >= pop) &&
            (isdigit(region_static[row-1][col-1])))  {
                count++;
        }

        if ((region_static[row-1 ][col]-'0' >= pop) &&
            (isdigit(region_static[row-1][col])))  {
                count++;
        }

        if ((region_static[row-1 ][col+1 ]-'0' >= pop) &&
            (isdigit(region_static[row-1][col+1])))  {
                count++;
        }

        if ((region_static[row][col-1]-'0' >= pop) &&
            (isdigit(region_static[row][col-1])))  {
                count++;
        }

        if ((region_static[row][col+1 ]-'0' >= pop) &&
            (isdigit(region_static[row][col+1])))  {
                count++;
        }
    } else if ((row-1) < 0){  // if cell is in top row
        if ((region_static[row][col-1]-'0' >= pop) &&
            (isdigit(region_static[row][col-1])))  {
                count++;
        }

        if ((region_static[row][col+1 ]-'0' >= pop) &&
            (isdigit(region_static[row][col+1])))  {
                count++;
        }

        if ((region_static[row+1][col-1]-'0' >= pop) &&
            (isdigit(region_static[row+1][col-1])))  {
                count++;
        }
        if ((region_static[row+1][col]-'0' >= pop) &&
            (isdigit(region_static[row+1][col])))  {
                count++;
        }
        
        if ((region_static[row+1][col+1]-'0' >= pop) &&
            (isdigit(region_static[row+1][col+1])))  {
                count++;
        }
    } else if ((col+1) >= region_static[0].size()){  // if cell is in rightmost column
        if ((region_static[row-1 ][col-1 ]-'0' >= pop) &&
            (isdigit(region_static[row-1][col-1])))  {
                count++;
        }

        if ((region_static[row-1 ][col]-'0' >= pop) &&
            (isdigit(region_static[row-1][col])))  {
                count++;
        }

        if ((region_static[row][col-1]-'0' >= pop) &&
            (isdigit(region_static[row][col-1])))  {
                count++;
        }

        if ((region_static[row+1][col-1]-'0' >= pop) &&
            (isdigit(region_static[row+1][col-1])))  {
                count++;
        }

        if ((region_static[row+1][col]-'0' >= pop) &&
            (isdigit(region_static[row+1][col])))  {
                count++;
        }
    } else if ((col-1) < 0){  // if cell is in leftmost column
        if ((region_static[row-1 ][col]-'0' >= pop) &&
            (isdigit(region_static[row-1][col])))  {
                count++;
        }

        if ((region_static[row-1 ][col+1 ]-'0' >= pop) &&
            (isdigit(region_static[row-1][col+1])))  {
                count++;
        }
         if ((region_static[row][col+1 ]-'0' >= pop) &&
            (isdigit(region_static[row][col+1])))  {
                count++;
        }

            if ((region_static[row+1][col]-'0' >= pop) &&
            (isdigit(region_static[row+1][col])))  {
                count++;
        }
        
        if ((region_static[row+1][col+1]-'0' >= pop) &&
            (isdigit(region_static[row+1][col+1])))  {
                count++;
        }

    }
    
 
    // Returns count of the number of adjacent nodes >= pop
    return count;
}

/*
    regionSearch:
      ~Takes 4 ints representing user input for the desired region
      ~Assesses where the correct start point is, and calculates region population for residential only
      ~Returns that population
*/
int Residential::regionSearch(int user_startRow, int user_startCol, int user_endRow, int user_endCol){

    if((user_endRow < startRow) || (user_endCol < startCol) ||
    (endRow < user_startRow) || (endCol < user_startCol) ){ // if there is no overlap of user area and region area
        return 0;
    }

    int count = 0;

    int search_startRow;
    int search_startCol;
    int search_endRow;
    int search_endCol;


    if(startRow <= user_startRow){
        search_startRow = user_startRow;
    } else {
        search_startRow = startRow;
    }

    if(endRow >= user_endRow){
        search_endRow = user_endRow;
    } else {
        search_endRow = endRow;
    }

    if(startCol <= user_startCol){
        search_startCol = user_startCol;
    } else {
        search_startCol = startCol;
    }

    if(endCol >= user_endCol){
        search_endCol = user_endCol;
    } else {
        search_endCol = endCol;
    }



    for (int row = search_startRow; row <= search_endRow; row++){
        for (int col = search_startCol; col <= search_endCol; col++){
            if (isdigit(region[row][col])){
                count += (region[row][col] - '0');
            }
        }
    }

    return count;

}

//vector<vector<char>> Residential::assignJob(int count, char x){
//     // if x= 'c'

//     // else if x == 'i'

//     // else if x == 'a'

//     //     for i in x
//     //         for j in y
//     //             find employment[x][y] that contains 'u'
//                     // employment[x][y] == x;
// }


/*
    
    Res::assignJobs intakes a character representative of the employment type of a worker (determined by sim actions
    taken in main.cpp) and assigns that character (job type) to the first unemployed worker ('U') found in the population
    cell being read. These cells are generated into empMap (employment map) when the worker count is increased in the
    cases present in the resSim function. Essentially, when a new worker is generated, they are automatically unemployed
    until assigned a job type through the simulation actions in main.cpp.
    ~ 'C' indicates a Commercial-type worker
    ~ 'I' indicates an Industrial-type worker
    ~ 'A' indicates an Airport-type worker

*/
vector<vector<char>> Residential::assignJobs(int count, char x){

    if(x == 'C' || x == 'I' || x == 'A'){

        for(int i = startRow; i == endRow; i++){

            for(int j = startCol; j == endCol; j++){

                if(empMap[i][j] == 'U'){
                    empMap[i][j] = x;
                    --count;
                    if(count == 0){
                        return empMap;
                    }
                }

            }

        }

    }
return empMap;
}