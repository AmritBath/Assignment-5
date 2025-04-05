#ifndef INTERACTIONS_H
#define INTERACTIONS_H

#include "Photon.h"
#include "Electron.h"
#include <vector>
#include <memory>

double photoelectricEffect(const Photon& p);
void comptonScattering(Photon& p, double angle_deg);
std::vector<std::shared_ptr<Electron>> pairProduction(const Photon& p);

#endif
