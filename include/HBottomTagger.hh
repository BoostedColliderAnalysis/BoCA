# ifndef HBottomTagger_hh
# define HBottomTagger_hh

# include "Tagger.hh"
# include "HBranch.hh"
# include "Event.hh"
# include "HJetTag.hh"
# include "Reader.hh"
# include "Event.hh"
# include "Analysis.hh"

/**
 * @brief Bottom BDT tagger
 *
 */
class analysis::HBottomTagger : public Tagger
{

public:

    HBottomTagger();

    HBottomTagger(const std::string &ProjectName);

    void SetTagger();

    std::vector< BottomBranch > GetBranches(analysis::Event &event, const analysis::Object::Tag Tag);

    Jets GetMultiJetBdt(Jets &jets, const analysis::Reader &BottomReader);

    BottomBranch GetBranch(const fastjet::PseudoJet &Jet) const;

    analysis::Object::Tag GetTag(const fastjet::PseudoJet &Jet) const;

    Jets GetJetBdt(const Jets &jets, const analysis::Reader &BottomReader);

    Jets GetSubBdt(const Jets &jets, const analysis::Reader &BottomReader, const int SubJetNumber);

    float ReadBdt(const TClonesArray &eventClonesArray, const int Entry) {
        return ((BottomBranch *) eventClonesArray.At(Entry))->Bdt;
    }

    TClass &Class() const {
        return *BottomBranch::Class();
    }

//     ExRootTreeBranch *SetBranch(ExRootTreeWriter &NewTreeWriter, const HStage stage) {
//       switch(Stage){
//         case kTrainer :
//           return NewTreeWriter.NewBranch(tagger_name().c_str(), BottomBranch::Class());
//         case kReader :
//           return NewTreeWriter.NewBranch(reader_name().c_str(), BottomBranch::Class());
//       }
//     }

//     void SetTreeBranch(ExRootTreeWriter &NewTreeWriter, const analysis::HAnalysis::HStage stage) {
//       SetTreeBranch(NewTreeWriter,*BottomBranch::Class(),Stage);
//     }


//     ExRootTreeBranch *SetReaderBranch(ExRootTreeWriter &NewTreeWriter) {
//         return NewTreeWriter.NewBranch(ReaderName().c_str(), BottomBranch::Class());
//     }

//     bool SetBranch(analysis::Event &event, const HTag Tag) {
//         std::vector<BottomBranch> Bottoms = GetBranches(event, Tag);
//         if (Bottoms.empty()) return 0;
//         for (const auto & Bottom : Bottoms) *static_cast<BottomBranch *>(TreeBranch->NewEntry()) = Bottom;
//         return 1;
//     }

//     bool GetBottomReader(analysis::Event &event, const HTag Tag)
//     {
//       Print(kDebug, "Get Bottom Reader", Tag);
//       Jets jets = GetJets(event);
//       Reader Reader; // this wont work
//       jets = GetJetBdt(jets, Reader);
//
//       Jets Particles = event.partons().Generator();
//       Particles.erase(std::remove_if(Particles.begin(), Particles.end(), WrongAbsId(BottomId)), Particles.end());
//
//       for (const auto & Particle : Particles) {
//         std::sort(jets.begin(), jets.end(), MinDeltaR(Particle));
//         static_cast<analysis::JetInfo *>(jets.front().user_info_shared_ptr().get())->SetTag(kSignal);
//       }
//
//       for (const auto & Jet : jets)  {
//         if (Tag != Jet.user_info<analysis::JetInfo>().Tag()) continue;
//         if (std::abs(Jet.rap()) > detector_geometry().TrackerEtaMax) continue;
//         *static_cast<BottomBranch *>(TreeBranch->NewEntry()) = GetBranch(Jet);
//       }
//       return 1;
//     }

//     void PrepareReader(){
//       Reader.set_tagger(*this);
//     }
protected:

    virtual inline std::string ClassName() const {
        return "HBottomTagger";
    };

private:

    void DefineVariables();

    Jets CleanJets(Jets &jets, const Jets &Particles, const analysis::Object::Tag Tag);


    Jets GetSubJets(const Jets &jets, const Jets &Particles, const Tag Tag, const int SubJetNumber);


    float GetDeltaR(const fastjet::PseudoJet &Jet) const;

    float GetSpread(const fastjet::PseudoJet &Jet) const;

    BottomBranch Branch;

    HJetTag JetTag;

};

#endif
