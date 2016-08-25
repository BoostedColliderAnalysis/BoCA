#pragma once

#include "boca/multiplets/ThreeBody.hh"
#include "boca/multiplets/Quintet.hh"

namespace toppartner
{

class Duodecuplet552 : public ThreeBody<Quintet, Quintet, boca::Doublet>
{

public:

    using ThreeBody<Quintet, Quintet, boca::Doublet>::ThreeBody;

    Quintet Quintet_1() const {
        return Multiplet1();
    }

    Quintet Quintet_2() const {
        return Multiplet2();
    }

    boca::Doublet Doublet() const {
        return Multiplet3();
    }

};

}
