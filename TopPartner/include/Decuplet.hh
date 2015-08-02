#pragma once

#include "Septet.hh"
#include "Octet.hh"

namespace analysis {

namespace toppartner {

class Decuplet55 : public TwoBody<Quintet, Quintet> {

public:

    using TwoBody<Quintet, Quintet>::TwoBody;

    const Quintet& Quintet1() const
    {
        return Multiplet1();
    }

    const Quintet& Quintet2() const
    {
        return Multiplet2();
    }

};

class Decuplet73 : public TwoBody<analysis::toppartner::Septet, analysis::Triplet> {

public:

    using TwoBody<Septet, Triplet>::TwoBody;

    const analysis::toppartner::Septet& Septet() const
    {
        return Multiplet1();
    }

    const analysis::Triplet& Triplet() const
    {
        return Multiplet2();
    }

};

class Decuplet82 : public TwoBody<Octet53, analysis::Doublet> {

public:

  using TwoBody<Octet53, analysis::Doublet>::TwoBody;

  const Octet53& Octet() const
  {
    return Multiplet1();
  }

  const analysis::Doublet& Doublet() const
  {
    return Multiplet2();
  }

};

}

}
