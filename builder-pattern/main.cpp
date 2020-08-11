#include <iostream>

#include "Person.hpp"
#include "PersonBuilder.hpp"

int main(int argc, char* argv[]) {

    Person p = Person::create("Satyajit")
        .lives()
        .at("123 London Road")
        .with_postcode("SW1 1GB")
        .in("London")
        .works()
        .with("Inkers Technology")
        .as_a("Visual Processing Intern")
        .earning("1.1e4");

    std::cout << p << std::endl;

    return EXIT_SUCCESS;
}