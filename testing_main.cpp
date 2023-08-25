#include <iostream>
#include <vector>
#include "City.h"
//#include "Airport.h"
#include "Industrial.h"

using namespace std;

int main()
{
     string configFile;
    ifstream fin;   //file-in variable
    string configRegion;
    string configTime;
    string configRR;

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
    int workers = 1;
    Industrial industrial(regionMap);

    // Call class constructor, initialize region, refresh rate, & time max
    City city;
    city.init(regionMap, configRR, configTime);

    // Prints from class City
    cout << "\n\nStarting region layout:" << endl;
    city.display();

    regionMap[1][0] = 'I';
    regionMap[2][0] = '2';
    regionMap[3][0] = '3';

    regionMap[1][1] = '1';
    regionMap[2][1] = '2';
    regionMap[3][1] = '3';

    regionMap[1][2] = '1';
    regionMap[2][2] = '2';
    regionMap[3][2] = '3';
    regionMap = industrial.deleteWorker(0,regionMap);
/*
    Airport airport(regionMap);
    regionMap = airport.allocate(regionMap);
    regionMap = airport.buildRoadAndPower(regionMap);
    regionMap = airport.build(regionMap, workers);
    regionMap = airport.simulation(region, workers);
    

    */
    cout<< "\n\nEnding region layout:" <<endl;
    city.setRegion(regionMap);
    city.display();

}