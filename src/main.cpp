#include <iostream>
#include "Car.h"
#include <ixwebsocket/IXNetSystem.h>
#include <ixwebsocket/IXWebSocket.h>
#include <chrono>
#include <thread>

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
std::cout << "  'v' : Display Vehicle State" << std::endl;
std::cout << "  'h' : Show Commands" << std::endl;
std::cout << "  'q' : Quit" << std::endl;
std::cout << "----------------------------" << std::endl;
};   

int main() { 

    // Start the websocket server and listen for incoming connections from the client (e.g., a web application).
    // When a client connects, send the current state of the car (lat, long, heading, speed) to the client in JSON format.
    // Continuously update the car's state based on user input and send updates to the client in real-time via the websocket connection.

    // --------- WebSocket Setup --------- 
    ix::initNetSystem();
    ix::WebSocket webSocket;

    webSocket.setUrl("wss://ws.ifelse.io");

    webSocket.setOnMessageCallback(
        [&webSocket](const ix::WebSocketMessagePtr& msg)
        {
            if (msg->type == ix::WebSocketMessageType::Open)
            {
                std::cout << "Connected\n";
                webSocket.send("hello from ixwebsocket");
            }
            else if (msg->type == ix::WebSocketMessageType::Message)
            {
                std::cout << "Received: " << msg->str << "\n";
            }
            else if (msg->type == ix::WebSocketMessageType::Error)
            {
                std::cout << "Error: " << msg->errorInfo.reason << "\n";
            }
        });

    webSocket.start();

    std::this_thread::sleep_for(std::chrono::seconds(2));
    webSocket.stop();

    ix::uninitNetSystem();

    // --------- End WebSocket Setup ---------

    // Confirm C++ version
    if (__cplusplus == 202302L) std::cout << "C++23";
    else if (__cplusplus == 202002L) std::cout << "C++20";
    else if (__cplusplus == 201703L) std::cout << "C++17";
    else if (__cplusplus == 201402L) std::cout << "C++14";
    else if (__cplusplus == 201103L) std::cout << "C++11";
    else if (__cplusplus == 199711L) std::cout << "C++98";
    else std::cout << "pre-standard C++." << __cplusplus;
    std::cout << "\n";

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
            case 'v': // Display Vehicle State
                myCar.DisplayVehicleState();
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