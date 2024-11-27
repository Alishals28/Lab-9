#include <iostream>
#include <string>
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
        cout << "Ride added: ID=" << id << ", Pickup=" << pickup << ", Destination=" << destination << endl;
    }

    // Display ride history from oldest to newest
    void displayForward() {
        if (!head) {
            cout << "No ride history available." << endl;
            return;
        }
        Ride* current = head;
        cout << "Ride History (Oldest to Newest):" << endl;
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
        cout << "Ride History (Newest to Oldest):" << endl;
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

int main() {
    RideHistory userHistory;

    // Adding rides to the history
    userHistory.addRide(1, "NUST", "Airport");
    userHistory.addRide(2, "Centauras Mall", "University");
    userHistory.addRide(3, "F7 park", "PIMS");

    // Displaying ride history
    userHistory.displayForward();
    cout << endl;
    userHistory.displayBackward();

    return 0;
}
