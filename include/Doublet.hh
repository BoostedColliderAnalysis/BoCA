/**
 * Copyright (C) 2015 Jan Hajer
 */
#pragma once

#include "TwoBody.hh"
#include "Singlet.hh"

namespace boca {

class Doublet : public TwoBody<Singlet, Singlet> {

public:

    using TwoBody<Singlet, Singlet>::TwoBody;

    Singlet const& Singlet1() const;

    Singlet const& Singlet2() const;

    float Dipolarity2() const;

private:

};

}
