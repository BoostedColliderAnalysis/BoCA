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
class hanalysis::HChargedHiggsLeptonicTagger : public Tagger
{

public:

    HChargedHiggsLeptonicTagger(const hanalysis::HBottomTagger &NewBottomTagger, const hanalysis::HTopLeptonicTagger &NewTopLeptonicTagger);

    ~HChargedHiggsLeptonicTagger();

    std::vector< HChargedHiggsLeptonicBranch > GetBranches(hanalysis::HEvent &Event, const hanalysis::HObject::Tag Tag);

    HChargedHiggsLeptonicBranch GetBranch(const hanalysis::HTriplet &Triplet);

    std::vector<hanalysis::HTriplet> GetBdt(const std::vector< hanalysis::HDoublet > &Doublets, const std::vector<fastjet::PseudoJet> Jets, const hanalysis::Reader & Reader);

protected:

    virtual inline std::string ClassName() const {
        return "HChargedHiggsLeptonicTagger";
    }

private:

    void DefineVariables();

    hanalysis::HObject::Tag GetTag(const hanalysis::HTriplet &Triplet);


    HBottomTagger BottomTagger;
    HTopLeptonicTagger TopLeptonicTagger;

    Reader BottomReader;
    Reader TopLeptonicReader;

    HChargedHiggsLeptonicBranch Branch;

    HJetTag JetTag;

};

#endif
