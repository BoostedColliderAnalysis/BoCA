# pragma once

# include "../Leptons.hh"

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

    analysis::Jets Electrons();

    analysis::Jets Muons();

protected:

     std::string NameSpaceName() const {
        return "delphes";
    }

private:

    analysis::Jets Electrons(analysis::FourVector::JetDetail jet_detail);

    analysis::Jets Muons(analysis::FourVector::JetDetail jet_detail);


};

}

}
