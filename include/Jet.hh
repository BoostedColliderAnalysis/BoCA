/**
 * Copyright (C) 2015 Jan Hajer
 */
#pragma once

#include "PseudoJet.hh"
#include "JetInfo.hh"

namespace boca
{

class Jet : public PseudoJet
{
public:

//     Jet(fastjet::PseudoJet& const jet);

    JetInfo const& Info() const;

    JetInfo& Info();

private:

    JetInfo jet_info_;

};

using Lepton  = Jet;

}
