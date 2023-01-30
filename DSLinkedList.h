//
// Created by giova on 3/22/2022.
//

#ifndef INC_22S_FLIGHT_PLANNER_DSLINKEDLIST_H
#define INC_22S_FLIGHT_PLANNER_DSLINKEDLIST_H

#include <ostream>

#include "DSNode.h"

using namespace std;

template<typename T>
class DSLinkedList {
    private:

        DSNode<T>* back;
        DSNode<T>* front;
        DSNode<T>* itr;
        int size;

    public:

        /**
         * Default constructor.
         * @return None.
         **/
        DSLinkedList();
        /**
         * Copy constructor.
         * @return None.
         **/
        DSLinkedList(const DSLinkedList& arg);
        /**
         * Destructor.
         * @return None.
         **/
        ~DSLinkedList();
        /**
         * Assignment operator.
         * @return Reference to a DSLinkedList<T>.
         **/
        DSLinkedList<T>& operator=(const DSLinkedList<T>& arg);

        /**
         * Pushes the given data to the end of the list.
         * @return Void.
         **/
        void push_front(T data);
        /**
         * Pushes the given data to the beginning of the list.
         * @return Void.
         **/
        void push_back(T data);

        /**
         * Removes the last element from the list.
         * Returns a boolean indicating if the element was successfully
         * popped.
         * @return Boolean.
         **/
        bool pop_back();
        /**
         * Removes the first element from the list.
         * Returns a boolean indicating if the element was successfully
         * popped.
         * @return Boolean.
         **/
        bool pop_front();

        /**
         * Returns the data at the beginning of the list.
         * @return Reference to a data type.
         **/
        T& get_front();
        /**
         * Returns the data at the end of the list.
         * @return Reference to a data type.
         **/
        T& get_back();

        /**
         * Returns the size of the list.
         * @return Integer.
         **/
        int get_size();

        /**
         * Returns a boolean indicating if the list is empty.
         * @return Boolean.
         **/
        bool is_empty() const;

        /**
         * Clears the contents of the list.
         * @return Void.
         **/
        void clear();

        /**
         * Returns the data at specified index of the list.
         * @return Reference to a data type.
         **/
        T& at(int index);
        /**
         * Subscript operator.
         * @return Reference to a data type.
         **/
        T& operator[](int index);
        /**
         * Returns the data at specified index of the list (constant).
         * @return Reference to a data type.
         **/
        T& at(int index) const;
        /**
         * Subscript operator (constant).
         * @return Reference to a data type.
         **/
        T& operator[](int index) const;

        /**
         * Overloaded stream insertion operator to print the contents of the
         * DSLinkedList to the output stream in the first argument.
         * @return Reference to an ostream object.
         **/
        template<class O>
        friend ostream& operator<<(ostream&, const DSLinkedList<O>&);

        /** Iterator **/

        /**
         * Resets the iterator
         * @return Void.
         **/
        void reset_itr();

        /**
         * Checks if value of iterator is null or if iterator has a next
         * element.
         * @return Boolean.
         **/
        bool has_next();
        /**
         * Returns a boolean indicating if iterator is null pointer.
         * @return Boolean.
         **/
        bool itr_null();

        /**
         * Returns the data currently held by the iterator and
         * increments the iterator.
         * @throws If iterator is null pointer, a logic error is thrown.
         * @return Reference to a data type.
         **/
        T& get_next();
        /**
         * Returns the data currently held by the iterator.
         * @throws If list is empty, a logic error is thrown.
         * @return Reference to a data type.
         **/
        T& get_curr();

};

template<typename T>
DSLinkedList<T>::DSLinkedList() {
    front = nullptr;
    back = nullptr;
    itr = front;
    size = 0;
}

