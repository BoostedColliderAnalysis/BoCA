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

    Spectators.push_back(NewObservable(&Branch->LeptonNumber, "LeptonNumber"));
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

    Observables.push_back(NewObservable(&Branch->DeltaPt1, "DeltaPt1"));
    Observables.push_back(NewObservable(&Branch->DeltaRap1, "DeltaRap1"));
    Observables.push_back(NewObservable(&Branch->DeltaPhi1, "DeltaPhi1"));
    Observables.push_back(NewObservable(&Branch->DeltaR1, "DeltaR1"));

    Observables.push_back(NewObservable(&Branch->DeltaPt2, "DeltaPt2"));
    Observables.push_back(NewObservable(&Branch->DeltaRap2, "DeltaRap2"));
    Observables.push_back(NewObservable(&Branch->DeltaPhi2, "DeltaPhi2"));
    Observables.push_back(NewObservable(&Branch->DeltaR2, "DeltaR2"));

    Observables.push_back(NewObservable(&Branch->HiggsMass, "HiggsMass"));
    Observables.push_back(NewObservable(&Branch->PairRap, "PairRap"));

    Observables.push_back(NewObservable(&Branch->RestM, "RestM"));
    Observables.push_back(NewObservable(&Branch->RestPt, "RestPt"));
    Observables.push_back(NewObservable(&Branch->RestHt, "RestHt"));
    Observables.push_back(NewObservable(&Branch->RestPhi, "RestPhi"));
    Observables.push_back(NewObservable(&Branch->RestRap, "RestRap"));
    Observables.push_back(NewObservable(&Branch->RestBTag, "RestBTag"));
    Observables.push_back(NewObservable(&Branch->RestBBdt, "RestBBdt"));
    Observables.push_back(NewObservable(&Branch->MaxBBdt, "MaxBBdt"));
    Observables.push_back(NewObservable(&Branch->TotalBBdt, "TotalBBdt"));
    Observables.push_back(NewObservable(&Branch->ThirdBBdt, "ThirdBBdt"));

    Observables.push_back(NewObservable(&Branch->Bdt, "Bdt"));
    Spectators.push_back(NewObservable(&Branch->Tag, "Tag"));

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

    EventLeptonicBranch->DeltaPt1 = Octet.GetDeltaPt1();
    EventLeptonicBranch->DeltaRap1 = Octet.GetDeltaRap1();
    EventLeptonicBranch->DeltaPhi1 = Octet.GetDeltaPhi1();
    EventLeptonicBranch->DeltaR1 = Octet.GetDeltaR1();

    EventLeptonicBranch->DeltaPt2 = Octet.GetDeltaPt2();
    EventLeptonicBranch->DeltaRap2 = Octet.GetDeltaRap2();
    EventLeptonicBranch->DeltaPhi2 = Octet.GetDeltaPhi2();
    EventLeptonicBranch->DeltaR2 = Octet.GetDeltaR2();

    EventLeptonicBranch->HiggsMass = Octet.GetSextet().GetSextetJet().m();
    EventLeptonicBranch->PairRap = Octet.GetDoublet().GetDeltaRap();

    EventLeptonicBranch->RestM = Octet.GetEventStruct().RestM;
    EventLeptonicBranch->RestPt = Octet.GetEventStruct().RestPt;
    EventLeptonicBranch->RestHt = Octet.GetEventStruct().RestHt;
    EventLeptonicBranch->RestRap = Octet.GetEventStruct().RestRap;
    EventLeptonicBranch->RestPhi = Octet.GetEventStruct().RestPhi;
    EventLeptonicBranch->RestBTag = Octet.GetEventStruct().RestBTag;
    EventLeptonicBranch->RestBBdt = Octet.GetEventStruct().RestBBdt;
    EventLeptonicBranch->MaxBBdt = Octet.GetEventStruct().MaxBBdt;
    EventLeptonicBranch->TotalBBdt = Octet.GetEventStruct().TotalBBdt;
    EventLeptonicBranch->ThirdBBdt = Octet.GetEventStruct().ThirdBBdt;

    EventLeptonicBranch->Bdt = Octet.GetBdt();
    Print(HError, "Bdt", Octet.GetBdt(), EventLeptonicBranch->Bdt);
    EventLeptonicBranch->Tag = Octet.GetTag();
}

void hheavyhiggs::HEventLeptonicTagger::FillBranch(const HOctet &Octet)
{
    Print(HInformation, "Fill Branch");
    FillBranch(Branch, Octet);
}

