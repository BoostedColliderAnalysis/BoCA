/**
 * Copyright (C) 2015 Jan Hajer
 */
#pragma once

#include <vector>

namespace fastjet{
  class PseudoJet;
  class JetDefinition;
}


namespace boca {

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
    fastjet::PseudoJet GetMassDropJet(fastjet::PseudoJet const&) const;

    fastjet::PseudoJet GetMassDropJet(fastjet::PseudoJet const&, const float, const float) const;


    Jets GetSubjet_taggedJets(Jets const& FatJets) const;

    fastjet::PseudoJet GetSubjet_taggedJet(fastjet::PseudoJet const& FatJet) const;

    /**
     * @brief Filter Jets
     *
     */
    fastjet::PseudoJet GetFilteredJet(fastjet::PseudoJet const&);

    static bool JetIsBad(fastjet::PseudoJet const& Jet);

    Jets GetFatjet_tag(Jets&);

};

}
