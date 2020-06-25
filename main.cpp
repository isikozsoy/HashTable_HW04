/*
* Author : Işık Özsoy
* ID: 21703160
* Section : 1
* Assignment : 4
*/

#include <iostream>
#include <fstream>
#include <string>
#include <string.h>
#include "HashTable.h"
#include <vector>

using namespace std;

int main( int argc, char* argv[]) {
    string fileName = argv[1];
    int tableSize = std::stoi(argv[2]);
    CollisionStrategy strategy;

    // Collision Strategy is decided
    if( strcmp(argv[3], "LINEAR") == 0)
        strategy = LINEAR;
    else if( strcmp(argv[3], "QUADRATIC") == 0)
        strategy = QUADRATIC;
    else if( strcmp(argv[3], "DOUBLE") == 0)
        strategy = DOUBLE;
    else {
        cout << "Please enter a valid input." << endl;
        return 0;
    }

    // Table is created according to the values entered by the user
    HashTable* h = new HashTable( tableSize, strategy);

    // Operations are read from the file
    string str;		// str contains lines in file
    ifstream file;
    file.open( fileName);	// we open file
    int cur = -1;
    while( getline( file, str)) {
        cur = str.find(" "); // we find the first index containing space
        string operation = str.substr( 0, cur);
        str.erase( 0, cur + 1);
        int item = std::stoi(str);
        cout << operation << " " << item << endl;
        if( operation == "I") {    // If the first char is "I", insert the item
            if( h -> insert( item))
                cout << item << " inserted" << endl;
            else
                cout << item << " not inserted" << endl;
        }
        else if( operation == "R") {    // If the first char is "R", remove the item
            if(h -> remove( item))
                cout << item << " removed" << endl;
            else
                cout << item << " not removed" << endl;
        }
        else if( operation == "S") {    // If the first char is "S", search the item
            int numProbes;
            if( h -> search(item, numProbes))
                cout << item << " found after " << numProbes << " probes" << endl;
            else
                cout << item << " not found after " << numProbes << " probes" << endl;
        }
    }
    h -> display();     // Table is displayed
    double numSuccProbes, numUnsuccProbes;
    h -> analyze(numSuccProbes, numUnsuccProbes);      // Analysis is done and printed
    cout << "Average number of successful probes is " << numSuccProbes << endl;
    cout << "Average number of unsuccessful probes is " << numUnsuccProbes << endl;
    cout << "Table Size: " << tableSize << endl;
    return 0;
}
