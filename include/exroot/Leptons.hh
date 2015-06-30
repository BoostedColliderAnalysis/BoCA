#pragma once

#include "../Leptons.hh"

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

    analysis::Jets Electrons();


    analysis::Jets Muons();

protected:

     std::string NameSpaceName() const {
        return "exroot";
    }

private:

};

}

}
