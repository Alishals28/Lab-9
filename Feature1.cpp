#include <iostream>
#include <queue>
#include <vector>
#include <string>
#include <unordered_map>

using namespace std;

// RideRequest class
class RideRequest
{
public:
    string user;
    string pickupLocation;
    string dropoffLocation;

    RideRequest(string u, string p, string d)
        : user(u), pickupLocation(p), dropoffLocation(d) {}
};

// User Class
class User
{
public:
    string username;
    string password;
    string phoneNumber;

    User(string u, string p, string phone) : username(u), password(p), phoneNumber(phone) {}
};

// Driver Class
class Driver
{
public:
    string name;
    string password;
    string phoneNumber;
    bool available;

    Driver(string n, string p, string phone) : name(n), password(p), phoneNumber(phone), available(true) {}
};

// SmartRide Class
class SmartRide
{
private:
    queue<RideRequest> rideRequests;
    unordered_map<string, User> users;
    unordered_map<string, Driver> drivers;

public:
    void addUser(const string& username, const string& password, const string& phoneNumber)
    {
        users.emplace(username, User(username, password, phoneNumber));
    }

    void addDriver(const string& name, const string& password, const string& phoneNumber)
    {
        drivers.emplace(name, Driver(name, password, phoneNumber));
    }

    void addRideRequest(const string& user, const string& pickup, const string& dropoff)
    {
        rideRequests.emplace(user, pickup, dropoff);
    }

    void processRideRequests()
    {
        while (!rideRequests.empty())
        {
            RideRequest request = rideRequests.front();
            rideRequests.pop();
            cout << "Processing ride request for user: " << request.user
                 << " from " << request.pickupLocation
                 << " to " << request.dropoffLocation << endl;
        }
    }
};


// Main Method
int main()
{
    SmartRide smartRide;
    smartRide.addUser("john_doe", "password123", "123-456-7890");
    smartRide.addDriver("driver1", "driverpass", "098-765-4321");

    smartRide.addRideRequest("john_doe", "LocationA", "LocationB");
    smartRide.processRideRequests();

    return 0;
}
