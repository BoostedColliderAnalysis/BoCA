# include "HEventLeptonicTagger.hh"

hheavyhiggs::HEventLeptonicTagger::HEventLeptonicTagger(
    hanalysis::HBottomTagger *const NewBottomTagger,
    hanalysis::HJetPairTagger *const NewJetPairTagger,
    hanalysis::HTopLeptonicTagger *const NewTopTagger,
    hanalysis::HHeavyHiggsLeptonicTagger *const NewHeavyHiggsTagger)
{
    DebugLevel = HError;
    Print(HNotification , "Constructor");
    SetTaggerName("EventLeptonic");
    BottomTagger = NewBottomTagger;
    BottomReader = new hanalysis::HReader(BottomTagger);
    TopLeptonicTagger = NewTopTagger;
    TopLeptonicReader = new hanalysis::HReader(TopLeptonicTagger);
    HeavyHiggsLeptonicTagger = NewHeavyHiggsTagger;
    HeavyHiggsLeptonicReader = new hanalysis::HReader(HeavyHiggsLeptonicTagger);
    JetPairTagger = NewJetPairTagger;
    JetPairReader = new hanalysis::HReader(JetPairTagger);
    Branch = new hheavyhiggs::HEventLeptonicBranch();
    JetTag = new hanalysis::HJetTag();
    DefineVariables();
}

hheavyhiggs::HEventLeptonicTagger::HEventLeptonicTagger()
{
    Print(HNotification , "Constructor");
    SetTaggerName("EventLeptonic");
    Branch = new hheavyhiggs::HEventLeptonicBranch();
    DefineVariables();
}


hheavyhiggs::HEventLeptonicTagger::~HEventLeptonicTagger()
{
    Print(HNotification , "Constructor");
    delete Branch;
    delete JetTag;
    delete BottomReader;
    delete TopLeptonicReader;
    delete HeavyHiggsLeptonicReader;
    delete JetPairReader;
}

void hheavyhiggs::HEventLeptonicTagger::DefineVariables()
{

    Print(HNotification , "Define Variables");

    Observables.push_back(NewObservable(&Branch->JetNumber, "JetNumber"));
    Observables.push_back(NewObservable(&Branch->BottomNumber, "BottomNumber"));
    Observables.push_back(NewObservable(&Branch->ScalarHt, "ScalarHt"));

    Observables.push_back(NewObservable(&Branch->Mass, "Mass"));
    Observables.push_back(NewObservable(&Branch->Pt, "Pt"));
    Observables.push_back(NewObservable(&Branch->Rap, "Rap"));
    Observables.push_back(NewObservable(&Branch->Phi, "Phi"));

    Observables.push_back(NewObservable(&Branch->DeltaPt, "DeltaPt"));
    Observables.push_back(NewObservable(&Branch->DeltaRap, "DeltaRap"));
    Observables.push_back(NewObservable(&Branch->DeltaPhi, "DeltaPhi"));
    Observables.push_back(NewObservable(&Branch->DeltaR, "DeltaR"));

    Observables.push_back(NewObservable(&Branch->Bdt, "Bdt"));
    Spectators.push_back(NewObservable(&Branch->Tag, "Tag"));
    Spectators.push_back(NewObservable(&Branch->LeptonNumber, "LeptonNumber"));

    Print(HNotification, "Variables defined");

}

void hheavyhiggs::HEventLeptonicTagger::FillBranch(hheavyhiggs::HEventLeptonicBranch *EventLeptonicBranch, const HOctet &Octet)
{
    Print(HInformation, "Fill Branch", Octet.GetBdt());

    EventLeptonicBranch->LeptonNumber = Octet.GetLeptonNumber();
    EventLeptonicBranch->JetNumber = Octet.GetJetNumber();
    EventLeptonicBranch->BottomNumber = Octet.GetBottomNumber();
    EventLeptonicBranch->ScalarHt = Octet.GetScalarHt();

    EventLeptonicBranch->Mass = Octet.GetOctetJet().m();
    EventLeptonicBranch->Pt = Octet.GetOctetJet().pt();
    EventLeptonicBranch->Rap = Octet.GetOctetJet().rap();
    EventLeptonicBranch->Phi = Octet.GetOctetJet().phi();

    EventLeptonicBranch->DeltaPt = Octet.GetDoublet().GetDeltaPt();
    EventLeptonicBranch->DeltaRap = Octet.GetDoublet().GetDeltaRap();
    EventLeptonicBranch->DeltaPhi = Octet.GetDoublet().GetDeltaPhi();
    EventLeptonicBranch->DeltaR = Octet.GetDoublet().GetDeltaR();

    EventLeptonicBranch->Bdt = Octet.GetBdt();
    EventLeptonicBranch->Tag = Octet.GetTag();
}

