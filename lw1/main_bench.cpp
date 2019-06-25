#include <iostream>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <algorithm>
#include <vector>
#include <stdio.h>
#include <cstdlib>


#define TDtype char

const int MIN_CAP = 10000000;

const int KEY_LEN = 32;
const int VALUE_LEN = 64;
const int BOXES = 16; // .16 count system

class TDict {
public:
	TDtype Key[KEY_LEN+1]; // '\0'
	TDtype Value[VALUE_LEN+1];
};

int CharToNum(char letter) { // from .16 to int
	if (letter == '0') return 0;
	if (letter == '1') return 1;
	if (letter == '2') return 2;
	if (letter == '3') return 3;
	if (letter == '4') return 4;
	if (letter == '5') return 5;
	if (letter == '6') return 6;
	if (letter == '7') return 7;
	if (letter == '8') return 8;
	if (letter == '9') return 9;
	if (letter == 'a') return 10;
	if (letter == 'b') return 11;
	if (letter == 'c') return 12;
	if (letter == 'd') return 13;
	if (letter == 'e') return 14;
	if (letter == 'f') return 15;
	return -1;
}

void Postprocessing(TDict* arr, int arrSize) {
	for(int i = 0; i < arrSize; i++){
        std::cout << arr[i].Key << '\t' <<arr[i].Value << std::endl;
	}
}

void RadixSort(TDict *arr, int arrLen, int capacity, int *cArray, TDict *bArray) {
	if (!arrLen) {
		return;
	}

	for (int i = 1; i <= KEY_LEN; ++i) {

        memset(cArray, 0, sizeof(int)*BOXES);

        int chint = 0; //temp
        char ch = '0'; //

		for (int k = 0; k < arrLen; ++k) { //last ch in Key & filling cArray with freq
			ch = CharToNum(arr[k].Key[KEY_LEN-i]);
			chint = int(ch);
			++cArray[chint];
		}

		for (int j = 1; j < BOXES; ++j) { // array , >= current Value
			cArray[j] += cArray[j-1];
		}

		for (int j = arrLen - 1; j >= 0; --j) {
			ch = CharToNum(arr[j].Key[KEY_LEN-i]);
			chint = int(ch);
			bArray[cArray[chint]-1] = arr[j];
			--cArray[chint];
		}

        memcpy(arr, bArray, sizeof(TDict)*arrLen);
	}
}

int main(int argc, char const **argv) {

    std::ios::sync_with_stdio(false);

	using namespace std;
	TDict dict = { '\0', '\0' };
	int capacity = MIN_CAP; // elements
    int arrSize = 0; // pairs

	TDict *arr = new TDict[capacity];
    int *cArray = new int[BOXES];
	TDict *bArray = new TDict[capacity];

	while (cin >> dict.Key >> dict.Value) {
		if (arrSize == capacity) {
			capacity *= 2;
			arr = (TDict*)realloc(arr, sizeof(TDict) * capacity);
		}

        dict.Key[KEY_LEN] = '\0';
        dict.Value[VALUE_LEN] = '\0';

		arr[arrSize] = dict;
		++arrSize;
	}

	clock_t start;
	double duration;

	vector<string> bench(arrSize);

    for (int i = 0; i < arrSize; ++i){
    	string mystr(arr[i].Key);
    	bench[i] = mystr;
    }

    start = clock();
    sort(bench.begin(), bench.end());
    duration = (clock() - start) / (double)CLOCKS_PER_SEC;

    cout << "STL sort: " << duration << endl;

	start = clock();
	RadixSort(arr, arrSize, capacity, cArray, bArray);
	duration = (clock() - start) / (double)CLOCKS_PER_SEC;

	cout << "My radix sort: " << duration << endl;
/////////////////////



   // for(int j = 0; j < arrSize; j++){
   // 	cout << bench[j] << endl;
   // }

	delete[]arr; //mem free
	delete[]cArray;
	delete[]bArray;

	return 0;
}
