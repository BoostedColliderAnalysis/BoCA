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

    std::vector< HBottomBranch > GetBranches(hanalysis::HEvent &Event, const hanalysis::HObject::Tag Tag);

    HJets GetMultiJetBdt(HJets &Jets, const hanalysis::Reader &BottomReader);

    HBottomBranch GetBranch(const fastjet::PseudoJet &Jet) const;

    hanalysis::HObject::Tag GetTag(const fastjet::PseudoJet &Jet) const;

    HJets GetJetBdt(const HJets &Jets, const hanalysis::Reader &BottomReader);

    HJets GetSubBdt(const HJets &Jets, const hanalysis::Reader &BottomReader, const int SubJetNumber);

    float ReadBdt(const TClonesArray &EventClonesArray, const int Entry) {
        return ((HBottomBranch *) EventClonesArray.At(Entry))->Bdt;
    }

    TClass &Class() const {
        return *HBottomBranch::Class();
    }

//     ExRootTreeBranch *SetBranch(ExRootTreeWriter &NewTreeWriter, const HStage stage) {
//       switch(Stage){
//         case kTrainer :
//           return NewTreeWriter.NewBranch(tagger_name().c_str(), HBottomBranch::Class());
//         case kReader :
//           return NewTreeWriter.NewBranch(reader_name().c_str(), HBottomBranch::Class());
//       }
//     }

//     void SetTreeBranch(ExRootTreeWriter &NewTreeWriter, const hanalysis::HAnalysis::HStage stage) {
//       SetTreeBranch(NewTreeWriter,*HBottomBranch::Class(),Stage);
//     }


//     ExRootTreeBranch *SetReaderBranch(ExRootTreeWriter &NewTreeWriter) {
//         return NewTreeWriter.NewBranch(ReaderName().c_str(), HBottomBranch::Class());
//     }

//     bool SetBranch(hanalysis::HEvent &Event, const HTag Tag) {
//         std::vector<HBottomBranch> Bottoms = GetBranches(Event, Tag);
//         if (Bottoms.empty()) return 0;
//         for (const auto & Bottom : Bottoms) *static_cast<HBottomBranch *>(TreeBranch->NewEntry()) = Bottom;
//         return 1;
//     }

//     bool GetBottomReader(hanalysis::HEvent &Event, const HTag Tag)
//     {
//       Print(HDebug, "Get Bottom Reader", Tag);
//       HJets Jets = GetJets(Event);
//       Reader Reader; // this wont work
//       Jets = GetJetBdt(Jets, Reader);
//
//       HJets Particles = Event.GetParticles()->Generator();
//       Particles.erase(std::remove_if(Particles.begin(), Particles.end(), WrongAbsId(BottomId)), Particles.end());
//
//       for (const auto & Particle : Particles) {
//         std::sort(Jets.begin(), Jets.end(), MinDeltaR(Particle));
//         static_cast<hanalysis::HJetInfo *>(Jets.front().user_info_shared_ptr().get())->SetTag(kSignal);
//       }
//
//       for (const auto & Jet : Jets) {
//         if (Tag != Jet.user_info<hanalysis::HJetInfo>().Tag()) continue;
//         if (std::abs(Jet.rap()) > detector_geometry().TrackerEtaMax) continue;
//         *static_cast<HBottomBranch *>(TreeBranch->NewEntry()) = GetBranch(Jet);
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

    HJets CleanJets(HJets &Jets, const HJets &Particles, const hanalysis::HObject::Tag Tag);


    HJets GetSubJets(const HJets &Jets, const HJets &Particles, const Tag Tag, const int SubJetNumber);


    float GetDeltaR(const fastjet::PseudoJet &Jet) const;

    float GetSpread(const fastjet::PseudoJet &Jet) const;

    HBottomBranch Branch;

    HJetTag JetTag;

};

#endif
