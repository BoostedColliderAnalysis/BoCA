/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#include "fastjet/contrib/Nsubjettiness.hh"
#include "boca/fastjet/SubJettiness.hh"

namespace boca
{

SubJettiness::SubJettiness() {}

SubJettiness::SubJettiness(Jet const& jet)
{
    jet_ = jet;
}

NSubJettiness SubJettiness::beta_1() const
{
    auto wta_kt_axes = fastjet::contrib::OnePass_WTA_KT_Axes{};
    return NSubJettiness(jet_, wta_kt_axes, 1);
}

NSubJettiness SubJettiness::beta_2() const
{
    auto kt_axes = fastjet::contrib::OnePass_KT_Axes{};
    return NSubJettiness(jet_, kt_axes, 2);
}


}
