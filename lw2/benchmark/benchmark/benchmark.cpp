#include <iostream>
#include <chrono>
#include <map>
#include <vector>
#include <random>
#include <ctime>
#include <climits>

//#include "avl.hpp"
#include "rb.cpp"

// #define INSERT
// #define FIND
#define REMOVE

long DATA_SET_SIZE = 0;
const int MAX_VALUE = 1000;

using namespace std;

int main(int argc, char const *argv[])
{
    typedef pair<int, int> ccpair;
    
    ofstream ofs("2plot");
    
    vector<pair<long, int>> v1, v2;

    srand(time(0));
    rand();

    if (!ofs)
        return 0;
    for (; DATA_SET_SIZE < 2000000; DATA_SET_SIZE += 200000)
    {
        cout << "Dataset size: " << DATA_SET_SIZE << endl;
        map<int, int> m;
        TRBTree a;

        ccpair *data = new ccpair[DATA_SET_SIZE];

        for(long i = 0; i < DATA_SET_SIZE; ++i)
            data[i] = ccpair(rand() % DATA_SET_SIZE, rand() % DATA_SET_SIZE);
    #ifndef INSERT
        for (long i = 0; i < DATA_SET_SIZE; ++i){
            m.insert(data[i]);
            a.InsertNode(data[i].first);
        }
    #endif

        // a.Print();

        int fstTime, scdTime;

        chrono::time_point<chrono::system_clock> start, end;

        start = chrono::system_clock::now();
        for(long i = 0; i < DATA_SET_SIZE; ++i)
    #ifdef INSERT
            m.insert(data[i]);
    #endif
    #ifdef FIND
        m.find(data[i].first);
    #endif
    #ifdef REMOVE
        m.erase(data[i].first);
    #endif
        end = chrono::system_clock::now();

        fstTime = chrono::duration_cast<chrono::milliseconds>(end - start).count();

        start = chrono::system_clock::now();
        for (int i = 0; i < DATA_SET_SIZE; ++i)
    #ifdef INSERT
            a.InsertNode(data[i].first, data[i].second);
    #endif
    #ifdef FIND
            a.Search(data[i].first);
    #endif
    #ifdef REMOVE
            a.Delete(data[i].first);
    #endif
            end = chrono::system_clock::now();

        scdTime = chrono::duration_cast<chrono::milliseconds>(end - start).count();

        // a.Print();

        cout << "std::map result: " << fstTime  << "ms" << endl;
        cout << "my rbt result: " << scdTime << "ms" << endl;
        // v1.push_back(pair<long, int>(DATA_SET_SIZE, fstTime));
        // v2.push_back(pair<long, int>(DATA_SET_SIZE, scdTime));
        ofs << DATA_SET_SIZE << " " << fstTime << " " << scdTime << endl;
    }
    // for(pair<long, int> p : v1)
    //     ofs << "map" << p.first << " " << p.second << endl;
    // for (pair<long, int> p : v2)
    //     ofs << "avl" << p.first << " " << p.second << endl;
    ofs.close();
    return 0;
}
