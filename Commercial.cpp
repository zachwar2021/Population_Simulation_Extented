#include "City.h"  
#include "Commercial.h"

#include <iostream>
#include <vector>
#include <string>

using namespace std;


Commercial::Commercial(vector<vector<char>> map)
{
    vvc_shapshotVector = map;
    vvc_workingVector = map;
    powerAdj();
    findCommercialZone();
    i_generalPop = 0;
}

int Commercial::getAvailWorker(){return i_availableWorkers;}
int Commercial::getAvailGood(){return i_products;}
int Commercial::getGenPop(){return i_generalPop;}

vector<vector<char>> Commercial::deleteWorker(int c, vector<vector<char>> regionMap)
{
    srand(time(NULL));
    int X = (i_commercialStartX+i_commercialXLength-1);
    int Y = (i_commercialStartY+i_commercialYLength-1);
    int x = rand()%(i_commercialEndX - i_commercialStartX +1)+i_commercialStartX;
    int y = rand()%(i_commercialEndY - i_commercialStartY +1)+i_commercialStartY;
    if(regionMap[x][y] != '1' || regionMap[x][y] != 'C')
    {
        regionMap[x][y]--;
        i_generalPop--;
    }
    else if(regionMap[x][y] == '1'){
        regionMap[x][y] = 'C';
        i_generalPop--;
    }
    else{
        regionMap = deleteWorker(c,regionMap);
    }
     return regionMap;
}

int Commercial::getCellPop(int x, int y)
{
    int cell = static_cast<int>(vvc_shapshotVector[x-1][y-1]);
    if(cell >= 0 && cell <= 9)
        return  cell;
    else
        return -1;
}


void Commercial::findCommercialZone()
{
    bool b_firstC = false;
    bool b_Xcounted = false;
    bool b_Ycounted = false;
    i_commercialXLength=0;
    i_commercialYLength=0;
    for(int x=0; x < vvc_shapshotVector.size(); x++)
    {
        for(int y=0; y < vvc_shapshotVector[x].size(); y++)
        {
            if(vvc_shapshotVector[x][y] == 'C' && !b_firstC && !b_Ycounted)
            {
                i_commercialStartX = x;
                i_commercialStartY = y;
                b_firstC = true;
                i_commercialYLength++;
            }
            else if(vvc_shapshotVector[x][y] == 'C' && !b_Ycounted)
            {
                i_commercialYLength++;
            }
            if(vvc_shapshotVector[x][y] == 'C' && !b_Xcounted)
            {
                i_commercialXLength++;
                b_Xcounted=true;
            }
        }
        if(b_firstC)
        {
            b_Ycounted = true;
            b_Xcounted = false;
        }
    }
    // if(b_testingMode)
    // {
    //     cout<<"start: "<<i_commercialStartX<<" "<<i_commercialStartY<<endl;
    //     cout<<"X length: "<<i_commercialXLength<<endl;
    //     cout<<"Y length: "<<i_commercialYLength<<endl;
    // }

    i_commercialEndX = i_commercialStartX + i_commercialXLength -1;
    i_commercialEndY = i_commercialStartY + i_commercialYLength -1;
}


