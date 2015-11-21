/**
 * Copyright (C) 2015 Jan Hajer
 */
#pragma once

#include <vector>

namespace fastjet
{
class JetDefinition;
}

namespace boca
{

class Jet;

/**
 * @brief FastJet calculations
 *
 */
class Reconstruction
{

public:

    virtual void NewEvent();

protected:

    /**
     * @brief Get vecto of all fatjets
     *
     */
    std::vector<Jet> GetFatJets(std::vector<Jet> const&) const;

    /**
     * @brief Get vecto of all fatjets
     *
     */
    std::vector<Jet> GetFatJets(std::vector<Jet> const&, const fastjet::JetDefinition&) const;

    std::vector<Jet> GetMassDropJets(std::vector<Jet> const&) const;

    /**
     * @brief Get mass drop jet
     *
     */
    Jet GetMassDropJet(Jet const&) const;

    Jet GetMassDropJet(Jet const&, const float, const float) const;


    std::vector<Jet> GetSubjet_taggedJets(std::vector<Jet> const& FatJets) const;

    Jet GetSubjet_taggedJet(Jet const& FatJet) const;

    /**
     * @brief Filter Jets
     *
     */
    Jet GetFilteredJet(Jet const&);

    static bool JetIsBad(Jet const& Jet);

    std::vector<Jet> GetFatjet_tag(std::vector<Jet> &);

};

}
