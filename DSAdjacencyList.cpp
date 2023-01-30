//
// Created by giova on 3/28/2022.
//

#include "DSAdjacencyList.h"

DSAdjacencyList::DSAdjacencyList() {

}

void DSAdjacencyList::push(City sourceCity, City destinationCity) {
    // Declare a variable to store if the source city is found
    bool found = false;

    // Try to find source city in source list
    for (int i = 0; i < sourceList.get_size() && !found; i++) {
        // If source city is found in list
        if (sourceList[i][0].name == sourceCity.name) {
            // Push back the new destination
            sourceList[i].push_back(destinationCity);

            // Set found to true
            found = true;
        }
    }

    // If city was not found
    if (!found) {
        DSLinkedList<City> temp;
        temp.push_back(sourceCity);
        temp.push_back(destinationCity);
        // Push back the new source city
        sourceList.push_back(temp);
    }
}

DSLinkedList<City>* DSAdjacencyList::findConnections(City source) {
    // Try to find source city in source list
    for (int i = 0; i < sourceList.get_size(); i++) {
        // If source city is found in list
        if (sourceList[i][0].name == source.name) {
            // Return linked list at that position
            return &sourceList[i];
        }
    }
    // If not found, return null pointer
    return nullptr;
}

bool DSAdjacencyList::pop_back() {
    // Pop last element of source list
    return sourceList.pop_back();
}

bool DSAdjacencyList::pop_front() {
    // Pop first element of source list
    return sourceList.pop_front();
}

DSLinkedList<City>& DSAdjacencyList::operator[](int index) {
    // Return element in source list at index specified
    return sourceList[index];
}

int DSAdjacencyList::get_size() {
    // Return the size of the source list
    return sourceList.get_size();
}
