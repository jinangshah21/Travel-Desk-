#include <iostream>
#include <cassert>
#include <bits/stdc++.h>
#include "Travel_Desk_RBT.cpp"  // Include your actual class header file here
//#include "StudentSolution.cpp"// Include your actual class header file here
// #include "interface_template.cpp"
using namespace std::literals::chrono_literals;
using namespace std;
int testCasesPassed = 0;

bool customAssert(bool condition, const char* message) {
    if (!condition) {
        std::cout << "Assertion failed: " << message << std::endl;
        return false;
    }
    else return true;
}

void test_show_trips_by_time_destination() {
    TravelDesk travelDesk;
    travelDesk.addTrip("ABC123", 4, "LocationA", "LocationB", 1000);
    travelDesk.addTrip("XYZ789", 3, "LocationX", "LocationY", 1500);
    travelDesk.addTrip("ABC123", 4, "LocationA", "LocationB", 900);
    travelDesk.addTrip("ABC123", 4, "LocationA", "LocationX", 950);
    travelDesk.addTrip("ABC123", 4, "LocationA", "LocationB", 1400);
    travelDesk.addTrip("ABC123", 4, "LocationZ", "LocationB", 900);
    travelDesk.addTrip("ABC123", 4, "LocationY", "LocationX", 1000);

    std::vector<Trip*> trips = travelDesk.showTripsbydestination("LocationA", "LocationB", 800, 1200);

    bool flag1=customAssert(trips.size() == 2 , "Number of trips is not as expected.");
    if(flag1)testCasesPassed++;

    
}
void test_show_trips_by_time() {
    TravelDesk travelDesk;
    travelDesk.addTrip("ABC123", 4, "LocationA", "LocationB", 1000);
    travelDesk.addTrip("XYZ789", 3, "LocationX", "LocationY", 1500);
    travelDesk.addTrip("ABC123", 4, "LocationA", "LocationB", 900);
    travelDesk.addTrip("ABC123", 4, "LocationA", "LocationX", 950);
    travelDesk.addTrip("ABC123", 4, "LocationA", "LocationB", 1400);
    travelDesk.addTrip("ABC123", 4, "LocationZ", "LocationB", 900);
    travelDesk.addTrip("ABC123", 4, "LocationY", "LocationX", 1000);

    std::vector<Trip*> trips = travelDesk.showTrips("LocationA", 800, 1200);

    // assert(trips.size() == 4 && "Number of trips is not as expected.");
    bool flag1=customAssert(trips.size() == 3 , "Number of trips is not as expected.");
    if(flag1)testCasesPassed++;

}

void countNodes(node* Node, int& count, string pickup, string drop) {
    if (Node == nullptr) {
        return;
    }

    if (Node->getTripNodePtr()->getPickUpLocation() == pickup && Node->getTripNodePtr()->getDropLocation() == drop)
        count++;

    
    countNodes(Node->getLeftPtr(), count, pickup, drop);
    countNodes(Node->getRightPtr(), count, pickup, drop);
}
void test_correct_pickup_drop() {
    
    TravelDesk travelDesk;
    for (int i = 0; i < 15; ++i) {
        std::string vehicleNumber = "A" + std::to_string(i);
        travelDesk.addTrip(vehicleNumber, 4, "LocationA", "LocationX", 1000 + i * 100);
    }
    for (int i = 0; i < 10; ++i) {
        std::string vehicleNumber = "X" + std::to_string(i);
        travelDesk.addTrip(vehicleNumber, 3, "LocationA", "LocationY", 1500 + i * 100);
    }
    int nodeCount = 0;
    node* rootLocationA = travelDesk.getLocation("LocationA")->getServicePtr("LocationX")->getRBT()->getRoot();

    
    countNodes(rootLocationA, nodeCount, "LocationA", "LocationX");

   
    bool flag1=customAssert(nodeCount == 15, "Number of nodes with specified pickup and drop locations is not as expected.");
    if(flag1)testCasesPassed++;
    
}


void test_book_trip() {
    TravelDesk travelDesk;
    travelDesk.addTrip("XYZ", 2, "LocationX", "LocationY", 1500);

    Trip* firstBooking = travelDesk.bookTrip("LocationX", "LocationY", "XYZ", 1500);
    bool flag1=customAssert(firstBooking != nullptr,"wrong booking");
    bool flag2=customAssert(firstBooking->getBookedSeats() == 1,"wrong booking");


    Trip *Booking = travelDesk.bookTrip("LocationX", "LocationZ", "XYZ", 1500);

    bool flag3=customAssert(Booking ==nullptr ,"Trip is not there but booking function is not returning nullptr ");
    if(flag1 && flag2 && flag3)testCasesPassed++;
}

void test_max_capacity(){

    TravelDesk travelDesk;
    travelDesk.addTrip("ABC123", 4, "LocationA", "LocationB", 1000);
    travelDesk.addTrip("XYZ789", 3, "LocationX", "LocationY", 1500);
    travelDesk.addTrip("ABC123", 4, "LocationA", "LocationB", 900);
    travelDesk.addTrip("ABC123", 4, "LocationA", "LocationX", 950);
    travelDesk.addTrip("ABC123", 4, "LocationA", "LocationB", 1400);
    travelDesk.addTrip("ABC123", 4, "LocationZ", "LocationB", 900);
    travelDesk.addTrip("ABC123", 4, "LocationY", "LocationX", 1000);
    
    Trip *Booking1 = travelDesk.bookTrip("LocationX", "LocationY", "XYZ789", 1500);
    Trip *Booking2 = travelDesk.bookTrip("LocationX", "LocationY", "XYZ789", 1500);
    Trip *Booking3 = travelDesk.bookTrip("LocationX", "LocationY", "XYZ789", 1500);
    Trip *Booking4 = travelDesk.bookTrip("LocationX", "LocationY", "XYZ789", 1500);

    bool flag1=customAssert(Booking4 == nullptr, "Maximum Capacity not maintained Properly.");
    if(flag1)testCasesPassed++;
}



int main() {

	auto start = std::chrono::high_resolution_clock::now();
   
    test_show_trips_by_time_destination();
    test_show_trips_by_time();
    test_correct_pickup_drop();
    test_book_trip();
    test_max_capacity();
    auto end = std::chrono::high_resolution_clock::now();
	std::chrono::duration<float> duration = end-start;
	std::cout<<duration.count()*1000<<"ms"<<'\n';

    std::cout << "Number of test cases passed: " << testCasesPassed << "/" << 5 << std::endl;

    return 0;
}