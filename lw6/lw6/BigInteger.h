#ifndef BIGINTEGER_HPP
#define BIGINTEGER_HPP

#include <vector>
#include <iostream>
#include <cmath>
#include <algorithm>
#include <iomanip>

const int BASE_POW = 4;
const int BASE = pow(10, BASE_POW);

class BigInteger {
public:
    BigInteger() {};
    BigInteger(const std::string &str);
    BigInteger(const size_t &size);
    BigInteger(int n);
    inline size_t size() const { return mVec.size(); }
    BigInteger operator+(const BigInteger &other);
    BigInteger operator-(const BigInteger &other);
    BigInteger operator*(const BigInteger &other);
    BigInteger operator/(BigInteger &other);
    BigInteger Power(int r);
    bool operator<(const BigInteger &other) const;
    bool operator<=(const BigInteger &other) const;
    bool operator>(const BigInteger &other) const;
    bool operator==(const BigInteger &other) const;
    int Get(size_t i) const { return mVec[i]; };
    void Set(size_t i, int num) { mVec[i] = num; } ;
    friend std::ostream& operator<< (std::ostream& stream, const BigInteger & number);
protected:
    std::vector<int> mVec;
private:
    void FilterZeros();
};

#endif