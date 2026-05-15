#include <vector>
#include <random>
#include <ctime>
#include <SFML/Graphics.hpp>
#include "RideClass.h"
class RideSystem {
private:
    vector<Ride> activeRides;
    vector<Ride> completedRides;
    
    // Ride generation parameters
    long long rideCounter;
    float rideGenerationChance;  // 0.0 to 1.0 - chance to generate ride each frame
    time_t lastRideGeneratedTime;
    mt19937 rng;
    
    // Location names for variety
    const vector<string> locations = {
        "Downtown", "Airport", "Train Station", "Mall", "Hospital",
        "University", "Tech Park", "Harbor", "Central Plaza", "Business District",
        "Suburbs", "Industrial Zone", "Entertainment District", "Residential Area", "Casino"
    };

public:
    RideSystem() : rideCounter(0), rideGenerationChance(0.15f), lastRideGeneratedTime(0) {
        rng.seed(static_cast<unsigned>(time(nullptr)));
    }

    // Generate new random ride
    void generateRide() {
        time_t now = time(nullptr);
        
        // Generate ride every ~5-10 seconds on average with rideGenerationChance
        if (now - lastRideGeneratedTime < 3){
            return;
        } // Cooldown between generations
        
        uniform_real_distribution<float> chanceDist(0.0f, 1.0f);
        if (chanceDist(rng) > rideGenerationChance){
            return;
        }

        uniform_int_distribution<> locDist(0, locations.size() - 1);
        uniform_int_distribution<> distDist(2, 50);    // 2-50 km
        uniform_int_distribution<> passDist(1, 4);     // 1-4 passengers
        uniform_real_distribution<> fareDist(1.5, 3.0); // Base fare variation
        uniform_real_distribution<> multDist(0.9, 2.0); // Urgency multiplier

        string start = locations[locDist(rng)];
        string end = locations[locDist(rng)];
        
        // Ensure start and end are different
        while (end == start) {
            end = locations[locDist(rng)];
        }

        long long distance = distDist(rng);
        double baseFare = fareDist(rng);
        long long passengers = passDist(rng);
        double multiplier = multDist(rng);

        Ride newRide(start, end, distance, baseFare, passengers, multiplier);
        activeRides.push_back(newRide);
        lastRideGeneratedTime = now;
        rideCounter++;
    }

    // Accept ride (make it active/assign to driver)
    bool acceptRide(size_t rideIndex) {
        if (rideIndex >= activeRides.size()) return false;
        activeRides[rideIndex].setActive(true);
        return true;
    }

    // Complete ride and earn money
    long long completeRide(size_t rideIndex) {
        if (rideIndex >= activeRides.size()) return 0;
        
        Ride completedRide = activeRides[rideIndex];
        long long earnings = completedRide.getEarnings();
        
        completedRide.setActive(false);
        completedRides.push_back(completedRide);
        activeRides.erase(activeRides.begin() + rideIndex);
        
        return earnings;
    }

    // Decline/remove ride from list
    void declineRide(size_t rideIndex) {
        if (rideIndex < activeRides.size()) {
            activeRides.erase(activeRides.begin() + rideIndex);
        }
    }

    // Getters
    vector<Ride>& getActiveRides() { return activeRides; }
    vector<Ride>& getCompletedRides() { return completedRides; }
    size_t getActiveRideCount() const { return activeRides.size(); }
    size_t getCompletedRideCount() const { return completedRides.size(); }
    long long getTotalRidesGenerated() const { return rideCounter; }
    
    // Calculate total earnings from completed rides
    long long getTotalEarnings() const {
        long long total = 0;
        for (const auto& ride : completedRides) {
            total += ride.getEarnings();
        }
        return total;
    }

    // Setters
    void setRideGenerationChance(float chance) { 
        if (chance >= 0.0f && chance <= 1.0f) {
            rideGenerationChance = chance;
        }
    }

    // Clear all rides (for reset)
    void clearRides() {
        activeRides.clear();
        completedRides.clear();
        rideCounter = 0;
    }
};

