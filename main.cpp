/*
    CSCE 2110-002
    Group 3
    Chambers
    Due 4/8

    Individual Contributions
    
        Ashley: residential

        McKenzie: commercial

        Zach: industrial

        Parker: Pollution & wiki

        Kevin: config/read-in & wiki
*/



#include <iostream>
#include <vector>
#include "City.h"
#include "Residential.h"
#include "Industrial.h"
#include "pollution.h"
#include "Commercial.h"
#include "Airport.h"
#include "PlaneCrash.h"
using namespace std;


int main(){
/*
    Reading in config file: VARIABLES
        - configFile = string, user input
        - configRegion = region csv file name
        - configTime = sim time limit
        - configRR = sim refresh rate
*/
    string configFile;
    ifstream fin;   //file-in variable
    string configRegion;
    string configTime;
    string configRR;

    

    //Prompting user to enter the the file name of the config file
    cout << "Enter the name of the config file you wish to open:" << endl;
    cin >> configFile; 
    cout << endl;

    //Opening the config file
    fin.open(configFile);
    //Failcheck in case file does not exist in directory
    if(fin.fail()){
        cout << "The file " << configFile << " could not be found and opened." << endl;
        cout << "Program ended." << endl;
        exit(1);
    }

    // Reading in each row, unparsed
    getline(fin, configRegion);
    getline(fin, configTime);
    getline(fin, configRR);

    fin.close();    //close the config file read

    // identify index location of colon for parsing
    int posRegion = configRegion.find(":");
    int posTime = configTime.find(":");
    int posRR = configRR.find(":");

    // Using substring function + 1 to make our new
    //   string index begin after the colon and space
    configRegion = configRegion.substr(posRegion + 1);
    configTime = configTime.substr(posTime + 1);
    configRR = configRR.substr(posRR + 1);

    // static cast int value instead of string
    int i_configTime = stoi(configTime);
    int i_configRR = stoi(configRR);



/*
    Reading in region layout file:
        - csv filename stored in configRegion
        - fileline = row of csv
        - regionMap = 2d char vector, end point of read-in values
*/
    fin.open(configRegion);         //open the region file using the file name grabbed in the config file
    string fileline; 
    vector<vector<char>> regionMap;

    //fail check for file-in
    if(fin.fail()){
        cout << "The file " << configRegion << " could not be found and opened." << endl;
        cout << "Program ended." << endl;
        exit(1);
    }

    while(getline(fin, fileline)){

        vector<char> r;     //row vector

        for (char &c : fileline) {      //TERNARY OPERATOR: I dont understand it too well but remember a bit of sample code given to me in CSCE1040 that utitllized its logic, so I used that
            if (c != ',') {             //conditions of ternary being "for every char 'c that is in file-in fileline"
                r.push_back(c);         //push_back char into ROW of 2D vector if char is not a comma
            }
        }
        regionMap.push_back(r);         //then push_back that vector ROW into the 2D vector
    }


/*
    Beginning of simulation operations:
*/

    // Call class constructor, initialize region, refresh rate, & time max
    City city;
    city.init(regionMap, configRR, configTime);

    // Prints from class City
    cout << "\n\nStarting region layout:" << endl;
    city.display();

    Residential r(regionMap);
    Industrial industrial(regionMap);
    Commercial commercial(regionMap);

    // sim variables:
    bool commercialChange = false; // tracks change in commercial
    int newWorkers = 0; // this variable takes the return value of resSim
    int i_totalWorkers = 0; // total workers, for use in final output
    int i_availableWorkers = 0; // available workers, for use in Industrial and Commercial
    int i_availableGoods = 0;
    int count;
    bool b_airport = false; // false = no airport; true = yes airport
    bool b_airportBuilt; // false = airport not built; true = airport built
    bool b_planeCrashChance = false; // flase = no chance of a plane crashing
    bool b_construction = false;
    int i_timeUnderConstructor = 0;
    int* i_CrashArea;
    Airport airport(regionMap);
    PlaneCrashfunc planeCrashing;

    for(int time=0; time < i_configTime; time++)
    {
        // Residential
        if(!b_airportBuilt)
        {
            newWorkers = r.resSim(regionMap);
        }
        else
        {
            //residential needs less people in adj cells to grow if airport is built
            newWorkers = r.resAirpotSim(regionMap);
        }

        // adjust for new workers from Res growth
        i_totalWorkers += newWorkers;
        i_availableWorkers += newWorkers;

        regionMap = r.getRegion();
        city.setRegion(regionMap);

        // commercial first call
        if(i_availableGoods && i_availableWorkers){

            // commercial returns count, representing the number of cells changed
            count = 0;
            count = commercial.simulation(i_availableWorkers, i_availableGoods, regionMap);

            if (count){ // if change occurred
                commercialChange = true;

                i_availableWorkers -= count;
                i_availableGoods -= count;

                r.assignJobs(count, 'C');   //commercial change TRUE = assign first unemployed worker commercial job 'C' in the employment vector
                //SEE: Residential::assignJobs in Residential.cpp

            }
            regionMap = commercial.getRegion();
            city.setRegion(regionMap);

        }

        
        // airport
        if(!b_airport && (i_totalWorkers > 10) && (industrial.getLargest() >=2)){
            
            
            if(!b_airport)
            {
                regionMap = airport.allocate(regionMap);
                regionMap = airport.buildRoadAndPower(regionMap);
                b_airport = true;
                b_construction = true;
            }
        } else if (b_airport){ // if airport has been begun
            // regionMap = airport(regionMap);
            regionMap = airport.simulation(regionMap, i_availableWorkers); // runs simulation for first step
            b_planeCrashChance = planeCrashing.ChanceOfPlaneCrash(b_airport);
            if(b_planeCrashChance)
            {
                i_CrashArea = planeCrashing.sim(regionMap);
            }

                //randomly 3-5 goods added add in airport
                srand(time(NULL));
                int i_newGoods = rand() %5 +3;
                i_availableGoods += i_newGoods;
        }

        


        industrial.setNumAvailableWorkers(i_availableWorkers);
        industrial.setWorkingVector(regionMap);
        regionMap = industrial.simulation();    //industrial simulation
        city.setRegion(regionMap);
        i_availableGoods = industrial.getNumProducts(); // gets number of goods from industrial

        
        if(!commercialChange && i_availableGoods && i_availableWorkers)
        {
            count = 0;
            count = commercial.simulation(i_availableWorkers, i_availableGoods, regionMap);

            if (count){ // if change occurred
                commercialChange = true;

                i_availableWorkers -= count;
                i_availableGoods -= count;
            }
            regionMap = commercial.getRegion();
            city.setRegion(regionMap);
        }
        city.setRegion_static(regionMap);


    }

/*
    OUTPUT:
*/
        
    

    vector<vector<string>> vvs_Polution_Vector;
    int sizeX = regionMap.size();
    int sizeY = regionMap[0].size();
    for(int x=0; x<sizeX; x++)
    {
        // sizeY = regionMap[x].size();
        vector<string> row(sizeY);
        for(int y=0; y<sizeY; y++)
        {
            row.at(y)=regionMap[x].at(y);
        }
        vvs_Polution_Vector.push_back(row);
    }

    // get industrial coordinates
    int* coords;
    coords = industrial.getIndustrialZoneCord();
    // initialize pollution
    Pollution pollution(coords, vvs_Polution_Vector);
    pollution.polluteArea();
    pollution.crashPollution(i_CrashArea[0] ,i_CrashArea[1]);


// Output the final region state
    cout << "Final region state:" << endl;
    city.display();
// Output the total, regional population for residential zones, industrial zones, and commercial zones
    cout << "Residential population: " << i_totalWorkers << endl;
    cout << "Industrial Population: " << industrial.getgeneralPop() << endl; // needs function call to get industrial population
    cout << "Commercial: " << commercial.getGenPop() <<endl; // needs function call to get commercial population

// Output the final regional pollution state
    cout<<endl;
    cout<<"Map after Pollution"<<endl;
    pollution.pollutionDisplay();

// Output the total pollution in the region
    pollution.getNumPollution();
    cout<<endl;

// Prompt the user for the coordinates of some rectangular area of the region to analyze more closely
    bool verify = false;
    int i_startRow;
    int i_startCol;
    int i_endRow;
    int i_endCol;

    while(!verify){
        cout << "Enter values for region you would like to view:" << endl;
        cout << "Start row: ";
        cin >> i_startRow;
        cout << "\nStart column: ";
        cin >> i_startCol;
        cout << "\nEnd row: ";
        cin  >> i_endRow;
        cout << "\nEnd column: ";
        cin >> i_endCol;

        if((i_startCol<0) || (i_startRow<0) || (i_endCol >= regionMap[0].size()) || (i_endRow >= regionMap.size())){
            cout << "  !! Invalid input, please try again. !!" << endl;
        }else{
            cout << "Valid" << endl;
            verify = true;
        }

    }

    cout << "User Region information:" << endl;

    cout << "Residential count: " << r.regionSearch(i_startRow, i_startCol, i_endRow, i_endCol) << endl;
    cout << "Industrial count: " << industrial.regionSearch(i_startRow, i_startCol, i_endRow, i_endCol) << endl; // industrial
    cout << "Commercial count: " << commercial.regionSearch(i_startRow, i_startCol, i_endRow, i_endCol) << endl;//commercial
    cout << "Pollution count: " << pollution.regionSearch(i_startRow, i_startCol, i_endRow, i_endCol) << endl;//pollution

    // end
    exit(0); //the return would throw a segmentation fault
    return 0;
}
