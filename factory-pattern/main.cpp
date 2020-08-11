#include <iostream>
#include <map>
#include <memory>
#include <functional>
#include <math.h>
#include <sstream>

enum class PointType {
    cartesian, polar
};

struct Point {
    float m_x;
    float m_y;

    Point(float x, float y) : m_x(x), m_y(y) {}
public:
    std::string to_string() {
        std::stringstream ss;
        ss << "x : " << m_x << ", y : " << m_y << std::endl;
        return ss.str();
    }
};

class PointFunctionalFactory {
    std::map<PointType, std::function<std::unique_ptr<Point>(float x, float y)>> m_factories;

public:
    PointFunctionalFactory() {
        // Registered Classes
        // to register more classes a function `regsiter_class` can be added to this FuntionalFactory
        m_factories[PointType::cartesian] = [](float x, float y) { return std::make_unique<Point>(x, y); };
        m_factories[PointType::polar] = [](float r, float theta) { return std::make_unique<Point>(r * std::cos(theta), r * std::sin(theta)); };
    }

    std::unique_ptr<Point> create(PointType type, float x, float y) {
        return m_factories[type](x, y);
    }
};

int main(int argc, char* argv[]) {
    PointFunctionalFactory pf;
    auto polarP = pf.create(PointType::polar, 2.4, 1.2);
    std::cout << polarP->to_string();

    return EXIT_SUCCESS;
}
