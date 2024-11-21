// A class for an expandable stack. There is already a stack class in the
// Standard C++ Library; this class serves as an exercise for students to
// learn the mechanics of building generic, expandable, data structures
// from scratch with smart pointers.

// A class for an expandable stack. There is already a stack class in the
// Standard C++ Library; this class serves as an exercise for students to
// learn the mechanics of building generic, expandable, data structures
// from scratch with smart pointers.
// A class for an expandable stack. There is already a stack class in the
// Standard C++ Library; this class serves as an exercise for students to
// learn the mechanics of building generic, expandable, data structures
// from scratch with smart pointers.

#include <stdexcept>
#include <string>
#include <memory>
#include <algorithm>
using namespace std;

#define MAX_CAPACITY 32768
#define INITIAL_CAPACITY 16

template <typename T>
class Stack {
private:
    unique_ptr<T[]> elements;
    size_t capacity;
    size_t top;

    // Prohibit copying, moving, and assignment
    Stack(const Stack&) = delete;
    Stack(Stack&&) = delete;
    Stack& operator=(const Stack&) = delete;
    Stack& operator=(Stack&&) = delete;

    // Private reallocation method
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

public:
    // Constructor
    Stack() : elements(std::make_unique<T[]>(INITIAL_CAPACITY)), 
              capacity(INITIAL_CAPACITY), 
              top(0) {}

    // Returns the number of elements in the stack
    size_t size() const {
        return top;
    }

    // Returns true if the stack contains no elements
    bool is_empty() const {
        return top == 0;
    }

    // Returns true if the stack is at maximum capacity
    bool is_full() const {
        return top >= MAX_CAPACITY;
    }

    // Adds the given item to the top of the stack
    void push(const T& item) {
        if (is_full()) {
            throw overflow_error("Stack has reached maximum capacity");
        }

        // Check if we need to expand
        if (top == capacity) {
            size_t new_capacity = std::min(capacity * 2, static_cast<size_t>(MAX_CAPACITY));
            reallocate(new_capacity);
        }

        elements[top++] = item;
    }

    // Removes and returns the top item from the stack
    T pop() {
        if (is_empty()) {
            throw underflow_error("cannot pop from empty stack");
        }

        T item = elements[--top];

        // Check if we need to shrink
        if (top > 0 && top * 4 <= capacity && capacity > INITIAL_CAPACITY) {
            size_t new_capacity = capacity / 2;
            reallocate(new_capacity);
        }

        return item;
    }
};