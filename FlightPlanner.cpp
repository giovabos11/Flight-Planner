//
// Created by giova on 3/28/2022.
//

#include "FlightPlanner.h"

FlightPlanner::FlightPlanner() {

}

void FlightPlanner::readData(const char* fileName) {
    // Declare input file buffer
    ifstream inputFile;
    char bufferCityFrom[25];
    char bufferCityTo[25];
    char bufferCost[7];
    char bufferTime[6];
    char bufferAirline[25];
    char bufferDataCount[5];
    // Declare DSString variables to store the data
    DSString cityFrom;
    DSString cityTo;
    DSString cost;
    DSString time;
    DSString airline;
    DSString dataCount;
    // Open flights file
    inputFile.open(fileName);

    // If input file opened correctly
    if (inputFile) {
        // Get data count
        inputFile.getline(bufferDataCount, 5);
        dataCount = bufferDataCount;

        // Read until the end of the file
        while (!inputFile.eof()) {
            // Get each element from data file
            inputFile.getline(bufferCityFrom, 24, ' ');
            inputFile.getline(bufferCityTo, 24, ' ');
            inputFile.getline(bufferCost, 6, ' ');
            inputFile.getline(bufferTime, 5, ' ');
            inputFile.getline(bufferAirline, 24);

            // Store read data into their respective DSString
            cityFrom = bufferCityFrom;
            cityTo = bufferCityTo;
            cost = bufferCost;
            time = bufferTime;
            airline = bufferAirline;

            // Clean strings
            cityFrom.clean();
            cityTo.clean();
            cost.clean();
            time.clean();
            airline.clean();

            // If the cities lengths are greater than 0
            if (cityFrom.getLength() > 0 && cityTo.getLength() > 0) {
                // Create a new destination city
                City destTemp;
                destTemp.name = cityTo;
                destTemp.cost = cost;
                destTemp.time = time;
                destTemp.airline = airline;

                // Create a new source city
                City sourceTemp;
                sourceTemp.name = cityFrom;

                // Push source city to adjacency list
                adjList.push(sourceTemp, destTemp);

                // Switch the destinations and sources
                destTemp.name = cityFrom;
                sourceTemp.name = cityTo;

                // Push again but in inverted order
                adjList.push(sourceTemp, destTemp);
            }
        }
    }

    // Close input file
    inputFile.close();
}

void FlightPlanner::readRequested(const char* fileName) {
    // Declare input file buffer
    ifstream inputFile;
    char bufferCityFrom[25];
    char bufferCityTo[25];
    char bufferType[3];
    char bufferDataCount[5];
    // Declare DSString variables to store the data
    DSString cityFrom;
    DSString cityTo;
    DSString type;
    DSString dataCount;
    // Open flights file
    inputFile.open(fileName);

    // If input file opened correctly
    if (inputFile) {
        // Get data count
        inputFile.getline(bufferDataCount, 5);
        dataCount = bufferDataCount;

        // Read until the end of the file
        while (!inputFile.eof()) {
            // Get each element from data file
            inputFile.getline(bufferCityFrom, 24, ' ');
            inputFile.getline(bufferCityTo, 24, ' ');
            inputFile.getline(bufferType, 3);

            // Store read data into their respective DSString
            cityFrom = bufferCityFrom;
            cityTo = bufferCityTo;
            type = bufferType;

            // Clean strings
            cityFrom.clean();
            cityTo.clean();
            type.clean();

            // If the cities lengths are greater than 0
            if (cityFrom.getLength() > 0 && cityTo.getLength() > 0 && type.getLength() > 0) {
                Request tempRequest;
                tempRequest.source = cityFrom;
                tempRequest.destination = cityTo;
                tempRequest.type = type;

                requests.push_back(tempRequest);
            }
        }
    }

    // Close input file
    inputFile.close();
}

