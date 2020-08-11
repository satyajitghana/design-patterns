#include <iostream>

class bar {
public:
    double val;
    bar() : val(10.0) {}
    bar(double val) : val(val) {}
};

class foo {
public:
    operator bar() {
        std::cout << "user-defined-conversion to `bar` called" << std::endl;
        return { 10.0 };
    }

    operator double() {
        std::cout << "user-defined-conversion to `double` called" << std::endl;
        return 20.0;
    }
};

int main() {
    foo A;
    bar B = A;
    double val = (double)A;
    std::cout << "value of (double)A : " << val << std::endl;

    return EXIT_SUCCESS;
}