void hheavyhiggs::HEventLeptonicTagger::FillBranch(const HOctet &Octet)
{
    Print(HInformation, "Fill Branch");
    FillBranch(Branch, Octet);
}

// struct SortBySextetBdt {
//     inline bool operator()(const HOctet &Octet1, const HOctet &Octet2) {
//         return (Octet1.GetSextet().GetBdt() > Octet2.GetSextet().GetBdt());
//     }
// };


std::vector<hheavyhiggs::HEventLeptonicBranch *> hheavyhiggs::HEventLeptonicTagger::GetBranches(hanalysis::HEvent *const Event, const HObject::HTag Tag)
{
    Print(HInformation, "Get Branches");

    JetTag->HeavyParticles = {GluonId, TopId};
    HJets Jets = Event->GetJets()->GetStructuredTaggedJets(JetTag);

    Jets = BottomTagger->GetBdt(Jets, BottomReader);

    HJets Leptons = Event->GetLeptons()->GetTaggedJets(JetTag);
    Print(HInformation, "Numeber of Jets", Jets.size(), Leptons.size());

    std::vector<hanalysis::HDoublet> TopDoublets = TopLeptonicTagger->GetBdt(Jets, Leptons, TopLeptonicReader);

    fastjet::PseudoJet MissingEt = Event->GetJets()->GetMissingEt();

    std::vector<hanalysis::HSextet> Sextets = HeavyHiggsLeptonicTagger->GetBdt(TopDoublets, MissingEt, HeavyHiggsLeptonicReader);

    std::vector<hanalysis::HDoublet> Doublets = JetPairTagger->GetBdt(Jets, JetPairReader);

    std::vector<HOctet> Octets;
    for (const auto & Doublet : Doublets) {
        for (const auto & Sextet : Sextets) {
            if (Sextet.GetTriplet1().GetSinglet() == Doublet.GetJet1()) continue;
            if (Sextet.GetTriplet1().GetSinglet() == Doublet.GetJet2()) continue;
            if (Sextet.GetTriplet2().GetSinglet() == Doublet.GetJet1()) continue;
            if (Sextet.GetTriplet2().GetSinglet() == Doublet.GetJet2()) continue;
            HOctet Octet(Sextet, Doublet);
            Octet.SetTag(GetTag(Octet));
            if (Octet.GetTag() != Tag) continue;
            Octets.push_back(Octet);
        }
    }

    if (Tag == HSignal && Octets.size() > 1) {
        Print(HError, "more than one event");
        std::sort(Octets.begin(), Octets.end());
        Octets.erase(Octets.begin() + 1, Octets.end());
    }

    std::vector<hheavyhiggs::HEventLeptonicBranch *> EventLeptonicBranches;
    for (auto & Octet : Octets) {
        hheavyhiggs::HEventLeptonicBranch *EventLeptonicBranch = new hheavyhiggs::HEventLeptonicBranch();
        Octet.SetLeptonNumber(Event->GetLeptons()->GetLeptonJets().size());
        Octet.SetJetNumber(Event->GetJets()->GetJets().size());
        Octet.SetBottomNumber(Event->GetJets()->GetBottomJets().size());
        Octet.SetScalarHt(Event->GetJets()->GetScalarHt());
        Octet.SetTag(Tag);
        FillBranch(EventLeptonicBranch, Octet);
        EventLeptonicBranches.push_back(EventLeptonicBranch);
    }

    return EventLeptonicBranches;

}


