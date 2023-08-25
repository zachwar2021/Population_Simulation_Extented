#include <iostream>
#include <vector>

#include "Industrial.h"

using namespace std;

/*
construstor that take paramiters of a 2d vector of chars that is a map of the region
and a boolean for testing mod. sets the working and snapshot vector to the passed in 3d vector of chars. 
Then sets the testing varable to the passed in boolean. Also calls powerAdj and findINdustrialZone
*/
Industrial::Industrial(vector<vector<char>> map)
{
    vvc_shapshotVector = map;
    vvc_workingVector = map;
    // b_testingMode = testing;
    i_generalPop = 0;
    powerAdj();
    findIndustrialZone();
}

/*
This is a group of fuctions that accesses a private varable and returns accordingly
*/

int Industrial::getNumAvailableWorkers(){return i_availableWorkers;}
int Industrial::getNumProducts(){return i_generalPop;}
int Industrial::getgeneralPop(){return i_generalPop;}

vector<vector<char>> Industrial::deleteWorker(int i, vector<vector<char>> regionMap)
{
    srand(time(NULL));
    int *temp = getIndustrialZoneCord();
    int x = rand()%(temp[2])+temp[0];
    int y = rand()%(temp[3])+temp[1];
    if(regionMap[x][y] != '1' || regionMap[x][y] != 'I')
    {
        regionMap[x][y]--;
        i_generalPop--;
    }
    else if(regionMap[x][y] == '1'){
        regionMap[x][y] = 'I';
        i_generalPop--;
    }
    else{
        regionMap = deleteWorker(i,regionMap);
    }
     return regionMap;
}

/*
This function finds the population of a certin cell and returns accordingly.
It requires two ints to be passed into the function most likely a x and y cordnate
*/
int Industrial::getCellPop(int x, int y)
{
    int i_cell = static_cast<int>(vvc_shapshotVector[x-1][y-1]);
    if(i_cell >= 0 && i_cell <= 9){
        return  i_cell;
    } else{
        return -1;
    }
}

/*
This function takes the starting location of the INdustrial zone found in when the constructor is called
and puts the x and v into the first two indexes in a int array. Then 
*/

int* Industrial::getIndustrialZoneCord()
{
    static int temp[4];
    temp[0]=i_industrialStartX;
    temp[1]=i_industrialStartY;
    temp[2]=i_industrialStartX + i_industrialXLength;
    temp[3]=i_industrialStartY + i_industrialYLength;
    return temp;
}


/*
THis function takes a passed int and sets a variable to the passed value
*/
void Industrial::setNumAvailableWorkers(int workers){i_availableWorkers = workers;}

/*
This function finds the start x and y cordnates of an Industrial zone. 
It finds the first I wich is most likey the the TOP LEFT. Then sets according variables to the x and y
(i_industrialStartX and i_industrialStartY)
It also counts the length of the zone in its x and y cords accortingly
*/
void Industrial::findIndustrialZone()
{
    bool b_firstI = false;
    bool b_Xcounted = false;
    bool b_Ycounted = false;
    i_industrialXLength=0;
    i_industrialYLength=0;
    for(int x=0; x < vvc_shapshotVector.size(); x++)
    {
        for(int y=0; y < vvc_shapshotVector[x].size(); y++)
        {
            //If it finds the first instance of I
            if(vvc_shapshotVector[x][y] == 'I' && !b_firstI && !b_Ycounted)
            {
                i_industrialStartX = x;
                i_industrialStartY = y;
                b_firstI = true;
                i_industrialYLength++;
            }
            //If its an instance of I if the y line hasnt been counted already
            else if(vvc_shapshotVector[x][y] == 'I' && !b_Ycounted)
            {
                i_industrialYLength++;
            }
            //If its an instance of I if the X cord hasnt been counted already
            if(vvc_shapshotVector[x][y] == 'I' && !b_Xcounted)
            {
                i_industrialXLength++;
                b_Xcounted=true;
            }
        }
        //if the first I is counted sets ycounted to true - meaning the y length has been counted
        //and set b ounted to flase so we can count x one more time in the loop
        if(b_firstI)
        {
            b_Ycounted = true;
            b_Xcounted = false;
        }
    }
    // if(b_testingMode)
    // {
    //     cout<<"start: "<<i_industrialStartX<<" "<<i_industrialStartY<<endl;
    //     cout<<"X length: "<<i_industrialXLength<<endl;
    //     cout<<"Y length: "<<i_industrialYLength<<endl;
    // }
}

