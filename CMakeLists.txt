cmake_minimum_required(VERSION 3.10)
project(HLA_Personal_Project LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin")

   # Define the source files for your executable
set(SOURCES
    src/main.cpp
    src/Car.cpp 
    # Add any other .cpp files here
)

# ixwebsocket defaults TLS off; enable it so wss:// URLs work.
set(USE_TLS ON CACHE BOOL "Enable TLS support for ixwebsocket" FORCE)
add_subdirectory(external/ixwebsocket)

# Add the executable target
add_executable(${PROJECT_NAME} ${SOURCES})

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/include)

target_link_libraries(${PROJECT_NAME} PRIVATE ixwebsocket) 