struct SortJetsByBdt {
    inline bool operator()(const fastjet::PseudoJet &Jet1, const fastjet::PseudoJet &Jet2) {
        return (Jet1.user_info<hanalysis::HJetInfo>().GetBdt() > Jet2.user_info<hanalysis::HJetInfo>().GetBdt());
    }
};


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

    std::sort(Jets.begin(), Jets.end(), SortJetsByBdt());
    float MaxBBdt = 0;
    for (int i = 0; i < std::min(3, int(Jets.size())); ++i) {
        MaxBBdt += Jets.at(i).user_info<hanalysis::HJetInfo>().GetBdt() / std::min(3, int(Jets.size()));
        Print(HInformation, "BDt", Jets.at(i).user_info<hanalysis::HJetInfo>().GetBdt(), MaxBBdt);
    }

    float ThirdBBdt = 0;
    if (Jets.size() > 2) ThirdBBdt = Jets.at(2).user_info<hanalysis::HJetInfo>().GetBdt();

    for (auto & Octet : Octets) {
        HEventStruct EventStruct;
        EventStruct.LeptonNumber = Event->GetLeptons()->GetLeptonJets().size();
        EventStruct.JetNumber = Event->GetJets()->GetJets().size();
        EventStruct.BottomNumber = Event->GetJets()->GetBottomJets().size();
        EventStruct.ScalarHt = Event->GetJets()->GetScalarHt();
        EventStruct.MaxBBdt = MaxBBdt;
        EventStruct.ThirdBBdt = ThirdBBdt;
        fastjet::PseudoJet RestJet(0., 0., 0., 0.);
        int  RestNumber = 0;
        for (const auto & Jet : Jets) {
            EventStruct.TotalBBdt  += Jet.user_info<hanalysis::HJetInfo>().GetBdt() / Jets.size();
            if (Octet.GetSextet().GetTriplet1().GetSinglet() == Jet) continue;
            if (Octet.GetSextet().GetTriplet2().GetSinglet() == Jet) continue;
            if (Octet.GetSextet().GetTriplet2().GetDoublet().GetJet1() == Jet) continue;
            if (Octet.GetSextet().GetTriplet2().GetDoublet().GetJet2() == Jet) continue;
            if (Octet.GetDoublet().GetJet1() == Jet) continue;
            if (Octet.GetDoublet().GetJet2() == Jet) continue;
            ++RestNumber;
            EventStruct.RestHt += Jet.pt();
            EventStruct.RestBTag += Jet.user_info<hanalysis::HJetInfo>().GetBTag();
            Print(HInformation, "Rest BTag", EventStruct.RestBTag);
            EventStruct.RestBBdt += Jet.user_info<hanalysis::HJetInfo>().GetBdt();
            RestJet += Jet;
        }
        EventStruct.RestBBdt /= RestNumber;
        if (RestJet != fastjet::PseudoJet(0, 0, 0, 0)) {
            EventStruct.RestM = RestJet.m();
            EventStruct.RestPt = RestJet.pt();
            EventStruct.RestRap = RestJet.rap();
            EventStruct.RestPhi = RestJet.phi();
        }
        Octet.SetEventStruct(EventStruct);
    }

    std::vector<hheavyhiggs::HEventLeptonicBranch *> EventLeptonicBranches;
    for (auto & Octet : Octets) {
        hheavyhiggs::HEventLeptonicBranch *EventLeptonicBranch = new hheavyhiggs::HEventLeptonicBranch();
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




std::vector<HOctet> hheavyhiggs::HEventLeptonicTagger::GetBdt(const std::vector< hanalysis::HSextet > &Sextets, const std::vector< hanalysis::HDoublet > &Doublets, std::vector<fastjet::PseudoJet> &Jets, HEventStruct &EventStruct, const hanalysis::HReader *const EventLeptonicReader)
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
            Octet.SetBdt(EventLeptonicReader->GetBdt());
            Octets.push_back(Octet);
        }
    }
    std::sort(Octets.begin(), Octets.end());
    if (Octets.size() > 1)Octets.erase(Octets.begin() + 1, Octets.end());
    Print(HError, "Event Number", Octets.size(), Jets.size());

    std::sort(Jets.begin(), Jets.end(), SortJetsByBdt());
    float MaxBBdt = 0;
    for (int i = 0; i < std::min(3, int(Jets.size())); ++i)
        MaxBBdt += Jets.at(i).user_info<hanalysis::HJetInfo>().GetBdt() / std::min(3, int(Jets.size()));

    float ThirdBBdt = 0;
    if (Jets.size() > 2) ThirdBBdt = Jets.at(2).user_info<hanalysis::HJetInfo>().GetBdt();

    for (auto & Octet : Octets) {
        fastjet::PseudoJet RestJet(0., 0., 0., 0.);
        int RestNumber = 0;
        for (const auto & Jet : Jets) {
            Octet.EventStruct.TotalBBdt  += Jet.user_info<hanalysis::HJetInfo>().GetBdt() / Jets.size();
            if (Octet.GetSextet().GetTriplet1().GetSinglet() == Jet) continue;
            if (Octet.GetSextet().GetTriplet2().GetSinglet() == Jet) continue;
            if (Octet.GetSextet().GetTriplet2().GetDoublet().GetJet1() == Jet) continue;
            if (Octet.GetSextet().GetTriplet2().GetDoublet().GetJet2() == Jet) continue;
            if (Octet.GetDoublet().GetJet1() == Jet) continue;
            if (Octet.GetDoublet().GetJet2() == Jet) continue;
            ++RestNumber;
            Octet.EventStruct.RestHt += Jet.pt();
            Octet.EventStruct.RestBTag += Jet.user_info<hanalysis::HJetInfo>().GetBTag();
            Octet.EventStruct.RestBBdt += Jet.user_info<hanalysis::HJetInfo>().GetBdt();
            Octet.EventStruct.MaxBBdt = MaxBBdt;
            RestJet += Jet;
        }
        Octet.EventStruct.RestBBdt /= RestNumber;
        Octet.EventStruct.ThirdBBdt = ThirdBBdt;
        if (RestJet != fastjet::PseudoJet(0, 0, 0, 0)) {
            Octet.EventStruct.RestM = RestJet.m();
            Octet.EventStruct.RestPt = RestJet.pt();
            Octet.EventStruct.RestRap = RestJet.rap();
            Octet.EventStruct.RestPhi = RestJet.phi();
        }

    }

    return Octets;
}



std::vector<int> hheavyhiggs::HEventLeptonicTagger::ApplyBdt2(const ExRootTreeReader *const TreeReader, const std::string TreeName, const TFile *const ExportFile, TMVA::Reader *Reader)
{
    Print(HNotification, "Apply Bdt", EventBranchName);
    std::string Temp = EventBranchName; // TODO remove this dirty trick
    EventBranchName += "Reader";

    const int Steps = 20;
    std::vector<int> EventNumbers(Steps, 0);

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






