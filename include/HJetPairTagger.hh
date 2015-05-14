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

    std::vector< EventJetPairBranch> GetBranches(hanalysis::Event &event, const hanalysis::HObject::Tag Tag, const hanalysis::HObject::HParticleId MotherId = GluonId);

    std::vector<Doublet> GetBdt(const Jets &jets, const hanalysis::Reader &JetPairReader);

    EventJetPairBranch GetBranch(const hanalysis::Doublet &doublet) const;

    float ReadBdt(const TClonesArray &eventClonesArray, const int Entry){
      return ((EventJetPairBranch *) eventClonesArray.At(Entry))->Bdt;
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

    EventJetPairBranch Branch;

    HJetTag JetTag;

};

#endif