/*
This function finds a T and sees if a I in one cell around it meaning the industrial zone has power
*/

void Industrial::powerAdj()
{
    i_powerX = 0;
    i_powerY = 0;
    for(int x=0; x < vvc_shapshotVector.size(); x++)
    {
        for(int y=0; y < vvc_shapshotVector[x].size(); y++)
        {
            //if a cell is a T
            if(vvc_shapshotVector[x][y] == 'T')
            {
                // if(b_testingMode)
                // {
                //     cout<<"Found a t"<<endl;
                // }
                //if the T is on the TOP edge of the map
                if(x == 0)
                {
                    //if the T is on the RIGHT edge of the map
                    if(y==0)
                    {
                        //these search around T to find I starting top left and moves counter clockwise
                        if(vvc_shapshotVector[x][y+1]=='I')
                        {
                            b_powerAdj = true;
                            i_powerX = x;
                            i_powerY = y+1;
                            break;
                        }
                        else if(vvc_shapshotVector[x+1][y+1]=='I')
                        {
                            b_powerAdj = true;
                            i_powerX = x+1;
                            i_powerY = y+1;
                            break;
                        }
                        else if(vvc_shapshotVector[x+1][y]=='I')
                        {
                            b_powerAdj = true;
                            i_powerX = x+1;
                            i_powerY = y;
                            break;
                        }
                    }
                    //if T is on the Left edge of the map
                    else if(y == vvc_shapshotVector[x].size()-1)
                    {
                        //these search around T to find I starting top left and moves counter clockwise
                        if(vvc_shapshotVector[x][y-1]=='I')
                        {
                            b_powerAdj = true;
                            i_powerX = x;
                            i_powerY = y-1;
                            break;
                        }
                        else if(vvc_shapshotVector[x+1][y-1]=='I')
                        {
                            b_powerAdj = true;
                            i_powerX = x+1;
                            i_powerY = y-1;
                            break;
                        }
                        else if(vvc_shapshotVector[x+1][y]=='I')
                        {
                            b_powerAdj = true;
                            i_powerX = x+1;
                            i_powerY = y;
                            break;
                        }
                        
                    }
                    //if T is not on the Left or Right edge of map
                    else
                    {
                        //these search around T to find I starting top left and moves counter clockwise
                        if(vvc_shapshotVector[x][y-1]=='I')
                        {
                            b_powerAdj = true;
                            i_powerX = x;
                            i_powerY = y-1;
                            break;
                        }
                        else if(vvc_shapshotVector[x][y+1]=='I')
                        {
                            b_powerAdj = true;
                            i_powerX = x;
                            i_powerY = y+1;
                            break;
                        }
                        else if(vvc_shapshotVector[x+1][y-1]=='I')
                        {
                            b_powerAdj = true;
                            i_powerX = x+1;
                            i_powerY = y-1;
                            break;
                        }
                        else if(vvc_shapshotVector[x+1][y]=='I')
                        { 
                            b_powerAdj = true;
                            i_powerX = x+1;
                            i_powerY = y;
                            break;
                        }
                        else if(vvc_shapshotVector[x+1][y+1]=='I')
                        {
                            b_powerAdj = true;
                            i_powerX = x+1;
                            i_powerY = y+1;
                            break;
                        }
                        
                    }

                    
                }
                //If T is on the BOTTOM edge of the map
                else if(x == vvc_shapshotVector.size()-1)
                {
                    //If T is on the LEFT edge of the map
                    if(y==0)
                    {
                        //these search around T to find I starting top left and moves counter clockwise
                        if(vvc_shapshotVector[x-1][y]=='I')
                        {
                            b_powerAdj = true;
                            i_powerX = x-1;
                            i_powerY = y;
                            break;
                        }
                        else if(vvc_shapshotVector[x-1][y+1]=='I')
                        {
                            b_powerAdj = true;
                            i_powerX = x-1;
                            i_powerY = y+1;
                            break;
                        }
                        else if(vvc_shapshotVector[x][y+1]=='I')
                        {
                            b_powerAdj = true;
                            i_powerX = x;
                            i_powerY = y+1;
                            break;
                        }
                    }
                    //if T is of the RIGHT edge of the map
                    else if(y == vvc_shapshotVector[x].size()-1)
                    {
                        //these search around T to find I starting top left and moves counter clockwise
                        if(vvc_shapshotVector[x][y-1]=='I')
                        {
                            b_powerAdj = true;
                            i_powerX = x;
                            i_powerY = y-1;
                            break;
                        }
                        else if(vvc_shapshotVector[x-1][y-1]=='I')
                        {
                            b_powerAdj = true;
                            i_powerX = x-1;
                            i_powerY = y-1;
                            break;
                        }
                        else if(vvc_shapshotVector[x-1][y]=='I')
                        {
                            b_powerAdj = true;
                            i_powerX = x-1;
                            i_powerY = y;
                            break;
                        }
                        
                    }
                    //if T is not on the RIGHT or LEFT edge of the map
                    else
                    {
                        //these search around T to find I starting top left and moves counter clockwise
                        if(vvc_shapshotVector[x][y-1]=='I')
                        {
                            b_powerAdj = true;
                            i_powerX = x;
                            i_powerY = y-1;
                            break;
                        }
                        else if(vvc_shapshotVector[x-1][y-1]=='I')
                        {
                            b_powerAdj = true;
                            i_powerX = x-1;
                            i_powerY = y-1;
                            break;
                        }
                        else if(vvc_shapshotVector[x-1][y]=='I')
                        {
                            b_powerAdj = true;
                            i_powerX = x-1;
                            i_powerY = y;
                            break;
                        }
                        else if(vvc_shapshotVector[x-1][y+1]=='I')
                        {
                            b_powerAdj = true;
                            i_powerX = x-1;
                            i_powerY = y+1;
                            break;
                        }
                        else if(vvc_shapshotVector[x][y+1]=='I')
                        {
                            b_powerAdj = true;
                            i_powerX = x;
                            i_powerY = y+1;
                            break;
                        }
                    }
                }
                //if T is not on the TOP or BOTTOM edge of the map
                else
                {
                    //If T is on the LEFT edge of the map
                    if(y==0)
                    {
                        //these search around T to find I starting top left and moves counter clockwise
                        if(vvc_shapshotVector[x-1][y]=='I')
                        {
                            b_powerAdj = true;
                            i_powerX = x-1;
                            i_powerY = y;
                            break;
                        }
                        else if(vvc_shapshotVector[x-1][y+1]=='I')
                        {
                            b_powerAdj = true;
                            i_powerX = x-1;
                            i_powerY = y+1;
                            break;
                        }
                        else if(vvc_shapshotVector[x][y+1]=='I')
                        {
                            b_powerAdj = true;
                            i_powerX = x;
                            i_powerY = y+1;
                            break;
                        }
                        else if(vvc_shapshotVector[x+1][y+1]=='I')
                        {
                            b_powerAdj = true;
                            i_powerX = x+1;
                            i_powerY = y+1;
                            break;
                        }
                        else if(vvc_shapshotVector[x+1][y]=='I')
                        {
                            b_powerAdj = true;
                            i_powerX = x+1;
                            i_powerY = y;
                            break;
                        }
                    }
                    //If T is on the RIGHT edge of the map
                    else if(y == vvc_shapshotVector[x].size()-1)
                    {
                        //these search around T to find I starting top left and moves counter clockwise
                        if(vvc_shapshotVector[x-1][y]=='I')
                        {
                            b_powerAdj = true;
                            i_powerX = x-1;
                            i_powerY = y;
                            break;
                        }
                        else if(vvc_shapshotVector[x-1][y-1]=='I')
                        {
                            b_powerAdj = true;
                            i_powerX = x-1;
                            i_powerY = y-1;
                            break;
                        }
                        else if(vvc_shapshotVector[x][y-1]=='I')
                        {
                            b_powerAdj = true;
                            i_powerX = x;
                            i_powerY = y-1;
                            break;
                        }
                        else if(vvc_shapshotVector[x+1][y-1]=='I')
                        {
                            b_powerAdj = true;
                            i_powerX = x+1;
                            i_powerY = y-1;
                            break;
                        }
                        else if(vvc_shapshotVector[x-1][y]=='I')
                        {
                            b_powerAdj = true;
                            i_powerX = x-1;
                            i_powerY = y;
                            break;
                        }
                        
                    }
                    //If T is not on the LEFT or RIGHT edge of the map
                    else
                    {
                        //these search around T to find I starting top left and moves counter clockwise
                        if(vvc_shapshotVector[x-1][y]=='I')
                        {
                            b_powerAdj = true;
                            i_powerX = x-1;
                            i_powerY = y;
                            break;
                        }
                        else if(vvc_shapshotVector[x-1][y+1]=='I')
                        {
                            b_powerAdj = true;
                            i_powerX = x-1;
                            i_powerY = y+1;
                            break;
                        }
                        else if(vvc_shapshotVector[x][y+1]=='I')
                        {
                            b_powerAdj = true;
                            i_powerX = x;
                            i_powerY = y+1;
                            break;
                        }
                        else if(vvc_shapshotVector[x+1][y+1]=='I')
                        {
                            b_powerAdj = true;
                            i_powerX = x+1;
                            i_powerY = y+1;
                            break;
                        }
                        else if(vvc_shapshotVector[x+1][y]=='I')
                        {
                            b_powerAdj = true;
                            i_powerX = x+1;
                            i_powerY = y;
                            break;
                        }
                        else if(vvc_shapshotVector[x+1][y-1]=='I')
                        {
                            b_powerAdj = true;
                            i_powerX = x+1;
                            i_powerY = y-1;
                            break;
                        }
                        else if(vvc_shapshotVector[x][y-1]=='I')
                        {
                            b_powerAdj = true;
                            i_powerX = x;
                            i_powerY = y-1;
                            break;
                        }
                        else if(vvc_shapshotVector[x-1][y-1]=='I')
                        {
                            b_powerAdj = true;
                            i_powerX = x-1;
                            i_powerY = y-1;
                            break;
                        }
                    }
                }
            }
        }
        //if we did find a I next to a T stop the functiopn
        // if(b_powerAdj && b_testingMode){
        //     cout<<"Leaving"<<endl;
        //     cout<<"i_powerX: "<<i_powerX<<endl;
        //     cout<<"i_powerY: "<<i_powerY<<endl;
        //     break;
        // }else
        if(b_powerAdj){
            break;
        }
    }
}

