#pragma once

#include "Decuplet.hh"
#include "Quartet.hh"

namespace analysis
{

namespace toppartner
{

class Quattuordecuplet : public Multiplet<toppartner::Decuplet55, Quartet22>
{

public:

    using Multiplet<toppartner::Decuplet55, Quartet22>::Multiplet;

     toppartner::Decuplet55 Decuplet() const {
        return Multiplet1();
    }

     Quartet22 Quartet() const {
        return Multiplet2();
    }

};

}

}
