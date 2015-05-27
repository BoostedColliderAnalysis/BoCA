# pragma once

# include "../Leptons.hh"

namespace analysis
{

namespace exroot
{

/**
 * @brief PGS leptons
 *
 */
class Leptons : public analysis::Leptons
{

public:

protected:

    inline std::string NameSpaceName() const {
        return "exroot";
    }

private:

    analysis::Jets Electrons();


    analysis::Jets Muons();

};

}

}
