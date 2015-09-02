/**
 * Copyright (C) 2015 Jan Hajer
 */
#pragma once

#include "Sextet.hh"

namespace boca {

class Quartet22;

/**
 * @brief Wrapper for WimpMass class
 * reconstructs two missing neutrino momenta
 *
 */
class WimpMass {

public:

    std::vector<boca::Sextet> Sextets(const std::vector<Quartet22>& quartets, fastjet::PseudoJet const& missing_et);

    std::vector<boca::Sextet> Sextet(Quartet22 const& quartet, fastjet::PseudoJet const& missing_et, Jets const& neutrinos, Tag tag);

    std::vector<boca::Sextet> Sextets(Quartet22 const& quartet, fastjet::PseudoJet const& missing_et);

    boca::Sextet Fake(Quartet22 const& quartet) const;

private:

    void Momentum(double momentum[4], fastjet::PseudoJet const& jet);

    fastjet::PseudoJet PseudoJet(const double Momentum[4]) const
    {
        // wimpmass (E,px,py,pz)
        // fastjet (px,py,pz,E)
        return fastjet::PseudoJet(Momentum[1], Momentum[2], Momentum[3], Momentum[0]);
    }

};

}
