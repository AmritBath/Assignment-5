// PHYS30762 Programming in C++
// Author: 10899510
// Date: April 5th 2024
// Interactions header file
// Declares functions for simulating photon interactions with matter,
// including the photoelectric effect, Compton scattering, and pair production.

#ifndef INTERACTIONS_H
#define INTERACTIONS_H

#include "Photon.h"
#include "Electron.h"
#include <vector>
#include <memory>

// Simulates the photoelectric effect
double photoelectric_effect(const Photon& p);

// Simulates Compton scattering at a specified angle
void compton_scattering(Photon& p, double angle_deg);

// Simulates pair production if energy conditions are met
std::vector<std::shared_ptr<Electron>> pair_production(const Photon& p);

#endif
