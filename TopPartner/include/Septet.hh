#pragma once

#include "Quintet.hh"

namespace analysis {

namespace toppartner {

class Septet : public TwoBody<analysis::Quintet, analysis::Doublet> {

public:

    using TwoBody<analysis::Quintet, analysis::Doublet>::TwoBody;

    analysis::Quintet Quintet() const
    {
        return Multiplet1();
    }

    analysis::Doublet Doublet() const
    {
        return Multiplet2();
    }

};

}

}
