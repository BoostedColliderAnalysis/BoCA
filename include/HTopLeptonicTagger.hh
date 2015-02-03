# ifndef HTopLeptonicTagger_hh
# define HTopLeptonicTagger_hh

# include "HBottomTagger.hh"
# include "HDoublet.hh"

/**
 * @brief Top leptonic BDT tagger
 *
 */
class hanalysis::HTopLeptonicTagger : public HMva
{

public:

    HTopLeptonicTagger();

    HTopLeptonicTagger(const HBottomTagger &NewBottomTagger);

    ~HTopLeptonicTagger();

    std::vector< HTopLeptonicBranch > GetBranches(hanalysis::HEvent *const Event, const hanalysis::HObject::HTag Tag);

    std::vector< HDoublet> GetBdt(const HJets &Jets, HJets &Leptons, const hanalysis::HReader & Reader);

    HTopLeptonicBranch GetBranch(const hanalysis::HDoublet &Doublet);

protected:

    virtual inline std::string ClassName() const {
        return "HTopLeptonicTagger";
    };

private:

    void DefineVariables();

    HTag GetTag(const HDoublet &Doublet);

    HBottomTagger BottomTagger;

    HReader BottomReader;

    HTopLeptonicBranch Branch;

    HJetTag JetTag;

};

#endif
