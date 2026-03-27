   cmake_minimum_required(VERSION 3.10)
   project(HLA_Personal_Project LANGUAGES CXX)

   set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin")

   add_executable(${PROJECT_NAME} src/main.cpp)

   # Optional: Add include directory
   target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/include)