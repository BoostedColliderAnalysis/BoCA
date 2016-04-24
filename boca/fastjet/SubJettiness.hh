/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#pragma once
#include "boca/multiplets/Jet.hh"

namespace fastjet
{
namespace contrib
{
class AxesDefinition;
}
}

namespace boca
{

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
