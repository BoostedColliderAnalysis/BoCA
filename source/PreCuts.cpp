/**
 * Copyright (C) 2015 Jan Hajer
 */
#include "PreCuts.hh"

namespace boca
{

bool PreCuts::DoSubJets() const
{
    return do_sub_jets_;
}

void PreCuts::SetSubJets(bool do_sub_jets)
{
    do_sub_jets_ = do_sub_jets;
}

bool PreCuts::SemiLeptonic() const
{
    return semi_leptonic_;
}

void PreCuts::SetSemiLeptonic(bool semi_leptonic)
{
    semi_leptonic_ = semi_leptonic;
}

}
