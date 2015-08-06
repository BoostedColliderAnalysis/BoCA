#pragma once
#include <vector>

namespace fastjet{
  class PseudoJet;
  class JetDefinition;
}


namespace analysis {

typedef std::vector<fastjet::PseudoJet> Jets;

/**
 * @brief FastJet calculations
 *
 */
class Reconstruction {

public:

    virtual void NewEvent();

protected:

    /**
     * @brief Get vecto of all fatjets
     *
     */
    Jets GetFatJets(const Jets&) const;

    /**
     * @brief Get vecto of all fatjets
     *
     */
    Jets GetFatJets(const Jets&, const fastjet::JetDefinition&) const;

    Jets GetMassDropJets(const Jets&) const;

    /**
     * @brief Get mass drop jet
     *
     */
    fastjet::PseudoJet GetMassDropJet(const fastjet::PseudoJet&) const;

    fastjet::PseudoJet GetMassDropJet(const fastjet::PseudoJet&, const float, const float) const;


    Jets GetSubjet_taggedJets(const Jets& FatJets) const;

    fastjet::PseudoJet GetSubjet_taggedJet(const fastjet::PseudoJet& FatJet) const;

    /**
     * @brief Filter Jets
     *
     */
    fastjet::PseudoJet GetFilteredJet(const fastjet::PseudoJet&);

    static bool JetIsBad(const fastjet::PseudoJet& Jet);

    Jets GetFatjet_tag(Jets&);

};

}