void Commercial::powerAdj()
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
                        if(vvc_shapshotVector[x][y+1]=='C')
                        {
                            b_powerAdj = true;
                            i_powerX = x;
                            i_powerY = y+1;
                            break;
                        }
                        else if(vvc_shapshotVector[x+1][y+1]=='C')
                        {
                            b_powerAdj = true;
                            i_powerX = x+1;
                            i_powerY = y+1;
                            break;
                        }
                        else if(vvc_shapshotVector[x+1][y]=='C')
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
                        if(vvc_shapshotVector[x][y-1]=='C')
                        {
                            b_powerAdj = true;
                            i_powerX = x;
                            i_powerY = y-1;
                            break;
                        }
                        else if(vvc_shapshotVector[x+1][y-1]=='C')
                        {
                            b_powerAdj = true;
                            i_powerX = x+1;
                            i_powerY = y-1;
                            break;
                        }
                        else if(vvc_shapshotVector[x+1][y]=='C')
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
                        if(vvc_shapshotVector[x][y-1]=='C')
                        {
                            b_powerAdj = true;
                            i_powerX = x;
                            i_powerY = y-1;
                            break;
                        }
                        else if(vvc_shapshotVector[x][y+1]=='C')
                        {
                            b_powerAdj = true;
                            i_powerX = x;
                            i_powerY = y+1;
                            break;
                        }
                        else if(vvc_shapshotVector[x+1][y-1]=='C')
                        {
                            b_powerAdj = true;
                            i_powerX = x+1;
                            i_powerY = y-1;
                            break;
                        }
                        else if(vvc_shapshotVector[x+1][y]=='C')
                        { 
                            b_powerAdj = true;
                            i_powerX = x+1;
                            i_powerY = y;
                            break;
                        }
                        else if(vvc_shapshotVector[x+1][y+1]=='C')
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
                        if(vvc_shapshotVector[x-1][y]=='C')
                        {
                            b_powerAdj = true;
                            i_powerX = x-1;
                            i_powerY = y;
                            break;
                        }
                        else if(vvc_shapshotVector[x-1][y+1]=='C')
                        {
                            b_powerAdj = true;
                            i_powerX = x-1;
                            i_powerY = y+1;
                            break;
                        }
                        else if(vvc_shapshotVector[x][y+1]=='C')
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
                        if(vvc_shapshotVector[x][y-1]=='C')
                        {
                            b_powerAdj = true;
                            i_powerX = x;
                            i_powerY = y-1;
                            break;
                        }
                        else if(vvc_shapshotVector[x-1][y-1]=='C')
                        {
                            b_powerAdj = true;
                            i_powerX = x-1;
                            i_powerY = y-1;
                            break;
                        }
                        else if(vvc_shapshotVector[x-1][y]=='C')
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
                        if(vvc_shapshotVector[x][y-1]=='C')
                        {
                            b_powerAdj = true;
                            i_powerX = x;
                            i_powerY = y-1;
                            break;
                        }
                        else if(vvc_shapshotVector[x-1][y-1]=='C')
                        {
                            b_powerAdj = true;
                            i_powerX = x-1;
                            i_powerY = y-1;
                            break;
                        }
                        else if(vvc_shapshotVector[x-1][y]=='C')
                        {
                            b_powerAdj = true;
                            i_powerX = x-1;
                            i_powerY = y;
                            break;
                        }
                        else if(vvc_shapshotVector[x-1][y+1]=='C')
                        {
                            b_powerAdj = true;
                            i_powerX = x-1;
                            i_powerY = y+1;
                            break;
                        }
                        else if(vvc_shapshotVector[x][y+1]=='C')
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
                        if(vvc_shapshotVector[x-1][y]=='C')
                        {
                            b_powerAdj = true;
                            i_powerX = x-1;
                            i_powerY = y;
                            break;
                        }
                        else if(vvc_shapshotVector[x-1][y+1]=='C')
                        {
                            b_powerAdj = true;
                            i_powerX = x-1;
                            i_powerY = y+1;
                            break;
                        }
                        else if(vvc_shapshotVector[x][y+1]=='C')
                        {
                            b_powerAdj = true;
                            i_powerX = x;
                            i_powerY = y+1;
                            break;
                        }
                        else if(vvc_shapshotVector[x+1][y+1]=='C')
                        {
                            b_powerAdj = true;
                            i_powerX = x+1;
                            i_powerY = y+1;
                            break;
                        }
                        else if(vvc_shapshotVector[x+1][y]=='C')
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
                        if(vvc_shapshotVector[x-1][y]=='C')
                        {
                            b_powerAdj = true;
                            i_powerX = x-1;
                            i_powerY = y;
                            break;
                        }
                        else if(vvc_shapshotVector[x-1][y-1]=='C')
                        {
                            b_powerAdj = true;
                            i_powerX = x-1;
                            i_powerY = y-1;
                            break;
                        }
                        else if(vvc_shapshotVector[x][y-1]=='C')
                        {
                            b_powerAdj = true;
                            i_powerX = x;
                            i_powerY = y-1;
                            break;
                        }
                        else if(vvc_shapshotVector[x+1][y-1]=='C')
                        {
                            b_powerAdj = true;
                            i_powerX = x+1;
                            i_powerY = y-1;
                            break;
                        }
                        else if(vvc_shapshotVector[x-1][y]=='C')
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
                        if(vvc_shapshotVector[x-1][y]=='C')
                        {
                            b_powerAdj = true;
                            i_powerX = x-1;
                            i_powerY = y;
                            break;
                        }
                        else if(vvc_shapshotVector[x-1][y+1]=='C')
                        {
                            b_powerAdj = true;
                            i_powerX = x-1;
                            i_powerY = y+1;
                            break;
                        }
                        else if(vvc_shapshotVector[x][y+1]=='C')
                        {
                            b_powerAdj = true;
                            i_powerX = x;
                            i_powerY = y+1;
                            break;
                        }
                        else if(vvc_shapshotVector[x+1][y+1]=='C')
                        {
                            b_powerAdj = true;
                            i_powerX = x+1;
                            i_powerY = y+1;
                            break;
                        }
                        else if(vvc_shapshotVector[x+1][y]=='C')
                        {
                            b_powerAdj = true;
                            i_powerX = x+1;
                            i_powerY = y;
                            break;
                        }
                        else if(vvc_shapshotVector[x+1][y-1]=='C')
                        {
                            b_powerAdj = true;
                            i_powerX = x+1;
                            i_powerY = y-1;
                            break;
                        }
                        else if(vvc_shapshotVector[x][y-1]=='C')
                        {
                            b_powerAdj = true;
                            i_powerX = x;
                            i_powerY = y-1;
                            break;
                        }
                        else if(vvc_shapshotVector[x-1][y-1]=='C')
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
        //if we did find a I next to a T stop the function
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
 


