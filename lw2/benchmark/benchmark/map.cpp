#include <iostream>
#include <chrono>
#include <map>
#include <vector>
#include <random>
#include <ctime>
#include <climits>

using namespace std;

int main(int argc, char const *argv[])
{
    map<string, int> m;

    string act;
    string key;
    string value;

    double stdTime;
    clock_t start;

    start = clock();

	while(cin >> act >> key >> value){

		if(act == "+"){
			int number = value[0];
			//cout << act << " " << key << " " << number << endl;
			m.insert(pair<string,int>(key, number));
		}
		if(act == "-"){
			//cout << act << " " << key << endl;
			m.erase(key);
		}

	}

	stdTime = (clock() - start) / (double)CLOCKS_PER_SEC;
	std::cout << "Std time is: " << stdTime << " ms" << std::endl;

return 0;
}