# HLA Car Sim

A C++ vehicle simulation built on the **HLA 1516e** standard using the **MAK RTI**. The simulation accepts keyboard commands to control a vehicle (start engine, accelerate, brake) and tracks vehicle state (latitude, longitude, heading, speed) with planned real-time WebSocket telemetry broadcast to a browser-based map client.

## Requirements

- **CMake 3.10+**
- **MSVC** (Visual Studio Build Tools 2019+) with C++14 support
- **MAK RTI 5.0+** — set the `MAK_RTI_HOME` environment variable to your install directory
- Windows (x64)

## Setup

Set the `MAK_RTI_HOME` environment variable before building:

```powershell
$env:MAK_RTI_HOME = "C:\MAK\makRti5.0.1"
```

Or set it permanently via System Properties > Environment Variables.

## Build

**Full clean build (Windows):**
```powershell
.\full_build.bat
```

This deletes the `build/` directory, runs CMake, and builds in Release mode. The executable is placed in `bin/`.

**Incremental builds:**
```powershell
cmake --build build --config Release
```

## Run

```powershell
.\bin\HLA_Personal_Project.exe
```

## Commands

| Key | Action |
|-----|--------|
| `s` | Start engine |
| `o` | Stop engine |
| `w` | Accelerate (+10 mps) |
| `b` | Brake (stop immediately) |
| `d` | Display current speed |
| `v` | Display full vehicle state |
| `h` | Show commands |
| `q` | Quit |

## HLA / RTI Integration

The `Car` class extends `rti1516e::NullFederateAmbassador` and connects to the MAK RTI via `RTIambassadorFactory`. The CMake build links against:

- `librti1516e64` (Release)
- `librti1516e64d` (Debug)
- `ws2_32` (Windows Sockets)

Build warnings C4290 and C5040 from the MAK RTI headers are expected and harmless — they reflect the library's pre-C++17 exception specification syntax.

## Map Client

`data/map.html` is a Leaflet.js map intended to connect to a WebSocket server. When vehicle state is broadcast, the map updates in real time:

- The car is rendered as a **directional SVG icon** that rotates with the vehicle's heading
- The map pans to keep the car in view
- A popup shows current speed and heading

Planned JSON payload format:
```json
{ "lat": 53.3498, "lon": -6.2603, "heading": 0.0, "speed": 10.0 }
```

## Project Structure

```
HLA_Car_Sim/
├── CMakeLists.txt        # Build configuration
├── full_build.bat        # Full clean build script (Windows)
├── include/
│   └── Car.h             # Car class declaration (HLA federate ambassador)
├── src/
│   ├── HLA_main.cpp      # Entry point and command loop
│   └── Car.cpp           # Car class implementation
├── external/
│   └── ixwebsocket/      # WebSocket library (TLS enabled)
├── data/
│   └── map.html          # Leaflet.js browser map client
└── bin/                  # Built executable output
```
