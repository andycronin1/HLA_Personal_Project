#pragma once 

#include <memory>
#include <string>
#include <vector>
#include <RTI/RTIambassadorFactory.h>
#include <RTI/NullFederateAmbassador.h>
#include <RTI/RTIambassador.h>
#include <RTI/Exception.h>

namespace Entities {

// Nested struct for Location Data
struct VehicleState {
    double latitude;
    double longitude;
    double heading; // Direction in degrees (0-360)
    double speed_mps;
    // Default constructor
    VehicleState() : latitude(53.3498), longitude(-6.2603), heading(0.0), speed_mps(0.0) {}
    VehicleState(double lat, double lon, double head, double speed): latitude(lat), longitude(lon), heading(head), speed_mps(speed) {}
};

class Car : public rti1516e::NullFederateAmbassador {
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

    // HLA setup 
    void initializeRTI();
    // void createOrJoinFederation();
    // void publishAndSubscribe();
    // void reserveLocalObjectInstanceName(const std::wstring& objectInstanceName);
    void RunSetup(); // Function to run all setup steps

    std::unique_ptr<rti1516e::RTIambassador> rtiAmb_;
};

}