# pragma once

# include "Tagger.hh"
# include "Branches.hh"
# include "Event.hh"
# include "JetTag.hh"
# include "Reader.hh"
# include "Event.hh"

namespace analysis {

/**
 * @brief Bottom BDT tagger
 *
 */
class TauTagger : public Tagger
{

public:

    TauTagger();

    std::vector< TauBranch > GetBranches(analysis::Event &event, const analysis::Object::Tag Tag);

    Jets GetBdt(Jets &jets, const analysis::Reader &BottomReader);

    TauBranch GetBranch(const fastjet::PseudoJet &Jet) const;

//     analysis::Object::HTag GetTag(const fastjet::PseudoJet &Jet) const;

    Jets GetJetBdt(const Jets &jets, const analysis::Reader &BottomReader);

    Jets GetSubBdt(const Jets &jets, const analysis::Reader &BottomReader, const int SubJetNumber);

protected:

    virtual inline std::string ClassName() const {
        return "TauTagger";
    }

private:

    void DefineVariables();

    Jets CleanJets(Jets &jets, const Jets &Particles, const analysis::Object::Tag Tag);

    Jets GetSubJets(const Jets &jets,const Jets &Particles, const Tag Tag, const int SubJetNumber);


    float GetDeltaR(const fastjet::PseudoJet &Jet) const;

    float GetSpread(const fastjet::PseudoJet &Jet) const;

    TauBranch branch_;

    JetTag jet_tag;

};

}
