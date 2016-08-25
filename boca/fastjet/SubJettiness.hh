/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#pragma once
#include "boca/multiplets/Jet.hh"
#include "boca/fastjet/NSubJettiness.hh"

namespace boca
{

/**
* @ingroup FastJet
* @brief Calculate <a href="https://inspirehep.net/record/876746">N-subjettiness</a> of a jet
*
*/
class SubJettiness
{

public:

    SubJettiness();

    SubJettiness(Jet const& jet);

    NSubJettiness beta_1() const;

    NSubJettiness beta_2() const;

private:

    Jet jet_;

};

}
