/**
 * Copyright (C) 2015 Jan Hajer
 */
#pragma once

#include "FourVector.hh"

namespace boca {

/**
 * @brief calculation regarding leptons
 *
 */
class Leptons : public FourVector {

public:

    virtual ~Leptons();

    void NewEvent(ClonesArrays const& clones_arrays);

    Jets leptons() const;

    virtual boca::Jets Electrons() const = 0;

    virtual boca::Jets Muons() const = 0;

};

}
