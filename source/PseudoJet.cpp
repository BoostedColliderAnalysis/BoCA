/**
 * Copyright (C) 2015 Jan Hajer
 */

#include "Jet.hh"
namespace boca
{
Jet::Jet(fastjet::PseudoJet& jet)
{
    *this = jet;
}

Momentum Jet::Pt() const
{
    return pt() * GeV;
}

Mass Jet::Mass() const
{
    return m() * GeV;
}

}

