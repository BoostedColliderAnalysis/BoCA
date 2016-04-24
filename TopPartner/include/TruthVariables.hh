/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#pragma once

#include "multiplets/Identification.hh"
#include "multiplets/Particle.hh"
#include "multiplets/Jet.hh"

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

    Momentum LeptonPt(unsigned int number) const;

    Momentum TopPt(unsigned int number) const;

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

    Energy MissingEt() const;

    Momentum ScalarHt() const;

    void SetMissingEt(boca::MissingEt const& missing_et);

    void SetScalarHt(Momentum const& scalar_ht);

    void SetJets(std::vector<Jet> const& jets);

    Momentum JetPt(unsigned number) const;

private:

    std::vector<Particle> leptons_;

    std::vector<Particle> bosons_;

    std::vector<Particle> tops_;

    std::vector<Particle> detectable_;

    std::vector<Jet> jets_;

    boca::MissingEt missing_et_;

    Momentum scalar_ht_;

};

}

}
