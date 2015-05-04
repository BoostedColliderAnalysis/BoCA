# pragma once

# include "HMva.hh"
# include "HBranch.hh"
# include "HEvent.hh"
# include "HJetTag.hh"
# include "HReader.hh"
# include "HEvent.hh"
# include "HAnalysis.hh"

/**
 * @brief Bottom BDT tagger
 *
 */

namespace hbtagger{
class HBottomTaggerSimple : public hanalysis::HMva
{

public:

    HBottomTaggerSimple();

    HBottomTaggerSimple(const std::string &ProjectName);

    void SetTagger();

    std::vector< HBottomBranch > GetBranches(hanalysis::HEvent &Event, const hanalysis::HObject::HTag Tag);

//     HJets GetMultiJetBdt(HJets &Jets, const hanalysis::HReader &BottomReader);

    HBottomBranch GetBranch(const fastjet::PseudoJet &Jet) const;

    hanalysis::HObject::HTag GetTag(const fastjet::PseudoJet &Jet) const;

    HJets GetJetBdt(const HJets &Jets, const hanalysis::HReader &BottomReader);

//     HJets GetSubBdt(const HJets &Jets, const hanalysis::HReader &BottomReader, const int SubJetNumber);

    float ReadBdt(const TClonesArray &EventClonesArray, const int Entry){
      return ((HBottomBranch *) EventClonesArray.At(Entry))->Bdt;
    }

//     ExRootTreeBranch *SetBranch(ExRootTreeWriter &NewTreeWriter, const hanalysis::HAnalysis::HStage Stage) {
//       switch(Stage){
//         case hanalysis::HAnalysis::HTrainer :
//           return NewTreeWriter.NewBranch(GetTaggerName().c_str(), HBottomBranch::Class());
//         case hanalysis::HAnalysis::HReader :
//           return NewTreeWriter.NewBranch(ReaderName().c_str(), HBottomBranch::Class());
//       }
//     }

//     void SetTreeBranch(ExRootTreeWriter &NewTreeWriter, const hanalysis::HAnalysis::HStage Stage) {
//       switch(Stage){
//         case hanalysis::HAnalysis::HTrainer :
//           TreeBranch = NewTreeWriter.NewBranch(GetTaggerName().c_str(), HBottomBranch::Class());
//         case hanalysis::HAnalysis::HReader :
//           TreeBranch = NewTreeWriter.NewBranch(ReaderName().c_str(), HBottomBranch::Class());
//       }
//     }


//     ExRootTreeBranch *SetReaderBranch(ExRootTreeWriter &NewTreeWriter) {
//         return NewTreeWriter.NewBranch(ReaderName().c_str(), HBottomBranch::Class());
//     }

//     bool SetBranch(hanalysis::HEvent &Event, const HTag Tag) {
//         std::vector<HBottomBranch> Bottoms = GetBranches(Event, Tag);
//         if (Bottoms.size() < 1) return 0;
//         for (const auto & Bottom : Bottoms) *static_cast<HBottomBranch *>(TreeBranch->NewEntry()) = Bottom;
//         return 1;
//     }

//     bool GetBottomReader(hanalysis::HEvent &Event, const HTag Tag)
//     {
//       Print(HDebug, "Get Bottom Reader", Tag);
//       HJets Jets = GetJets(Event);
//       hanalysis::HReader Reader; // this wont work
//       Jets = GetJetBdt(Jets, Reader);
//
//       HJets Particles = Event.GetParticles()->Generator();
//       Particles.erase(std::remove_if(Particles.begin(), Particles.end(), WrongAbsId(BottomId)), Particles.end());
//
//       for (const auto & Particle : Particles) {
//         std::sort(Jets.begin(), Jets.end(), MinDeltaR(Particle));
//         static_cast<hanalysis::HJetInfo *>(Jets.front().user_info_shared_ptr().get())->SetTag(HSignal);
//       }
//
//       for (const auto & Jet : Jets) {
//         if (Tag != Jet.user_info<hanalysis::HJetInfo>().Tag()) continue;
//         if (std::abs(Jet.rap()) > DetectorGeometry.TrackerEtaMax) continue;
//         *static_cast<HBottomBranch *>(TreeBranch->NewEntry()) = GetBranch(Jet);
//       }
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

    hanalysis::HJetTag JetTag;

};
}
