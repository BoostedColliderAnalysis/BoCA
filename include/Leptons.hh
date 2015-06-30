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

    Leptons();

    virtual ~Leptons();

    void NewEvent(const ClonesArrays &clones_arrays);

    Jets leptons();

    virtual analysis::Jets Electrons() = 0;

    virtual analysis::Jets Muons() = 0;

protected:

private:

    virtual  std::string ClassName() const {
        return ("Leptons");
    }

};

}
