#include <stdexcept>
#include <string>
#include <memory>
#include <algorithm>
using namespace std;

#define MAX_CAPACITY 32768
#define INITIAL_CAPACITY 16

template <typename T>
class Stack {
    unique_ptr<T[]> elements;
    size_t capacity;
    size_t top;

public:
    Stack() : 
        top(0), 
        capacity(INITIAL_CAPACITY), 
        elements(make_unique<T[]>(INITIAL_CAPACITY)) {
        }

    int size() const {
        return top;
    }

    bool is_empty() const {
        return top == 0;
    }

    bool is_full() const {
        return top >= MAX_CAPACITY;
    }

    void push(const T& item) {
        if (is_full()) {
            throw overflow_error("Stack has reached maximum capacity");
        }

        if (top == capacity) {
            size_t new_capacity = std::min(capacity * 2, static_cast<size_t>(MAX_CAPACITY));
            reallocate(new_capacity);
        }

        elements[top++] = item;
    }

    T pop() {
        if (is_empty()) {
            throw underflow_error("cannot pop from empty stack");
        }

        T item = elements[--top];

        if (top > 0 && top * 4 <= capacity && capacity > INITIAL_CAPACITY) {
            size_t new_capacity = capacity / 2;
            reallocate(new_capacity);
        }

        return item;
    }

private:
    Stack(const Stack&) = delete;
    Stack(Stack&&) = delete;
    Stack<T>& operator=(const Stack<T>&) = delete;
    Stack& operator=(Stack&&) = delete;

    void reallocate(size_t new_capacity) {
        if (new_capacity > MAX_CAPACITY) {
            throw runtime_error("Stack has reached maximum capacity");
        }
        if (new_capacity < INITIAL_CAPACITY) {
            new_capacity = INITIAL_CAPACITY;
        }

        auto new_elements = std::make_unique<T[]>(new_capacity);
        std::copy(elements.get(), elements.get() + top, new_elements.get());
        elements = std::move(new_elements);
        capacity = new_capacity;
    }
};