#pragma once

#include "Triplet.hh"

namespace analysis
{

class Quartet22 : public Multiplet<Doublet, Doublet>
{

public:

    using Multiplet<Doublet, Doublet>::Multiplet;

    Doublet &Doublet1()const;

    Doublet &Doublet2()const;

};

class Quartet31 : public Multiplet<analysis::Triplet, analysis::Singlet>
{

public:

    using Multiplet<analysis::Triplet, analysis::Singlet>::Multiplet;

    analysis::Triplet &Triplet() const;

    fastjet::PseudoJet SingletJet() const;

    analysis::Singlet &Singlet() const;

};

}
