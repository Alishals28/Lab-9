#include <iostream>
#include <string>
#include <unordered_map>
using namespace std;

// Node structure for storing ride details
struct Ride {
    int rideID;
    string pickup;
    string destination;
    Ride* next;
    Ride* prev;

    Ride(int id, string p, string d) : rideID(id), pickup(p), destination(d), next(nullptr), prev(nullptr) {}
};

// Class to manage ride history using a doubly linked list
class RideHistory {
private:
    Ride* head;
    Ride* tail;

public:
    RideHistory() : head(nullptr), tail(nullptr) {}

    // Add a new ride to the history
    void addRide(int id, string pickup, string destination) {
        Ride* newRide = new Ride(id, pickup, destination);
        if (!head) {
            head = tail = newRide;
        } else {
            tail->next = newRide;
            newRide->prev = tail;
            tail = newRide;
        }
    }

    // Display ride history from oldest to newest
    void displayForward() {
        if (!head) {
            cout << "No ride history available." << endl;
            return;
        }
        Ride* current = head;
        while (current) {
            cout << "Ride ID: " << current->rideID << ", Pickup: " << current->pickup
                 << ", Destination: " << current->destination << endl;
            current = current->next;
        }
    }

    // Display ride history from newest to oldest
    void displayBackward() {
        if (!tail) {
            cout << "No ride history available." << endl;
            return;
        }
        Ride* current = tail;
        while (current) {
            cout << "Ride ID: " << current->rideID << ", Pickup: " << current->pickup
                 << ", Destination: " << current->destination << endl;
            current = current->prev;
        }
    }

    // Destructor to free memory
    ~RideHistory() {
        while (head) {
            Ride* temp = head;
            head = head->next;
            delete temp;
        }
    }
};

// Main program to manage users and their ride histories
int main() {
    // User ride histories managed in an unordered_map
    unordered_map<string, RideHistory*> userHistories;

    // Hardcoded data: Add users and their rides
    userHistories["Alisha"] = new RideHistory();
    userHistories["Asma"] = new RideHistory();
    userHistories["Rimsha"] = new RideHistory();

    // Adding rides for Alisha
    userHistories["Alisha"]->addRide(1, "Home", "Airport");
    userHistories["Alisha"]->addRide(2, "Airport", "Office");

    // Adding rides for Asma
    userHistories["Asma"]->addRide(3, "Park", "Hospital");
    userHistories["Asma"]->addRide(4, "University", "Mall");

    // Adding rides for Rimsha
    userHistories["Rimsha"]->addRide(5, "University", "Library");
    userHistories["Rimsha"]->addRide(6, "Library", "Cafe");

    // Displaying user ride histories
    for (const auto& user : userHistories) {
        cout << "Ride History for " << user.first << ":" << endl;
        user.second->displayForward();
        cout << endl;
    }

    // Free allocated memory for RideHistory objects
    for (const auto& user : userHistories) {
        delete user.second;
    }

    return 0;
}
