// Nathan Tran
// assignment 3 header file

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class DataEntry{
    private:
        string date;
        string country;
        int c_cases;
        int c_deaths;
    public:
        DataEntry();
        DataEntry(string date, string country, int c_cases, int c_deaths);

        // setters 
        void assignCountry(string country);
        void assignDate(string date);
        void assignCases(int c_cases);
        void assignDeaths(int c_deaths);

        // getters 
        string getCountry();
        string getDate();
        int getCases();
        int getDeaths();
};

class CovidDB{
    private:
        vector<vector<DataEntry*>> dataBase;
    public:
        int hash(string country);
        void display();

        // required
        bool add(DataEntry* entry);
        DataEntry* get(string country);
        void remove(string country);

        // reflect any update later made to the hash table
        void update(string date, string country, int c_cases, int c_deaths);

        // If the date is earlier than the date in the current hash table, 
        // we just ignore the new entry.
        bool compareDate(string date1, string date2);

        // destructor
        ~CovidDB();
};
