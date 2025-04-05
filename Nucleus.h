#ifndef NUCLEUS_H
#define NUCLEUS_H

#include <string>
#include <memory>
#include <vector>
#include "Photon.h"
#include "Positron.h"

class Nucleus {
protected:
    std::string type;
    int atomic_mass;
    int atomic_number;
    bool decayed;
    std::shared_ptr<Photon> emitted_photon;
public:
    // Constructor
    Nucleus(std::string t, int am, int an);

    // Rule of Five
    virtual ~Nucleus();
    Nucleus(const Nucleus& other);
    Nucleus& operator=(const Nucleus& other);
    Nucleus(Nucleus&& other) noexcept;
    Nucleus& operator=(Nucleus&& other) noexcept;

    virtual void decay(std::vector<std::shared_ptr<Photon>>& photon_log) = 0;
    virtual void printData() const;
};

class StableNucleus : public Nucleus {
public:
    StableNucleus(std::string t, int am, int an);
    void decay(std::vector<std::shared_ptr<Photon>>& photon_log) override;
};

class RadioactiveNucleus : public Nucleus {
private:
    double half_life;
    std::vector<double> decay_energies;
public:
    RadioactiveNucleus(std::string t, int am, int an, double hl, std::vector<double> de);
    void decay(std::vector<std::shared_ptr<Photon>>& photon_log) override;
    double getHalfLife() const { return half_life; }
    const std::vector<double>& getDecayEnergies() const { return decay_energies; }
};

#endif