/*
This function finds the outer bounds for one cell (all I surrounding an specific I cell)
these bounds are for find how many population is adj to one cell
*/

int* Industrial::nextCell(int x, int y)
{
    static int ia_cords[4];
    int i_boundTX = x;
    int i_boundLY = y;
    int i_boundBX = x;
    int i_boundRY = y;
    //if there is an I cell ABOVE it
    if(i_boundTX-1>=0 && (vvc_shapshotVector[i_boundTX-1][i_powerY] == 'I' || isdigit(vvc_shapshotVector[i_boundTX-1][i_powerY])))
    {
        i_boundTX--;
    }
    //if there is an I cell BELOW it
    if(i_boundBX+1<=vvc_shapshotVector.size() && (vvc_shapshotVector[i_boundBX+1][i_powerY] == 'I' || isdigit(vvc_shapshotVector[i_boundBX+1][i_powerY])))
    {
        i_boundBX++;
    }
    //if there is an I cell To the LEFT of it
    if(i_boundLY-1>=0 && (vvc_shapshotVector[i_powerX][i_boundLY-1] == 'I' || isdigit(vvc_shapshotVector[i_powerX][i_boundLY-1])))
    {
        i_boundLY--;
    }
    //if there is an I cell To the RIGHT of it
    if(i_boundRY+1<=vvc_shapshotVector[i_boundTX].size() && (vvc_shapshotVector[i_powerX][i_boundRY+1] == 'I' || isdigit(vvc_shapshotVector[i_powerX][i_boundRY+1])))
    {
        i_boundRY++;
    }
    ia_cords[0]=i_boundTX;
    ia_cords[1]=i_boundBX;
    ia_cords[2]=i_boundLY;
    ia_cords[3]=i_boundRY;
    return ia_cords;
}

