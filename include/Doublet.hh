#pragma once

#include "TwoBody.hh"
#include "Singlet.hh"

namespace analysis {

class Doublet : public TwoBody<Singlet, Singlet> {

public:

    using TwoBody<Singlet, Singlet>::TwoBody;

    Singlet const& Singlet1() const;

    Singlet const& Singlet2() const;

    float Dipolarity2() const;

private:

};

}