void FlightPlanner::calculatePaths() {
    // Create new stack object
    DSStack<City> stack;
    // Create a DSLinkedList to store all paths from a specific request
    DSLinkedList<DSStack<City>> currPath;
    // For every flight requested
    for (int i = 0; i < requests.get_size(); i++) {
        // Reset every element in adjacency list
        for (int k = 0; k < adjList.get_size(); k++) {
            // Reset iterator
            adjList[k].reset_itr();
            // Get next element
            adjList[k].get_next();
        }

        // Create temp city to store source city requested
        City tempSource;
        tempSource.name = requests[i].source;

        // Push source flight to the stack
        stack.push(tempSource);

        // While the stack is not empty
        while (!stack.is_empty()) {
            // Check if top of the stack is the destination
            if (stack.top().name == requests[i].destination) {
                // Store the current path into the paths list
                currPath.push_back(stack);
                // Pop last element on stack
                stack.pop();
            }
            // Otherwise, continue
            else {
                // Find connections for the top of the stack
                DSLinkedList<City>* connections = adjList.findConnections(stack.top());

                // If the connection is null
                if (connections->itr_null()) {
                    // Reset iterator
                    connections = adjList.findConnections(stack.top());
                    connections->reset_itr();
                    connections->get_next();

                    // Pop the stack
                    stack.pop();
                }
                // Otherwise
                else {
                    // If connection is not in the stack
                    if (!in_stack(stack, connections->get_curr())) {
                        // Push the connection to the stack
                        stack.push(connections->get_curr());
                    }

                    // Move the iterator
                    connections->get_next();
                }
            }
        }
        // Push back all the paths for a request
        paths.push_back(currPath);
        // Clear list
        currPath.clear();
    }
}

bool FlightPlanner::in_stack(DSStack<City> stack, City find) {
    // While the stack is not empty
    while (!stack.is_empty()) {
        // If the top of the stack is equal to the name to find
        if (stack.top().name == find.name) {
            // Return true
            return true;
        }
        // Pop the stack (get next element)
        stack.pop();
    }
    // If not found, return false
    return false;
}

void FlightPlanner::calculateItineraries() {
    // Create a temporary list of itineraries
    DSLinkedList<Itinerary> tempItineraries;
    // Create a temporary itinerary
    Itinerary tempItinerary;

    // For every path in paths
    for (int i = 0; i < paths.get_size(); i++) {
        for (int j = 0; j < paths[i].get_size(); j++) {
            // Reverse current path
            while (!paths[i][j].is_empty()) {
                tempItinerary.path.push(paths[i][j].top());
                paths[i][j].pop();
            }

            // Calculate itinerary time and cost
            tempItinerary.time = calculate_time(tempItinerary.path);
            tempItinerary.cost = calculate_cost(tempItinerary.path);

            // Push itinerary to the end of list of itineraries
            tempItineraries.push_back(tempItinerary);

            // Clear temporary path stack
            tempItinerary.path.clear();
        }
        // If the list of itineraries is not empty
        if (!tempItineraries.is_empty()) {
            // Push list of itineraries to flights list
            flights.push_back(tempItineraries);
        }
        // Clear list of itineraries
        tempItineraries.clear();
    }
}

int FlightPlanner::calculate_time(DSStack<City> path) {
    // Create a variable to store the time
    int time = 0;
    // Create a counter variable to check if flight is scale
    int count = 0;
    // Create a variable to store the previous airline
    DSString prevAirline;
    // If path is not empty
    if (!path.is_empty()) {
        // Pop first city (source city)
        path.pop();
    }
    // While path is not empty
    while(!path.is_empty()) {
        // Increment count
        count++;

        // Add top element time to total time
        time += strtol(path.top().time.c_str(), NULL, 10);

        // If count is greater or equal than 2 flights
        if (count >= 2) {
            // Add time penalty
            time += 43;
            // If the previous airline is not equal to the current airline
            if (!(path.top().airline == prevAirline)) {
                // Add penalty for changing airlines
                time += 27;
            }
        }

        // Set previous airline
        prevAirline = path.top().airline;

        // Pop path (get next city)
        path.pop();
    }

    return time;
}

int FlightPlanner::calculate_cost(DSStack<City> path) {
    // Create a variable to store the cost
    int cost = 0;
    // Create a counter variable to check if flight is scale
    int count = 0;
    // If path is not empty
    if (!path.is_empty()) {
        // Pop first city (source city)
        path.pop();
    }
    // While path is not empty
    while(!path.is_empty()) {
        // Increment count
        count++;

        // Add top element cost to total cost
        cost += strtol(path.top().cost.c_str(), NULL, 10);

        // If count is greater or equal than 2 flights
        if (count >= 2) {
            // Add cost penalty
            cost += 23;
        }

        // Pop path (get next city)
        path.pop();
    }

    return cost;
}