template<typename T>
DSLinkedList<T>::DSLinkedList(const DSLinkedList& arg) {
    // Set back and front to nullptr (temporarily)
    front = nullptr;
    back = nullptr;
    // Copy all the elements from the argument list
    for (int i = 0; i < arg.size; i++) {
        push_back(arg[i]);
    }
    // Set previous pointer of front to null pointer
    front->setPrev(nullptr);
    // Set next pointer of back to null pointer
    back->setNext(nullptr);
    // Set the size to the argument list size
    size = arg.size;
    // Set iterator to the beginning position
    itr = front;
}

template<typename T>
DSLinkedList<T>::~DSLinkedList() {
    // If front is not null pointer (list is not empty)
    if (front != nullptr) {
        // Declare a current and temporary pointer pointing to front
        DSNode<T>* curr = front;
        DSNode<T> *temp = curr;
        // While current is not null pointer
        while (curr != nullptr) {
            // Get next element
            curr = curr->getNext();
            // Delete previous
            delete temp;
            // Set temp to current
            temp = curr;
        }
    }
}

template<typename T>
DSLinkedList<T>& DSLinkedList<T>::operator=(const DSLinkedList<T>& arg) {
    // If list is not empty
    if (!is_empty()) {
        // Clear list
        clear();
    }

    // Set back and front to nullptr (temporarily)
    front = nullptr;
    back = nullptr;
    // Copy all the elements from the argument list
    for (int i = 0; i < arg.size; i++) {
        push_back(arg[i]);
    }
    // Set previous pointer of front to null pointer
    front->setPrev(nullptr);
    // Set next pointer of back to null pointer
    back->setNext(nullptr);
    // Set the size to the argument list size
    size = arg.size;
    // Set iterator to the beginning position
    itr = front;

    // Return the object
    return *this;
}

template<typename T>
void DSLinkedList<T>::push_front(T data) {
    // Create a new node
    DSNode<T>* newNode = new DSNode<T>();

    // Set new node data to argument
    newNode->setData(data);
    // Set new node next to the current front
    newNode->setNext(front);
    // Set new node previous to null pointer
    newNode->setPrev(nullptr);

    // If front is not null (Linked List is not empty)
    if (front != nullptr) {
        // Change the previous front node to the new node
        front->setPrev(newNode);
    }
    // Set front to new node
    front = newNode;

    // Special case: the list was empty
    if (back == nullptr) {
        back = newNode;
    }

    // Increment size
    size++;
}

template<typename T>
void DSLinkedList<T>::push_back(T data) {
    // Create a new node
    DSNode<T>* newNode = new DSNode<T>();

    // Set new node data to argument
    newNode->setData(data);
    // Set new node next to null pointer
    newNode->setNext(nullptr);
    // Set new node previous to current back
    newNode->setPrev(back);

    // If back is not null (Linked List is not empty)
    if (back != nullptr) {
        // Change the previous front node to the new node
        back->setNext(newNode);
    }
    // Set front to new node
    back = newNode;

    // Special case: the list was empty
    if (front == nullptr) {
        front = newNode;
    }

    // Increment size
    size++;
}

template<typename T>
bool DSLinkedList<T>::pop_back() {
    // If list is not empty
    if (!is_empty()) {
        // Temporary store the back before deletion
        DSNode<T> *temp = back;

        // If front is equal to back (only one element in the list)
        if (front == back) {
            front = nullptr;
            back = nullptr;
        }
        // Otherwise, there are more elements in the list
        else {
            DSNode<T>* curr = front;

            // Find penultimate element
            while(curr->getNext() != back) {
                curr = curr->getNext();
            }

            // Remove last node
            back = curr;
            // Current is now the last pointer
            curr->setNext(nullptr);
        }

        // Free memory occupied by front
        delete temp;

        // Decrement size
        size--;

        // Return true
        return true;
    }
    // Otherwise, list is empty
    else {
        // Return false
        return false;
    }
}

template<typename T>
bool DSLinkedList<T>::pop_front() {
    // If list is not empty
    if (!is_empty()) {
        // Temporary store the front before deletion
        DSNode<T> *temp = front;

        // If front is equal to back (only one element in the list)
        if (front == back) {
            front = nullptr;
            back = nullptr;
        }
        // Otherwise, there are more elements in the list
        else {
            front = front->getNext();
        }

        // Free memory occupied by back
        delete temp;

        // Decrement size
        size--;

        // Return true
        return true;
    }
    // Otherwise, list is empty
    else {
        // Return false
        return false;
    }
}

