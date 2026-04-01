# HLA Personal Project

A C++17 car simulation with real-time WebSocket telemetry. The simulation accepts keyboard commands to control a vehicle (start engine, accelerate, brake) and streams vehicle state (latitude, longitude, heading, speed) over a WebSocket connection.

## Requirements

- CMake 3.10+
- A C++ compiler with C++17 support (clang++ or g++)
- [ixwebsocket](https://github.com/machinezone/IXWebSocket) (included in `external/`)

## Build

**First time / after changing CMakeLists.txt:**
```bash
./build.sh
```

**Incremental builds (day-to-day development):**
```bash
cd build && make
```

The executable is placed in `bin/`.

## Run

```bash
./bin/HLA_Personal_Project
```

## Commands

| Key | Action |
|-----|--------|
| `s` | Start engine |
| `w` | Accelerate (+10 mps) |
| `b` | Brake (stop immediately) |
| `d` | Display current speed |
| `v` | Display vehicle state + send over WebSocket |
| `h` | Show commands |
| `q` | Quit |

## Project Structure

```
HLA_Personal_Project/
├── CMakeLists.txt        # Build configuration
├── build.sh              # Full clean build script
├── include/              # Header files (Car.h)
├── src/                  # Source files (main.cpp, Car.cpp)
├── external/ixwebsocket/ # WebSocket library
├── bin/                  # Built executable
├── build/                # CMake-generated build files
├── data/                 # Runtime/project data
├── doc/                  # Documentation
└── lib/                  # Libraries
```

## WebSocket

On startup, connects to `wss://echo.websocket.org`. When the `v` command is used, the current vehicle state is sent as a message over the WebSocket connection.
