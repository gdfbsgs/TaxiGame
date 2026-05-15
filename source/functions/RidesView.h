#include <SFML/Graphics.hpp>
#include <string>
#include <sstream>
#include <iomanip>
using namespace std;
// Display active rides on screen
void viewActiveRides(sf::RenderWindow& app, sf::Font& font, RideSystem& rideSystem, TaxiGame& game) {
    const auto& rides = rideSystem.getActiveRides();
    
    if (rides.empty()) {
        return; // No rides to display
    }

    // Display title
    sf::Text ridesTitle;
    ridesTitle.setFont(font);
    ridesTitle.setString("ACTIVE RIDES");
    ridesTitle.setCharacterSize(20);
    ridesTitle.setFillColor(sf::Color::Yellow);
    ridesTitle.setPosition(10, 10);
    app.draw(ridesTitle);

    // Display each ride
    float yPos = 40;
    for (long long i = 0; i < rides.size() and i < 5; i++) { // Show max 5 rides
        const Ride& ride = rides[i];

        // Ride info background
        sf::RectangleShape rideBox(sf::Vector2f(300, 80));
        rideBox.setPosition(10, yPos);
        rideBox.setFillColor(sf::Color(0, 50, 100));
        rideBox.setOutlineThickness(2);
        rideBox.setOutlineColor(sf::Color::Cyan);
        app.draw(rideBox);

        // Format ride info
        std::ostringstream rideInfo;
        rideInfo << ride.getStartLocation() << " -> " << ride.getEndLocation() << "\n"
                 << "Distance: " << ride.getDistance() << "km | "
                 << "Passengers: " << ride.getPassengers() << "\n"
                 << "Fare: $" << std::fixed << std::setprecision(2) << ride.getTotalFare()
                 << "Surge: " << std::setprecision(1) << ride.getUrgencyMultiplier() << "x\n"
                 << "[SPACE+" << i << " to accept]";

        sf::Text rideText;
        rideText.setFont(font);
        rideText.setString(rideInfo.str());
        rideText.setCharacterSize(12);
        rideText.setFillColor(sf::Color::White);
        rideText.setPosition(15, yPos + 5);
        app.draw(rideText);

        yPos += 90;
    }

    // Display ride count
    sf::Text rideCountText;
    rideCountText.setFont(font);
    std::ostringstream countInfo;
    countInfo << "Total Active: " << rides.size() 
              << " | Completed: " << rideSystem.getCompletedRideCount()
              << " | Earnings: $" << rideSystem.getTotalEarnings();
    rideCountText.setString(countInfo.str());
    rideCountText.setCharacterSize(12);
    rideCountText.setFillColor(sf::Color::Green);
    rideCountText.setPosition(10, (float)(app.getSize().y - 30));
    app.draw(rideCountText);
}


