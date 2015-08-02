#pragma once

#include "Triplet.hh"

namespace analysis {

class Quartet22 : public TwoBody<Doublet, Doublet> {

public:

    using TwoBody<Doublet, Doublet>::TwoBody;

    Doublet& Doublet1() const;

    Doublet& Doublet2() const;

};

class Quartet31 : public TwoBody<analysis::Triplet, analysis::Singlet> {

public:

    using TwoBody<analysis::Triplet, analysis::Singlet>::TwoBody;

    analysis::Triplet& Triplet() const;

    analysis::Singlet& Singlet() const;

};

}
