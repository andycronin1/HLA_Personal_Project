#include <iostream>
#include "Car.h"


// TODO: add functionality to compute lat, long, heading, speed, timestamp'. 
// TODO: Add a websocket library 
// TODO: Add a JSON library to serialize/deserialize data for websocket communication.


// Function to display available commands
void displayCommands() {
std::cout << "\n--- Car Control Commands ---" << std::endl;
std::cout << "  's' : Start Engine" << std::endl;
std::cout << "  'o' : Stop Engine" << std::endl;
std::cout << "  'w' : Accelerate (by 10 mph)" << std::endl;
std::cout << "  'b' : Brake (stop immediately)" << std::endl;
std::cout << "  'd' : Display Current Speed" << std::endl;
std::cout << "  'h' : Show Commands" << std::endl;
std::cout << "  'q' : Quit" << std::endl;
std::cout << "----------------------------" << std::endl;
};   

int main() { 

    // Confirm C++ version
    long cpp_version = __cplusplus;

    std::cout << "C++ Standard being used: " << cpp_version << std::endl;

    std::cout << "--- Starting Car Simulation ---" << std::endl;

    // Create an instance of the Car class
    Entities::Car myCar("Deloitte Mobile", 100, 50);

    char command; // To store user input
    displayCommands(); // Show commands initially

    // Main input loop
    while (true) {
        std::cout << "\nEnter command (h for help): ";
        std::cin >> command; // Read a single character from the keyboard

        switch (command) {
            case 's': // Start Engine
                myCar.StartEngine();
                break;
            case 'w': // Accelerate
                myCar.Accelerate(10.0, 10.0); // Accelerate by 10 mps over 10 seconds
                break;
            case 'b': // Brake
                myCar.Brake();
                break;
            case 'd': // Display Speed
                myCar.DisplaySpeed();
                break;
            case 'h': // Show Commands
                displayCommands();
                break;
            case 'q': // Quit
                std::cout << "Exiting car simulation. Goodbye!" << std::endl;
                return 0; // Exit the program
            default:
                std::cout << "Invalid command. Press 'h' for help." << std::endl;
                break;
        }
    }

    // The 'myCar' object's destructor will be called automatically when main exits.
    return 0;

} 