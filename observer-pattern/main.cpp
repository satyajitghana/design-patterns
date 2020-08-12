#include <iostream>
#include <vector>
#include <string>

template<typename T>
struct Observer {
    virtual void field_changed(T& source, const std::string& field_name) = 0;
};

template<typename T>
struct Observable {
    void notify(T& source, const std::string& field_name) {
        for (auto observer: m_observers)
            observer->field_changed(source, field_name);
    }
    void subscribe(Observer<T>& observer) {
        m_observers.push_back(&observer);
    }
    void unsubscribe(Observer<T>& observer) {
        // std::remove(std::begin(m_observers), std::end(m_observers), &observer);
    }
private:
    std::vector<Observer<T>*>    m_observers;
};

struct Person : Observable<Person> {
    void set_age(uint8_t age) {
        auto old_can_vote = get_can_vote();
        this->m_age = age;
        notify(*this, "age");
        if (old_can_vote != get_can_vote()) notify(*this, "can_vote");
    }
    uint8_t get_age() const {
        return m_age;
    }
    bool get_can_vote() const {
        return m_age >= 16;
    }
private:
    uint8_t m_age{ 0 };
};

struct TrafficAdministration : Observer<Person> {
    void field_changed(Person &source, const std::string& field_name) {
        if (field_name == "age") {
            if (source.get_age() < 17)
                std::cout << "not old enough to drive!\n";
            else {
                std::cout << "mature enough to drive!\n";
                source.unsubscribe(*this);
            }
        }
    }
};

int main() {
    Person p;
    TrafficAdministration ta;
    p.subscribe(ta);
    p.set_age(16);
    p.set_age(17);
    return EXIT_SUCCESS;
}

