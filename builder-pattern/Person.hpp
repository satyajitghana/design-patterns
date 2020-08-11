#pragma once

#include <iostream>

class PersonBuilder;

class Person {
    std::string m_name, m_street_address, m_post_code, m_city;
    std::string m_company_name, m_position, m_annual_income;

    Person(std::string name) : m_name(name) {}

public:
    friend class PersonBuilder;
    friend std::ostream& operator<<(std::ostream& out, const Person& obj);
    static PersonBuilder create(std::string name);
};
