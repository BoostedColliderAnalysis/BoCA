/**
 * Copyright (C) 2015 Jan Hajer
 */
#pragma once

#include "TwoBody.hh"
#include "Singlet.hh"

namespace boca {

class Doublet : public TwoBody<boca::Singlet, boca::Singlet> {

public:

    using TwoBody<boca::Singlet, boca::Singlet>::TwoBody;

    boca::Singlet const& Singlet1() const;

    boca::Singlet const& Singlet2() const;

private:

};

}
