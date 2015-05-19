# pragma once

# include "../Hadrons.hh"

namespace analysis
{

namespace exroot
{

/**
 * @brief Pgs Jets
 *
 */
class Hadrons : public analysis::Hadrons
{

public:

    /**
     * @brief AnalyseJet calls AnalyseEFlow
     *
     * @return void
     */
    bool GetJets(const JetDetail jet_detail);

private:

    inline std::string NameSpaceName() const {
        return "exroot";
    }

};

}

}
