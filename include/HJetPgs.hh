# pragma once
# include "Hadrons.hh"

/**
 * @brief Pgs Jets
 *
 */
class analysis::hpgs::HJet : public analysis::Hadrons
{

public:

    /**
     * @brief constructor
     *
     */
    HJet();

    /**
     * @brief AnalyseJet calls AnalyseEFlow
     *
     * @return void
     */
    bool GetJets(const HJetDetails JetDetails);

private:

    inline std::string NameSpaceName() const {
        return "HPgs";
    }

    inline std::string ClassName() const {
        return "HJet";
    };

};
