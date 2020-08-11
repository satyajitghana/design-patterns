#include "Person.hpp"
#include "PersonBuilder.hpp"

#include <iostream>

PersonBuilder Person::create(std::string name) {
    return PersonBuilder{ name };
}

std::ostream& operator<<(std::ostream& out, const Person& obj) {
    return out
        << obj.m_name << std::endl
        << "lives : " << std::endl
        << "at " << obj.m_street_address
        << " with postcode " << obj.m_post_code
        << " in " << obj.m_city
        << std::endl
        << "works : " << std::endl
        << "with " << obj.m_company_name
        << " as a " << obj.m_position
        << " earning " << obj.m_annual_income;
}

