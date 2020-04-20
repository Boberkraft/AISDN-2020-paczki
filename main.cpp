#include <iostream>
#include <vector>
#include <string>


struct Pack
{
    int weight;
    int cost;

    Pack()
    {};

    Pack(int r_weight, int r_cost)
        : weight(r_weight)
        , cost(r_cost)
    {}
};

template <class X>
class Stack {
    int top;
    int capacity;
    X* a;
public:
    Stack();

    void push(X & x);
    int size();
    X & pop();
    X & get(int i);
    void print();
    // dodac dekstruktor
};

template <class X>
Stack<X>::Stack() {
    capacity = 20;
    a = new X[20];
    top = -1;
}

template <class X>
int Stack<X>::size() {
    return top + 1;
}

template <class X>
void Stack<X>::push(X &v) {

    top++;
    a[top] = v;
}

template <class X>
X &Stack<X>::pop() {
    if (top < 0) {
        throw std::logic_error("Stack undefrlow");
    }

    return a[top--];
}

template <class X>
X &Stack<X>::get(int i) {
    return a[i];
}

int calculate(Pack parcels[], int size, Stack<Pack> & car, int weight, int cost) {
    if (weight > 1766) {
        return 0;
    }

    for (int i = car.size(); i < size; i++) {
        car.push(parcels[i]);

        int new_cost = parcels[i].cost;
        int new_weight = parcels[i].weight;

        if (parcels[i].cost > 100) {
            new_cost -= 5;
        }

        int this_cost = calculate(
            parcels, size, car, 
            weight + new_weight,
            cost + new_cost
        );
        if (this_cost > cost) {
            cost = this_cost;
        }
        car.pop();
    }

    return cost;
}

int main(int argc, char *argv[]) {

    Pack packs [] = {
         Pack {588, 211},
         Pack {40, 30},
         Pack {307, 974},
         Pack {367, 943},
         Pack {206, 622}
    };

    // wynik 965
    auto car = Stack<Pack>{};
    std::cout << calculate(packs, 5, car, 0, 0) << std::endl;
}
