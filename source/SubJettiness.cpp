/**
 * Copyright (C) 2015-2016 Jan Hajer
 */

#include "fastjet/contrib/Nsubjettiness.hh"
#include "SubJettiness.hh"
#include "multiplets/Jet.hh"

namespace boca
{

NSubJettiness::NSubJettiness() {}

NSubJettiness::NSubJettiness(Jet const& jet, fastjet::contrib::AxesDefinition const& axes, int beta)
{
    fastjet::contrib::UnnormalizedMeasure unnormalized_measure(beta);
    fastjet::contrib::Nsubjettiness n_subjettiness_1(1, axes, unnormalized_measure);
    fastjet::contrib::Nsubjettiness n_subjettiness_2(2, axes, unnormalized_measure);
    fastjet::contrib::Nsubjettiness n_subjettiness_3(3, axes, unnormalized_measure);
    fastjet::contrib::NsubjettinessRatio n_subjettiness_21(2, 1, axes, unnormalized_measure);
    fastjet::contrib::NsubjettinessRatio n_subjettiness_32(3, 2, axes, unnormalized_measure);
    tau_1_ = n_subjettiness_1(jet);
    tau_2_ = n_subjettiness_2(jet);
    tau_3_ = n_subjettiness_3(jet);
    tau_2_1_ = n_subjettiness_21(jet);
    tau_3_2_ = n_subjettiness_32(jet);
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

SubJettiness::SubJettiness() {}

SubJettiness::SubJettiness(Jet const& jet)
{
    jet_ = jet;
}

NSubJettiness SubJettiness::beta_1() const
{
    fastjet::contrib::OnePass_WTA_KT_Axes wta_kt_axes;
    return NSubJettiness(jet_, wta_kt_axes, 1);
}

NSubJettiness SubJettiness::beta_2() const
{
    fastjet::contrib::OnePass_KT_Axes kt_axes;
    return NSubJettiness(jet_, kt_axes, 2);
}


}
