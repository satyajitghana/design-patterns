/**
 * source: http://www.vishalchovatiya.com/composite-design-pattern-in-modern-cpp/
*/

#include <iostream>
#include <vector>
#include <memory>
#include <string>

template <typename Self>
struct SomeNeurons {
    template <typename T>
    void connect_to(T &other);
};

struct Neuron : SomeNeurons<Neuron> {
    std::vector<Neuron*>    in, out;
    uint32_t                id;

    Neuron() {
        static int id = 1;
        this->id = id++;
    }

    Neuron* begin() {
        return this;
    }
    Neuron* end() {
        return this + 1;
    }

};

struct NeuronLayer : std::vector<Neuron>, SomeNeurons<NeuronLayer> {
    NeuronLayer(int count) {
        while (count-- > 0)
            emplace_back(Neuron{});
    }
};

template <typename Self>
template <typename T>
void SomeNeurons<Self>::connect_to(T &other) {
    for (Neuron &from : *static_cast<Self *>(this)) {
        for (Neuron &to : other) {
            from.out.push_back(&to);
            to.in.push_back(&from);
        }
    }
}

template<typename Self>
std::ostream &operator<<(std::ostream &os, SomeNeurons<Self> &object) {
    for (Neuron &obj : *static_cast<Self *>(&object)) {
        for (Neuron *n : obj.in)
            os << n->id << "\t-->\t[" << obj.id << "]" << std::endl;

        for (Neuron *n : obj.out)
            os << "[" << obj.id << "]\t-->\t" << n->id << std::endl;
    }
    return os;
}



int main(int argc, char const *argv[]) {
    Neuron n1, n2;
    NeuronLayer l1{ 1 }, l2{ 2 };

    n1.connect_to(l1);
    l2.connect_to(n2);
    l1.connect_to(l2);
    n1.connect_to(n2);

    std::cout << "Neuron " << n1.id << "\n" << n1 << "\n";
    std::cout << "Neuron " << n2.id << "\n" << n2 << "\n";

    std::cout << "Layer " << "\n" << l1 << "\n";
    std::cout << "Layer " << "\n" << l2 << "\n";

    return EXIT_SUCCESS;
}

