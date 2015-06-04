# pragma once

# include "Triplet.hh"
# include "TopLeptonicTagger.hh"

namespace analysis {

/**
 * @brief Leptonic heavy higgs BDT tagger
 *
 */
class ChargedHiggsLeptonicTagger : public Tagger
{

public:

    ChargedHiggsLeptonicTagger();

    int Train(analysis::Event& event, const analysis::Object::Tag tag);

    std::vector<Triplet> Multiplets(analysis::Event& event, const TMVA::Reader& reader);

protected:

    virtual inline std::string ClassName() const {
        return "ChargedHiggsLeptonicTagger";
    }

private:

    void DefineVariables();

    BottomTagger bottom_tagger_;

    TopLeptonicTagger top_leptonic_tagger_;

    Reader bottom_reader_;

    Reader top_leptonic_reader_;

    ChargedHiggsLeptonicBranch branch_;

};

}
