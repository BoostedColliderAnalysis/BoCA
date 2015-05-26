# pragma once

# include "BottomTagger.hh"
# include "Doublet.hh"
# include "Reader.hh"

namespace analysis {

/**
 * @brief Top leptonic BDT tagger
 *
 */
class HTopLeptonicTagger : public Tagger
{

public:

    HTopLeptonicTagger();

    HTopLeptonicTagger(const BottomTagger &NewBottomTagger);

    ~HTopLeptonicTagger();

    std::vector< HTopLeptonicBranch > GetBranches(Event &event, const Object::Tag Tag);

    std::vector< Doublet> GetBdt(const Jets &jets, Jets &Leptons, const Reader & Reader);

    HTopLeptonicBranch GetBranch(const Doublet &doublet);

protected:

    virtual inline std::string ClassName() const {
        return "HTopLeptonicTagger";
    };

private:

    void DefineVariables();

    Tag GetTag(const Doublet &doublet);

    BottomTagger bottom_tagger_;

    Reader BottomReader;

    HTopLeptonicBranch Branch;

    JetTag jet_tag;

};

}
