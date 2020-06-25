/*
* Author : Işık Özsoy
* ID: 21703160
* Section : 1
* Assignment : 4
*/

#include "HashTable.h"
#include <iostream>

using namespace std;

// Constructor
HashTable :: HashTable( const int tableSize, const CollisionStrategy option)
{
    tableItem = new int[tableSize];
    tableState = new State[tableSize];
    for( int i = 0; i < tableSize; i++)
        tableState[i] = EMPTY;
    this -> tableSize = tableSize;
    strategy = option;
    size = 0;
}

// Destructor
HashTable :: ~HashTable()
{
    delete [] tableItem;
    delete [] tableState;
}

// Function that calculates the index
int HashTable :: hash( const int key)
{
    if( tableSize == size)  // If the table is full return -1
        return -1;
    int index = key % tableSize;  // Calculate mod tableSize
    if(tableState[index] == OCCUPIED)  // If it is occupied, continue searching for an appropriate index
    {
        int tempIndex = index;
        switch( strategy)
        {
        case LINEAR:
            for( int i = 1; tableState[tempIndex] == OCCUPIED; i++)
            {
                if( i > tableSize)  // stopping case
                    return -1;
                tempIndex = index + i;
                tempIndex = tempIndex % tableSize;
            }
            index = tempIndex;
        case QUADRATIC:
            for( int i = 1; tableState[tempIndex] == OCCUPIED; i++)
            {
                if( i > tableSize)  // stopping case
                    return -1;
                tempIndex = i * i + index;
                tempIndex = tempIndex % tableSize;
            }
            index = tempIndex;
        case DOUBLE:
            int h2 = 0;
            int tempKey = key;
            while(tempKey != 0)
            {
                h2 = h2 * 10;
                h2 = h2 + tempKey % 10;
                tempKey = tempKey / 10;
            }
            for( int i = 1; tableState[tempIndex] == OCCUPIED; i++)
            {
                if( i > tableSize)  // stopping case
                    return -1;
                tempIndex = i * h2 + index;
                tempIndex = tempIndex % tableSize;
            }
            index = tempIndex;
        }
    }
    return index;
}

bool HashTable :: insert( const int item)
{
    int numProbes;
    if( !search( item, numProbes)) {
        int index = hash(item);
        if( index == -1)         // if hashing function returns -1, return false
            return false;
        tableItem[index] = item;
        tableState[index] = OCCUPIED;   // Add item to the table at the position index
        size++;     // Increase the number of the items in the table
        return true;
    }
    else     // If the item already exists in the table, do not insert
        return false;
}

bool HashTable :: remove( const int item)
{
    if( size == 0)  // If there is not any item n the table, return false
        return false;
    int index = item % tableSize;
    int tempIndex = index;
    switch( strategy)
    {
    case LINEAR:
        for( int i = 0; tableState[tempIndex] != EMPTY && i < tableSize; i++)
        {
            tempIndex = index + i;
            tempIndex = tempIndex % tableSize;
            if( tableState[tempIndex] == OCCUPIED && tableItem[tempIndex] == item)
            {
                tableState[tempIndex] = DELETED;   // If the item is found, label it with DELETED
                size--;   // Decrease the number of the item
                return true;
            }
        }
        return false;
    case QUADRATIC:
        for( int i = 0; tableState[tempIndex] != EMPTY && i < tableSize; i++)
        {
            tempIndex = i * i + index;
            tempIndex = tempIndex % tableSize;
            if( tableState[tempIndex] == OCCUPIED && tableItem[tempIndex] == item)
            {
                tableState[tempIndex] = DELETED;   // If the item is found, label it with DELETED
                size--;   // Decrease the number of the item
                return true;
            }
        }
        return false;
    case DOUBLE:
        int h2 = 0;
        int tempKey = item;
        while(tempKey != 0)   // Here the reverse of the key is calculated (second hash function)
        {
            h2 = h2 * 10;
            h2 = h2 + tempKey % 10;
            tempKey = tempKey / 10;
        }
        for( int i = 0; tableState[tempIndex] != EMPTY && i < tableSize; i++)
        {
            tempIndex = i * h2 + index;
            tempIndex = tempIndex % tableSize;
            if( tableState[tempIndex] == OCCUPIED && tableItem[tempIndex] == item)
            {
                tableState[tempIndex] = DELETED;   // If the item is found, label it with DELETED
                size--;   // Decrease the number of the item
                return true;
            }
        }
        return false;
    }
    return false;
}

bool HashTable :: search( const int item, int& numProbes)
{
    if( size == 0) {
        numProbes = 1;
        return false;
    }
    numProbes = 0;
    int index = item % tableSize;
    int tempIndex = index;
    switch( strategy)
    {
    case LINEAR:
        for( int i = 0; tableState[tempIndex] != EMPTY && i < tableSize; i++)
        {
            numProbes++;
            tempIndex = index + i;
            tempIndex = tempIndex % tableSize;
            if( tableState[tempIndex] == OCCUPIED && tableItem[tempIndex] == item)
            {
                return true;
            }
        }
        if( numProbes == 0)
            numProbes = 1;
        return false;
    case QUADRATIC:
        for( int i = 0; tableState[tempIndex] != EMPTY && i < tableSize; i++)
        {
            numProbes++;
            tempIndex = i * i + index;
            tempIndex = tempIndex % tableSize;
            if( tableState[tempIndex] == OCCUPIED && tableItem[tempIndex] == item)
            {
                return true;
            }
        }
        if( numProbes == 0)
            numProbes = 1;
        return false;
    case DOUBLE:
        int h2 = 0;
        int tempKey = item;
        while(tempKey != 0)
        {
            h2 = h2 * 10;
            h2 = h2 + tempKey % 10;
            tempKey = tempKey / 10;
        }
        for( int i = 0; tableState[tempIndex] != EMPTY && i < tableSize; i++)
        {
            numProbes++;
            tempIndex = i * h2 + index;
            tempIndex = tempIndex % tableSize;
            if( tableState[tempIndex] == OCCUPIED && tableItem[tempIndex] == item)
            {
                return true;
            }
        }
        if( numProbes == 0)
            numProbes = 1;
        return false;
    }
    return false;
}

// Function displays the content of the table
void HashTable :: display()
{
    for( int i = 0; i < tableSize; i++)
    {
        if( tableState[i] == OCCUPIED)
            cout << i << ": " << tableItem[i] << endl;
        else
            cout << i << ": " << endl;
    }
}

// Function that computes the average number of the successful and unsuccessful probes
void HashTable :: analyze( double& numSuccProbes, double& numUnsuccProbes)
{
    numSuccProbes = 0;
    numUnsuccProbes = 0;
    int probe;
    double count = 0;
    for( int i = 0; i < tableSize; i++)
    {
        if( tableState[i] == OCCUPIED)
        {
            search(tableItem[i], probe);
            numSuccProbes += probe;
            count++;
        }
    }
    numSuccProbes = numSuccProbes / count;

    if( strategy != DOUBLE)
    {
        for( int i = 0; i < tableSize; i++)
        {
            int unsuccItem = i;
            while( search(unsuccItem, probe))
                unsuccItem += tableSize;
            numUnsuccProbes += probe;
        }
        numUnsuccProbes = numUnsuccProbes / tableSize;  // We divide it to tableSize since we tried values for each index in the table
    }
    else
        numUnsuccProbes = -1;
}
