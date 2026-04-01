#pragma once 

#include <string>
#include <vector>

namespace Entities {

// Nested struct for Location Data
struct VehicleState {
    double latitude;
    double longitude;
    double heading; // Direction in degrees (0-360)
    double speed_mps;
    // Default constructor
    VehicleState() : latitude(0.0), longitude(0.0), heading(0.0), speed_mps(0.0) {}
    VehicleState(double lat, double lon, double head, double speed): latitude(lat), longitude(lon), heading(head), speed_mps(speed) {}
};

class Car {
public: 

    // Constructor
    Car(const std::string& name, int health, int armour);

    // Public Member Functions
    void StartEngine();
    void Accelerate(double amount, double time); 
    void Brake();
    void DisplaySpeed() const; // Renamed to match C++ convention
    void DisplayVehicleState() const; // function to display all vehicle state information

    // Update Position and Heading 
    void UpdatePosition(double latitude, double longitude);
    void UpdateHeading(double heading);

    // Getter Functions
    VehicleState getVehicleState() const;

    // Destructor
     ~Car();

private: 
    std::string name_;
    int health_;
    int armour_;
    bool engineStart_;
    int speed_;
    double time;

    VehicleState VehicleState_;
};

}