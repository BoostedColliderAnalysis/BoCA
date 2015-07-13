#pragma once

#include "Septet.hh"

namespace analysis {

namespace toppartner
{

class Decuplet55 : public Multiplet<Quintet, Quintet>
{

public:

    using Multiplet<Quintet, Quintet>::Multiplet;

     Quintet Quintet1() const {
        return Multiplet1();
    }

     Quintet Quintet2() const {
        return Multiplet2();
    }

};

class Decuplet73 : public Multiplet<Septet, Triplet>
{

public:

  using Multiplet<Septet, Triplet>::Multiplet;

   Septet Quintet1() const {
    return Multiplet1();
  }

   Triplet Quintet2() const {
    return Multiplet2();
  }

};

}

}
