# ifndef HChargedHiggsLeptonicTagger_hh
# define HChargedHiggsLeptonicTagger_hh

# include "HTriplet.hh"
// # include "HQuartet31.hh"
# include "HTopLeptonicTagger.hh"
// # include "WIMPMASS.h"

/**
 * @brief Leptonic heavy higgs BDT tagger
 *
 */
class hanalysis::HChargedHiggsLeptonicTagger : public HMva
{

public:

    HChargedHiggsLeptonicTagger(const hanalysis::HBottomTagger &NewBottomTagger, const hanalysis::HTopLeptonicTagger &NewTopLeptonicTagger);

    ~HChargedHiggsLeptonicTagger();

    std::vector< HChargedHiggsLeptonicBranch > GetBranches(hanalysis::HEvent *const Event, const hanalysis::HObject::HTag Tag);

    HChargedHiggsLeptonicBranch GetBranch(const hanalysis::HTriplet &Triplet);

    std::vector<hanalysis::HTriplet> GetBdt(const std::vector< hanalysis::HDoublet > &Doublets, const std::vector<fastjet::PseudoJet> Jets, const hanalysis::HReader & Reader);

protected:

    virtual inline std::string ClassName() const {
        return "HChargedHiggsLeptonicTagger";
    }

private:

    void DefineVariables();

    hanalysis::HObject::HTag GetTag(const hanalysis::HTriplet &Triplet);


    HBottomTagger BottomTagger;
    HTopLeptonicTagger TopLeptonicTagger;

    HReader BottomReader;
    HReader TopLeptonicReader;

    HChargedHiggsLeptonicBranch Branch;

    HJetTag JetTag;

};

#endif