hanalysis::HObject::HTag hheavyhiggs::HEventLeptonicTagger::GetTag(const HOctet &Octet)
{
    Print(HInformation, "Get Sextet Tag");

    hanalysis::HJetInfo JetInfoB1 = Octet.GetSextet().GetTriplet1().GetSinglet().user_info<hanalysis::HJetInfo>();
    JetInfoB1.ExtractFraction(BottomId, TopId);
    if (std::abs(JetInfoB1.GetMaximalId()) != BottomId) return HBackground;

    hanalysis::HJetInfo JetInfoL = Octet.GetSextet().GetTriplet1().GetDoublet().GetJet1().user_info<hanalysis::HJetInfo>();
    JetInfoL.ExtractFraction(WId);
    if (std::abs(JetInfoL.GetMaximalId()) != WId) return HBackground;
    if (sgn(JetInfoL.GetMaximalId()) != sgn(JetInfoB1.GetMaximalId())) return HBackground;

    hanalysis::HJetInfo JetInfoB2 = Octet.GetSextet().GetTriplet2().GetSinglet().user_info<hanalysis::HJetInfo>();
    JetInfoB2.ExtractFraction(BottomId, TopId);
    if (JetInfoB1.GetMaximalId() != -JetInfoB2.GetMaximalId()) return HBackground;

    hanalysis::HJetInfo JetInfoW1 = Octet.GetSextet().GetTriplet2().GetDoublet().GetJet1().user_info<hanalysis::HJetInfo>();
    JetInfoW1.ExtractFraction(WId, TopId);
    if (std::abs(JetInfoW1.GetMaximalId()) != WId) return HBackground;
    if (sgn(JetInfoW1.GetMaximalId()) != sgn(JetInfoB2.GetMaximalId())) return HBackground;

    hanalysis::HJetInfo JetInfoB3 = Octet.GetDoublet().GetJet1().user_info<hanalysis::HJetInfo>();
    JetInfoB3.ExtractFraction(BottomId, GluonId);
    if (std::abs(JetInfoB3.GetMaximalId()) != BottomId) return HBackground;

    hanalysis::HJetInfo JetInfoB4 = Octet.GetDoublet().GetJet2().user_info<hanalysis::HJetInfo>();
    JetInfoB4.ExtractFraction(BottomId, GluonId);
    if (JetInfoB3.GetMaximalId() != -JetInfoB4.GetMaximalId()) return HBackground;

    return HSignal;
}




std::vector<HOctet> hheavyhiggs::HEventLeptonicTagger::GetBdt(const std::vector< hanalysis::HSextet > &Sextets, const std::vector< hanalysis::HDoublet > &Doublets, const HEventStruct &EventStruct, const hanalysis::HReader *const EventSemiReader)
{
    Print(HInformation, "Get Event Tags");

    std::vector<HOctet> Octets;
    for (const auto & Doublet : Doublets) {
        for (const auto & Sextet : Sextets) {
            if (Sextet.GetTriplet1().GetSinglet() == Doublet.GetJet1()) continue;
            if (Sextet.GetTriplet1().GetSinglet() == Doublet.GetJet2()) continue;
            if (Sextet.GetTriplet2().GetSinglet() == Doublet.GetJet1()) continue;
            if (Sextet.GetTriplet2().GetSinglet() == Doublet.GetJet2()) continue;
            HOctet Octet(Sextet, Doublet, EventStruct);
            FillBranch(Octet);
            Octet.SetBdt(EventSemiReader->GetBdt());
            Octets.push_back(Octet);
        }
    }
    std::vector<HOctet> FinalOctets;

    if (Octets.size() > 0) FinalOctets.push_back(*std::min_element(Octets.begin(), Octets.end()));
    return FinalOctets;
}



