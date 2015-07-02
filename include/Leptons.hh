#pragma once

#include "FourVector.hh"

namespace analysis
{

/**
 * @brief calculation regarding leptons
 *
 */
class Leptons : public FourVector
{

public:

    virtual ~Leptons();

    void NewEvent(const ClonesArrays &clones_arrays);

    Jets leptons() const;

    virtual analysis::Jets Electrons() const = 0;

    virtual analysis::Jets Muons() const = 0;

};

}
