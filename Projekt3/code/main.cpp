#include <iostream>
#include "timer.h"
using namespace std;

int main()
{   
    HashTable<int, int>* a;
    Separate<int, int> b;
    Open<int, int> c;
    Cuckoo<int, int> x;
    Timer<int, int> timer;

    a = &c;

    int count = 1000000;

    for(int i=0; i<count; i++)
    {
        a->insert(1,i);
    }

    //timer.insert_time(*a,1,count);
    timer.find_time(*a, 1,count-1);
    //timer.getSize_time(*a);
    
    return 0;
}