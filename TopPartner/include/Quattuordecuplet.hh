#pragma once

#include "Decuplet.hh"
#include "Quartet.hh"

namespace analysis {

namespace toppartner {

class Quattuordecuplet : public TwoBody<toppartner::Decuplet55, Quartet22> {

public:

    using TwoBody<toppartner::Decuplet55, Quartet22>::TwoBody;

    toppartner::Decuplet55 Decuplet() const
    {
        return Multiplet1();
    }

    Quartet22 Quartet() const
    {
        return Multiplet2();
    }

};

}

}
