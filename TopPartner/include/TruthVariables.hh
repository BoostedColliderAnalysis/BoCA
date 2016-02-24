/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#pragma once

#include "Identification.hh"
#include "Particle.hh"
#include "physics/Particles.hh"
#include "physics/Units.hh"
#include "Sort.hh"
#include "Vector.hh"

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

    Momentum LeptonPt(int number) const {
//         std::cout << "lepton pt " << number << "  " << leptons_.size() << std::endl;
        return leptons_.size() > number ? leptons_.at(number).Pt() : at_rest;
    }

    Momentum TopPt(int number) const {
//         std::cout << "top pt " << number << "  " << tops_.size() << std::endl;
        return tops_.size() > number ? tops_.at(number).Pt() : at_rest;
    }

    int BosonNumber() const {
        return bosons_.size();
    }

    int HardBosonNumber() const {
      return RemoveIfSoft(bosons_, 20_GeV).size();
    }

    int DetectableBosonNumber() const {
      return jets_.size();
    }

    Momentum SoftBosonPt() const {
      return bosons_.empty() ? at_rest : bosons_.back().Pt();
    }

    void SetLeptons(std::vector<Particle> const& leptons) {
        leptons_ = SortedByPt(leptons);
    }

    void SetBosons(std::vector<Particle> const& bosons) {
        bosons_ = SortedByPt(bosons);
    }

    void SetTops(std::vector<Particle> const& tops) {
        tops_ = SortedByPt(tops);
    }

    void SetJets(std::vector<Particle> const& jets) {
      jets_ = SortedByPt(jets);
    }

private:
    std::vector<Particle> leptons_ = {};
    std::vector<Particle> bosons_ = {};
    std::vector<Particle> tops_ = {};
    std::vector<Particle> jets_ = {};

};


}

}
