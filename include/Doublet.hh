#pragma once

#include "TwoBody.hh"
#include "Singlet.hh"
#include "Vector2.hh"

namespace analysis {

class Doublet : public TwoBody<Singlet, Singlet> {

public:

    using TwoBody<Singlet, Singlet>::TwoBody;

    Singlet& Singlet1() const;

    Singlet& Singlet2() const;

    float Dipolarity2() const;

private:

};

}
