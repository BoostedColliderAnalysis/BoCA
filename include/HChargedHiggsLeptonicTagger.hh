# pragma once

# include "Triplet.hh"
# include "HTopLeptonicTagger.hh"

namespace analysis {

/**
 * @brief Leptonic heavy higgs BDT tagger
 *
 */
class HChargedHiggsLeptonicTagger : public Tagger
{

public:

    HChargedHiggsLeptonicTagger(const BottomTagger &NewBottomTagger, const HTopLeptonicTagger &NewTopLeptonicTagger);

    ~HChargedHiggsLeptonicTagger();

    std::vector< HChargedHiggsLeptonicBranch > GetBranches(Event &event, const Object::Tag Tag);

    HChargedHiggsLeptonicBranch GetBranch(const Triplet &triplet);

    std::vector<Triplet> GetBdt(const std::vector< Doublet > &doublets, const Jets &jets, const Reader & Reader);

protected:

    virtual inline std::string ClassName() const {
        return "HChargedHiggsLeptonicTagger";
    }

private:

    void DefineVariables();

    Object::Tag GetTag(const Triplet &triplet);


    BottomTagger bottom_tagger_;
    HTopLeptonicTagger TopLeptonicTagger;

    Reader BottomReader;
    Reader TopLeptonicReader;

    HChargedHiggsLeptonicBranch Branch;

    JetTag jet_tag;

};

}
