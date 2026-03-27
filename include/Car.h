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


    // Destructor
     ~Car();

private: 
    std::string name_;
    int health_;
    int armour_;
    bool engineStart_;
};

}