# ifndef HChargedHiggsLeptonicTagger_hh
# define HChargedHiggsLeptonicTagger_hh

# include "Triplet.hh"
// # include "HQuartet31.hh"
# include "HTopLeptonicTagger.hh"
// # include "WIMPMASS.h"

/**
 * @brief Leptonic heavy higgs BDT tagger
 *
 */
class hanalysis::HChargedHiggsLeptonicTagger : public Tagger
{

public:

    HChargedHiggsLeptonicTagger(const hanalysis::BottomTagger &NewBottomTagger, const hanalysis::HTopLeptonicTagger &NewTopLeptonicTagger);

    ~HChargedHiggsLeptonicTagger();

    std::vector< HChargedHiggsLeptonicBranch > GetBranches(hanalysis::HEvent &Event, const hanalysis::HObject::Tag Tag);

    HChargedHiggsLeptonicBranch GetBranch(const hanalysis::Triplet &triplet);

    std::vector<hanalysis::Triplet> GetBdt(const std::vector< hanalysis::Doublet > &doublets, const Jets &jets, const hanalysis::Reader & Reader);

protected:

    virtual inline std::string ClassName() const {
        return "HChargedHiggsLeptonicTagger";
    }

private:

    void DefineVariables();

    hanalysis::HObject::Tag GetTag(const hanalysis::Triplet &triplet);


    BottomTagger bottom_tagger_;
    HTopLeptonicTagger TopLeptonicTagger;

    Reader BottomReader;
    Reader TopLeptonicReader;

    HChargedHiggsLeptonicBranch Branch;

    HJetTag JetTag;

};

#endif
