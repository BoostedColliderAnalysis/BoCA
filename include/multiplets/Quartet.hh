/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#pragma once

#include "multiplets/Triplet.hh"
#include "multiplets/ThreeBody.hh"

namespace boca {

class Quartet22 : public TwoBody<Doublet, Doublet> {

public:

    using TwoBody<Doublet, Doublet>::TwoBody;

    Doublet const& Doublet1() const;

    Doublet const& Doublet2() const;

    Doublet& Doublet1();

    Doublet& Doublet2();

};

class Quartet31 : public TwoBody<boca::Triplet, boca::Singlet> {

public:

    using TwoBody<boca::Triplet, boca::Singlet>::TwoBody;

    boca::Triplet const& Triplet() const;

    boca::Singlet const& Singlet() const;

};

class Quartet211 : public ThreeBody<boca::Doublet, boca::Singlet, boca::Singlet> {

public:

  using ThreeBody<boca::Doublet, boca::Singlet, boca::Singlet>::ThreeBody;

  boca::Doublet const& Doublet() const;

  boca::Singlet const& Singlet1() const;

  boca::Singlet const& Singlet2() const;

};

}
