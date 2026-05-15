#ifndef RIDE_CLASS_H
#define RIDE_CLASS_H

#include <string>
#include <ctime>

class Ride {
private:
    std::string startLocation;
    std::string endLocation;
    long long distance;           // Distance in km
    double baseFare;             // Base fare rate from car tier
    double totalFare;            // Calculated total fare
    long long passengersCount;   // Number of passengers
    bool isActive;               // Is ride currently running
    time_t createdTime;          // When ride was created
    time_t completedTime;        // When ride was completed
    double urgencyMultiplier;    // Rush hour or surge pricing (1.0 to 2.5)

public:
    // Constructor
    Ride(std::string start, std::string end, long long dist, double fare, 
         long long passengers, double multiplier = 1.0) 
        : startLocation(start), endLocation(end), distance(dist), 
          baseFare(fare), passengersCount(passengers), urgencyMultiplier(multiplier),
          isActive(false), completedTime(0) {
        createdTime = time(nullptr);
        calculateFare();
    }

    // Calculate fare: baseFare + (distance * baseFare * 1.76) * urgencyMultiplier
    void calculateFare() {
        totalFare = baseFare + (distance * baseFare * 1.76) * urgencyMultiplier;
    }

    // Getters
    std::string getStartLocation() const { return startLocation; }
    std::string getEndLocation() const { return endLocation; }
    long long getDistance() const { return distance; }
    double getBaseFare() const { return baseFare; }
    double getTotalFare() const { return totalFare; }
    long long getPassengers() const { return passengersCount; }
    bool getIsActive() const { return isActive; }
    time_t getCreatedTime() const { return createdTime; }
    double getUrgencyMultiplier() const { return urgencyMultiplier; }
    long long getEarnings() const { return (long long)(totalFare + passengersCount * 5); } // Base + per-passenger bonus

    // Setters
    void setActive(bool active) { 
        isActive = active; 
        if (!active) completedTime = time(nullptr);
    }
    void setUrgencyMultiplier(double mult) { 
        urgencyMultiplier = mult; 
        calculateFare();
    }
    void setDistance(long long dist) { 
        distance = dist; 
        calculateFare();
    }
};

#endif


