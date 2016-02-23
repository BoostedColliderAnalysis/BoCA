/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#pragma once

namespace fastjet
{
namespace contrib
{
class AxesDefinition;
}
}

namespace boca
{
class Jet;

class NSubJettiness
{

public:

    NSubJettiness();

    NSubJettiness(Jet const& jet, fastjet::contrib::AxesDefinition const& axes, int beta);

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

    SubJettiness(Jet const& jet);

    NSubJettiness const& beta_1() const;

    NSubJettiness const& beta_2() const;

private:

    NSubJettiness beta_1_;

    NSubJettiness beta_2_;

};

}
