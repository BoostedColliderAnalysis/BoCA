/**
 * Copyright (C) 2015 Jan Hajer
 */
#pragma once

#include "Triplet.hh"
#include "ThreeBody.hh"

namespace analysis {

class Quartet22 : public TwoBody<Doublet, Doublet> {

public:

    using TwoBody<Doublet, Doublet>::TwoBody;

    Doublet const& Doublet1() const;

    Doublet const& Doublet2() const;

    Doublet& Doublet1();

    Doublet& Doublet2();

};

class Quartet31 : public TwoBody<analysis::Triplet, analysis::Singlet> {

public:

    using TwoBody<analysis::Triplet, analysis::Singlet>::TwoBody;

    analysis::Triplet const& Triplet() const;

    analysis::Singlet const& Singlet() const;

};

class Quartet211 : public ThreeBody<analysis::Doublet, analysis::Singlet, analysis::Singlet> {

public:

  using ThreeBody<analysis::Doublet, analysis::Singlet, analysis::Singlet>::ThreeBody;

  analysis::Doublet const& Doublet() const;

  analysis::Singlet const& Singlet1() const;

  analysis::Singlet const& Singlet2() const;

};

}
