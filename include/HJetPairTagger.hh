# ifndef HJetPairTagger_hh
# define HJetPairTagger_hh

# include "BottomTagger.hh"
# include "Doublet.hh"
# include "Reader.hh"

/**
 * @brief JetPair BDT tagger
 *
 */
class hanalysis::HJetPairTagger : public Tagger
{

public:

    HJetPairTagger();

    void SetTagger(const hanalysis::BottomTagger &NewBottomTagger);

    std::vector< HEventJetPairBranch> GetBranches(hanalysis::HEvent &Event, const hanalysis::HObject::Tag Tag, const hanalysis::HObject::HParticleId MotherId = GluonId);

    std::vector<Doublet> GetBdt(const Jets &jets, const hanalysis::Reader &JetPairReader);

    HEventJetPairBranch GetBranch(const hanalysis::Doublet &doublet) const;

    float ReadBdt(const TClonesArray &EventClonesArray, const int Entry){
      return ((HEventJetPairBranch *) EventClonesArray.At(Entry))->Bdt;
    }

    BottomTagger bottom_tagger_;

    Reader BottomReader;

protected:

    virtual inline std::string ClassName() const {
        return "HJetPairTagger";
    }

private:

    void DefineVariables();

    hanalysis::HObject::Tag GetTag(const Doublet &);

    HEventJetPairBranch Branch;

    HJetTag JetTag;

};

#endif
