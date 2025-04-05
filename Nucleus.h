// PHYS30762 Programming in C++
// Author: 10899510
// Date: April 5th 2024
// Nucleus header file
// Defines the abstract Nucleus base class and its two derived classes:
// StableNucleus and RadioactiveNucleus. Also includes decay behaviour,
// dynamic memory handling, and relevant physical properties.

#ifndef NUCLEUS_H
#define NUCLEUS_H

#include <string>
#include <memory>
#include <vector>
#include "Photon.h"
#include "Positron.h"

// Abstract base class representing a generic atomic nucleus
class Nucleus 
{
protected:
  std::string type;                           
  int atomic_mass;                            
  int atomic_number;                          
  bool decayed;                              
  std::shared_ptr<Photon> emitted_photon;    

public:
  Nucleus(std::string t, int am, int an);

  // Rule of Five: Virtual destructor + copy/move constructors and assignment
  virtual ~Nucleus();
  Nucleus(const Nucleus& other);
  Nucleus& operator=(const Nucleus& other);
  Nucleus(Nucleus&& other) noexcept;
  Nucleus& operator=(Nucleus&& other) noexcept;

  virtual void decay(std::vector<std::shared_ptr<Photon>>& photon_log,
    int& annihilation_photon_count) = 0;

  virtual void print_data() const;
};

// Stable nucleus — cannot decay
class StableNucleus : public Nucleus 
{
public:
  StableNucleus(std::string t, int am, int an);
  void decay(std::vector<std::shared_ptr<Photon>>& photon_log,
               int& annihilation_photon_count) override;
};

// Radioactive nucleus — emits one or more photons (and possibly a positron)
class RadioactiveNucleus : public Nucleus 
{
private:
  double half_life;                          
  std::vector<double> decay_energies;        

public:
  RadioactiveNucleus(std::string t, int am, int an, double hl, std::vector<double> de);

  void decay(std::vector<std::shared_ptr<Photon>>& photon_log,
               int& annihilation_photon_count) override;

  double getHalfLife() const 
  { return half_life; 
}
  const std::vector<double>& getDecayEnergies() const {
     return decay_energies; 
    }
};

#endif 
