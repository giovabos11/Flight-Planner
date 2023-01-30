//
// Created by giova on 3/22/2022.
//

#ifndef INC_22S_FLIGHT_PLANNER_DSNODE_H
#define INC_22S_FLIGHT_PLANNER_DSNODE_H

template<typename T>
class DSNode {
private:
    DSNode<T>* prev;
    DSNode<T>* next;
    T data;

public:
    /**
     * Default constructor.
     * @return None.
     **/
    DSNode();
    /**
     * Data constructor.
     * @return None.
     **/
    DSNode(const T& arg);
    /**
     * Copy constructor.
     * @return None.
     **/
    DSNode(const DSNode<T>& arg);
    /**
     * Assignment operator.
     * @return Reference to a DSNode<T>.
     **/
    DSNode<T>& operator=(const DSNode<T>& arg);

    /**
     * Returns a reference the data.
     * @return Reference to a data type.
     **/
    T& getData();
    /**
     * Sets the data to the argument.
     * @return Void.
     **/
    void setData(const T& arg);

    /**
     * Returns a pointer that points to the previous node.
     * @return Pointer to DSNode<T>.
     **/
    DSNode<T>* getPrev();
    /**
     * Sets the previous pointer to the argument.
     * @return Void.
     **/
    void setPrev(DSNode* arg);

    /**
     * Returns a pointer that points to the next node.
     * @return Pointer to DSNode<T>.
     **/
    DSNode<T>* getNext();
    /**
     * Sets the next pointer to the argument.
     * @return Void.
     **/
    void setNext(DSNode* arg);
};

template<typename T>
DSNode<T>::DSNode() {
    // Set previous and next to null pointer
    prev = nullptr;
    next = nullptr;
}

template<typename T>
DSNode<T>::DSNode(const T& arg) {
    // Set previous and next to null pointer
    prev = nullptr;
    next = nullptr;
    // Set data to the argument
    data = arg;
}

template<typename T>
DSNode<T>::DSNode(const DSNode<T>& arg) {
    // Copy all members
    prev = arg.prev;
    next = arg.next;
    data = arg.data;
}

template<typename T>
DSNode<T>& DSNode<T>::operator=(const DSNode<T>& arg) {
    // Copy all members
    next = arg.next;
    prev = arg.prev;
    data = arg.data;
    // Return a reference to this object
    return *this;
}

template<typename T>
T& DSNode<T>::getData() {
    // Return the data
    return data;
}

template<typename T>
void DSNode<T>::setData(const T& arg) {
    // Set data to the argument
    data = arg;
}

template<typename T>
DSNode<T>* DSNode<T>::getPrev() {
    // Return previous pointer
    return prev;
}

template<typename T>
void DSNode<T>::setPrev(DSNode* arg) {
    // Set previous pointer to the argument
    prev = arg;
}

template<typename T>
DSNode<T>* DSNode<T>::getNext() {
    // Return next pointer
    return next;
}

template<typename T>
void DSNode<T>::setNext(DSNode* arg) {
    // Set next pointer to the argument
    next = arg;
}

#endif //INC_22S_FLIGHT_PLANNER_DSNODE_H
