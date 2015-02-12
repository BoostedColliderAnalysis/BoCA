# ifndef HBottomTagger_hh
# define HBottomTagger_hh

# include "HMva.hh"
# include "HBranch.hh"
# include "HEvent.hh"
# include "HJetTag.hh"
# include "HReader.hh"
# include "HEvent.hh"

/**
 * @brief Bottom BDT tagger
 *
 */
class hanalysis::HBottomTagger : public HMva
{

public:

    HBottomTagger();

    HBottomTagger(const std::string &ProjectName);

    void SetTagger();

    std::vector< HBottomBranch > GetBranches(hanalysis::HEvent &Event, const hanalysis::HObject::HTag Tag);

    HJets GetBdt(HJets &Jets, const hanalysis::HReader &BottomReader);

    HBottomBranch GetBranch(const fastjet::PseudoJet &Jet) const;

    hanalysis::HObject::HTag GetTag(const fastjet::PseudoJet &Jet) const;

    HJets GetJetBdt(const HJets &Jets, const hanalysis::HReader &BottomReader);

    HJets GetSubBdt(const HJets &Jets, const hanalysis::HReader &BottomReader, const int SubJetNumber);

    ExRootTreeBranch *SetBranch(ExRootTreeWriter &NewTreeWriter) {
        return NewTreeWriter.NewBranch(GetTaggerName().c_str(), HBottomBranch::Class());
    }

    ExRootTreeBranch *SetReaderBranch(ExRootTreeWriter &NewTreeWriter) {
        return NewTreeWriter.NewBranch(ReaderName().c_str(), HBottomBranch::Class());
    }

//     bool SetBranch(hanalysis::HEvent &Event, const HTag Tag){
//       std::vector<HBottomBranch> Bottoms = GetBranches(Event, Tag);
//       if (Bottoms.size() < 1) return 0;
//       for (const auto & Bottom : Bottoms) *static_cast<HBottomBranch *>(ExRootBranch->NewEntry()) = Bottom;
//       return 1;
//     }

//     void PrepareReader(){
//       Reader.SetMva(*this);
//     }

protected:

    virtual inline std::string ClassName() const {
        return "HBottomTagger";
    };

private:

    void DefineVariables();

    HJets CleanJets(HJets &Jets, const HJets &Particles, const hanalysis::HObject::HTag Tag);

    HJets GetSubJets(const HJets &Jets, const HJets &Particles, const HTag Tag, const int SubJetNumber);


    float GetDeltaR(const fastjet::PseudoJet &Jet) const;

    float GetSpread(const fastjet::PseudoJet &Jet) const;

    HBottomBranch Branch;

    HJetTag JetTag;

};

#endif
