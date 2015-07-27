#pragma once

#include "Septet.hh"
#include "Octet.hh"

namespace analysis {

namespace toppartner {

class Decuplet55 : public Multiplet<Quintet, Quintet> {

public:

    using Multiplet<Quintet, Quintet>::Multiplet;

    Quintet& Quintet1() const
    {
        return Multiplet1();
    }

    Quintet& Quintet2() const
    {
        return Multiplet2();
    }

};

class Decuplet73 : public Multiplet<analysis::toppartner::Septet, analysis::Triplet> {

public:

    using Multiplet<Septet, Triplet>::Multiplet;

    analysis::toppartner::Septet& Septet() const
    {
        return Multiplet1();
    }

    analysis::Triplet& Triplet() const
    {
        return Multiplet2();
    }

};

class Decuplet82 : public Multiplet<Octet53, analysis::Doublet> {

public:

  using Multiplet<Octet53, analysis::Doublet>::Multiplet;

  Octet53& Octet() const
  {
    return Multiplet1();
  }

  analysis::Doublet& Doublet() const
  {
    return Multiplet2();
  }

};

}

}
