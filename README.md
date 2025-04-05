# Assignment 5 – PHYS30762: Object-Oriented Programming in C++

## Overview
This project simulates radioactive decays and particle interactions using object-oriented design in C++. It includes multiple inheritance hierarchies and models physical processes such as photon emission, Compton scattering, photoelectric effect, pair production, and positron emission.

## Features Implemented
- **Nucleus class hierarchy**: Base `Nucleus` class with `StableNucleus` and `RadioactiveNucleus` derived types
- **Particle class hierarchy**: Base `Particle` class with `Photon`, `Electron`, and extended `Positron` class
- **Decay logic**: Simulates radioactive decay and photon emission based on energy values
- **Photon interactions**:
  - Photoelectric effect
  - Compton scattering (with angle input)
  - Pair production (valid and invalid cases)
- **Electron behaviour**: Electrons can store and radiate photons
- **Positron emission**: Triggered specifically during Sodium (Na) decay
- **Smart pointers** used throughout to manage memory safely
- **Rule of Five** implemented in `Nucleus` class
- **Well-structured console output** for simulation traceability

## Optional Enhancements Added
- ✅ Positron emission from Sodium decay
- ✅ Rule of Five in base class `Nucleus`
- ✅ Comprehensive simulation summary block
- ✅ Consistent output format with clear section headers
- ✅ Structured output for photon emissions per nucleus
- ✅ Labelled particle output for better readability

## Compilation & Execution
Ensure you are using a C++17 compatible compiler. Then:

```bash
make
./main.o
```

## Example Output Snippet
```
--- Nucleus Decay ---
[Photon] Energy: 1274.5 keV
Positron emission from Na detected.
[Positron] Energy: 511 keV
Nucleus (Na) | A: 23, Z: 11 | Status: Decayed
...
```

## File Structure
- `main.cpp`: Simulation logic
- `Nucleus.h/.cpp`: Class hierarchy and decay logic
- `Particle.h`: Abstract base for particles
- `Photon.h/.cpp`: Photon behaviour
- `Electron.h/.cpp`: Electron behaviour
- `Positron.h`: Lightweight positron class
- `Interactions.h/.cpp`: Physical interaction implementations

## Author Notes
This project aims to simulate nuclear decay processes while demonstrating mastery of object-oriented programming in C++. Beyond fulfilling the brief, it showcases best practices such as encapsulation, dynamic memory management, and modular design.