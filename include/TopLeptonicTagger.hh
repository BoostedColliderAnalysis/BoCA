# pragma once

# include "BottomTagger.hh"
# include "Doublet.hh"
# include "Reader.hh"

namespace analysis {

/**
 * @brief Top leptonic BDT tagger
 *
 */
class TopLeptonicTagger : public Tagger
{

public:

    TopLeptonicTagger();

    int Train(analysis::Event& event, const analysis::Object::Tag tag);

    std::vector< Doublet> Multiplets(analysis::Event& event, const TMVA::Reader &reader);

protected:

    virtual inline std::string ClassName() const {
        return "top_leptonic_tagger";
    }

private:

    void DefineVariables();

    BottomTagger bottom_tagger_;

    Reader bottom_reader_;

    TopLeptonicBranch branch_;

};

}