bool Commercial::numAdj(int* cords, int givinX, int givinY, char key, int numNeeded)
{
    int i_num = 0;
    for(int x=cords[0]; x<=cords[1]; x++)
    {
        for(int y=cords[2]; y<=cords[3]; y++)
        {
            if(x == givinX && y == givinY)
            {
                continue;
            }
            else
            {
                if(vvc_shapshotVector[x][y] == key)
                    i_num++;
            }
        }
    }
    if(i_num >= numNeeded)
    {
        return true;
    }
    else
    {
        return false;
    }
}

int* Commercial::nextCell(int x, int y)
{
    static int ia_cords[4];
    int i_boundTX = x;
    int i_boundLY = y;
    int i_boundBX = x;
    int i_boundRY = y;
    //if there is an I cell ABOVE it
    if(i_boundTX-1>=0 && (vvc_shapshotVector[i_boundTX-1][i_powerY] == 'C' || isdigit(vvc_shapshotVector[i_boundTX-1][i_powerY])))
    {
        i_boundTX--;
    }
    //if there is an I cell BELOW it
    if(i_boundBX+1<=vvc_shapshotVector.size() && (vvc_shapshotVector[i_boundBX+1][i_powerY] == 'C' || isdigit(vvc_shapshotVector[i_boundBX+1][i_powerY])))
    {
        i_boundBX++;
    }
    //if there is an I cell To the LEFT of it
    if(i_boundLY-1>=0 && (vvc_shapshotVector[i_powerX][i_boundLY-1] == 'C' || isdigit(vvc_shapshotVector[i_powerX][i_boundLY-1])))
    {
        i_boundLY--;
    }
    //if there is an I cell To the RIGHT of it
    if(i_boundRY+1<=vvc_shapshotVector[i_boundTX].size() && (vvc_shapshotVector[i_powerX][i_boundRY+1] == 'C' || isdigit(vvc_shapshotVector[i_powerX][i_boundRY+1])))
    {
        i_boundRY++;
    }
    ia_cords[0]=i_boundTX;
    ia_cords[1]=i_boundBX;
    ia_cords[2]=i_boundLY;
    ia_cords[3]=i_boundRY;
    return ia_cords;
}


