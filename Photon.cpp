#include "Photon.h"
#include "Electron.h"
#include <iostream>

Photon::Photon(double e) : Particle(0.0, e) {}

void Photon::addElectron(std::shared_ptr<Electron> e) {
    electrons.push_back(e);
}

const std::vector<std::shared_ptr<Electron>>& Photon::getElectrons() const {
    return electrons;
}

void Photon::printData() const {
    std::cout << "Photon | Energy: " << energy << " keV\n";
}
