# pragma once


# include "fastjet/JetDefinition.hh"
# include "Object.hh"

namespace analysis
{

/**
 * @brief FastJet calculations
 *
 */
class Reconstruction : public Object
{

public:

    /**
     * @brief constructor
     *
     */
    Reconstruction();

    virtual void NewEvent();

protected:

    /**
     * @brief Get vecto of all fatjets
     *
     */
    Jets GetFatJets(const Jets &) const;

    /**
     * @brief Get vecto of all fatjets
     *
     */
    Jets GetFatJets(const Jets &, const fastjet::JetDefinition &) const;

    Jets GetMassDropJets(const Jets &) const;

    /**
     * @brief Get mass drop jet
     *
     */
    fastjet::PseudoJet GetMassDropJet(const fastjet::PseudoJet &) const;

    fastjet::PseudoJet GetMassDropJet(const fastjet::PseudoJet &, const float, const float) const;


    Jets GetSubjet_taggedJets(const Jets &FatJets) const;

    fastjet::PseudoJet GetSubjet_taggedJet(const fastjet::PseudoJet &FatJet) const;

    /**
     * @brief Filter Jets
     *
     */
    fastjet::PseudoJet GetFilteredJet(const fastjet::PseudoJet &);

    static bool JetIsBad(const fastjet::PseudoJet &Jet);

    Jets GetFatjet_tag(Jets &);

    inline std::string ClassName() const {
        return "Reconstruction";
    }

};

}
