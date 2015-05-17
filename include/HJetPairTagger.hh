# ifndef HJetPairTagger_hh
# define HJetPairTagger_hh

# include "BottomTagger.hh"
# include "Doublet.hh"
# include "Reader.hh"

/**
 * @brief JetPair BDT tagger
 *
 */
class analysis::HJetPairTagger : public Tagger
{

public:

    HJetPairTagger();

    void SetTagger(const analysis::BottomTagger &NewBottomTagger);

    std::vector< EventJetPairBranch> GetBranches(analysis::Event &event, const analysis::Object::Tag Tag, const analysis::Object::HParticleId MotherId = GluonId);

    std::vector<Doublet> GetBdt(const Jets &jets, const analysis::Reader &JetPairReader);

    EventJetPairBranch GetBranch(const analysis::Doublet &doublet) const;

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

    analysis::Object::Tag GetTag(const Doublet &);

    EventJetPairBranch Branch;

    HJetTag JetTag;

};

#endif