//key is number needed to increase

/*
This finctions counts the number of a givin variable next to its cell
needs int array of cordnates, x and y of the cell you want to increase, key is the required population of one cell,
and num needed is the amount of keys around the cell 
returns true if the number of key cells around the cell is more or equal to numNeeded
*/
bool Industrial::numAdj(int* cords, int givinX, int givinY, char key, int numNeeded)
{
    int i_num = 0;
    for(int x=cords[0]; x<=cords[1]; x++)
    {
        for(int y=cords[2]; y<=cords[3]; y++)
        {
            if(x == givinX && y == givinY)
                continue;
            else
            {
                if(vvc_shapshotVector[x][y] == key)
                    i_num++;
            }
        }
    }
    if(i_num >= numNeeded)
        return true;
    else
        return false;
}

/*
This is the functions that simulates growth in the zone
Only increases one cell per call
Prioritizes cells with bigger population first
returns the vecter after being edited
*/

vector<vector<char>> Industrial::simulation()
{
    int* ia_cords; //0-TopX 1-BottomX 2-LeftY 3-RightY
    if(i_availableWorkers >= 2)
    {
        if(vvc_shapshotVector[i_powerX][i_powerY] == 'I')
        {
            vvc_workingVector[i_powerX].at(i_powerY) = '1';
            i_generalPop++;
            i_availableWorkers = i_availableWorkers-2;
            vvc_shapshotVector = vvc_workingVector;
            return vvc_workingVector;
        }
        else
        {
            int i_xLength = i_industrialStartX + i_industrialXLength;
            int i_yLength = i_industrialStartY + i_industrialYLength;
            for(int x=i_industrialStartX; x<=i_xLength; x++)
            {
                for(int y=i_industrialStartY; y<=i_yLength; y++)
                {
                    ia_cords=nextCell(x,y);                   
                    if(vvc_shapshotVector[x][y] == '2')
                    {
                        if(numAdj(ia_cords,x,y,'2',4))
                        {
                            vvc_workingVector[x][y] = '3';
                            i_generalPop++;
                            i_availableWorkers = i_availableWorkers-2;
                            vvc_shapshotVector = vvc_workingVector;
                            return vvc_workingVector;
                        }
                    }
                    else if(vvc_shapshotVector[x][y] == '1')
                    {
                        if(numAdj(ia_cords,x,y,'1',2))
                        {
                            vvc_workingVector[x][y] = '2';
                            i_generalPop++;
                            i_availableWorkers = i_availableWorkers-2;
                            vvc_shapshotVector = vvc_workingVector;
                            return vvc_workingVector;
                        }
                    }
                    else if(vvc_shapshotVector[x][y] == 'I')
                    {
                        
                        if(numAdj(ia_cords,x,y,'1',1))
                        {
                            vvc_workingVector[x][y] = '1';
                            i_generalPop++;
                            i_availableWorkers = i_availableWorkers-2;
                            vvc_shapshotVector = vvc_workingVector;
                            return vvc_workingVector;
                        }
                    }
                }
            }
            vvc_shapshotVector = vvc_workingVector;
            return vvc_workingVector;
        }
    }
    cout<<endl;
    vvc_shapshotVector = vvc_workingVector;
    return vvc_workingVector;
}


