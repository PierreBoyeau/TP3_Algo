#include <iostream>
#include <algorithm>
#include <string>
#include <map>
#include <vector>
#include <set>
#include <time.h>
#include <stdlib.h>

#include "point2d.h"
#include "town.h"

using namespace std;


#ifndef srcPath
#define srcPath "."
#endif
// The path and name of the town file
string townFile = srcPath "/villes.txt";

/*
 * Study French isotoponyms
 */



template<typename T>
void create_hist(map<T,int> occurrences, bool DoPrint){
    if(DoPrint){
        map<int, int> repetitions_histogram;
        int number_of_sosies;
        for(auto occ_it = occurrences.begin();
            occ_it != occurrences.end(); occ_it++){
            number_of_sosies = occ_it->second;
            repetitions_histogram[number_of_sosies]++;
        }
        for(auto it = repetitions_histogram.begin();
            it != repetitions_histogram.end(); it++){
            cout<<it->first;
            cout<<" : ";
            cout<<it->second<<endl;
        }
    }
}


map<string,int> name_occurrences(const vector<Town>& towns, bool DoPrint){
    map<string, int> names_occurrences;
    string name;
    // Creates a map that gives the number of occurrences for a given city name
    for(auto town_it = towns.begin();
        town_it != towns.end(); town_it++){
        name = town_it->name();
        names_occurrences[name]++;
    }
    // Creates a histogram t if DoPrint
    create_hist<string>(names_occurrences, DoPrint);

    return(names_occurrences);
}


map<Point2D,int> coor_occurrences(const vector<Town>& towns, bool DoPrint){
    map<Point2D, int> coor_occurrences;
    Point2D point;
    // Creates a map that gives the number of occurrences for a given city name
    for(auto town_it = towns.begin();
        town_it != towns.end(); town_it++){
        point = town_it->point();
        coor_occurrences[point]++;
    }
    // Creates a histogram t
    create_hist<Point2D>(coor_occurrences, DoPrint);

    return(coor_occurrences);
}

void build_N(set<Town>& N, const vector<Town>& town,
             map<string, int> names_occ){
    string town_name;
    for(auto town_it = town.begin(); town_it != town.end(); town_it++){
        town_name = town_it->name();
        if(names_occ[town_name] >= 2)
            N.insert(*town_it);
    }
}

void build_C(set<Town>& C, const vector<Town>& town,
             map<Point2D, int> coor_occ){
    Point2D town_coor;
    for(auto town_it = town.begin(); town_it != town.end(); town_it++){
        town_coor = town_it->point();
        if(coor_occ[town_coor] >= 2)
            C.insert(*town_it);
    }
}


int main()
{
    /////
    ///// Read town file
    /////
    // Create an empty list of towns
    vector<Town> towns;
    // Read file
    cout << "Reading town file: " << townFile << endl;
    clock_t time1 = clock();
    int nb_towns = Town::read_file(townFile, towns);
    clock_t time2 = clock();
    // Sanity check
    if (nb_towns < 0) {
    cout << "Error while reading file" << endl;
    return 2;
    }
    if (nb_towns == 0) {
    cout << "No town found" << endl;
    return 1;
    }
    // Initialize random seed
    srand(time(NULL));
    // Say how many towns have been read
    cout << "File read in: "
     << ((float)(time2-time1)/CLOCKS_PER_SEC) << " s" << endl;
    cout << "Number of towns in file: "
     << towns.size() /* same as nb_towns */ << endl;


    cout << "A random town, using format \"name[lat,lon](x,y)\": "
     << towns[rand() % towns.size()] << endl;




    // ---Question 1
    cout<<"Question 1"<<endl;
    map<string, int> names_occ = name_occurrences(towns, true);
    // ---Question 2
    cout<<"Question 2"<<endl;
    map<Point2D, int> coor_occ = coor_occurrences(towns, true);

    // ---Question 3
    cout<<"Question 3"<<endl;
    // Construction de N
    set<Town> N;
    build_N(N, towns, names_occ);
    cout<<"N size : "<<N.size()<<endl;
    // Construction de C
    set<Town> C;
    build_C(C, towns, coor_occ);
    cout<<"C size : "<<C.size()<<endl;
    //Intersection
    set<Town> intersection;
    set_intersection(N.begin(), N.end(), C.begin(), C.end(), inserter(intersection, intersection.begin()));
    cout<<"intersection N^C size : "<<intersection.size()<<endl;
    //Question 4

    return 0;
}
