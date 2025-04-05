// PHYS30762 Programming in C++
// Author: 10899510
// Date: April 5th 2024
// Interactions class implementation
// This file contains the implementation of photon interaction functions, simulating
// the photoelectric effect, Compton scattering, and pair production. These functions
// operate on Photon and Electron objects using appropriate physics approximations.

#include "Interactions.h"
#include <iostream>
#include <cmath>

#define PINKRED "\033[38;5;198m"
#define RESET   "\033[0m"

// Simulates the photoelectric effect and returns the energy of the incoming photon
double photoelectric_effect(const Photon& p)
{
  return p.energy;
}

// Simulates Compton scattering of a photon with a scattering angle in degrees
// and updates the photon's energy
void compton_scattering(Photon& p, double angle_deg)
{
  double theta = angle_deg * M_PI / 180.0;
  double E = p.energy;
  double me = 511;
  p.energy = E / (1 + (E / me) * (1 - std::cos(theta)));
  std::cout << "After Compton scattering, new photon energy: " << p.energy << " keV\n";
}

// Simulates pair production if photon energy exceeds 1.022 MeV
std::vector<std::shared_ptr<Electron>> pair_production(const Photon& p)
{
  double me = 511;

  if(p.energy > 2 * me)
  {
    double e = p.energy / 2;
    auto e1 = std::make_shared<Electron>(e);
    auto e2 = std::make_shared<Electron>(e);

    // Associate electrons with the photon that created them
    const_cast<Photon&>(p).add_electron(e1);
    const_cast<Photon&>(p).add_electron(e2);

    return { e1, e2 };
  }
  else
  {
    std::cout << PINKRED << "ERROR: Insufficient energy for pair production.\n" << RESET;
    return {};
  }
}