template<typename T>
T& DSLinkedList<T>::get_front() {
    // If list is empty
    if (is_empty()) {
        // Throw logic error
        throw logic_error("List is empty");
    }
    // Return the data stored in front
    return front->getData();
}

template<typename T>
T& DSLinkedList<T>::get_back() {
    // If list is empty
    if (is_empty()) {
        // Throw logic error
        throw logic_error("List is empty");
    }
    // Return the data stored in the back
    return back->getData();
}

template<typename T>
int DSLinkedList<T>::get_size() {
    // Return the size of the list
    return size;
}

template<typename T>
bool DSLinkedList<T>::is_empty() const {
    // Size is 0, the list is empty
    return size == 0;
}

template<typename T>
void DSLinkedList<T>::clear() {
    // While the list is not empty
    while(!is_empty()) {
        // Delete all the elements
        pop_back();
    }
}

template<typename T>
T& DSLinkedList<T>::at(int index) {
    // Create a current node to keep track of the current index
    DSNode<T>* curr = front;
    // For every index, get the next element
    for (int i = 0; i < index; i++) {
        // Get next element
        curr = curr->getNext();
    }
    // Return the element at the given index
    return curr->getData();
}

template<typename T>
T& DSLinkedList<T>::operator[](int index) {
    // Return the data stored at that specific index
    return at(index);
}

template<typename T>
T& DSLinkedList<T>::at(int index) const {
    // Create a current node to keep track of the current index
    DSNode<T>* curr = front;
    // For every index, get the next element
    for (int i = 0; i < index; i++) {
        // Get next element
        curr = curr->getNext();
    }
    // Return the element at the given index
    return curr->getData();
}

template<typename T>
T& DSLinkedList<T>::operator[](int index) const {
    // Return the data stored at that specific index
    return at(index);
}

template<typename T>
ostream& operator<<(ostream& out, const DSLinkedList<T>& l) {
    // If the list is not empty
    if (!l.is_empty()) {
        // Create a current node to keep track of the current element
        DSNode<T>* curr = l.front;
        while(curr != nullptr) {
            // Output the data
            out << curr->getData();
            // Output arrows if there are more elements
            if (curr->getNext() != nullptr) {
                out << "<=>";
            }
            // Get next element
            curr = curr->getNext();
        }
    }

    // Return the ostream object
    return out;
}

/** Iterator **/

template<typename T>
void DSLinkedList<T>::reset_itr() {
    // Set iterator to the front of the list
    itr = front;
}

template<typename T>
bool DSLinkedList<T>::has_next() {
    // If iterator is null return false
    if (itr == nullptr) {
        return false;
    }
    else {
        // Return if the iterator has a next element
        return itr->getNext() != nullptr;
    }
}

template<typename T>
bool DSLinkedList<T>::itr_null() {
    // If iterator is null return true
    if (itr == nullptr) {
        return true;
    }
    // Otherwise, return false
    return false;
}

template<typename T>
T& DSLinkedList<T>::get_next() {
    // If iterator is null
    if (itr == nullptr) {
        // Throw logic error
        throw logic_error("No next element");
    }
    // Declare a temporary DSNode<T> pointer to store the old address of iterator
    DSNode<T>* temp = itr;
    // Get next element of iterator
    itr = itr->getNext();
    // Return the data contained by the old address of iterator
    return temp->getData();
}

template<typename T>
T& DSLinkedList<T>::get_curr() {
    // If list is empty
    if (is_empty()) {
        // Throw logic error
        throw logic_error("List is empty");
    }
    // Return the data contained by the iterator
    return itr->getData();
}



#endif //INC_22S_FLIGHT_PLANNER_DSLINKEDLIST_H
