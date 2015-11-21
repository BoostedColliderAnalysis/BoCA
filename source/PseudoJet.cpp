/**
 * Copyright (C) 2015 Jan Hajer
 */

#include "PseudoJet.hh"
namespace boca
{
//   PseudoJet::PseudoJet(fastjet::PseudoJet const& jet)
// {
//     *this = jet;
// }

Momentum PseudoJet::Pt() const
{
    return pt() * GeV;
}

Mass PseudoJet::Mass() const
{
    return m() * GeV;
}

}

