//
// Created by giova on 3/29/2022.
//

#ifndef INC_22S_FLIGHT_PLANNER_FLIGHT_H
#define INC_22S_FLIGHT_PLANNER_FLIGHT_H

#include "DSString.h"
#include "DSStack.h"

/**
 * Stores a path, time and cost of a flight
 **/
struct Itinerary {
    DSStack<City> path;
    int time;
    int cost;
};

/**
 * Stores the source city name, destination, and type
 * (time or cost) for each request.
 **/
struct Request {
    DSString source;
    DSString destination;
    DSString type;
};

#endif //INC_22S_FLIGHT_PLANNER_FLIGHT_H
