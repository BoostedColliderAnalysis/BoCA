/**
 * Copyright (C) 2015 Jan Hajer
 */
#pragma once

#include "fastjet/PseudoJet.hh"
#include "Units.hh"
#include "JetInfo.hh"

namespace boca
{

class PseudoJet : public fastjet::PseudoJet
{
public:

//     PseudoJet(fastjet::PseudoJet const& jet);

    virtual fastjet::PseudoJet::UserInfoBase const& Info() const = 0;

    virtual fastjet::PseudoJet::UserInfoBase& Info() = 0;

    Momentum Pt() const;

    boca::Mass Mass()const;

};

}