std::vector<int> hheavyhiggs::HEventLeptonicTagger::ApplyBdt2(const ExRootTreeReader *const TreeReader, const std::string TreeName, const TFile *const ExportFile, TMVA::Reader *Reader)
{
    Print(HNotification, "Apply Bdt", EventBranchName);
    std::string Temp = EventBranchName; // TODO remove this dirty trick
    EventBranchName += "Reader";

    const int Steps = 20;
    std::vector<int> EventNumbers(Steps,0);

    const TClonesArray *const EventClonesArray = const_cast<ExRootTreeReader *>(TreeReader)->UseBranch(EventBranchName.c_str());

    ExRootTreeWriter *TreeWriter = new ExRootTreeWriter(const_cast<TFile *>(ExportFile), TreeName.c_str());
    ExRootTreeBranch *ResultBranch = TreeWriter->NewBranch(EventBranchName.c_str(), HResultBranch::Class());

    for (const int EventNumber : HRange(const_cast<ExRootTreeReader *>(TreeReader)->GetEntries())) {

        const_cast<ExRootTreeReader *>(TreeReader)->ReadEntry(EventNumber);

        for (const int Entry : HRange(EventClonesArray->GetEntriesFast())) {


            HEventLeptonicBranch *Test = (HEventLeptonicBranch *) EventClonesArray->At(Entry);
            const float Bdt = Test->Bdt;

            HResultBranch *Export = static_cast<HResultBranch *>(ResultBranch->NewEntry());
            Export->Bdt = Bdt;

            for (int Step = 0; Step < Steps; ++Step) {
                const float Cut = float(2 * Step) / Steps;
                if (Bdt > Cut) ++EventNumbers.at(Step);
            }

        }

        TreeWriter->Fill();
        TreeWriter->Clear();
    }

    TreeWriter->Write();
    delete TreeWriter;
    EventBranchName = Temp;

    return EventNumbers;

}




// std::vector<int> hheavyhiggs::HEventLeptonicTagger::ApplyBdt2(const ExRootTreeReader *const TreeReader, const std::string TreeName, const TFile *const ExportFile, TMVA::Reader *Reader)
// {
//     Print(HNotification, "Apply Bdt", EventBranchName);
//
//     const int Steps = 10;
//     std::vector<int> EventNumbers(Steps);
//
//     const TClonesArray *const EventClonesArray = const_cast<ExRootTreeReader *>(TreeReader)->UseBranch(EventBranchName.c_str());
//
//     ExRootTreeWriter *TreeWriter = new ExRootTreeWriter(const_cast<TFile *>(ExportFile), TreeName.c_str());
//     ExRootTreeBranch *BdtBranch = TreeWriter->NewBranch(EventBranchName.c_str(), HBdtBranch::Class());
//
//     for (const int EventNumber : HRange(const_cast<ExRootTreeReader *>(TreeReader)->GetEntries())) {
//
//         const_cast<ExRootTreeReader *>(TreeReader)->ReadEntry(EventNumber);
//
//         for (const int Entry : HRange(EventClonesArray->GetEntriesFast())) {
//
//             (*Branch) = *((HEventLeptonicBranch *) EventClonesArray->At(Entry));
//             HBdtBranch *Export = static_cast<HBdtBranch *>(BdtBranch->NewEntry());
//
//             const float Bdt = Reader->EvaluateMVA(BdtMethodName);
//             const float Error = Reader->GetMVAError();
//             const float Rarity = Reader->GetRarity(GetBdtMethodName());
//             const int Steps1 = 10;
//             std::vector<float> Probabilities;
//             for (int Step = Steps1; Step > 0; --Step) {
//                 const float SignalFraction = float(Step) / Steps1;
//                 const float Probability = Reader->GetProba(GetBdtMethodName(), SignalFraction);
//                 Probabilities.push_back(Probability);
//
//             }
//             Print(HDebug, "Bdt", Bdt, Error, Rarity);
//             Export->Mass = Branch->Mass;
//             Export->EventTag = Branch->Tag;
//             Export->Bdt = Bdt;
//             Export->Error = Error;
//             Export->Rarity = Rarity;
//             Export->Probability01 = Probabilities.at(0);
//             Export->Probability02 = Probabilities.at(1);
//             Export->Probability03 = Probabilities.at(2);
//             Export->Probability04 = Probabilities.at(3);
//             Export->Probability05 = Probabilities.at(4);
//             Export->Probability06 = Probabilities.at(5);
//             Export->Probability07 = Probabilities.at(6);
//             Export->Probability08 = Probabilities.at(7);
//             Export->Probability09 = Probabilities.at(8);
//             Export->Probability10 = Probabilities.at(9);
//
//             for (int Step = 0; Step < Steps; ++Step) {
//                 const float Cut = float(Step) / Steps;
//                 if (Bdt > Cut) ++EventNumbers.at(Step);
//                 Print(HDebug, "Bdt", Bdt, Cut, EventNumbers.at(Step));
//             }
//
//         }
//
//         TreeWriter->Fill();
//         TreeWriter->Clear();
//
//     }
//
//     TreeWriter->Write();
//     delete TreeWriter;
//
//     return EventNumbers;
// }






