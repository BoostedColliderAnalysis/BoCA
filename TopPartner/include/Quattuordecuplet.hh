#pragma once

#include "Decuplet.hh"
#include "Quartet.hh"

namespace boca {

namespace naturalness {

class Quattuordecuplet : public TwoBody<naturalness::Decuplet55, Quartet22> {

public:

    using TwoBody<naturalness::Decuplet55, Quartet22>::TwoBody;

    naturalness::Decuplet55 Decuplet() const
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
