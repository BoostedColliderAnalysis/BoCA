# pragma once

# include "FourVector.hh"

namespace analysis {

/**
 * @brief particles for HAnalysis
 *
 */
class Partons : public FourVector
{

public:

    Partons();

    virtual ~Partons(){};

    void NewEvent(const analysis::ClonesArrays &clones_arrays);

    virtual Jets Particles() = 0;

    virtual Jets GenParticles() = 0;

protected:

    virtual inline std::string ClassName() const {
        return ("Partons");
    }

private:

};

}
