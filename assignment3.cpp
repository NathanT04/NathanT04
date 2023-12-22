// Nathan Tran
// assignment 3

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "CovidDB.h"

using namespace std;

const string FILE_NAME = "WHO-COVID-D2ata.csv";

void readFile(CovidDB &dataBase);

int main(){
    CovidDB CDB;
    int choice, cases, deaths;
    string date, country;

    cout << endl;
    while (true) {
        cout << endl;
        cout << "Welcome to my Covid database!" << endl;
        cout << "There are 5 total operations in this program, below you will find a guide." << endl;
        cout << "Press 1 to create the initial hash table." << endl;
        cout << "Press 2 to add a new data entry." << endl;
        cout << "Press 3 to get a data entry" << endl;
        cout << "Press 4 to remove a data entry." << endl;
        cout << "Press 5 to display hash table." << endl;
        cout << "Press 0 to exit" << endl;
        cout << "Please enter your choice: ";
        cin >> choice;

        switch(choice){
            case 1: {
                readFile(CDB);
                cout << "Hashtable has been created." << endl;
                break;
            }

            case 2: {
                cout << "Please enter data in this format: " << endl;
                cout << "date(m/d/yy) country cases deaths" << endl;
                cin >> date >> country >> cases >> deaths;
                DataEntry* newEntry = new DataEntry(date, country, cases, deaths);
                bool success = CDB.add(newEntry);
                if(success){
                    cout << "Your entry was successful." << endl;
                }else{
                    cout << "Unsuccessful entry. Please try again or use a new entry." << endl;
                }
                break;
            }

            case 3: {
                cout << "Please enter your desired country: " << endl;
                cin.ignore();
                getline(cin, country);
                DataEntry* entry = CDB.get(country);
                if(entry != nullptr){
                    cout << country << " data:" << endl;
                    cout << "Date: " << entry->getDate() << endl;
                    cout << "Cases: " << entry->getCases() << endl;
                    cout << "Total deaths: " << entry->getDeaths() << endl;
                }else{
                    cout << "There is currently no information for " << country << "." << endl;
                }
                break;
            }

            case 4: {
                cout << "Please enter your desired country to remove: ";
                cin.ignore();
                getline(cin, country);
                CDB.remove(country);
                cout << "Data for " << country << " removed successfully." << endl;
                break;
            }

            case 5: {
                CDB.display();
                break;
            }

            case 0:
                cout << "Exiting the program." << endl;
                return 0;
            default:
                cout << "Invalid choice. Please try again." << endl;
                break;
        }
    }
        cout << endl;
        cout << "----------------------------------------" << endl;
        cout << endl;

    return 0;
}

void readFile(CovidDB &dataBase){
    const string FILE = "WHO-COVID-Data.csv";
    ifstream inFile;
    inFile.open(FILE);
    if(!inFile){
        cout << "Error, file could not be read. Press enter to continue: " << endl;
        cin.ignore();
    }

    string line;
    getline(inFile, line);

    while(getline(inFile, line)){
        stringstream ss(line);
        string date, country, cases, deaths;

        getline(ss, date, ',');
        cout << date << ' ';
        getline(ss, country, ',');
        cout << country << ' ';
        getline(ss, cases, ',');
        cout << cases << ' ';
        getline(ss, deaths, ',');
        cout << deaths << endl;

        int c_cases = stoi(cases);
        int c_deaths = stoi(deaths);

        DataEntry *newEntry = new DataEntry(date, country, c_cases, c_deaths);
        dataBase.add(newEntry);
    }
    inFile.close();
}