/**
 * Fall 2021 PA 04 - Flight Planner Template Repo.
 * Based on PA 02 Template repo
 */

#include <iostream>
#include <fstream>

/**
 * catch_setup.h and catch_setup.cpp contain the #define directive for
 * the CATCH2 framework.  You can see in main below how I'm calling the
 * runCatchTests() function which is declared in this header.
 *
 * On average, this should reduce the build time for your project on your local
 * machine.
 */
#include "catch_setup.h"

#include "FlightPlanner.h"

using namespace std;

void run(char*, char*, char*);

int main(int argc, char** argv) {
    if(argc == 1) {
        runCatchTests();
    }
    else {
        run(argv[1], argv[2], argv[3]);
    }
    return 0;
}

void run(char* arg1, char* arg2, char* arg3) {
    // Create a new flight planner object
    FlightPlanner planner;

    /** READ DATA FILE **/

    planner.readData(arg1);

    /** READ REQUESTED CALCULATIONS **/

    planner.readRequested(arg2);

    /** CALCULATE FLIGHTS PATHS **/

    planner.calculatePaths();

    /** CALCULATE ITINERARIES **/

    planner.calculateItineraries();

    /** GENERATE OUTPUT FILE **/

    planner.report(arg3);
}
