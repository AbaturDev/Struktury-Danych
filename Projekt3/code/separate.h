#ifndef SEPARATE_H
#define SEPARATE_H
#include "hash_table.h"
#include <cmath>

template<typename K, typename V>
struct Node
{
    K key;
    V value;
    Node *next;
};

template<typename K, typename V>
class Separate : public HashTable<K, V>
{
private:
    int size;
    int capacity;
    Node<K,V>** array;

    public:
    Separate(int size = 0, int capacity = 5);
    ~Separate();
    void display();
    void insert(K key, V value);
    int getSize();
    bool find(K key, V value);

    private:
    void rehashing();
    int hash(K key);
};

//~~~~~~~~~CODE IMPLEMENTATION~~~~~~~~~

template<typename K, typename V>
Separate<K,V>::Separate(int size, int capacity)
{
    this->capacity = capacity;
    this->size = size;
    array = new Node<K,V>*[capacity];

    for(int i = 0; i<capacity; i++)
    {
        array[i]=nullptr;
    }
}

template<typename K, typename V>
int Separate<K,V>::hash(K key)
{
    return key % capacity;
}

template<typename K, typename V>
void Separate<K,V>::rehashing()
{
    capacity = capacity * 2;
    Node<K,V>** temp = new Node<K,V>*[capacity];

    for(int i = 0; i< capacity; i++)
    {
        temp[i]=nullptr;
    }
    
    for(int i = 0; i < size; i++)
    {
        Node<K,V> *ptr = array[i];
        while(ptr != nullptr)
        {
            Node<K,V>* next = ptr->next;
            int index = hash(ptr->key);
            ptr->next = temp[index];
            temp[index] = ptr;
            ptr = next;
        }
    }

    delete [] array;
    array = temp;
}

template<typename K, typename V>
void Separate<K,V>::insert(K key, V value)
{
    float loadFactor = size/capacity;
    if(loadFactor >= 1)  //loadFactor >= 1
    {
        rehashing();
    }

    int index = hash(key);
    Node<K,V>* temp = new Node<K,V>;
    temp->key = key;
    temp->value = value;
    temp->next = nullptr;

    if(array[index]==nullptr)
    {
        array[index] = temp;
    }
    else
    {
        Node<K,V>* ptr = array[index];
        while(ptr->next != nullptr)
        {
            ptr = ptr->next;
        }
        ptr->next = temp;
    }
    size++;
    //temp->next = array[index];
    //array[index] = temp;
}

template<typename K, typename V>
void Separate<K,V>::display()
{
    for(int i = 0; i < capacity; i++)
    {
        Node<K,V> *temp = array[i];
        while(temp != nullptr)
        {
            cout << temp->key << ":" << temp->value << endl;
            temp = temp->next;
        }
    }
}

template<typename K, typename V>
int Separate<K,V>::getSize()
{
    return size;
}

template<typename K, typename V>
bool Separate<K,V>::find(K key, V value)
{
    int index = hash(key);
    Node<K,V> *temp = array[index];
    while(temp != nullptr)
    {
        if(temp->key == key && temp->value == value)
        {
            return true;
        }
        temp = temp->next;
    }
    cout<<"Data not found! Returning defult value"<<endl;
    return false;
}

template<typename K, typename V>
Separate<K,V>::~Separate()
{
    Node<K,V>* temp =  new Node<K,V>;
    Node<K,V>* next = nullptr;
    for(int i = 0; i<capacity; i++)
    {
        temp = array[i];
        while(temp != nullptr)
        {
            next = temp->next;
            delete temp;
            temp = next;
        }
    }
    delete [] array;
}

#endif