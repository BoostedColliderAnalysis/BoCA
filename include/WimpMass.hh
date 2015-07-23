#pragma once

#include "Quartet.hh"
#include "Sextet.hh"

namespace analysis {

/**
 * @brief Wrapper for WimpMass class
 * reconstructs two missing neutrino momenta
 *
 */
class WimpMass {

public:

    std::vector<analysis::Sextet> Sextets(const std::vector<Quartet22>& quartets, const fastjet::PseudoJet& missing_et);

    std::vector<analysis::Sextet> Sextet(const Quartet22& quartet, const fastjet::PseudoJet& missing_et, const Jets& neutrinos,  Tag tag);

    std::vector<analysis::Sextet> Sextets(const Quartet22& quartet, const fastjet::PseudoJet& missing_et);

    analysis::Sextet Fake(const Quartet22& quartet) const;

private:

    void Momentum(double momentum[4], const fastjet::PseudoJet& jet);

    fastjet::PseudoJet PseudoJet(const double Momentum[4]) const
    {
        // wimpmass (E,px,py,pz)
        // fastjet (px,py,pz,E)
        return fastjet::PseudoJet(Momentum[1], Momentum[2], Momentum[3], Momentum[0]);
    }

};

}
