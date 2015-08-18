#pragma once

#include "Quintet.hh"
#include "Quartet.hh"

namespace boca {

namespace toppartner {

class Nonet : public TwoBody<boca::Quintet, boca::Quartet22> {

public:

    using TwoBody<boca::Quintet, boca::Quartet22>::TwoBody;

    boca::Quintet Quintet() const
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
