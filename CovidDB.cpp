// Nathan Tran
// assignment 3 implementation file

#include <iostream>
#include <sstream>
#include "CovidDB.h"

using namespace std;

// DataEntry class

// constructor
DataEntry::DataEntry(){
    date = "";
    country = "";
    c_cases = 0;
    c_deaths = 0;

}

DataEntry::DataEntry(string date, string country, int c_cases, int c_deaths){
    assignDate(date);
    assignCountry(country);
    assignCases(c_cases);
    assignDeaths(c_deaths);
}


void DataEntry::assignCountry(string country){
    this->country = country;
}

void DataEntry::assignDate(string date){
    this->date = date;
}

void DataEntry::assignCases(int c_cases){
    this->c_cases = c_cases;
}

void DataEntry::assignDeaths(int c_deaths){
    this->c_deaths = c_deaths;
}

string DataEntry::getCountry(){
    return country;
}

string DataEntry::getDate(){
    return date;
}

int DataEntry::getCases(){
    return c_cases;
}

int DataEntry::getDeaths(){
    return c_deaths;
}

// CovidDB class

int CovidDB::hash(string country){
    int sum = 0;
    int m  = 17;
    for(int i = 0; i < static_cast<int>(country.length()); i++){
        char c  = country[i];
        sum += (i + 1) * static_cast<int>(c);
    }
    return sum % m;
}

bool CovidDB::add(DataEntry* entry){
    int index = hash(entry->getCountry());

    if(static_cast<int>(dataBase.size() <= index)){
        dataBase.resize(index + 1);
    }

    // vector is empty
    if(static_cast<int>(dataBase[index].size()) == 0){
        dataBase[index].push_back(entry);
        return true;
    }
    // duplicate check
    for(int i = 0; i < static_cast<int>(dataBase[index].size()); i++){
        if(dataBase[index][i]->getCountry() == entry->getCountry()){
            if(compareDate(dataBase[index][i]->getDate(), entry->getDate())){
                update(entry->getDate(), entry->getCountry(), entry->getCases(), entry->getDeaths());
                return true;
            }else{
                return false;
            }
        }
    }
    dataBase[index].push_back(entry);
    return true;
}


DataEntry* CovidDB::get(string country){
    int index = hash(country);

    if(dataBase[index].empty()){
        // Handle case when entry doesn't exist
        return nullptr;
    }

    for(int i = 0; i < static_cast<int>(dataBase[index].size()); i++){
        if(dataBase[index][i]->getCountry() == country){
            return dataBase[index][i];
        }
    }
    return nullptr;
}

void CovidDB::remove(string country){
    int index = hash(country);

    if(dataBase[index].empty()){
        return;
    }

    for(int i = 0; i < static_cast<int>(dataBase[index].size()); i++){
        if(dataBase[index][i]->getCountry() == country){
            delete dataBase[index][i];
            dataBase[index].erase(dataBase[index].begin() + i);
            return;
        }
    }
}

// reflect any update later made to the hash table
void CovidDB::update(string date, string country, int c_cases, int c_deaths){
    vector<DataEntry*>& entries = dataBase[hash(country)];

    // Iterate over the entries to find the matching one
    for (int i = 0; i < static_cast<int>(entries.size()); i++){
        if (entries[i]->getCountry() == country) {
            int newCases = entries[i]->getCases() + c_cases;
            int newDeaths = entries[i]->getDeaths() + c_deaths;
            DataEntry* newEntry = new DataEntry(date, country, newCases, newDeaths);
            
            // Update the entry in the database
            delete entries[i];
            entries[i] = newEntry;
            return;
        }
    }
}

// If the date is earlier than the date in the current hash table, we just ignore the new entry.
bool CovidDB::compareDate(string date1, string date2) {
    istringstream iss1(date1), iss2(date2);
    char delimiter; // To store the delimiter '/' between date components

    int month1, day1, year1, month2, day2, year2;

    // Extract month, day, and year directly from the stream
    iss1 >> month1 >> delimiter >> day1 >> delimiter >> year1;
    iss2 >> month2 >> delimiter >> day2 >> delimiter >> year2;

    //compare the dates
    //return true if year is earlier than second
    if (year1 < year2) {
        return true;
    } else if (year1 > year2) {
        return false;
    //if years are the same, we compare the months
    } else if (month1 < month2) {
        return true;
    } else if (month1 > month2) {
        return false;
    //and if months are the same we compare the days to see whch one is earlier
    } else if (day1 < day2) {
        return true;
    } else {
        return false;
    }
}

CovidDB::~CovidDB(){
    for (int i = 0; i < (int)dataBase.size(); i++) {
        for (int j = 0; j < (int)dataBase[i].size(); j++) {
            delete dataBase[i][j];
        }
        dataBase[i].clear();
    }
    dataBase.clear();
}

void CovidDB::display(){
    cout << "Covid Database" << endl;
    for(int i = 0; i < static_cast<int>(dataBase.size()); i++){
        cout << "Index " << i << ": ";
        if(dataBase[i].empty()){
            cout << "Empty slot. " << endl;
        }else{
            for(int j = 0; j < static_cast<int>(dataBase[i].size()); j++){
                cout << "(" << dataBase[i][j]->getCountry() << ", " << dataBase[i][j]->getDate()
                     <<  ", " << dataBase[i][j]->getCases() << ", " << dataBase[i][j]->getDeaths()
                     << ") ";
            }
            cout << endl << endl;
        }
    }
}