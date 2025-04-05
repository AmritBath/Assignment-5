#ifndef ELECTRON_H
#define ELECTRON_H

#include "Particle.h"
#include <vector>
#include <memory>

class Photon;

class Electron : public Particle {
private:
    std::vector<std::shared_ptr<Photon>> photons;
    
public:
    Electron(double e);
    void addPhoton(std::shared_ptr<Photon> p);
    std::shared_ptr<Photon> radiate();
    void printData() const override;
};

#endif
