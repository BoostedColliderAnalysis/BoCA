# include "HEventBottomTagger.hh"

hbottomsumtagger::HEventBottomTagger::HEventBottomTagger()
{
    //   DebugLevel = HDebug;
    Print(HNotification , "Constructor");
    DefineVariables();
}

void hbottomsumtagger::HEventBottomTagger::SetTagger(const hanalysis::HBottomTagger &NewBottomTagger)
{
    Print(HNotification , "Constructor");

    BottomTagger = NewBottomTagger;
    DefineVariables();
}

void hbottomsumtagger::HEventBottomTagger::DefineVariables()
{
    Print(HNotification , "Define Variables");
    SetTaggerName("EventBottom");

    ClearVectors();


    AddObservable(Branch.BottomBdt1, "BottomBdt1");
    AddObservable(Branch.BottomBdt2, "BottomBdt2");
    AddObservable(Branch.BottomBdt3, "BottomBdt3");
    AddObservable(Branch.BottomBdt4, "BottomBdt4");
    AddObservable(Branch.BottomBdt5, "BottomBdt5");
    AddObservable(Branch.BottomBdt6, "BottomBdt6");

    AddObservable(Branch.BottomBdt12, "BottomBdt12");
    AddObservable(Branch.BottomBdt34, "BottomBdt34");
    AddObservable(Branch.BottomBdt56, "BottomBdt56");

    AddObservable(Branch.BottomBdt123, "BottomBdt123");
    AddObservable(Branch.BottomBdt1234, "BottomBdt1234");

    AddObservable(Branch.Bdt, "Bdt");
    AddSpectator(Branch.Tag, "Tag");


    Print(HNotification, "Variables defined");

}

HEventBottomTaggerBranch hbottomsumtagger::HEventBottomTagger::GetBranch(const HEventBottomMultiplet &Event) const
{
    Print(HInformation, "FillPairTagger", Event.Bdt());

    HEventBottomTaggerBranch EventSemiBranch;

    EventSemiBranch.Tag = Event.Tag();

    EventSemiBranch.BottomBdt1 = Event.TotalBottomBdt(1);
    EventSemiBranch.BottomBdt2 = Event.TotalBottomBdt(2);
    EventSemiBranch.BottomBdt3 = Event.TotalBottomBdt(3);
    EventSemiBranch.BottomBdt4 = Event.TotalBottomBdt(4);
    EventSemiBranch.BottomBdt5 = Event.TotalBottomBdt(5);
    EventSemiBranch.BottomBdt6 = Event.TotalBottomBdt(6);

    EventSemiBranch.BottomBdt12 = Event.TotalBottomBdt(1, 2);
    EventSemiBranch.BottomBdt34 = Event.TotalBottomBdt(3, 4);
    EventSemiBranch.BottomBdt56 = Event.TotalBottomBdt(5, 6);

    EventSemiBranch.BottomBdt123 = Event.TotalBottomBdt(1, 2, 3);
    EventSemiBranch.BottomBdt1234 = Event.TotalBottomBdt(1, 2, 3, 4);

    EventSemiBranch.Bdt = Event.Bdt();
    EventSemiBranch.Tag = Event.Tag();

    return EventSemiBranch;

}

struct SortJetsByBdt {
    inline bool operator()(const fastjet::PseudoJet &Jet1, const fastjet::PseudoJet &Jet2) {
        return (Jet1.user_info<hanalysis::HJetInfo>().Bdt() > Jet2.user_info<hanalysis::HJetInfo>().Bdt());
    }
};


std::vector<HEventBottomTaggerBranch> hbottomsumtagger::HEventBottomTagger::GetBranches(hanalysis::HEvent &Event, const HObject::Tag Tag)
{
    Print(HInformation, "Get Event Tags");

    HJets PreJets = GetJets(Event);
    HJets Jets = BottomTagger.GetJetBdt(PreJets, BottomReader);
    std::vector<HEventBottomTaggerBranch> EventSemiBranches;


//     const int JetNumber = 2;
//     const int SignalBottomNumber = 2;
//     const int BackgroundBottomNumber = 0;
//     if (Jets.size() < JetNumber) return EventSemiBranches;
//     HJets BottomJets;
//     HJets Particles = Event.GetParticles()->Generator();
//     Particles = RemoveIfWrongAbsParticle(Particles, BottomId);
//     for (const auto & Particle : Particles) {
//         std::sort(Jets.begin(), Jets.end(), MinDeltaR(Particle));
//         if (Jets.front().delta_R(Particle) < DetectorGeometry.JetConeSize)
//             BottomJets.push_back(Jets.front());
//     }
//
//     if (Tag == kSignal && BottomJets.size() < SignalBottomNumber)  return EventSemiBranches;
//     if (Tag == HBackground && BottomJets.size() < BackgroundBottomNumber)  return EventSemiBranches;

    if (!TruthLevelCheck(Jets,Event, Tag)) return EventSemiBranches;


    HEventBottomMultiplet EventMultiplet;
    EventMultiplet.SetJets(Jets);

    EventMultiplet.SetTag(Tag);
    EventSemiBranches.push_back(GetBranch(EventMultiplet));

    return EventSemiBranches;
}

