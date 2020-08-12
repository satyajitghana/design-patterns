/**
 * source: http://www.vishalchovatiya.com/crtp-c-examples/
*/

#include <iostream>

template <typename specific_animal>
struct animal {
    void who() {
        static_cast<specific_animal*>(this)->who();
    }
};

struct dog : animal<dog> {
    void who() {
        std::cout << "dog" << std::endl;
    }
};

struct cat : animal<cat> {
    void who() {
        std::cout << "cat" << std::endl;
    }
};

template<typename specific_animal>
void who_am_i(animal<specific_animal> &animal) {
    animal.who();
}

int main() {
    cat c;
    who_am_i(c);

    dog d;
    who_am_i(d);

    return EXIT_SUCCESS;
}
