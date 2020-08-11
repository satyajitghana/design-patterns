#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>

struct Database {
    virtual int32_t get_population(const std::string& country) = 0;
};

class SingletonDatabase : public Database {
    std::map<std::string, int32_t> m_countries;

    SingletonDatabase() {
        std::ifstream ifs("countries.txt", std::ifstream::in);
        std::string city, population;
        while (std::getline(ifs, city)) {
            std::getline(ifs, population);
            m_countries[city] = std::stoi(population);
        }
    }
public:
    /// delete the constructor and assignment constructors
    SingletonDatabase(SingletonDatabase const &) = delete;
    SingletonDatabase &operator=(SingletonDatabase const &) = delete;

    static SingletonDatabase &get() {
        static SingletonDatabase db;
        return db;
    }

    int32_t get_population(const std::string &country) {
        return m_countries[country];
    }
};

class DummyDatabase : public Database {
    std::map<std::string, int32_t> m_countries;
public:
    DummyDatabase() : m_countries{ { "alpha", 1 }, { "beta", 2 }, { "gamma", 3 } } {};
    int32_t get_population(const std::string &country) {
        return m_countries[country];
    }
};

class ConfigurableRecordFinder {
    Database& m_db;
public:
    ConfigurableRecordFinder(Database &db) : m_db{ db } {}
    int32_t total_population(const std::vector<std::string> &countries) {
        int32_t result = 0;
        for (auto &country : countries)
            result += m_db.get_population(country);

        return result;
    }
};

int main() {
    DummyDatabase db;
    ConfigurableRecordFinder rf(db);
    std::cout << "total population = " << rf.total_population({ "alpha", "beta", "gamma" }) << std::endl;

    ConfigurableRecordFinder srf(SingletonDatabase::get());
    std::cout << "singleton total population = " << srf.total_population({ "Japan", "India", "America" }) << std::endl;

    return EXIT_SUCCESS;
}
