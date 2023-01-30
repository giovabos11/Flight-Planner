#include "catch.hpp"

#include "DSStack.h"

TEST_CASE( "DSStack", "[DSStack]" ) {
    // Create a new stack
    DSStack<int> stack;

    SECTION("Push and top") {
        // Push a new element to the stack
        stack.push(0);
        REQUIRE(stack.top() == 0);
        // Push a new element to the stack
        stack.push(5);
        REQUIRE(stack.top() == 5);
        // Push a new element to the stack
        stack.push(10);
        REQUIRE(stack.top() == 10);
        // Push a new element to the stack
        stack.push(15);
        REQUIRE(stack.top() == 15);
        // Push a new element to the stack
        stack.push(20);
        REQUIRE(stack.top() == 20);
        // Push a new element to the stack
        stack.push(25);
        REQUIRE(stack.top() == 25);
    }

    SECTION("Is empty") {
        REQUIRE(stack.is_empty() == true);
        // Push a new element to the stack
        stack.push(0);
        REQUIRE(stack.is_empty() == false);
        // Push a new element to the stack
        stack.push(5);
        REQUIRE(stack.is_empty() == false);
    }

    // Push several elements to the stack
    stack.push(0);
    stack.push(5);
    stack.push(10);
    stack.push(15);
    stack.push(20);
    stack.push(25);

    SECTION("Pop") {
        REQUIRE(stack.top() == 25);
        REQUIRE(stack.pop() == true);
        REQUIRE(stack.top() == 20);
        REQUIRE(stack.pop() == true);
        REQUIRE(stack.top() == 15);
        REQUIRE(stack.pop() == true);
        REQUIRE(stack.top() == 10);
        REQUIRE(stack.pop() == true);
        REQUIRE(stack.top() == 5);
        REQUIRE(stack.pop() == true);
        REQUIRE(stack.top() == 0);
        REQUIRE(stack.pop() == true);
        REQUIRE(stack.is_empty() == true);
        REQUIRE(stack.pop() == false);
    }

    SECTION("Clear") {
        REQUIRE(stack.is_empty() == false);
        // Clear the stack
        stack.clear();
        REQUIRE(stack.is_empty() == true);
    }
}