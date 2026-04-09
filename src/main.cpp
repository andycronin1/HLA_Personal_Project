#include <iostream>
#include "Car.h"
#include <ixwebsocket/IXNetSystem.h>
#include <ixwebsocket/IXWebSocketServer.h>
#include <thread>

// TODO: add functionality to compute lat, long, heading, speed, timestamp'. 
// TODO: Add a JSON library to serialize/deserialize data for websocket communication.

// Function to display available commands
void displayCommands() {
std::cout << "\n--- Car Control Commands ---" << std::endl;
std::cout << "  's' : Start Engine" << std::endl;
std::cout << "  'o' : Stop Engine" << std::endl;
std::cout << "  'w' : Move Forward by 1" << std::endl;
std::cout << "  'a' : Accelerate (increase speed)" << std::endl;
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

    // --------- WebServer Setup --------- 

    ix::initNetSystem();

    int port = 8080;
    std::string host("127.0.0.1"); 
    ix::WebSocketServer server(port, host);

    server.setOnConnectionCallback(
        [&server](std::weak_ptr<ix::WebSocket> webSocket,
                std::shared_ptr<ix::ConnectionState> connectionState)
        {
            std::cout << "Remote ip: " << connectionState->getRemoteIp() << std::endl;

            // .lock() — safely convert to shared_ptr to use a weak ptr 
            // .lock() atomically checks:
            // If the object still exists → returns a shared_ptr (temporarily bumps ref count)
            // If the object was destroyed → returns nullptr
            // So reference count only increases if the object is still alive, preventing use-after-free errors.

            // The is(ws) is needed AS WELL AS THE WEAK PTR because of the time gap between checking and using — another thread can destroy the object in between:
            // The weak ptr will convert to a shared ptr if the object still exists, allowing us to safely use it. If it doesn't exist, we get a nullptr.
            // Dereferencing a nullptr will cause a crash as it's referencing empty memory (if the web server has been destroyed, the weak ptr will return nullptr when .lock() is called).
            // if(ws) is a safety check to ensure the object still exists before we try to use it. If ws is nullptr, we know the object was destroyed and we can avoid dereferencing it, preventing a crash.
            // This is needed because another thread can destroy the web server object after we check if it exists but before we use it, which would lead to a use-after-free error. This scenario is commonly referred to as a TO
            // This called a TOCTOU race — "Time Of Check, Time Of Use". The check and the use are two separate operations with a gap between them.
            // .lock() eliminates the gap because it's atomic — it checks existence AND bumps the ref count in a single indivisible CPU operation. No other thread can sneak in between and cause a crash. 


            auto ws = webSocket.lock();
            if (ws)
            {
                ws->setOnMessageCallback([webSocket, connectionState](const ix::WebSocketMessagePtr& msg)
                {
                    if (msg->type == ix::WebSocketMessageType::Open)
                    {
                        std::cout << "New connection" << std::endl;
                        std::cout << "id: " << connectionState->getId() << std::endl;
                        std::cout << "Uri: " << msg->openInfo.uri << std::endl;

                        std::cout << "Headers:" << std::endl;
                        for (auto it : msg->openInfo.headers)
                        {
                            std::cout << it.first << ": " << it.second << std::endl;
                        }
                    }
                    else if (msg->type == ix::WebSocketMessageType::Message)
                    {
                        auto ws = webSocket.lock();
                        if (ws)
                        {
                            ws->send(msg->str, msg->binary);
                        }
                    }
                });
            }
        });

    auto res = server.listen();
    if (!res.first)
    {
        std::cerr << "Server failed to listen on " << host << ":" << port << " — " << res.second << std::endl;
        return 1;
    }
    std::cout << "WebSocket server listening on " << host << ":" << port << std::endl;

    // Per message deflate connection is enabled by default. It can be disabled
    // which might be helpful when running on low power devices such as a Rasbery Pi
    server.disablePerMessageDeflate();

    // Run the server in the background. Server can be stoped by calling server.stop()
    server.start();


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
    bool running = true;
    displayCommands(); // Show commands initially

    // Main input loop
    while (running) {
        std::cout << "\nEnter command (h for help): ";
        std::cin >> command; // Read a single character from the keyboard

        switch (command) {
            case 's': // Start Engine
                myCar.StartEngine();
                break;
            case 'a': // Accelerate
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
                {
                    auto state = myCar.getVehicleState();
                    std::string json = "{\"lat\":"     + std::to_string(state.latitude)  +
                                    ",\"lon\":"     + std::to_string(state.longitude) +
                                    ",\"heading\":" + std::to_string(state.heading)   +
                                    ",\"speed\":"   + std::to_string(state.speed_mps) + "}";
                    for (auto& client : server.getClients())
                        client->send(json);
                }
                break;
            case 'h': // Show Commands
                displayCommands();
                break;
            case 'q': // Quit
                std::cout << "Exiting car simulation. Goodbye!" << std::endl;
                running = false;
                break;
            case 'w':
                myCar.MoveForward();
                {
                    auto state = myCar.getVehicleState();
                    std::string json = "{\"lat\":"     + std::to_string(state.latitude)  +
                                    ",\"lon\":"     + std::to_string(state.longitude) +
                                    ",\"heading\":" + std::to_string(state.heading)   +
                                    ",\"speed\":"   + std::to_string(state.speed_mps) + "}";
                    for (auto& client : server.getClients())
                        client->send(json);
                }
                break;
            default:
                std::cout << "Invalid command. Press 'h' for help." << std::endl;
                break;
        }
    }

    server.stop(); // Stop the websocket server when exiting the program

    ix::uninitNetSystem();

    return 0;

}