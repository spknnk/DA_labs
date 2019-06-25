#include "BigInteger.h"

BigInteger::BigInteger(const std::string &str) {
    for(int i = str.size() - 1; i >= 0; --i) {
        int tmp = 0;
        for(int j = 0;  i >= 0 && j < BASE_POW; ++j, --i) {
            tmp = static_cast<int>(tmp + (str[i] - '0') * pow(10, j));
        }
        ++i;
        mVec.push_back(tmp);
    }
    FilterZeros();
}

BigInteger::BigInteger(const size_t &size) {
    mVec.resize(size, 0);
}

BigInteger::BigInteger(int n) {
    if (n < BASE)
        mVec.push_back(n);
    else {
        for(; n; n /= BASE)
            mVec.push_back(n % BASE);
    }
}

void BigInteger::FilterZeros() {
    while(mVec.size() > 1 && mVec.back() == 0 ){
        mVec.pop_back();
    }
}

std::ostream &operator<<(std::ostream &stream, const BigInteger &number) {
    size_t n = number.size();
    if( n == 0 ) {
        return stream;
    }
    stream << number.mVec[n - 1];
    for( int i = n - 2; i >= 0; --i ) {
        stream << std::setfill('0') << std::setw(BASE_POW) << number.mVec[i];
    }
    return stream;
}

bool BigInteger::operator>(const BigInteger &other) const {
        size_t n = size(); // vec size
        if(n != other.size()) {
            return n > other.size();
        }
        for(int i = n - 1; i >= 0; --i) {
            if(Get(i) != other.Get(i)) {
                return Get(i) > other.Get(i);
            }
        }
        return false;
}

bool BigInteger::operator<(const BigInteger &other) const {
    size_t n = size(); // vec size
    if(n != other.size()) {
        return n < other.size();
    }
    for(int i = n - 1; i >= 0; --i) {
        if(Get(i) != other.Get(i)) {
            return Get(i) < other.Get(i);
        }
    }
    return false;
}

bool BigInteger::operator<=(const BigInteger &other) const {
    return (*this) < other || (*this) == other;
}

bool BigInteger::operator==(const BigInteger &other) const {
    size_t n = size(); // vec size
    if(n != other.size()) {
        return false;
    }
    for(int i = n - 1; i >= 0; --i) {
        if(Get(i) != other.Get(i)) {
            return false;
        }
    }
    return true;
}

BigInteger BigInteger::operator+(const BigInteger &other) {
    size_t  k = 0;
    size_t maxLen = std::max(mVec.size(), other.size());
    BigInteger result(maxLen + 1);
    int r = 0;
    for(size_t i = 0; i < maxLen; ++i) {
        if(mVec.size() <= i) {
            k = other.Get(i);
        } else if(other.size() <= i) {
            k = mVec[i];
        } else {
            k = mVec[i] + other.Get(i);
        }
        k += r;
        result.Set(i, k % BASE);
        r = k / BASE;
    }
    if(r != 0) { result.Set(maxLen, r); }
    result.FilterZeros();
    return result;
}

BigInteger BigInteger::operator-(const BigInteger &other) {
    int k = 0;
    int r = 0;
    int balance = 0;
    BigInteger result(mVec.size());
    for(int i = 0; i < mVec.size(); ++i) {
        r = i < other.size() ? other.Get(i) : 0;
        k = mVec[i] - r + balance;
        balance = k < 0 ? -1 : 0;
        result.Set(i, k < 0 ? k + BASE : k);
    }
    result.FilterZeros();
    return result;
}

BigInteger BigInteger::operator*(const BigInteger &other) {
    BigInteger result(mVec.size() + other.size());
    int i = 0;
    for(i = 0; i < other.size(); ++i){
        int r = 0;
        if (other.Get(i) == 0){
            continue;
        }
        for(int j = 0; j < size(); ++j){
            int tmp = mVec[j] * other.Get(i) + result.Get(i + j) + r;
            r = tmp / BASE;
            result.Set(i + j, tmp % BASE);
        }
        result.Set(i + size(), r);
    }
    //
    result.FilterZeros();
    return result;
}

BigInteger BigInteger::Power(int r) {
    if(r == 0) {
        return BigInteger("1");
    }
    if(r % 2 == 0) {
        BigInteger res = (*this).Power(r / 2);
        return res * res;
    } else {
        BigInteger res = (*this).Power(r - 1);
        return (*this) * res;
    }
}

BigInteger BigInteger::operator/(BigInteger &other) {
    BigInteger result(mVec.size());
    BigInteger cv(0);
    for (int i = static_cast<int>(mVec.size() - 1); i >= 0; --i) {
        cv.mVec.insert(cv.mVec.begin(), mVec[i]);
        if (!cv.mVec.back())
            cv.mVec.pop_back();
        int x = 0, l = 0, r = BASE;
        BigInteger cur;
        while (l <= r) {
            int m = (l + r) / 2;
            BigInteger tmp = BigInteger(m);
            cur = other * BigInteger(m);
            if (cur <= cv) {
                x = m;
                l = m + 1;
            } else {
                r = m - 1;
            }
        }

        result.mVec[i] = result.mVec[i] + x;
        cv = cv - other * BigInteger(x);
    }

    result.FilterZeros();
    return result;
}


