# ifndef HTauTagger_hh
# define HTauTagger_hh

# include "Tagger.hh"
# include "Branch.hh"
# include "HEvent.hh"
# include "HJetTag.hh"
# include "Reader.hh"
# include "HEvent.hh"

/**
 * @brief Bottom BDT tagger
 *
 */
class hanalysis::HTauTagger : public Tagger
{

public:

    HTauTagger();

    ~HTauTagger();

    void SetTagger();

    std::vector< HTauBranch > GetBranches(hanalysis::HEvent &Event, const hanalysis::HObject::Tag Tag);

    Jets GetBdt(Jets &jets, const hanalysis::Reader &BottomReader);

    HTauBranch GetBranch(const fastjet::PseudoJet &Jet) const;

//     hanalysis::HObject::HTag GetTag(const fastjet::PseudoJet &Jet) const;

    Jets GetJetBdt(const Jets &jets, const hanalysis::Reader &BottomReader);

    Jets GetSubBdt(const Jets &jets, const hanalysis::Reader &BottomReader, const int SubJetNumber);

protected:

    virtual inline std::string ClassName() const {
        return "HTauTagger";
    };

private:

    void DefineVariables();

    Jets CleanJets(Jets &jets, const Jets &Particles, const hanalysis::HObject::Tag Tag);

    Jets GetSubJets(const Jets &jets,const Jets &Particles, const Tag Tag, const int SubJetNumber);


    float GetDeltaR(const fastjet::PseudoJet &Jet) const;

    float GetSpread(const fastjet::PseudoJet &Jet) const;

    HTauBranch Branch;

    HJetTag JetTag;

};

#endif
