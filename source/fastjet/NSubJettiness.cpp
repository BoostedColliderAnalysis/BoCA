/**
 * Copyright (C) 2015-2016 Jan Hajer
 */

#include "fastjet/contrib/Nsubjettiness.hh"

#include "boca/fastjet/NSubJettiness.hh"
#include "boca/fastjet/Jet.hh"

namespace boca
{

NSubJettiness::NSubJettiness() {}

NSubJettiness::NSubJettiness(PseudoJet const& jet, fastjet::contrib::AxesDefinition const& axes, int beta)
{
    auto fast_jet = jet.FastJet();
    auto unnormalized_measure = fastjet::contrib::UnnormalizedMeasure(beta);
    auto n_subjettiness_1 = fastjet::contrib::Nsubjettiness{1, axes, unnormalized_measure};
    auto n_subjettiness_2 = fastjet::contrib::Nsubjettiness{2, axes, unnormalized_measure};
    auto n_subjettiness_3 = fastjet::contrib::Nsubjettiness{3, axes, unnormalized_measure};
    auto n_subjettiness_21 = fastjet::contrib::NsubjettinessRatio{2, 1, axes, unnormalized_measure};
    auto n_subjettiness_32 = fastjet::contrib::NsubjettinessRatio{3, 2, axes, unnormalized_measure};
    tau_1_ = n_subjettiness_1.result(fast_jet);
    tau_2_ = n_subjettiness_2.result(fast_jet);
    tau_3_ = n_subjettiness_3.result(fast_jet);
    tau_2_1_ = n_subjettiness_21.result(fast_jet);
    tau_3_2_ = n_subjettiness_32.result(fast_jet);
}

double NSubJettiness::tau_1() const
{
    return tau_1_;
}

double NSubJettiness::tau_2() const
{
    return tau_2_;
}

double NSubJettiness::tau_3() const
{
    return tau_3_;
}

double NSubJettiness::tau_2_1() const
{
    return tau_1_ > 0 ? tau_2_1_ : 0;
}

double NSubJettiness::tau_3_2() const
{
    return tau_2_ > 0 ? tau_3_2_ : 0;
}

}
