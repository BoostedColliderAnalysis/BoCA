#pragma once

#include "Quintet.hh"

namespace boca {

namespace naturalness {

class Septet : public TwoBody<boca::Quintet, boca::Doublet> {

public:

    using TwoBody<boca::Quintet, boca::Doublet>::TwoBody;

    boca::Quintet Quintet() const
    {
        return Multiplet1();
    }

    boca::Doublet Doublet() const
    {
        return Multiplet2();
    }

};

}

}
