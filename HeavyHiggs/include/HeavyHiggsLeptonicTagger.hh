# pragma once

# include "Quartet22.hh"
# include "Sextet.hh"
# include "TopLeptonicTagger.hh"
# include "Branch.hh"

namespace heavyhiggs {

/**
 * @brief Leptonic heavy higgs BDT tagger
 *
 */
class HeavyHiggsLeptonicTagger : public analysis::Tagger
{

public:

    HeavyHiggsLeptonicTagger();

    int Train(analysis::Event& event, const analysis::Object::Tag tag);

    std::vector<analysis::Sextet> Multiplets(analysis::Event& event, const TMVA::Reader& reader);

protected:

    virtual inline std::string ClassName() const {
        return "HeavyHiggsLeptonicTagger";
    }

private:

    void DefineVariables();

    void SetMomentum(double momentum[4], const fastjet::PseudoJet& jet);

    inline fastjet::PseudoJet GetJet(const double Momentum[4]) const {
        // wimpmass (E,px,py,pz)
        // fastjet (px,py,pz,E)
        return fastjet::PseudoJet(Momentum[1], Momentum[2], Momentum[3], Momentum[0]);
    }

    std::vector<analysis::Sextet> sextet(const analysis::Quartet22& quartet, const fastjet::PseudoJet& missing_et, const analysis::Jets& neutrinos, const Object::Tag tag);

    std::vector<analysis::Sextet> Sextets(const analysis::Quartet22& quartet, const fastjet::PseudoJet& missing_et);

    analysis::TopLeptonicTagger top_leptonic_tagger_;

    analysis::Reader top_leptonic_reader_;

    HeavyHiggsLeptonicBranch branch_;

};

}
