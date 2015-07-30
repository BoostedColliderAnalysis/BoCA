#pragma once

#include "Triplet.hh"

namespace analysis {

class Quintet : public Multiplet<analysis::Triplet, analysis::Doublet> {

public:

    using Multiplet<analysis::Triplet, analysis::Doublet>::Multiplet;

    analysis::Doublet& Doublet() const;

    analysis::Triplet& Triplet() const;

};

}
