#include <iostream>
#include <string>
#include <vector>
#include "Car.h"

namespace Entities {


Car::Car(const std::string& name, int health, int armour) : name_(name), health_(health), armour_(armour), engineStart_(false) 
{
    std::cout << "Car created: " << name_ << " with health: " << health_ << " and armour: " << armour_ << std::endl;
}

Car::~Car() {
    if (engineStart_) {
        std::cout << "Stopping engine of " << name_ << " before destruction." << std::endl;
        engineStart_ = false;
        std::cout << name_ << "'s engine stopped." << std::endl;
        std::cout << "Car destroyed: " << name_ << std::endl;
    }
}

// Public Member Function Implementation

void Car::StartEngine() {
    if (engineStart_) {
        std::cout << name_ << "'s engine is already running." << std::endl;
    } else {
        engineStart_ = true;
    }
    std::cout << name_ << "'s engine started." << std::endl;
}
};
