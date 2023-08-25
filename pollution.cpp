//Welcome to Pollution Parker's Playhouse
//(where parker pollutes and schemes about pollution)
#include <iostream>
#include <string>
#include <vector>
#include <cstring>

#include "pollution.h" 

using namespace std;
//constructor
Pollution::Pollution(int* cordies,vector<vector<string>> ptemp){
    rowS = cordies[0];
    colS = cordies[1];
    rowE = cordies[2];
    colE = cordies[3];
    numPollution = 0;
    region = ptemp;
    regionPolluted = ptemp;
    
}

//returns numPollution
int Pollution::getNumPollution(){
    return numPollution;
}

//goes through given area and calles the spreadPollution function
void Pollution::polluteArea() {
        for(int row = rowS; row <= rowE; row++){               // Iterate through row
            for(int col = colS; col <= colE; col++){          // Iterate through node in a row
                spreadPollution(row,col);                    // pollute
            //numPollution = numPollution + (findvalue(row,col)); //adds current tile to number of pollution // needs to be its own loop at the end
            }
    }
}

//this finds an integer value of the specified spot in the string vector
//this way I can use it for comparison
int Pollution::findvalue(int row, int col){
    int pollutionValue;

    // I put these up here instead of being buried in the conditional statements
    string stringValue = regionPolluted[row][col];
    //string cstringValue = {stringValue};

    // I chose to assess length first
    if(stringValue.length()==1){//checks to see if there is only one character, meaning the value is zero ( i will have to add parentheses later) T, -, 
        if(isdigit(stringValue[0])){ //checks if its an integer by index value
            pollutionValue = stoi(stringValue); //stoi is string to integer, and sets pollutionValue
            return pollutionValue;
        }
        pollutionValue = 0;
        return pollutionValue;
    } else{//make into c-string to search for ( )
        // searches for '('
        for(int i = 0; stringValue[i]; i++){
            if(stringValue[i] == '('){
                int value = (stringValue[i+1]-'0');//makes value the character after the open parentheses, meaning i've already added it
                return value;
            }
        }
    }
    pollutionValue = 0;
    return pollutionValue;
}

//changes the contets of the string to an appropriate pollution value
void Pollution::setPollution(int currentRow,int currentCol,int adjRow,int adjCol){
    int curValue = findvalue(currentRow,currentCol);
    int nextValue = (findvalue(currentRow,currentCol)-1);
    string strValue = to_string(nextValue);
    string digitTester = regionPolluted[adjRow][adjCol];


    if(nextValue < 1){
        return;
    }
    numPollution += (nextValue-findvalue(adjRow,adjCol));
    if(findvalue(adjRow,adjCol)==0){//adds (x) to the string with x being the pollution value
        regionPolluted[adjRow][adjCol] += "("+strValue+")";
    }else if(isdigit(digitTester[0])){ 
        regionPolluted[adjRow][adjCol] = strValue;

    }else{//now i need to convert to c string, to find the value between the parentheses, change it, then change it back to a string
        string stringValue = regionPolluted[adjRow][adjCol];

        for(int i = 0; i < stringValue.size();++i){
            if(stringValue[i]=='('){            
                stringValue[i+1]=nextValue+'0';//sets the c-string to the correct pollution value
                string nextStringValue = stringValue;//makes the c-string back into a string
                regionPolluted[adjRow][adjCol] = nextStringValue;//sets the region to the new value
            }
        }
    }
}
//this function should add pollution to nearby tiles with a value one less than its adjacent value
//bear wittness to the indominable power of pollution
void Pollution::spreadPollution(int row, int col){

    int size = region.size();
    bool isLeftValid = (col  - 1 >= 0);
    bool isRightValid = (col + 1  < size);
    bool isUpValid = (row - 1 >= 0);
    bool isDownValid = (row + 1 < size);

    if( regionPolluted[row][col].length()==1 && isdigit(regionPolluted[row][col][0])){
        numPollution += regionPolluted[row][col][0]-'0';
    }

    if(isLeftValid) {
        if(findvalue(row,col-1) < findvalue(row,col)){setPollution(row,col,row,col-1);}
    }
    if(isLeftValid && isUpValid) {
        if(findvalue(row-1,col-1) < findvalue(row,col)){setPollution(row,col,row-1,col-1);}
    }
    if(isLeftValid && isDownValid){
        if(findvalue(row+1,col-1) < findvalue(row,col)){setPollution(row,col,row+1,col-1);}
    }
    if(isDownValid){
       if(findvalue(row+1,col) < findvalue(row,col)){setPollution(row,col,row+1,col);} 
    }
    if(isRightValid && isDownValid){
        if(findvalue(row+1,col+1) < findvalue(row,col)){setPollution(row,col,row+1,col+1);}
    }
    if(isRightValid){
        if(findvalue(row,col+1) < findvalue(row,col)){setPollution(row,col,row,col+1);}
    }
    if(isRightValid && isUpValid){
        if(findvalue(row-1,col+1 ) < findvalue(row,col)){setPollution(row,col,row-1,col+1);}
    }
    if(isUpValid){
        if(findvalue(row-1,col) < findvalue(row,col)){setPollution(row,col,row-1,col);}
    }
}

//print function
void Pollution::pollutionDisplay(){
        for(int row=0; row<regionPolluted.size(); row++){               // Iterate through row
            for(int col=0; col<regionPolluted.size(); col++){        // Iterate through node in a row
                cout << regionPolluted[row][col] << "\t";               // Print node data
            }
            cout << endl;
        }
        cout<<"Total Pollution Value: "<<numPollution<<endl;
}

int Pollution::regionSearch(int user_startRow, int user_startCol, int user_endRow, int user_endCol)
    {

    if((user_endRow < rowS) || (user_endCol < colS) ||
    (rowE < user_startRow) || (colE < user_startCol) ){ // if there is no overlap of user area and region area
        return 0;
    }

    int count = 0;

    int search_startRow;
    int search_startCol;
    int search_endRow;
    int search_endCol;
    rowS--;

    if(rowS <= user_startRow){
        search_startRow = user_startRow;
    } else {
        search_startRow = rowS;
    }

    if(rowE >= user_endRow){
        search_endRow = user_endRow;
    } else {
        search_endRow = rowE;
    }

    if(colS <= user_startCol){
        search_startCol = user_startCol;
    } else {
        search_startCol = colS;
    }

    if(colE >= user_endCol){
        search_endCol = user_endCol;
    } else {
        search_endCol = colE;
    }



    for (int row = search_startRow; row <= search_endRow; row++){
        for (int col = search_startCol; col <= search_endCol; col++){
           count+=findvalue(row,col);
           /*
            if (isdigit(c_regionPolluted[row][col])){
                count += (c_regionPolluted[row][col] - '0');
            }*/
        }
    }

    return count;
}

//this function should take in coordinates and add pollution to the tile, then spread to nearby tiles.
void Pollution::crashPollution(int row, int col){
    int initialPollution = findvalue(row,col);
    cout<<"initial Pollution:"<<initialPollution<<endl;
    int finalPollution = initialPollution+2;
    string finalPollutionString = "*("+to_string(finalPollution)+")";
    cout<<"final Pollution String:"<<finalPollutionString<<endl;
    regionPolluted[row][col] = finalPollutionString;
    spreadPollution(row,col);
}
