# pragma once

# include "Triplet.hh"
# include "TopLeptonicTagger.hh"
# include "Branch.hh"

namespace heavyhiggs {

/**
 * @brief Leptonic heavy higgs BDT tagger
 *
 */
class ChargedHiggsLeptonicTagger : public analysis::Tagger
{

public:

    ChargedHiggsLeptonicTagger();

    int Train(analysis::Event& event, const analysis::Object::Tag tag);

    std::vector<analysis::Triplet> Multiplets(analysis::Event& event, const TMVA::Reader& reader);

protected:

    virtual inline std::string ClassName() const {
        return "ChargedHiggsLeptonicTagger";
    }

private:

    void DefineVariables();

    analysis::BottomTagger bottom_tagger_;

    analysis::TopLeptonicTagger top_leptonic_tagger_;

    analysis::Reader bottom_reader_;

    analysis::Reader top_leptonic_reader_;

    ChargedHiggsLeptonicBranch branch_;

};

}
