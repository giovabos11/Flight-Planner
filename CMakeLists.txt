cmake_minimum_required(VERSION 3.15)
project(22s_flight_planner)

set(CMAKE_CXX_STANDARD 14)

configure_file(data/sample01-flight-data.txt data/sample01-flight-data.txt COPYONLY)
configure_file(data/sample01-req-flights.txt data/sample01-req-flights.txt COPYONLY)

add_executable(22s_flight_planner main.cpp catch_setup.cpp DSString.cpp DSString.h DSString_test.cpp DSLinkedList.h DSLinkedList_test.cpp DSNode.h City.h DSStack.h DSStack_test.cpp DSAdjacencyList.cpp DSAdjacencyList.h FlightPlanner.cpp FlightPlanner.h Flight.h)
