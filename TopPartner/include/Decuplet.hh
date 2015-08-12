#pragma once

#include "Septet.hh"
#include "Octet.hh"

namespace analysis {

namespace toppartner {

class Decuplet55 : public TwoBody<Quintet, Quintet> {

public:

    using TwoBody<Quintet, Quintet>::TwoBody;

    Quintet const& Quintet1() const
    {
        return Multiplet1();
    }

    Quintet const& Quintet2() const
    {
        return Multiplet2();
    }

};

class Decuplet73 : public TwoBody<analysis::toppartner::Septet, analysis::Triplet> {

public:

  using TwoBody<analysis::toppartner::Septet, analysis::Triplet>::TwoBody;

    analysis::toppartner::Septet const& Septet() const
    {
        return Multiplet1();
    }

    analysis::Triplet const& Triplet() const
    {
        return Multiplet2();
    }

};

class Decuplet82 : public TwoBody<Octet53, analysis::Doublet> {

public:

  using TwoBody<Octet53, analysis::Doublet>::TwoBody;

  Octet53 const& Octet() const
  {
    return Multiplet1();
  }

  analysis::Doublet const& Doublet() const
  {
    return Multiplet2();
  }

};

}

}
