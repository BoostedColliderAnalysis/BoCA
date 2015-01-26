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

    std::vector<HTopLeptonicBranch *> GetBranches(HEvent *const Event, const HObject::HTag Tag);

    void FillBranch(const HDoublet &Doublet);

    std::vector< HDoublet> GetBdt(const HJets &Jets, HJets &Leptons, const hanalysis::HReader & Reader);

    void FillBranch(HTopLeptonicBranch *const TopLeptonicBranch, const HDoublet &Doublet);

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
