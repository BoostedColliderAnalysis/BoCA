/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#pragma once

#include "multiplets/Triplet.hh"

namespace boca {

class Quintet : public TwoBody<boca::Triplet, boca::Doublet> {

public:

//     Quintet(){}
//
//     Quintet(boca::Triplet const& triplet){
//       SetMultiplet1(boca::Triplet(triplet.Singlet()));
//       SetMultiplet2(triplet.Doublet());
//     }

    using TwoBody<boca::Triplet, boca::Doublet>::TwoBody;

    boca::Doublet const& Doublet() const;

    boca::Triplet const& Triplet() const;

};

}
