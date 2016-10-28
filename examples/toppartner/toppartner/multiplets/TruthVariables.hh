/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#pragma once

#include "boca/fastjet/Particle.hh"
#include "boca/fastjet/Particle.hh"
#include "boca/fastjet/Jet.hh"

namespace toppartner
{

using namespace boca;

/**
 * @brief Variables for truth level analyses
 *
 */
class TruthVariables : public Identification
{

public:

    Momentum LeptonPt(unsigned number) const;

    Momentum TopPt(unsigned number) const;

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

    void SetJets(std::vector<boca::Jet> const& jets);

    Momentum JetPt(unsigned number) const;

private:

    std::vector<Particle> leptons_;

    std::vector<Particle> bosons_;

    std::vector<Particle> tops_;

    std::vector<Particle> detectable_;

    std::vector<boca::Jet> jets_;

    boca::MissingEt missing_et_;

    Momentum scalar_ht_;

};

}
