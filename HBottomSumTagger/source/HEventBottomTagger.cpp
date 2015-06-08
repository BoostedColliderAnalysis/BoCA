# include "HEventBottomTagger.hh"
# include "TClonesArray.h"

hbottomsumtagger::EventBottomTagger::EventBottomTagger()
{
    //   DebugLevel = kDebug;
    Print(kNotification , "Constructor");
    DefineVariables();
}

void hbottomsumtagger::EventBottomTagger::SetTagger(const analysis::BottomTagger &NewBottomTagger)
{
    Print(kNotification , "Constructor");

    bottom_tagger_ = NewBottomTagger;
    DefineVariables();
}

void hbottomsumtagger::EventBottomTagger::DefineVariables()
{
    Print(kNotification , "Define Variables");
    set_tagger_name("eventBottom");

    ClearVectors();


    AddVariable(Branch.BottomBdt1, "BottomBdt1");
    AddVariable(Branch.BottomBdt2, "BottomBdt2");
    AddVariable(Branch.BottomBdt3, "BottomBdt3");
    AddVariable(Branch.BottomBdt4, "BottomBdt4");
    AddVariable(Branch.BottomBdt5, "BottomBdt5");
    AddVariable(Branch.BottomBdt6, "BottomBdt6");

    AddVariable(Branch.BottomBdt12, "BottomBdt12");
    AddVariable(Branch.BottomBdt34, "BottomBdt34");
    AddVariable(Branch.BottomBdt56, "BottomBdt56");

    AddVariable(Branch.BottomBdt123, "BottomBdt123");
    AddVariable(Branch.BottomBdt1234, "BottomBdt1234");

    AddVariable(Branch.Bdt, "Bdt");
    AddSpectator(Branch.Tag, "Tag");


    Print(kNotification, "Variables defined");

}

analysis::EventBottomTaggerBranch hbottomsumtagger::EventBottomTagger::GetBranch(const EventBottomMultiplet &event) const
{
    Print(kInformation, "FillPairTagger", event.Bdt());

    analysis::EventBottomTaggerBranch eventSemiBranch;

    eventSemiBranch.Tag = event.Tag();

    eventSemiBranch.BottomBdt1 = event.TotalBottomBdt(1);
    eventSemiBranch.BottomBdt2 = event.TotalBottomBdt(2);
    eventSemiBranch.BottomBdt3 = event.TotalBottomBdt(3);
    eventSemiBranch.BottomBdt4 = event.TotalBottomBdt(4);
    eventSemiBranch.BottomBdt5 = event.TotalBottomBdt(5);
    eventSemiBranch.BottomBdt6 = event.TotalBottomBdt(6);

    eventSemiBranch.BottomBdt12 = event.TotalBottomBdt(1, 2);
    eventSemiBranch.BottomBdt34 = event.TotalBottomBdt(3, 4);
    eventSemiBranch.BottomBdt56 = event.TotalBottomBdt(5, 6);

    eventSemiBranch.BottomBdt123 = event.TotalBottomBdt(1, 2, 3);
    eventSemiBranch.BottomBdt1234 = event.TotalBottomBdt(1, 2, 3, 4);

    eventSemiBranch.Bdt = event.Bdt();
    eventSemiBranch.Tag = event.Tag();

    return eventSemiBranch;

}

// struct SortJetsByBdt {
//     inline bool operator()(const fastjet::PseudoJet &Jet1, const fastjet::PseudoJet &Jet2) {
//         return (Jet1.user_info<analysis::JetInfo>().Bdt() > Jet2.user_info<analysis::JetInfo>().Bdt());
//     }
// };


std::vector<analysis::EventBottomTaggerBranch> hbottomsumtagger::EventBottomTagger::GetBranches(analysis::Event &event, const Object::Tag Tag)
{
    Print(kInformation, "event Tags");

    analysis::Jets jets = event.Hadrons().Jets();
    //     Jets jets = bottom_tagger_.GetJetBdt(PreJets, BottomReader); // TODO reenable this
    std::vector<analysis::EventBottomTaggerBranch> eventSemiBranches;


//     const int JetNumber = 2;
//     const int SignalBottomNumber = 2;
//     const int BackgroundBottomNumber = 0;
//     if (jets.size() < JetNumber) return eventSemiBranches;
//     Jets BottomJets;
//     Jets Particles = event.Partons().GenParticles();
//     Particles = RemoveIfWrongAbsParticle(Particles, BottomId);
//     for (const auto & Particle : Particles) {
//         std::sort(jets.begin(), jets.end(), MinDeltaR(Particle));
//         if (jets.front().delta_R(Particle) < detector_geometry().JetConeSize)
//             BottomJets.emplace_back(jets.front());
//     }
//
//     if (Tag == kSignal && BottomJets.size() < SignalBottomNumber)  return eventSemiBranches;
//     if (Tag == HBackground && BottomJets.size() < BackgroundBottomNumber)  return eventSemiBranches;

    if (!TruthLevelCheck(jets,event, Tag)) return eventSemiBranches;


    EventBottomMultiplet eventMultiplet;
    eventMultiplet.SetJets(jets);

    eventMultiplet.SetTag(Tag);
    eventSemiBranches.emplace_back(GetBranch(eventMultiplet));

    return eventSemiBranches;
}

