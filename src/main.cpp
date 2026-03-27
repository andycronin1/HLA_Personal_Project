#include <iostream>
#include "Car.h"

int main() { 

    std::cout << "Hello, World!" << std::endl;

    std::cout << "This is a C++14 project." << std::endl;

    Entities::Car myCar("Deloitte Car", 100, 50);
    myCar.StartEngine();

    return 0;

} 