bool hbottomsumtagger::HEventBottomTagger::TruthLevelCheck(const HJets &NewJets,hanalysis::HEvent &Event, const Tag Tag)
{
    const unsigned JetNumber = 2;
    const unsigned SignalBottomNumber = 2;
    const unsigned BackgroundBottomNumber = 0;

    HJets Jets = NewJets;

    if (Jets.size() < JetNumber) return 0;
    HJets BottomJets;
    HJets Particles = Event.GetParticles()->Generator();
    Particles = RemoveIfWrongAbsParticle(Particles, BottomId);
    for (const auto & Particle : Particles) {
        std::sort(Jets.begin(), Jets.end(), MinDeltaR(Particle));
        if (Jets.front().delta_R(Particle) < DetectorGeometry.JetConeSize)
            BottomJets.push_back(Jets.front());
    }

    if (Tag == kSignal && BottomJets.size() < SignalBottomNumber)  return 0;
    if (Tag == kBackground && BottomJets.size() < BackgroundBottomNumber)  return 0;

    return 1;
}




std::vector<hbottomsumtagger::HEventBottomMultiplet> hbottomsumtagger::HEventBottomTagger::GetBdt(const HJets &Jets, const hanalysis::HReader &EventSemiReader)
{
    Print(HInformation, "Get Event Tags");

    std::vector<HEventBottomMultiplet> EventMultiplets;

    HEventBottomMultiplet EventMultiplet;
    EventMultiplet.SetJets(Jets);
    Branch = GetBranch(EventMultiplet);
    EventMultiplet.SetBdt(EventSemiReader.Bdt());
    EventMultiplets.push_back(EventMultiplet);
    return EventMultiplets;
}

float hbottomsumtagger::HEventBottomTagger::ReadBdt(const TClonesArray &EventClonesArray, const int Entry)
{
    return ((HEventBottomTaggerBranch *) EventClonesArray.At(Entry))->Bdt;
}


// std::vector<int> hbottomsumtagger::HEventBottomTagger::ApplyBdt2(const ExRootTreeReader *const TreeReader, const std::string TreeName, const TFile *const ExportFile)
// {
//     Print(HNotification, "Apply Bdt", EventBranchName);
//     std::string NewEventBranchName = EventBranchName + "Reader";
//     const int Steps = 20;
//     std::vector<int> EventNumbers(Steps, 0);
//
//     const int BinSum = 100;
//     std::vector<int> Bins(BinSum, 0);
//
//     const TClonesArray *const EventClonesArray = const_cast<ExRootTreeReader *>(TreeReader)->UseBranch(NewEventBranchName.c_str());
//     ExRootTreeWriter *TreeWriter = new ExRootTreeWriter(const_cast<TFile *>(ExportFile), TreeName.c_str());
//     ExRootTreeBranch *ResultBranch = TreeWriter->NewBranch(NewEventBranchName.c_str(), HResultBranch::Class());
//     for (const int EventNumber : HRange(const_cast<ExRootTreeReader *>(TreeReader)->GetEntries())) {
//         const_cast<ExRootTreeReader *>(TreeReader)->ReadEntry(EventNumber);
//         for (const int Entry : HRange(EventClonesArray->GetEntriesFast())) {
//             HEventBottomTaggerBranch *Test = (HEventBottomTaggerBranch *) EventClonesArray->At(Entry);
//             const float Bdt = Test->Bdt;
//             HResultBranch *Export = static_cast<HResultBranch *>(ResultBranch->NewEntry());
//             Export->Bdt = Bdt;
//
//             ++Bins.at(floor(Bdt * BinSum / 2));
//
//             for (int Step = 0; Step < Steps; ++Step) {
//                 const float CutValue = (float(Step) / Steps + 1);
//                 if (Bdt > CutValue) ++EventNumbers.at(Step);
//             }
//         }
//         TreeWriter->Fill();
//         TreeWriter->Clear();
//     }
//     TreeWriter->Write();
//     delete TreeWriter;
//
//     return EventNumbers;
// }
