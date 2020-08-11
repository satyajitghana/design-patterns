#pragma once

#include "Person.hpp"

class PersonBuilder {
    Person person;

public:
    PersonBuilder(std::string name) : person(name) { }

    /// read about cast_operator: https://en.cppreference.com/w/cpp/language/cast_operator
    operator Person() const {
        return std::move(person);
    }

    PersonBuilder& lives();
    PersonBuilder& at(std::string street_address);
    PersonBuilder& with_postcode(std::string post_code);
    PersonBuilder& in(std::string city);
    PersonBuilder& works();
    PersonBuilder& with(std::string company_name);
    PersonBuilder& as_a(std::string position);
    PersonBuilder& earning(std::string annual_income);
};