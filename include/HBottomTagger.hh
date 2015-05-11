# ifndef HBottomTagger_hh
# define HBottomTagger_hh

# include "Tagger.hh"
# include "HBranch.hh"
# include "HEvent.hh"
# include "HJetTag.hh"
# include "Reader.hh"
# include "HEvent.hh"
# include "HAnalysis.hh"

/**
 * @brief Bottom BDT tagger
 *
 */
class hanalysis::HBottomTagger : public Tagger
{

public:

    HBottomTagger();

    HBottomTagger(const std::string &ProjectName);

    void SetTagger();

    std::vector< BottomBranch > GetBranches(hanalysis::HEvent &Event, const hanalysis::HObject::Tag Tag);

    Jets GetMultiJetBdt(Jets &jets, const hanalysis::Reader &BottomReader);

    BottomBranch GetBranch(const fastjet::PseudoJet &Jet) const;

    hanalysis::HObject::Tag GetTag(const fastjet::PseudoJet &Jet) const;

    Jets GetJetBdt(const Jets &jets, const hanalysis::Reader &BottomReader);

    Jets GetSubBdt(const Jets &jets, const hanalysis::Reader &BottomReader, const int SubJetNumber);

    float ReadBdt(const TClonesArray &EventClonesArray, const int Entry) {
        return ((BottomBranch *) EventClonesArray.At(Entry))->Bdt;
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

//     void SetTreeBranch(ExRootTreeWriter &NewTreeWriter, const hanalysis::HAnalysis::HStage stage) {
//       SetTreeBranch(NewTreeWriter,*BottomBranch::Class(),Stage);
//     }


//     ExRootTreeBranch *SetReaderBranch(ExRootTreeWriter &NewTreeWriter) {
//         return NewTreeWriter.NewBranch(ReaderName().c_str(), BottomBranch::Class());
//     }

//     bool SetBranch(hanalysis::HEvent &Event, const HTag Tag) {
//         std::vector<BottomBranch> Bottoms = GetBranches(Event, Tag);
//         if (Bottoms.empty()) return 0;
//         for (const auto & Bottom : Bottoms) *static_cast<BottomBranch *>(TreeBranch->NewEntry()) = Bottom;
//         return 1;
//     }

//     bool GetBottomReader(hanalysis::HEvent &Event, const HTag Tag)
//     {
//       Print(kDebug, "Get Bottom Reader", Tag);
//       Jets jets = GetJets(Event);
//       Reader Reader; // this wont work
//       jets = GetJetBdt(jets, Reader);
//
//       Jets Particles = Event.GetParticles()->Generator();
//       Particles.erase(std::remove_if(Particles.begin(), Particles.end(), WrongAbsId(BottomId)), Particles.end());
//
//       for (const auto & Particle : Particles) {
//         std::sort(jets.begin(), jets.end(), MinDeltaR(Particle));
//         static_cast<hanalysis::JetInfo *>(jets.front().user_info_shared_ptr().get())->SetTag(kSignal);
//       }
//
//       for (const auto & Jet : jets)  {
//         if (Tag != Jet.user_info<hanalysis::JetInfo>().Tag()) continue;
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

    Jets CleanJets(Jets &jets, const Jets &Particles, const hanalysis::HObject::Tag Tag);


    Jets GetSubJets(const Jets &jets, const Jets &Particles, const Tag Tag, const int SubJetNumber);


    float GetDeltaR(const fastjet::PseudoJet &Jet) const;

    float GetSpread(const fastjet::PseudoJet &Jet) const;

    BottomBranch Branch;

    HJetTag JetTag;

};

#endif
