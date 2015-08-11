#pragma once

#include "TwoBody.hh"
#include "Singlet.hh"

namespace analysis {

class Doublet : public TwoBody<Singlet, Singlet> {

public:

    using TwoBody<Singlet, Singlet>::TwoBody;

    const Singlet& Singlet1() const;

    const Singlet& Singlet2() const;

    float Dipolarity2() const;

private:

};

}
