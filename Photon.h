// PHYS30762 Programming in C++
// Author: 10899510
// Date: April 5th 2024
// Photon header file
// Defines the Photon class, a derived class of Particle.
// Stores a list of electrons created via pair production and
// declares friend functions for photon interactions.

#ifndef PHOTON_H
#define PHOTON_H

#include "Particle.h"
#include <vector>
#include <memory>

class Electron;

// Photon class represents a massless particle with energy
class Photon : public Particle
{
private:
  std::vector<std::shared_ptr<Electron>> electrons;

public:
  Photon(double e);
  void add_electron(std::shared_ptr<Electron> e);
  const std::vector<std::shared_ptr<Electron>>& getElectrons() const;

  void print_data() const override;

  // Friend functions for photon interactions
  friend double photoelectric_effect(const Photon& p);
  friend void compton_scattering(Photon& p, double angle_deg);
  friend std::vector<std::shared_ptr<Electron>> pair_production(const Photon& p);
};

#endif
