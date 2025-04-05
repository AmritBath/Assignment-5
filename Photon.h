#ifndef PHOTON_H
#define PHOTON_H

#include "Particle.h"
#include <vector>
#include <memory>

class Electron;

class Photon : public Particle {
private:
    std::vector<std::shared_ptr<Electron>> electrons;
    
public:
    Photon(double e);
    void addElectron(std::shared_ptr<Electron> e);
    const std::vector<std::shared_ptr<Electron>>& getElectrons() const;
    void printData() const override;

    friend double photoelectricEffect(const Photon& p);
    friend void comptonScattering(Photon& p, double angle_deg);
    friend std::vector<std::shared_ptr<Electron>> pairProduction(const Photon& p);
};

#endif
