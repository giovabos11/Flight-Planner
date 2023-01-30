#include "catch.hpp"

#include "DSLinkedList.h"

#include "DSString.h"

TEST_CASE( "DSLinkedList", "[DSLinkedList]" ) {
    // Create new linked list object
    DSLinkedList<DSString> list;

    SECTION("Copy constructor") {
        // Create old list
        DSLinkedList<DSString> old_list;
        // Populate new list
        old_list.push_back("lazy");
        old_list.push_back("dog");
        old_list.push_back("jumps");
        old_list.push_back("over");
        old_list.push_back("brown");
        old_list.push_back("fox");
        // Create new list
        DSLinkedList<DSString> new_list(old_list);
        REQUIRE(new_list.get_front() == "lazy");
        REQUIRE(new_list.get_back() == "fox");
        REQUIRE(new_list.get_size() == 6);
    }

    SECTION("Push front") {
        //REQUIRE(list.get_front() == NULL);
        // Push element in front of list
        list.push_front("lazy");
        REQUIRE(list.get_front() == "lazy");
        // Push element in front of list
        list.push_front("dog");
        REQUIRE(list.get_front() == "dog");
        // Push element in front of list
        list.push_front("jumps");
        REQUIRE(list.get_front() == "jumps");
        // Push element in front of list
        list.push_front("over");
        REQUIRE(list.get_front() == "over");
        // Push element in front of list
        list.push_front("brown");
        REQUIRE(list.get_front() == "brown");
    }

    SECTION("Push back") {
        //REQUIRE(list.get_back() == NULL);
        // Push element in front of list
        list.push_back("lazy");
        REQUIRE(list.get_back() == "lazy");
        // Push element in front of list
        list.push_back("dog");
        REQUIRE(list.get_back() == "dog");
        // Push element in front of list
        list.push_back("jumps");
        REQUIRE(list.get_back() == "jumps");
        // Push element in front of list
        list.push_back("over");
        REQUIRE(list.get_back() == "over");
        // Push element in front of list
        list.push_back("brown");
        REQUIRE(list.get_back() == "brown");
    }

    list.push_back("lazy");
    list.push_back("dog");
    list.push_back("jumps");
    list.push_back("over");
    list.push_back("brown");
    list.push_back("fox");

    SECTION("Pop front") {
        REQUIRE(list.get_front() == "lazy");
        // Pop front element from list
        list.pop_front();
        REQUIRE(list.get_front() == "dog");
        // Pop front element from list
        list.pop_front();
        REQUIRE(list.get_front() == "jumps");
        // Pop front element from list
        list.pop_front();
        REQUIRE(list.get_front() == "over");
        // Pop front element from list
        list.pop_front();
        REQUIRE(list.get_front() == "brown");
        // Pop front element from list
        list.pop_front();
        REQUIRE(list.get_front() == "fox");
        // Pop front element from list
        list.pop_front();
        REQUIRE(list.get_size() == 0);
        REQUIRE(list.is_empty() == true);
        REQUIRE(list.pop_front() == false);
        REQUIRE(list.pop_front() == false);
    }

    SECTION("Pop back") {
        REQUIRE(list.get_back() == "fox");
        // Pop back element from list
        list.pop_back();
        REQUIRE(list.get_back() == "brown");
        // Pop back element from list
        list.pop_back();
        REQUIRE(list.get_back() == "over");
        // Pop back element from list
        list.pop_back();
        REQUIRE(list.get_back() == "jumps");
        // Pop back element from list
        list.pop_back();
        REQUIRE(list.get_back() == "dog");
        // Pop back element from list
        list.pop_back();
        REQUIRE(list.get_back() == "lazy");
        // Pop back element from list
        list.pop_back();
        REQUIRE(list.get_size() == 0);
        REQUIRE(list.is_empty() == true);
        REQUIRE(list.pop_back() == false);
        REQUIRE(list.pop_back() == false);
    }

    SECTION("At and subscript operator") {
        REQUIRE(list.at(0) == "lazy");
        REQUIRE(list[0] == "lazy");
        REQUIRE(list.at(1) == "dog");
        REQUIRE(list[1] == "dog");
        REQUIRE(list.at(2) == "jumps");
        REQUIRE(list[2] == "jumps");
        REQUIRE(list.at(3) == "over");
        REQUIRE(list[3] == "over");
        REQUIRE(list.at(4) == "brown");
        REQUIRE(list[4] == "brown");
        REQUIRE(list.at(5) == "fox");
        REQUIRE(list[5] == "fox");
    }

    SECTION("Is empty") {
        // Create a new list
        DSLinkedList<DSString> test_list;
        REQUIRE(test_list.is_empty() == true);
        // Add a new element to the list
        test_list.push_back("lazy");
        REQUIRE(test_list.is_empty() == false);
        // Delete the only element in the list
        test_list.pop_back();
        REQUIRE(test_list.is_empty() == true);
        REQUIRE(list.is_empty() == false);
    }

    SECTION("Clear") {
        REQUIRE(list.is_empty() == false);
        REQUIRE(list.get_size() > 0);
        // Clear list
        list.clear();
        REQUIRE(list.get_size() == 0);
        REQUIRE(list.is_empty() == true);
    }

    SECTION("Iterators") {
        // Reset list iterator
        list.reset_itr();
        REQUIRE(list.get_curr() == "lazy");
        REQUIRE(list.has_next() == true);
        REQUIRE(list.get_next() == "lazy");
        REQUIRE(list.get_curr() == "dog");
        REQUIRE(list.has_next() == true);
        REQUIRE(list.get_next() == "dog");
        REQUIRE(list.get_curr() == "jumps");
        REQUIRE(list.has_next() == true);
        REQUIRE(list.get_next() == "jumps");
        REQUIRE(list.get_curr() == "over");
        REQUIRE(list.has_next() == true);
        REQUIRE(list.get_next() == "over");
        REQUIRE(list.get_curr() == "brown");
        REQUIRE(list.has_next() == true);
        REQUIRE(list.get_next() == "brown");
        REQUIRE(list.get_curr() == "fox");
        REQUIRE(list.has_next() == false);
        // Reset list iterator
        list.reset_itr();
        REQUIRE(list.get_curr() == "lazy");
        REQUIRE(list.has_next() == true);
        REQUIRE(list.get_next() == "lazy");
        REQUIRE(list.get_curr() == "dog");
        REQUIRE(list.has_next() == true);
    }

    SECTION("Double list") {
        DSLinkedList<DSLinkedList<int>> temp;
        DSLinkedList<int> a;
        a.push_back(5);
        a.push_back(4);
        DSLinkedList<int> b(a);
        DSLinkedList<int> c;
        c = a;
        a[0] = 20;
        temp.push_back(a);
        CHECK(temp[0][0] == 20);
        a.push_back(50);
        temp.push_back(a);
    }
}