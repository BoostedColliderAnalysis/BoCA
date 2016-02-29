/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#pragma once

#include "Identification.hh"
#include "Particle.hh"

namespace boca
{

namespace naturalness
{

/**
 * @brief Variables for truth level analyses
 *
 */
class TruthVariables : public Identification
{

public:

    Momentum LeptonPt(int number) const;

    Momentum TopPt(int number) const;

    int BosonNumber() const;

    int HardBosonNumber() const;

    int DetectableBosonNumber() const;

    Momentum HardBosonPt() const;

    Momentum SoftBosonPt() const;

    Angle BosonDeltaRMin()const;

    void SetLeptons(std::vector<Particle> const& leptons);

    void SetBosons(std::vector<Particle> const& bosons);

    void SetTops(std::vector<Particle> const& tops);

    void SetDetectable(std::vector<Particle> const& jets);

private:
    std::vector<Particle> leptons_;

    std::vector<Particle> bosons_;

    std::vector<Particle> tops_;

    std::vector<Particle> detectable_;

};

}

}
