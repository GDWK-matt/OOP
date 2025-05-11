#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>

class String {
private:
    char* str;
    size_t length;

public:
    String() : str(nullptr), length(0) {}

    String(const char* input) {
        length = std::strlen(input);
        str = new char[length + 1];
        strcpy_s(str, length + 1, input);
    }


    String(const String& other) {
        length = other.length;
        str = new char[length + 1];
        strcpy_s(str, length + 1, other.str);;
    }

    
    ~String() {
        delete[] str;
    }

    // Методы доступа
    const char* getStr() const { return str; }
    size_t getLength() const { return length; }

    
    String& operator+=(const String& other) {
        size_t newLength = length + other.length;
        char* newStr = new char[newLength + 1];

        std::strcpy(newStr, str);
        std::strcat(newStr, other.str);

        delete[] str;
        str = newStr;
        length = newLength;

        return *this;
    }

    
    String operator+(const String& other) const {
        String result(*this);
        result += other;
        return result;
    }

    
    bool operator>(const String& other) const {
        return length > other.length;
    }
    
    

    
    friend std::ostream& operator<<(std::ostream& os, const String& s) {
        if (s.str) os << s.str;
        return os;
    }

    friend std::istream& operator>>(std::istream& is, String& s) {
        char buffer[2048];
        is >> buffer;
        s = String(buffer);
        return is;
    }
};

int main() {

    String str1("Privet moya");
    String str2(" Planeta");

    String str3 = str1 + str2;
    std::cout << "Sovmeshenie strok: " << str3 << std::endl;
    std::cout << ("================================================================\n");
    if (str1 > str2) {
        std::cout << "str1 bolshe str2" << std::endl;
    }
    else {
        std::cout << "str2 bolshe str1" << std::endl;
    }
    std::cout << ("================================================================\n");
    str1 += str2;
    std::cout << "Ispolzuya +=: " << str1 << std::endl;

    

    return 0;
}