void FlightPlanner::report(const char* fileName) {
    // Declare output file buffer
    ofstream outputFile;

    // Create or overwrite the output file
    outputFile.open(fileName);

    // Declare an itinerary counter
    int itineraryCount = 0;
    // Declare a variable to store the request type
    DSString type;

    // For every request
    for (int i = 0; i < requests.get_size(); i++) {
        // If request type is "T"
        if (requests[i].type == "T") {
            type = "Time";
        }
        // Otherwise, the request type is "C"
        else {
            type = "Cost";
        }
        // Print flight title
        outputFile << "Flight " << i+1 << ": ";
        outputFile << requests[i].source << ", ";
        outputFile << requests[i].destination;
        outputFile << " (" << type << ")" << endl;

        // Declare a variable to store the index of the found flight itinerary
        int flightIndex = -1;
        bool found = false;
        // Find flight itineraries based on the request
        for (int j = 0; j < flights.get_size() && !found; j++) {
            // If path is not empty
            if (!flights[j][0].path.is_empty()) {
                // If source city is found in list
                if (flights[j][0].path.top().name == requests[i].source) {
                    flightIndex = j;
                    found = true;
                }
            }
        }

        // If current flight itinerary is empty
        if (flightIndex == -1) {
            outputFile << "  No flight plan can be created." << endl;
        }
        // Otherwise, report up to the first 3 best itineraries
        else {
            // If request type is "T"
            if (requests[i].type == "T") {
                // Sort by cost first
                sort_itineraries_cost(flights[flightIndex]);

                // Sort by time
                sort_itineraries_time(flights[flightIndex]);
            }
                // Otherwise, the request type is "C"
            else {
                // Sort by time first
                sort_itineraries_time(flights[flightIndex]);

                // Sort by cost
                sort_itineraries_cost(flights[flightIndex]);
            }

            // For the size of the itineraries of the current flight and no more than 3
            for (int j = 0; j < flights[flightIndex].get_size() && j < 3; j++) {
                // Print itinerary title
                outputFile << "  Itinerary " << j+1 << ":" << endl;

                // If path is not empty
                if (!flights[flightIndex][j].path.is_empty()) {
                    // Declare a variable to store the previous city
                    DSString prevCity = flights[flightIndex][j].path.top().name;
                    // Print the path
                    while (!flights[flightIndex][j].path.is_empty()) {
                        flights[flightIndex][j].path.pop();
                        if (!flights[flightIndex][j].path.is_empty()) {
                            outputFile << "    " << prevCity << " -> " << flights[flightIndex][j].path.top().name;
                            outputFile << " (" << flights[flightIndex][j].path.top().airline << ")" << endl;
                            prevCity = flights[flightIndex][j].path.top().name;
                        }
                    }
                }

                // Print totals
                outputFile << "    Totals for Itinerary "<< j+1 << ":";
                outputFile << "  Time: " << flights[flightIndex][j].time;
                outputFile << " Cost: " << flights[flightIndex][j].cost << ".00" << endl;
            }
        }
    }

    // Close output file
    outputFile.close();
}

void FlightPlanner::sort_itineraries_time(DSLinkedList<Itinerary>& itineraries) {
    // Sort itineraries by time using bubble sort
    bool done = false;
    for (int i = 0; i < itineraries.get_size() - 1 && !done; i++) {
        done = true;
        for (int j = 0; j < itineraries.get_size() - 1 - i; j++) {
            if (itineraries[j].time > itineraries[j + 1].time) {
                swap(itineraries[j], itineraries[j + 1]);
                done = false;
            }
        }
    }
}

void FlightPlanner::sort_itineraries_cost(DSLinkedList<Itinerary>& itineraries) {
    // Sort itineraries by cost using bubble sort
    bool done = false;
    for (int i = 0; i < itineraries.get_size() - 1 && !done; i++) {
        done = true;
        for (int j = 0; j < itineraries.get_size() - 1 - i; j++) {
            if (itineraries[j].cost > itineraries[j + 1].cost) {
                swap(itineraries[j], itineraries[j + 1]);
                done = false;
            }
        }
    }
}
