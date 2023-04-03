#ifndef STACK_H
#define STACK_H

#include "LinkedList.h"
#include <stdexcept>

template <class T>
class Stack {
private:
    LinkedList<T> list;

public:
    Stack() {}

    int size() const {
        return list.getSize();
    }

    bool empty() const {
        return list.isEmpty();
    }

    void push(const T& value) {
        list.prepend(value);
    }

    T pop() {
        if (list.isEmpty()) {
            throw std::out_of_range("Stack is empty");
        }
        T value = list.get(0);
        list.remove(0);
        return value;
    }

    T top() {
        if (list.isEmpty()) {
            throw std::out_of_range("Stack is empty");
        }
        return list.get(0);
    }
};

#endif // STACK_H