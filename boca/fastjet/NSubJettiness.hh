/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#pragma once

namespace fastjet
{
/**
* @brief <a href="https://fastjet.hepforge.org/contrib/">FastJet Contrib</a> is intended to provide a common location for access to 3rd party extensions of FastJet.
*
*/
namespace contrib
{
class AxesDefinition;
}
}

namespace boca
{

class Jet;
/**
* @ingroup FastJet
* @brief Helper class to calculate <a href="https://inspirehep.net/record/876746">N-subjettiness</a> of a jet
*
*/
class NSubJettiness
{

public:

    NSubJettiness();

    NSubJettiness(Jet const& jet, fastjet::contrib::AxesDefinition const& axes, int beta);

    double tau_1() const;
    double tau_2() const;
    double tau_3() const;
    double tau_2_1() const;
    double tau_3_2() const;

private:

    double tau_1_;
    double tau_2_;
    double tau_3_;
    double tau_2_1_;
    double tau_3_2_;
};

}
