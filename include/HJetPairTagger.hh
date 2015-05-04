# ifndef HJetPairTagger_hh
# define HJetPairTagger_hh

# include "HBottomTagger.hh"
# include "HDoublet.hh"

/**
 * @brief JetPair BDT tagger
 *
 */
class hanalysis::HJetPairTagger : public Tagger
{

public:

    HJetPairTagger();

    void SetTagger(const hanalysis::HBottomTagger &NewBottomTagger);

    std::vector< HEventJetPairBranch> GetBranches(hanalysis::HEvent &Event, const hanalysis::HObject::Tag Tag, const hanalysis::HObject::HParticleId MotherId = GluonId);

    std::vector<HDoublet> GetBdt(const HJets &Jets, const hanalysis::HReader &JetPairReader);

    HEventJetPairBranch GetBranch(const hanalysis::HDoublet &Doublet) const;

    float ReadBdt(const TClonesArray &EventClonesArray, const int Entry){
      return ((HEventJetPairBranch *) EventClonesArray.At(Entry))->Bdt;
    }

    HBottomTagger BottomTagger;

    HReader BottomReader;

protected:

    virtual inline std::string ClassName() const {
        return "HJetPairTagger";
    }

private:

    void DefineVariables();

    hanalysis::HObject::Tag GetTag(const HDoublet &);

    HEventJetPairBranch Branch;

    HJetTag JetTag;

};

#endif
