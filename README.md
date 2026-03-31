# HLA Personal Project

A C++ project built with CMake.

## Requirements

- CMake 3.10+
- A C++ compiler (clang++ or g++)

## Build

From the project root:

```bash
./build.sh
```

This generates build output in `build/` and places the executable in `bin/`.

## Run

```bash
./bin/HLA_Personal_Project
```

## Project Structure

- `CMakeLists.txt`: Build configuration
- `build.sh`: Build script
- `include/`: Header files
- `src/`: Source files
- `bin/`: Built executable
- `build/`: CMake-generated build files
- `data/`: Runtime/project data
- `doc/`: Documentation
- `lib/`: Third-party or internal libraries

## Notes

To set an explicit C++ standard, add this to `CMakeLists.txt`:

```cmake
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
```
