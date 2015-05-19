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

    /**
     * @brief Find the hardest of the light leptons
     *
     * @param ClonesArray ...
     * @return void
     */
    bool GetElectrons(JetDetail jet_detail);

    /**
     * @brief Find the hardest of the light leptons
     *
     * @param ClonesArray ...
     * @return void
     */
    bool GetMuons(JetDetail jet_detail);

};

}

}
