# pragma once

# include "../Leptons.hh"
# include "JetInfo.hh"

namespace analysis
{

namespace delphes
{

/**
 * @brief Delphes leptons
 *
 */
class Leptons : public analysis::Leptons
{

public:

    Leptons();

protected:

    inline std::string NameSpaceName() const {
        return "delphes";
    }

private:

  analysis::Jets Electrons();

    analysis::Jets Electrons(JetDetail jet_detail);

    analysis::Jets Muons();

    analysis::Jets Muons(JetDetail jet_detail);


};

}

}
