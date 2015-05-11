# include "HEventBottomTagger.hh"

hbottomsumtagger::HEventBottomTagger::HEventBottomTagger()
{
    //   DebugLevel = kDebug;
    Print(kNotification , "Constructor");
    DefineVariables();
}

void hbottomsumtagger::HEventBottomTagger::SetTagger(const hanalysis::BottomTagger &NewBottomTagger)
{
    Print(kNotification , "Constructor");

    bottom_tagger_ = NewBottomTagger;
    DefineVariables();
}

void hbottomsumtagger::HEventBottomTagger::DefineVariables()
{
    Print(kNotification , "Define Variables");
    set_tagger_name("EventBottom");

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

HEventBottomTaggerBranch hbottomsumtagger::HEventBottomTagger::GetBranch(const HEventBottomMultiplet &Event) const
{
    Print(kInformation, "FillPairTagger", Event.Bdt());

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
        return (Jet1.user_info<hanalysis::JetInfo>().Bdt() > Jet2.user_info<hanalysis::JetInfo>().Bdt());
    }
};


std::vector<HEventBottomTaggerBranch> hbottomsumtagger::HEventBottomTagger::GetBranches(hanalysis::HEvent &Event, const HObject::Tag Tag)
{
    Print(kInformation, "Get Event Tags");

    Jets jets = GetJets(Event);
    //     Jets jets = bottom_tagger_.GetJetBdt(PreJets, BottomReader); // TODO reenable this
    std::vector<HEventBottomTaggerBranch> EventSemiBranches;


//     const int JetNumber = 2;
//     const int SignalBottomNumber = 2;
//     const int BackgroundBottomNumber = 0;
//     if (jets.size() < JetNumber) return EventSemiBranches;
//     Jets BottomJets;
//     Jets Particles = Event.GetParticles()->Generator();
//     Particles = RemoveIfWrongAbsParticle(Particles, BottomId);
//     for (const auto & Particle : Particles) {
//         std::sort(jets.begin(), jets.end(), MinDeltaR(Particle));
//         if (jets.front().delta_R(Particle) < detector_geometry().JetConeSize)
//             BottomJets.emplace_back(jets.front());
//     }
//
//     if (Tag == kSignal && BottomJets.size() < SignalBottomNumber)  return EventSemiBranches;
//     if (Tag == HBackground && BottomJets.size() < BackgroundBottomNumber)  return EventSemiBranches;

    if (!TruthLevelCheck(jets,Event, Tag)) return EventSemiBranches;


    HEventBottomMultiplet EventMultiplet;
    EventMultiplet.SetJets(jets);

    EventMultiplet.SetTag(Tag);
    EventSemiBranches.emplace_back(GetBranch(EventMultiplet));

    return EventSemiBranches;
}

bool hbottomsumtagger::HEventBottomTagger::TruthLevelCheck(const Jets &NewJets,hanalysis::HEvent &Event, const Tag Tag)
{
    const unsigned JetNumber = 2;
    const unsigned SignalBottomNumber = 2;
    const unsigned BackgroundBottomNumber = 0;

    Jets jets = NewJets;

    if (jets.size() < JetNumber) return 0;
    Jets BottomJets;
    Jets Particles = Event.GetParticles()->Generator();
    Particles = RemoveIfWrongAbsParticle(Particles, BottomId);
    for (const auto & Particle : Particles) {
        std::sort(jets.begin(), jets.end(), MinDeltaRTo(Particle));
        if (jets.front().delta_R(Particle) < detector_geometry().JetConeSize)
            BottomJets.emplace_back(jets.front());
    }

    if (Tag == kSignal && BottomJets.size() < SignalBottomNumber)  return 0;
    if (Tag == kBackground && BottomJets.size() < BackgroundBottomNumber)  return 0;

    return 1;
}




std::vector<hbottomsumtagger::HEventBottomMultiplet> hbottomsumtagger::HEventBottomTagger::GetBdt(const Jets &jets, const hanalysis::Reader &EventSemiReader)
{
    Print(kInformation, "Get Event Tags");

    std::vector<HEventBottomMultiplet> EventMultiplets;

    HEventBottomMultiplet EventMultiplet;
    EventMultiplet.SetJets(jets);
    Branch = GetBranch(EventMultiplet);
    EventMultiplet.SetBdt(EventSemiReader.Bdt());
    EventMultiplets.emplace_back(EventMultiplet);
    return EventMultiplets;
}

float hbottomsumtagger::HEventBottomTagger::ReadBdt(const TClonesArray &EventClonesArray, const int Entry)
{
    return ((HEventBottomTaggerBranch *) EventClonesArray.At(Entry))->Bdt;
}


// std::vector<int> hbottomsumtagger::HEventBottomTagger::ApplyBdt2(const ExRootTreeReader *const TreeReader, const std::string TreeName, const TFile *const ExportFile)
// {
//     Print(kNotification, "Apply Bdt", EventBranchName);
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
