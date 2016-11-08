/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#pragma once

#include "boca/multiplets/Sextet.hh"

namespace boca
{

class Quartet22;
class Particle;

/**
 * @brief Wrapper for WimpMass class
 * reconstructs two missing neutrino momenta
 *
 */
class WimpMass
{

public:

    std::vector<boca::Sextet33> Sextets(std::vector<Quartet22> const &quartets, Jet const &missing_et);

    std::vector<boca::Sextet33> Sextet(Quartet22 const &quartet, Jet const &missing_et, std::vector<Particle> const &neutrinos, Tag tag);

    std::vector<boca::Sextet33> Sextets(Quartet22 const &quartet, Jet const &missing_et);

    boca::Sextet33 Fake(boca::Quartet22 const &quartet) const;

private:

};

}
