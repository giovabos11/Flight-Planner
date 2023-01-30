//
// Created by giova on 3/28/2022.
//

#ifndef INC_22S_FLIGHT_PLANNER_FLIGHTPLANNER_H
#define INC_22S_FLIGHT_PLANNER_FLIGHTPLANNER_H

#include <fstream>
#include <iomanip>

#include "DSAdjacencyList.h"
#include "City.h"
#include "Flight.h"

class FlightPlanner {
    private:

        DSAdjacencyList adjList;
        DSLinkedList<Request> requests;
        DSLinkedList<DSLinkedList<DSStack<City>>> paths;
        DSLinkedList<DSLinkedList<Itinerary>> flights;

        /**
         * Returns a boolean indicating if a City name is in a stack.
         * @return Boolean.
         **/
        bool in_stack(DSStack<City> stack, City find);
        /**
         * Calculates the time for a given path (DSStack<City>),
         * including the penalties.
         * @return Integer.
         **/
        int calculate_time(DSStack<City> path);
        /**
         * Calculates the cost for a given path (DSStack<City>),
         * including the penalties.
         * @return Integer.
         **/
        int calculate_cost(DSStack<City> path);
        /**
         * Sorts a list of itineraries by time in ascending order.
         * @return Void.
         **/
        void sort_itineraries_time(DSLinkedList<Itinerary>& itineraries);
        /**
         * Sorts a list of itineraries by cost in ascending order.
         * @return Void.
         **/
        void sort_itineraries_cost(DSLinkedList<Itinerary>& itineraries);

    public:

        /**
         * Default constructor.
         * @return None.
         **/
        FlightPlanner();

        /**
         * Reads the input data file and creates an adjacency list based
         * on it.
         * @return Void.
         **/
        void readData(const char*);

        /**
         * Reads the requested flights and stores them in the requests
         * list.
         * @return Void.
         **/
        void readRequested(const char*);

        /**
         * Calculates all the possible paths to the source to the
         * destination city using the iterative backtracking algorithm,
         * and stores all the possible paths for each request in the
         * paths list.
         * @return Void.
         **/
        void calculatePaths();

        /**
         * Calculates all the itineraries based on the paths list and
         * stores them in the flights list.
         * @return Void.
         **/
        void calculateItineraries();

        /**
         * Reports the data based on the requests and the contents of
         * the flights list.
         * @return Void.
         **/
        void report(const char*);
};



#endif //INC_22S_FLIGHT_PLANNER_FLIGHTPLANNER_H
