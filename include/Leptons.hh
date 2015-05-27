# pragma once

# include <algorithm>

# include "ClonesArrays.hh"
# include "FourVector.hh"

namespace analysis
{

/**
 * @brief calculation regarding leptons
 *
 */
class Leptons : public FourVector
{

public:

    /**
     * @brief constructor
     *
     */
    Leptons();

    /**
     * @brief destructor
     *
     */
    virtual ~Leptons();

    void NewEvent(const ClonesArrays &clones_arrays);

    Jets leptons();

protected:

    /**
     * @brief Find the hardest of the light leptons
     *
     */
    virtual analysis::Jets Electrons() = 0;

    /**
     * @brief Find the hardest of the light leptons
     *
     */
    virtual analysis::Jets Muons() = 0;

private:

    virtual inline std::string ClassName() const {
        return ("Leptons");
    }

};

}
