/**
 * Copyright (C) 2015 Jan Hajer
 */
#pragma once

namespace fastjet
{
class PseudoJet;
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

    NSubJettiness(fastjet::PseudoJet const& jet, fastjet::contrib::AxesDefinition const& axes, int beta);

    float tau_1() const;
    float tau_2() const;
    float tau_3() const;
    float tau_2_1() const;
    float tau_3_2() const;

private:

    float tau_1_;
    float tau_2_;
    float tau_3_;
    float tau_2_1_;
    float tau_3_2_;
};


class SubJettiness
{

public:

    SubJettiness();

    SubJettiness(fastjet::PseudoJet const& jet);

    NSubJettiness beta_1();

    NSubJettiness beta_2();

private:

    NSubJettiness beta_1_;

    NSubJettiness beta_2_;

};

}
