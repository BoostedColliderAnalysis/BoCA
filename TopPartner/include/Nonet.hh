#pragma once

#include "Quintet.hh"
#include "Quartet.hh"

namespace analysis
{

namespace toppartner
{

  class Nonet : public Multiplet<analysis::Quintet, analysis::Quartet22>
{

public:

  using Multiplet<analysis::Quintet, analysis::Quartet22>::Multiplet;

   analysis::Quintet Quintet()const {
        return Multiplet1();
    }

     Quartet22 Quartet()const {
        return Multiplet2();
    }

};

}

}
