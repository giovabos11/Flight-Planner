//
// Created by giova on 3/28/2022.
//

#ifndef INC_22S_FLIGHT_PLANNER_DSSTACK_H
#define INC_22S_FLIGHT_PLANNER_DSSTACK_H

#include "DSLinkedList.h"

template<typename T>
class DSStack {
    private:

        DSLinkedList<T> stack;

    public:

        /**
         * Default constructor.
         * @return None.
         **/
        DSStack();

        /**
         * Pushes an element to the stack.
         * @return Void.
         **/
        void push(T arg);

        /**
         * Removes an element from the stack.
         * Returns a boolean indicating if the element was successfully
         * removed.
         * @return Boolean.
         **/
        bool pop();

        /**
         * Returns the element at the top of the stack.
         * @return Data type.
         **/
        T top();

        /**
         * Returns a boolean indicating if the stack is empty.
         * @return Boolean.
         **/
        bool is_empty();

        /**
         * Clears the stack.
         * @return Void.
         **/
        void clear();
};

template<typename T>
DSStack<T>::DSStack() {

}

template<typename T>
void DSStack<T>::push(T arg) {
    // Push the argument in front of the list
    stack.push_front(arg);
}

template<typename T>
bool DSStack<T>::pop() {
    // If stack is not empty
    if (!is_empty()) {
        // Removes the front of the list
        stack.pop_front();
        // Return true
        return true;
    }
    // Otherwise, the stack is empty
    else {
        // Return false
        return false;
    }
}

template<typename T>
T DSStack<T>::top() {
    // Return the front of the list
    return stack.get_front();
}

template<typename T>
bool DSStack<T>::is_empty() {
    // Returns if the size of the list is 0
    return stack.get_size() == 0;
}

template<typename T>
void DSStack<T>::clear() {
    // Clear the list
    stack.clear();
}

#endif //INC_22S_FLIGHT_PLANNER_DSSTACK_H
