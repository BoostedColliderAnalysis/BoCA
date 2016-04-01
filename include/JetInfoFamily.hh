/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#pragma once

#include <map>
#include <unordered_map>

#include "fastjet/PseudoJet.hh"
#include "physics/Particles.hh"

#include "multiplets/Identification.hh"
#include "FourVector.hh"
#include "physics/Family.hh"

namespace boca {

/**
 * @brief Jet infos subclassed from Fastjet
 *
 */
class JetInfoFamily: public Identification, public fastjet::PseudoJet::UserInfoBase {

public:

    /**
     * @brief Constructor
     *
     */
    JetInfoFamily();

    JetInfoFamily(double bdt);

    void AddDaughter(int daughter);

    std::unordered_map<Family, double> FamilyFractions();

    void ExtractFraction(int id);

    void ExtractAbsFraction(int id);

    void ExtractFraction(int id, int mother_id);

    double MaximalFraction() const;

    double Fraction(int id) const;

    int MaximalId() const;

    void AddFamily(Family const& family, double weight);

    void ExtractFamilyFraction();

    Family MaximalFamily();

private:

    void AddParticle(int constituent_id, double weight);

    void AddParticle(Id constituent_id, double weight);

    double GetWeightSum() const;

    std::unordered_map<Family, double> family_fractions_;

    std::map<int, double> id_fractions_;

};

}
