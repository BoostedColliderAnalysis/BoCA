# ifndef HTauTagger_hh
# define HTauTagger_hh

# include "Tagger.hh"
# include "Branches.hh"
# include "Event.hh"
# include "HJetTag.hh"
# include "Reader.hh"
# include "Event.hh"

/**
 * @brief Bottom BDT tagger
 *
 */
class analysis::HTauTagger : public Tagger
{

public:

    HTauTagger();

    ~HTauTagger();

    void SetTagger();

    std::vector< HTauBranch > GetBranches(analysis::Event &event, const analysis::Object::Tag Tag);

    Jets GetBdt(Jets &jets, const analysis::Reader &BottomReader);

    HTauBranch GetBranch(const fastjet::PseudoJet &Jet) const;

//     analysis::Object::HTag GetTag(const fastjet::PseudoJet &Jet) const;

    Jets GetJetBdt(const Jets &jets, const analysis::Reader &BottomReader);

    Jets GetSubBdt(const Jets &jets, const analysis::Reader &BottomReader, const int SubJetNumber);

protected:

    virtual inline std::string ClassName() const {
        return "HTauTagger";
    };

private:

    void DefineVariables();

    Jets CleanJets(Jets &jets, const Jets &Particles, const analysis::Object::Tag Tag);

    Jets GetSubJets(const Jets &jets,const Jets &Particles, const Tag Tag, const int SubJetNumber);


    float GetDeltaR(const fastjet::PseudoJet &Jet) const;

    float GetSpread(const fastjet::PseudoJet &Jet) const;

    HTauBranch Branch;

    HJetTag JetTag;

};

#endif