int Commercial::simulation(int i_availableWorkers, int i_products, vector<vector<char>> region)
{
    vvc_workingVector = region;
    bool cell_change = false;
    int count = 0;
    int* cords;


    for (int row=i_commercialStartX; row<=i_commercialEndX; row++)
    {
        for (int col=i_commercialStartY; col<=i_commercialEndY; col++) 
        {
            cell_change = false;
            cords = nextCell(row, col);

            //while ((count<=i_availableWorkers) && (count<=i_products))
            //{ 
                if ((vvc_shapshotVector[row][col]=='1') && (numAdj(cords, row, col, '1', 2)) && (i_availableWorkers>=1) && (i_products>=1))
                {
                    i_generalPop++;
                    i_availableWorkers--;
                    i_products--;
                        vvc_workingVector[row][col] = '2';
                    cell_change=true;
                    count++;
                    break;
                }
                else if ((vvc_shapshotVector[row][col]=='C') && (numAdj(cords, row, col, 'C', 1)) && (i_availableWorkers>=1) && (i_products>=1))
                {
                    i_generalPop++;
                    i_availableWorkers--;
                    i_products--;
                        vvc_workingVector[row][col] = '1';
                    cell_change=true;
                    count++;
                    break;
                }
                else if ((vvc_shapshotVector[row][col]=='C') && (b_powerAdj==true) && (i_availableWorkers>=1) && (i_products>=1))
                {
                    i_generalPop++;
                    i_availableWorkers--;
                    i_products--;
                    vvc_workingVector[row][col] = '1';
                    cell_change = true;
                    count++;
                    break;
                }
                
                else if ((i_availableWorkers<1) || (i_products<1))
                {
                    cell_change = false; 
                }
            //}
        }
        if (cell_change == true)
            break;
    }
    vvc_shapshotVector = vvc_workingVector;
    return count;
}


void Commercial::printArea() //Output the final region state
{
    int i_tempXLength = i_commercialStartX + i_commercialXLength;
    int i_tempYLength = i_commercialStartY + i_commercialYLength;

    for(int x=i_commercialStartX; x<i_tempXLength; x++)
    {
    for(int y=i_commercialStartY; y<i_tempYLength; y++)
    {
        cout<<vvc_shapshotVector[x][y]<< " ";
    }
    cout<<endl;
    }

}

vector<vector<char>> Commercial::getRegion(){
    return vvc_shapshotVector;
}

    int Commercial::regionSearch(int user_startRow, int user_startCol, int user_endRow, int user_endCol)
    {
        int endRow = i_commercialEndX;
        int endCol = i_commercialEndY;

    if((user_endRow < i_commercialStartX) || (user_endCol < i_commercialStartY) ||
    (endRow < user_startRow) || (endCol < user_startCol) ){ // if there is no overlap of user area and region area
        return 0;
    }

    int count = 0;

    int search_startRow;
    int search_startCol;
    int search_endRow;
    int search_endCol;


    if(i_commercialStartX <= user_startRow){
        search_startRow = user_startRow;
    } else {
        search_startRow = i_commercialStartX;
    }

    if(i_commercialEndX >= user_endRow){
        search_endRow = user_endRow;
    } else {
        search_endRow = i_commercialEndX;
    }

    if(i_commercialStartY <= user_startCol){
        search_startCol = user_startCol;
    } else {
        search_startCol = i_commercialStartY;
    }

    if(i_commercialEndY >= user_endCol){
        search_endCol = user_endCol;
    } else {
        search_endCol = i_commercialEndY;
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