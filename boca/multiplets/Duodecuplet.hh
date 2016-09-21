#pragma once

#include "boca/multiplets/ThreeBody.hh"
#include "boca/multiplets/Quintet.hh"
#include "boca/multiplets/Sextet.hh"

namespace boca
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

class Duodecuplet633 : public ThreeBody<Sextet42, Triplet, Triplet>
{

public:

    using ThreeBody<Sextet42, Triplet, Triplet>::ThreeBody;

    Sextet42 Sextet() const {
        return Multiplet1();
    }

    Triplet Triplet1() const {
        return Multiplet2();
    }

    Triplet Triplet2() const {
        return Multiplet3();
    }

};

}