/*
prints the INdustrial area
*/
void Industrial::printArea()
{
    int i_tempXLength = i_industrialStartX + i_industrialXLength;
    int i_tempYLength = i_industrialStartY + i_industrialYLength;
    for(int x=i_industrialStartX; x<i_tempXLength; x++)
    {
        for(int y=i_industrialStartY; y<i_tempYLength; y++)
        {
            cout<<vvc_shapshotVector[x][y]<< " ";
        }
        cout<<endl;
    }
}

void Industrial::setWorkingVector(vector<vector<char>> region){
    vvc_workingVector = region;
}

int Industrial::regionSearch(int user_startRow, int user_startCol, int user_endRow, int user_endCol){

    int endRow = i_industrialStartX + i_industrialXLength;
    int endCol = i_industrialStartY + i_industrialYLength;
    if((user_endRow < i_industrialStartX) || (user_endCol < i_industrialStartY) ||
    (endRow < user_startRow) || (endCol < user_startCol) ){ // if there is no overlap of user area and region area
        return 0;
    }

    int count = 0;

    int search_startRow;
    int search_startCol;
    int search_endRow;
    int search_endCol;


    if(i_industrialStartX <= user_startRow){
        search_startRow = user_startRow;
    } else {
        search_startRow = i_industrialStartX;
    }

    if(endRow >= user_endRow){
        search_endRow = user_endRow;
    } else {
        search_endRow = endRow;
    }

    if(i_industrialStartY <= user_startCol){
        search_startCol = user_startCol;
    } else {
        search_startCol = i_industrialStartY;
    }

    if(endCol >= user_endCol){
        search_endCol = user_endCol;
    } else {
        search_endCol = endCol;
    }



    for (int row = search_startRow; row <= search_endRow; row++){
        for (int col = search_startCol; col <= search_endCol; col++){
            if (isdigit(vvc_shapshotVector[row][col])){
                count += (vvc_shapshotVector[row][col] - '0');
            }
        }
    }

    return count;

}

int Industrial::getLargest(){
    int i_tempXLength = i_industrialStartX + i_industrialXLength;
    int i_tempYLength = i_industrialStartY + i_industrialYLength;
    int large = 0;

    for(int x=i_industrialStartX; x<i_tempXLength; x++)
    {
        for(int y=i_industrialStartY; y<i_tempYLength; y++)
        {
            if ((isdigit(vvc_shapshotVector[x][y])) && (vvc_shapshotVector[x][y]-'0' >= large)){
                large = vvc_shapshotVector[x][y]-'0';
            }
        }
    }

    return large;
}


