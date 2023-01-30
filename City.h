//
// Created by giova on 3/28/2022.
//

#ifndef INC_22S_FLIGHT_PLANNER_CITY_H
#define INC_22S_FLIGHT_PLANNER_CITY_H

#include "DSString.h"
#include "DSLinkedList.h"

/**
 * Stores the name, cost, time, and airline for each City flight.
 **/
struct City {
    DSString name;
    DSString cost;
    DSString time;
    DSString airline;

    /**
     * Default constructor.
     * @return None.
     **/
    City() {
        this->name = "";
        this->cost = "";
        this->time = "";
        this->airline = "";
    }

    /**
     * Equal to operator.
     * @return Boolean.
     **/
    bool operator==(const City& arg) {
        return name == arg.name && cost == arg.cost && time == arg.time && airline == arg.airline;
    }
};

#endif //INC_22S_FLIGHT_PLANNER_CITY_H
