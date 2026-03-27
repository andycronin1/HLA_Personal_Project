cmake_minimum_required(VERSION 3.10)
project(HLA_Personal_Project LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin")

   # Define the source files for your executable
set(SOURCES
    src/main.cpp
    src/Car.cpp 
    # Add any other .cpp files here
)

# Add the executable target
add_executable(${PROJECT_NAME} ${SOURCES})

# Optional: Add include directory
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/include)