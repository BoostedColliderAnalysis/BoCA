/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#pragma once

#include "multiplets/Sextet.hh"

namespace boca {

class Quartet22;
class Particle;

/**
 * @brief Wrapper for WimpMass class
 * reconstructs two missing neutrino momenta
 *
 */
class WimpMass {

public:

    std::vector<boca::Sextet> Sextets(std::vector<Quartet22> const& quartets, Jet const& missing_et);

    std::vector<boca::Sextet> Sextet(Quartet22 const& quartet, Jet const& missing_et,std::vector<Particle> const& neutrinos, Tag tag);

    std::vector<boca::Sextet> Sextets(Quartet22 const& quartet, Jet const& missing_et);

    boca::Sextet Fake(boca::Quartet22 const& quartet) const;

private:

    void Momentum(double momentum[4], Jet const& jet);

//     Jet PseudoJet(double const Momentum[4]) const;

};

}
