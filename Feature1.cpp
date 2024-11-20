#include <iostream>
#include <queue>
#include <vector>
#include <string>
#include <unordered_map>

class RideRequest
{
public:
    std::string user;
    std::string pickupLocation;
    std::string dropoffLocation;

    RideRequest(std::string u, std::string p, std::string d)
        : user(u), pickupLocation(p), dropoffLocation(d) {}
};

class User
{
public:
    std::string username;
    std::string password;

    User(std::string u, std::string p) : username(u), password(p) {}
};

class Driver
{
public:
    std::string name;
    std::string password;
    bool available;

    Driver(std::string n, std::string p) : name(n), password(p), available(true) {}
};

class SmartRide
{
private:
    std::queue<RideRequest> rideRequests;
    std::unordered_map<std::string, User> users;
    std::unordered_map<std::string, Driver> drivers;

public:
    void registerUser(const std::string &username, const std::string &password)
    {
        users[username] = User(username, password);
        std::cout << "User " << username << " registered successfully." << std::endl;
    }

    void registerDriver(const std::string &name, const std::string &password)
    {
        drivers[name] = Driver(name, password);
        std::cout << "Driver " << name << " registered successfully." << std::endl;
    }

    bool loginUser(const std::string &username, const std::string &password)
    {
        if (users.find(username) != users.end() && users[username].password == password)
        {
            std::cout << "User " << username << " logged in successfully." << std::endl;
            return true;
        }
        std::cout << "Invalid username or password for user." << std::endl;
        return false;
    }

    bool loginDriver(const std::string &name, const std::string &password)
    {
        if (drivers.find(name) != drivers.end() && drivers[name].password == password)
        {
            std::cout << "Driver " << name << " logged in successfully." << std::endl;
            return true;
        }
        std::cout << "Invalid name or password for driver." << std::endl;
        return false;
    }

    void requestRide(const std::string &user, const std::string &pickup, const std::string &dropoff)
    {
        rideRequests.push(RideRequest(user, pickup, dropoff));
    }

    void assignRides()
    {
        while (!rideRequests.empty())
        {
            RideRequest request = rideRequests.front();
            rideRequests.pop();

            for (auto &driverPair : drivers)
            {
                Driver &driver = driverPair.second;
                if (driver.available)
                {
                    driver.available = false;
                    std::cout << "Driver " << driver.name << " is assigned to " << request.user << std::endl;
                    break;
                }
            }
        }
    }

    void completeRide(const std::string &driverName)
    {
        if (drivers.find(driverName) != drivers.end())
        {
            drivers[driverName].available = true;
            std::cout << "Driver " << driverName << " has completed the ride and is now available." << std::endl;
        }
    }
};

int main()
{
    SmartRide smartRide;

    // Register users and drivers
    smartRide.registerUser("User1", "password1");
    smartRide.registerUser("User2", "password2");
    smartRide.registerDriver("Rimsha", "password3");
    smartRide.registerDriver("Nasir", "password4");

    // Log in users and drivers
    smartRide.loginUser("User1", "password1");
    smartRide.loginUser("User2", "password2");
    smartRide.loginDriver("Rimsha", "password3");
    smartRide.loginDriver("Nasir", "password4");

    // Users request rides
    smartRide.requestRide("User1", "LocationA", "LocationB");
    smartRide.requestRide("User2", "LocationC", "LocationD");

    // Assign rides to available drivers
    smartRide.assignRides();

    // Complete rides
    smartRide.completeRide("Rimsha");
    smartRide.assignRides();

    return 0;
}
