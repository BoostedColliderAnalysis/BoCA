# pragma once

# include "Quartet22.hh"
# include "Sextet.hh"

namespace analysis
{

/**
 * @brief Leptonic heavy higgs BDT tagger
 *
 */
class WimpMass : public Object
{

public:

    WimpMass();


    std::vector<analysis::Sextet> Sextets(const std::vector<Quartet22> &quartets, const fastjet::PseudoJet &missing_et);

    std::vector<analysis::Sextet> Sextet(const Quartet22 &quartet, const fastjet::PseudoJet &missing_et, const Jets &neutrinos, const Object::Tag tag);

    std::vector<analysis::Sextet> Sextets(const Quartet22 &quartet, const fastjet::PseudoJet &missing_et);

protected:

    virtual inline std::string ClassName() const {
        return "WimpMass";
    }

private:


    void SetMomentum(double momentum[4], const fastjet::PseudoJet &jet);

    inline fastjet::PseudoJet PseudoJet(const double Momentum[4]) const {
        // wimpmass (E,px,py,pz)
        // fastjet (px,py,pz,E)
        return fastjet::PseudoJet(Momentum[1], Momentum[2], Momentum[3], Momentum[0]);
    }

};

}
