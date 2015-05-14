# pragma once
# include "HJet.hh"

/**
 * @brief Pgs Jets
 *
 */
class hanalysis::hpgs::HJet : public hanalysis::HJet
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
