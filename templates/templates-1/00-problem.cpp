#include <iostream>
#include <string>

int max(int a, int b) {
    return a > b ? a : b;
}

double max(double a, double b) {
    return a > b ? a : b;
}

std::string max(const std::string& a, const std::string& b) {
    return a > b ? a : b;
}

struct MyStruct {
    int a;
    double b;
    std::string c;

    bool operator>(const MyStruct& other) const {
        return a > other.a && b > other.b && c > other.c;
    }

    friend std::ostream& operator<<(std::ostream& os, const MyStruct& myStruct) {
        os << "MyStruct(" << myStruct.a << ", " << myStruct.b << ", " << myStruct.c << ")";
        return os;
    }
};

MyStruct max(const MyStruct& a, const MyStruct& b) {
    return a > b ? a : b;
}

int main() {
    std::cout << max(1, 2) << std::endl;
    std::cout << max(1.0, 2.0) << std::endl;
    std::cout << max("hello", "world") << std::endl;
    std::cout << max(MyStruct{1, 2.0, "hello"}, MyStruct{3, 4.0, "world"}) << std::endl;
    return 0;
}