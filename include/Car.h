#pragma once 

#include <string>
#include <vector>

namespace Entities {

class Car {
public: 
    
    // Constructor
    Car(const std::string& name, int health, int armour);

    // Public Member Functions
    void StartEngine();
    void Accelerate(int amount); // Renamed to match C++ convention (PascalCase for public methods)
    void Brake();
    void DisplaySpeed() const; // Renamed to match C++ convention


    // Destructor
     ~Car();

private: 
    std::string name_;
    int health_;
    int armour_;
    bool engineStart_;
    int speed_;
};

}