#pragma once

#include "Quintet.hh"
#include "Quartet.hh"

namespace analysis {

namespace toppartner {

class Nonet : public TwoBody<analysis::Quintet, analysis::Quartet22> {

public:

    using TwoBody<analysis::Quintet, analysis::Quartet22>::TwoBody;

    analysis::Quintet Quintet() const
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
