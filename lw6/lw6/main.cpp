#include "BigInteger.h"
#include <string>

int StingToInt(const std::string &str) {
    int tmp = 0;
    for (int i = 0; i < str.size(); ++i) {
        tmp = tmp * 10 + (str[i] - '0');
    }
    return tmp;
}

int main() {
    clock_t start, end;
    start = clock();
    
    std::string str1, str2;
    char op;

    while (std::cin >> str1 >> str2 >> op) {
        BigInteger num1(str1);
        BigInteger num2(str2);
        switch (op) {

            case '+':
                std::cout << num1 + num2 << std::endl;
                break;

            case '-':
                if (num1 < num2) {
                    std::cout << "Error" << std::endl;
                    break;
                } else {
                    std::cout << num1 - num2 << std::endl;
                    break;
                }

            case '*':
                std::cout << num1 * num2 << std::endl;
                break;

            case '/':
                if (num2 == 0) {
                    std::cout << "Error" << std::endl;
                    break;
                }
                else {
                    std::cout << num1 / num2 << std::endl;
                    break;
                }

            case '^':
                if (num1 == 0) {
                    if (num2 == 0) {
                        std::cout << "Error" << std::endl;
                        break;
                    }
                    else {
                        std::cout << "0" << std::endl;
                        break;
                    }
                } else if (num1 == 1) {
                    std::cout << "1" << std::endl;
                    break;
                } else {
                    std::cout << num1.Power(StingToInt(str2)) << std::endl;
                    break;
                }

            case '<':
                num1 < num2 ? (std::cout << "true" << std::endl) : (std::cout << "false" << std::endl);
                break;

            case '>':
                num1 > num2 ? (std::cout << "true" << std::endl) : (std::cout << "false" << std::endl);
                break;

            case '=':
                num1 == num2 ? (std::cout << "true" << std::endl) : (std::cout << "false" << std::endl);
                break;
        }

    }
    end = clock();
    std::cout << "cpp time: " << (double)(end - start) / CLOCKS_PER_SEC << " sec." << std::endl;
    return 0;
}