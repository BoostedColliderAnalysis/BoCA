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

    std::vector< HEventJetPairBranch> GetBranches(hanalysis::HEvent &Event, const hanalysis::HObject::HTag Tag);

    std::vector<HDoublet> GetBdt(const HJets &Jets, const hanalysis::HReader &JetPairReader);

    HEventJetPairBranch GetBranch(const hanalysis::HDoublet &Doublet) const;

    HBottomTagger BottomTagger;

    HReader BottomReader;

protected:

    virtual inline std::string ClassName() const {
        return "HJetPairTagger";
    }

private:

    void DefineVariables();

    hanalysis::HObject::HTag GetTag(const HDoublet &Doublet);

    HEventJetPairBranch Branch;

    HJetTag JetTag;

};

#endif