bool hbottomsumtagger::EventBottomTagger::TruthLevelCheck(const analysis::Jets &NewJets,analysis::Event &event, const Tag Tag)
{
    const unsigned JetNumber = 2;
    const unsigned SignalBottomNumber = 2;
    const unsigned BackgroundBottomNumber = 0;

    analysis::Jets jets = NewJets;

    if (jets.size() < JetNumber) return 0;
    analysis::Jets BottomJets;
    analysis::Jets Particles = event.Partons().GenParticles();
    Particles = RemoveIfWrongAbsParticle(Particles, BottomId);
    for (const auto & Particle : Particles) {
        std::sort(jets.begin(), jets.end(), analysis::MinDeltaRTo(Particle));
        if (jets.front().delta_R(Particle) < detector_geometry().JetConeSize)
            BottomJets.emplace_back(jets.front());
    }

    if (Tag == kSignal && BottomJets.size() < SignalBottomNumber)  return 0;
    if (Tag == kBackground && BottomJets.size() < BackgroundBottomNumber)  return 0;

    return 1;
}




std::vector<hbottomsumtagger::EventBottomMultiplet> hbottomsumtagger::EventBottomTagger::GetBdt(const analysis::Jets &jets, const analysis::Reader &eventSemiReader)
{
    Print(kInformation, "event Tags");

    std::vector<EventBottomMultiplet> eventMultiplets;

    EventBottomMultiplet eventMultiplet;
    eventMultiplet.SetJets(jets);
    Branch = GetBranch(eventMultiplet);
    eventMultiplet.SetBdt(eventSemiReader.Bdt());
    eventMultiplets.emplace_back(eventMultiplet);
    return eventMultiplets;
}

float hbottomsumtagger::EventBottomTagger::ReadBdt(const TClonesArray &clones_array, const int Entry)
{
  return ((analysis::EventBottomTaggerBranch *) clones_array.At(Entry))->Bdt;
}


// std::vector<int> hbottomsumtagger::EventBottomTagger::ApplyBdt2(const exroot::TreeReader *const TreeReader, const std::string TreeName, const TFile *const ExportFile)
// {
//     Print(kNotification, "Apply Bdt", eventBranchName);
//     std::string NeweventBranchName = eventBranchName + "Reader";
//     const int Steps = 20;
//     std::vector<int> eventNumbers(Steps, 0);
//
//     const int BinSum = 100;
//     std::vector<int> Bins(BinSum, 0);
//
//     const TClonesArray *const eventClonesArray = const_cast<exroot::TreeReader *>(TreeReader)->UseBranch(NeweventBranchName.c_str());
//     exroot::TreeWriter *TreeWriter = new exroot::TreeWriter(const_cast<TFile *>(ExportFile), TreeName.c_str());
//     exroot::TreeBranch *ResultBranch = TreeWriter->NewBranch(NeweventBranchName.c_str(), HResultBranch::Class());
//     for (const int eventNumber : HRange(const_cast<exroot::TreeReader *>(TreeReader)->GetEntries())) {
//         const_cast<exroot::TreeReader *>(TreeReader)->ReadEntry(eventNumber);
//         for (const int Entry : HRange(eventClonesArray->GetEntriesFast())) {
//             EventBottomTaggerBranch *Test = (EventBottomTaggerBranch *) eventClonesArray->At(Entry);
//             const float Bdt = Test->Bdt;
//             HResultBranch *Export = static_cast<HResultBranch *>(ResultBranch->NewEntry());
//             Export->Bdt = Bdt;
//
//             ++Bins.at(floor(Bdt * BinSum / 2));
//
//             for (int Step = 0; Step < Steps; ++Step) {
//                 const float CutValue = (float(Step) / Steps + 1);
//                 if (Bdt > CutValue) ++eventNumbers.at(Step);
//             }
//         }
//         TreeWriter->Fill();
//         TreeWriter->Clear();
//     }
//     TreeWriter->Write();
//     delete TreeWriter;
//
//     return eventNumbers;
// }
