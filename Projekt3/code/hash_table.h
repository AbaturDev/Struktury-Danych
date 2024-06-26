#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include <iostream>
using namespace std;

template<typename K, typename V>
class HashTable
{
public:
    virtual void display() = 0;
    virtual void insert(K key, V value) = 0;
    virtual int getSize() = 0;
    virtual bool find(K key, V value) = 0; 
};

#endif