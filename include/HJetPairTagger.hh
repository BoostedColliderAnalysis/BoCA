# ifndef HJetPairTagger_hh
# define HJetPairTagger_hh

# include "HBottomTagger.hh"
# include "HDoublet.hh"

/**
 * @brief JetPair BDT tagger
 *
 */
class hanalysis::HJetPairTagger : public HMva
{

public:

    HJetPairTagger();

    ~HJetPairTagger();

    void SetTagger(const hanalysis::HBottomTagger &NewBottomTagger);

    void FillBranch(const HDoublet &Pair);

    std::vector< HEventJetPairBranch * > GetBranches(HEvent *const Event, const HObject::HTag Tag);

    std::vector<HDoublet> GetBdt(const HJets &Jets, const hanalysis::HReader &JetPairReader);

    void FillBranch(HEventJetPairBranch *const JetPairBranch, const hanalysis::HDoublet &Doublet);

protected:

    virtual inline std::string ClassName() const {
        return "HJetPairTagger";
    }

private:

    void DefineVariables();

    hanalysis::HObject::HTag GetTag(const HDoublet &Doublet);

    HBottomTagger BottomTagger;

    HReader BottomReader;

    HEventJetPairBranch Branch;

    HJetTag JetTag;

};

#endif
