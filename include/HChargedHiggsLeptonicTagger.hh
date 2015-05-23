# ifndef HChargedHiggsLeptonicTagger_hh
# define HChargedHiggsLeptonicTagger_hh

# include "Triplet.hh"
// # include "Quartet31.hh"
# include "HTopLeptonicTagger.hh"
// # include "WIMPMASS.h"

/**
 * @brief Leptonic heavy higgs BDT tagger
 *
 */
class analysis::HChargedHiggsLeptonicTagger : public Tagger
{

public:

    HChargedHiggsLeptonicTagger(const analysis::BottomTagger &NewBottomTagger, const analysis::HTopLeptonicTagger &NewTopLeptonicTagger);

    ~HChargedHiggsLeptonicTagger();

    std::vector< HChargedHiggsLeptonicBranch > GetBranches(analysis::Event &event, const analysis::Object::Tag Tag);

    HChargedHiggsLeptonicBranch GetBranch(const analysis::Triplet &triplet);

    std::vector<analysis::Triplet> GetBdt(const std::vector< analysis::Doublet > &doublets, const Jets &jets, const analysis::Reader & Reader);

protected:

    virtual inline std::string ClassName() const {
        return "HChargedHiggsLeptonicTagger";
    }

private:

    void DefineVariables();

    analysis::Object::Tag GetTag(const analysis::Triplet &triplet);


    BottomTagger bottom_tagger_;
    HTopLeptonicTagger TopLeptonicTagger;

    Reader BottomReader;
    Reader TopLeptonicReader;

    HChargedHiggsLeptonicBranch Branch;

    JetTag jet_tag;

};

#endif
