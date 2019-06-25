#include <iostream>
#include <string>
#include <math.h>
#include <time.h>

int lengthOfNum(long long x){
    int l=1;
    while(x>9){ l++; x/=10; }
    return l;
}

long long nums(long long l, long long r, int m){
    while(l % m !=0){++l;}
    while(r % m !=0){--r;}

    return (r-l)/m+1;
}

long long dynamic(long long n, int m, int length){
    if(n < m){return 0;}
    long long x = nums((long long)(pow(10, length - 1)), n, m) + dynamic(n / 10, m, length-1);
    return x;
}

int main() {
    long long n;
    int m;
    double start_time =  clock();
    while (std::cin >> n >> m){
    	int length = lengthOfNum(n);
    //    std::cout << dynamic(n, m, length) - (int)(n % m == 0) << std::endl;
    }
    double end_time = clock();
    double search_time = end_time - start_time;
    printf("Time: %f sec\n", (double)search_time/CLOCKS_PER_SEC);
    return 0;
}