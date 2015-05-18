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


    /**
     * @brief constructor
     *
     */
    Leptons();

private:

    /**
     * @brief Find the hardest of the light leptons
     *
     * @param ClonesArray ...
     * @return void
     */
    bool GetElectrons();

    bool GetElectrons(HJetDetails JetDetails);

    /**
     * @brief Find the hardest of the light leptons
     *
     * @param ClonesArray ...
     * @return void
     */
    bool GetMuons();

    bool GetMuons(HJetDetails JetDetails);

//   Jets GetLeptons(HJetDetails JetDetails);

    inline std::string NameSpaceName() const {
        return "HDelphes";
    }

    inline std::string ClassName() const {
        return "HLepton";
    };

};

}

}
