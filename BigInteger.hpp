#ifndef BIGINTEGER_H_
#define BIGINTEGER_H_

#include <string>
#include <algorithm>
#include <iostream>

using str = std::string;

class BigInteger {
private:
    str value;

    static str add(const str& a, const str& b) {
        int sizeA = a.size();
        int sizeB = b.size();
        int carry = 0;
        str res = "";

        int maxLength = std::max(sizeA, sizeB);
        str aRev = std::string(maxLength - sizeA, '0') + a;
        str bRev = std::string(maxLength - sizeB, '0') + b;

        for (int i = maxLength - 1; i >= 0 || carry; --i) {
            int sum = carry;
            if (i >= 0) {
                sum += (aRev[i] - '0');
                sum += (bRev[i] - '0');
            }
            res.push_back(sum % 10 + '0');
            carry = sum / 10;
        }

        if (carry) {
            res.push_back(carry + '0');
        }

        std::reverse(res.begin(), res.end());
        return res;
    }

    static str subtract(const str& a, const str& b) {
        int sizeA = a.size();
        int sizeB = b.size();
        int borrow = 0;
        str res = "";

        str aRev = a;
        str bRev = std::string(sizeA - sizeB, '0') + b;

        for (int i = sizeA - 1; i >= 0; --i) {
            int sub = (aRev[i] - '0') - (bRev[i] - '0') - borrow;
            if (sub < 0) {
                sub += 10;
                borrow = 1;
            } else {
                borrow = 0;
            }
            res.push_back(sub + '0');
        }
        while (res.size() > 1 && res.back() == '0') {
            res.pop_back();
        }

        std::reverse(res.begin(), res.end());
        return res;
    }
    static bool IsBig(const str& a, const str& b){
        str s1 = a;
        str s2 = b;
        while(s1.size() < s2.size()){
            s1 = '0' + s1;
        }
        while(s2.size() < s1.size()){
            s2 = '0' + s2;
        }
        return (s1 > s2);
    }
    static bool IsSmall(const str& a, const str& b){
        str s1 = a;
        str s2 = b;
        while(s1.size() < s2.size()){
            s1 = '0' + s1;
        }
        while(s2.size() < s1.size()){
            s2 = '0' + s2;
        }
        return (s1 < s2);
    }
    static bool IsSame(const str& a, const str& b){
        return (a == b);
    }

    static bool IsDigit(const str& a){
        int sizeA = a.size();
        for(int i = 0; i < sizeA; ++i){
            if(!isdigit(a[i])){
                std::cerr << "What is " << a[i] << " It is not digit. BigInteger for only digit!!! Value is 0 now." << std::endl;
                return false;
            }
        }
        return true;
    }

public:
    BigInteger(const str& val = "0") : value(val) {}

    BigInteger operator+(const BigInteger& k) const {
        return BigInteger(add(this->value, k.value));
    }

    BigInteger operator-(const BigInteger& k) const {
        return BigInteger(subtract(this->value, k.value));
    }

    bool operator>(const BigInteger& k) const{
        return IsBig(this->value, k.value);
    } 

    bool operator<(const BigInteger& k) const{
        return IsSmall(this->value, k.value);
    }   

    bool operator==(const BigInteger& k) const{
        return IsSame(this->value, k.value);
    } 

    friend std::istream& operator>>(std::istream& is, BigInteger& num) {
        is >> num.value;
        if(!IsDigit(num.value)){
            num.value = "0";
        }
        return is;
    }

    friend std::ostream& operator<<(std::ostream& os, const BigInteger& num) {
        os << num.value;
        return os;
    }
};



#endif //!BIGINTEGER_H_