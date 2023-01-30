//
// Created by giova on 3/28/2022.
//

#ifndef INC_22S_FLIGHT_PLANNER_DSADJACENCYLIST_H
#define INC_22S_FLIGHT_PLANNER_DSADJACENCYLIST_H

#include "City.h"

class DSAdjacencyList {
    private:

        DSLinkedList<DSLinkedList<City>> sourceList;

    public:

        /**
         * Default constructor.
         * @return None.
         **/
        DSAdjacencyList();

        /**
         * Finds returns all the connections for a given source City.
         * If no source city is found, it returns null pointer.
         * @return Pointer to DSLinkedList<City>.
         **/
        DSLinkedList<City>* findConnections(City source);

        /**
         * Pushes a source City with its respective destination City.
         * If the source City exist in the adjacency list, the destination
         * City is added at the end of the existing source City.
         * @return Void.
         **/
        void push(City sourceCity, City destinationCity);

        /**
         * Deletes the last element in the adjacency list.
         * Returns a boolean indicating if the element was successfully
         * popped.
         * @return Boolean.
         **/
        bool pop_back();
        /**
         * Deletes the first element in the adjacency list.
         * Returns a boolean indicating if the element was successfully
         * popped.
         * @return Boolean.
         **/
        bool pop_front();

        /**
         * Subscript operator.
         * @return Reference to a DSLinkedList<City>.
         **/
        DSLinkedList<City>& operator[](int index);

        /**
         * Returns the size of the adjacency list.
         * @return Integer.
         **/
        int get_size();
};


#endif //INC_22S_FLIGHT_PLANNER_DSADJACENCYLIST_H
