/*
* Author : Işık Özsoy
* ID: 21703160
* Section : 1
* Assignment : 4
*/

#include <cmath>
#include <iostream>
#include <limits>

using namespace std;
enum CollisionStrategy { LINEAR, QUADRATIC, DOUBLE };
class HashTable
{
public:
    enum State { EMPTY, OCCUPIED, DELETED };
    HashTable( const int tableSize, const CollisionStrategy option);
    ~HashTable();
    int hash( const int key);
    bool insert( const int item);
    bool remove( const int item);
    bool search( const int item, int& numProbes);
    void display();
    void analyze( double& numSuccProbes, double& numUnsuccProbes);
private:
    int* tableItem;
    State* tableState;
    int tableSize;
    int size;
    CollisionStrategy strategy;

};
