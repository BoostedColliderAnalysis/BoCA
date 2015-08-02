#pragma once

#include "Triplet.hh"

namespace analysis {

class Quintet : public TwoBody<analysis::Triplet, analysis::Doublet> {

public:

    using TwoBody<analysis::Triplet, analysis::Doublet>::TwoBody;

    const analysis::Doublet& Doublet() const;

    const analysis::Triplet& Triplet() const;

};

}
