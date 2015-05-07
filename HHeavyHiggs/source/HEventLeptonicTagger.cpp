# include "HEventLeptonicTagger.hh"

// hheavyhiggs::HEventLeptonicTagger::HEventLeptonicTagger()
// {
//   Print(HNotification , "Constructor");
//   SetTaggerName("EventLeptonic");
// }

hheavyhiggs::HEventLeptonicTagger::HEventLeptonicTagger(
    const hanalysis::BottomTagger &NewBottomTagger,
    const hanalysis::HJetPairTagger &NewJetPairTagger,
    const hanalysis::HTopLeptonicTagger &NewTopTagger,
    const hanalysis::HHeavyHiggsLeptonicTagger &NewHeavyHiggsTagger)
{
    DebugLevel = HError;
    Print(HNotification , "Constructor");
    set_tagger_name("EventLeptonic");
    bottom_tagger_ = NewBottomTagger;
    BottomReader.set_tagger(bottom_tagger_);
    TopLeptonicTagger = NewTopTagger;
    TopLeptonicReader.set_tagger(TopLeptonicTagger);
    HeavyHiggsLeptonicTagger = NewHeavyHiggsTagger;
    HeavyHiggsLeptonicReader.set_tagger(HeavyHiggsLeptonicTagger);
    JetPairTagger = NewJetPairTagger;
    JetPairReader.set_tagger(JetPairTagger);
//     Branch = new hheavyhiggs::HEventLeptonicBranch();
    //JetTag = new hanalysis::HJetTag();
    DefineVariables();
}

hheavyhiggs::HEventLeptonicTagger::HEventLeptonicTagger()
{
    Print(HNotification , "Constructor");
    set_tagger_name("EventLeptonic");
//     Branch = new hheavyhiggs::HEventLeptonicBranch();
    DefineVariables();
}


hheavyhiggs::HEventLeptonicTagger::~HEventLeptonicTagger()
{
    Print(HNotification , "Constructor");
    // delete Branch;
    //delete JetTag;
//     delete BottomReader;
//     delete TopLeptonicReader;
//     delete HeavyHiggsLeptonicReader;
//     delete JetPairReader;
}

void hheavyhiggs::HEventLeptonicTagger::DefineVariables()
{

    Print(HNotification , "Define Variables");

    AddSpectator(Branch.LeptonNumber, "LeptonNumber");
    AddVariable(Branch.JetNumber, "JetNumber");
    AddVariable(Branch.BottomNumber, "BottomNumber");
    AddVariable(Branch.ScalarHt, "ScalarHt");

    AddVariable(Branch.Mass, "Mass");
    AddVariable(Branch.Pt, "Pt");
    AddVariable(Branch.Rap, "Rap");
    AddVariable(Branch.Phi, "Phi");

    AddVariable(Branch.DeltaPt, "DeltaPt");
    AddVariable(Branch.DeltaRap, "DeltaRap");
    AddVariable(Branch.DeltaPhi, "DeltaPhi");
    AddVariable(Branch.DeltaR, "DeltaR");

    AddVariable(Branch.DeltaPt1, "DeltaPt1");
    AddVariable(Branch.DeltaRap1, "DeltaRap1");
    AddVariable(Branch.DeltaPhi1, "DeltaPhi1");
    AddVariable(Branch.DeltaR1, "DeltaR1");

    AddVariable(Branch.DeltaPt2, "DeltaPt2");
    AddVariable(Branch.DeltaRap2, "DeltaRap2");
    AddVariable(Branch.DeltaPhi2, "DeltaPhi2");
    AddVariable(Branch.DeltaR2, "DeltaR2");

    AddVariable(Branch.HiggsMass, "HiggsMass");
    AddVariable(Branch.PairRap, "PairRap");

    AddVariable(Branch.RestM, "RestM");
    AddVariable(Branch.RestPt, "RestPt");
    AddVariable(Branch.RestHt, "RestHt");
    AddVariable(Branch.RestPhi, "RestPhi");
    AddVariable(Branch.RestRap, "RestRap");
    AddVariable(Branch.RestBTag, "RestBTag");
    AddVariable(Branch.RestBBdt, "RestBBdt");
    AddVariable(Branch.MaxBBdt, "MaxBBdt");
    AddVariable(Branch.TotalBBdt, "TotalBBdt");
    AddVariable(Branch.ThirdBBdt, "ThirdBBdt");

    AddVariable(Branch.Bdt, "Bdt");
    AddSpectator(Branch.Tag, "Tag");

    Print(HNotification, "Variables defined");

}

void hheavyhiggs::HEventLeptonicTagger::FillBranch(hheavyhiggs::HEventLeptonicBranch *EventLeptonicBranch, const HOctet &Octet)
{
    Print(HInformation, "Fill Branch", Octet.Bdt());

//     EventLeptonicBranch->LeptonNumber = Octet.LeptonNumber();
//     EventLeptonicBranch->JetNumber = Octet.JetNumber();
//     EventLeptonicBranch->BottomNumber = Octet.BottomNumber();
//     EventLeptonicBranch->ScalarHt = Octet.ScalarHt();

    EventLeptonicBranch->Mass = Octet.Jet().m();
    EventLeptonicBranch->Pt = Octet.Jet().pt();
    EventLeptonicBranch->Rap = Octet.Jet().rap();
    EventLeptonicBranch->Phi = Octet.Jet().phi();

    EventLeptonicBranch->DeltaPt = Octet.Doublet().DeltaPt();
    EventLeptonicBranch->DeltaRap = Octet.Doublet().DeltaRap();
    EventLeptonicBranch->DeltaPhi = Octet.Doublet().DeltaPhi();
    EventLeptonicBranch->DeltaR = Octet.Doublet().DeltaR();

    EventLeptonicBranch->DeltaPt1 = Octet.GetDeltaPt1();
    EventLeptonicBranch->DeltaRap1 = Octet.GetDeltaRap1();
    EventLeptonicBranch->DeltaPhi1 = Octet.GetDeltaPhi1();
    EventLeptonicBranch->DeltaR1 = Octet.GetDeltaR1();

    EventLeptonicBranch->DeltaPt2 = Octet.GetDeltaPt2();
    EventLeptonicBranch->DeltaRap2 = Octet.GetDeltaRap2();
    EventLeptonicBranch->DeltaPhi2 = Octet.GetDeltaPhi2();
    EventLeptonicBranch->DeltaR2 = Octet.GetDeltaR2();

    EventLeptonicBranch->HiggsMass = Octet.Sextet().Jet().m();
    EventLeptonicBranch->PairRap = Octet.Doublet().DeltaRap();

//     EventLeptonicBranch->RestM = Octet.EventStruct().RestM;
//     EventLeptonicBranch->RestPt = Octet.EventStruct().RestPt;
//     EventLeptonicBranch->RestHt = Octet.EventStruct().RestHt;
//     EventLeptonicBranch->RestRap = Octet.EventStruct().RestRap;
//     EventLeptonicBranch->RestPhi = Octet.EventStruct().RestPhi;
//     EventLeptonicBranch->RestBTag = Octet.EventStruct().RestBTag;
//     EventLeptonicBranch->RestBBdt = Octet.EventStruct().RestBBdt;
//     EventLeptonicBranch->MaxBBdt = Octet.EventStruct().MaxBBdt;
//     EventLeptonicBranch->TotalBBdt = Octet.EventStruct().TotalBBdt;
//     EventLeptonicBranch->ThirdBBdt = Octet.EventStruct().ThirdBBdt;

    EventLeptonicBranch->Bdt = Octet.Bdt();
    Print(HError, "Bdt", Octet.Bdt(), EventLeptonicBranch->Bdt);
    EventLeptonicBranch->Tag = Octet.Tag();
}

void hheavyhiggs::HEventLeptonicTagger::FillBranch(const HOctet &Octet)
{
    Print(HInformation, "Fill Branch");
    FillBranch(&Branch, Octet);
}

struct SortJetsByBdt {
    inline bool operator()(const fastjet::PseudoJet &Jet1, const fastjet::PseudoJet &Jet2) {
        return (Jet1.user_info<hanalysis::HJetInfo>().Bdt() > Jet2.user_info<hanalysis::HJetInfo>().Bdt());
    }
};


std::vector<hheavyhiggs::HEventLeptonicBranch *> hheavyhiggs::HEventLeptonicTagger::GetBranches(hanalysis::HEvent &Event, const HObject::Tag tag)
{
    Print(HInformation, "Get Branches");

    JetTag.HeavyParticles = {GluonId, TopId};
    HJets Jets = Event.GetJets()->GetStructuredTaggedJets(JetTag);

    //     Jets = bottom_tagger_.GetJetBdt(Jets, BottomReader); // TODO reenable this

    HJets Leptons = Event.GetLeptons()->GetTaggedJets(JetTag);
    Print(HInformation, "Numeber of Jets", Jets.size(), Leptons.size());

    std::vector<hanalysis::HDoublet> TopDoublets = TopLeptonicTagger.GetBdt(Jets, Leptons, TopLeptonicReader);

    fastjet::PseudoJet MissingEt = Event.GetJets()->GetMissingEt();

    std::vector<hanalysis::HSextet> Sextets = HeavyHiggsLeptonicTagger.GetBdt(TopDoublets, MissingEt, HeavyHiggsLeptonicReader);

    std::vector<hanalysis::HDoublet> Doublets = JetPairTagger.GetBdt(Jets, JetPairReader);

    std::vector<HOctet> Octets;
    for (const auto & Doublet : Doublets) {
        for (const auto & Sextet : Sextets) {
            if (Sextet.Triplet1().Singlet() == Doublet.Singlet1()) continue;
            if (Sextet.Triplet1().Singlet() == Doublet.Singlet2()) continue;
            if (Sextet.Triplet2().Singlet() == Doublet.Singlet1()) continue;
            if (Sextet.Triplet2().Singlet() == Doublet.Singlet2()) continue;
            HOctet Octet(Sextet, Doublet);
            Octet.SetTag(GetTag(Octet));
            if (Octet.Tag() != tag) continue;
            Octets.emplace_back(Octet);
        }
    }

    if (tag == kSignal && Octets.size() > 1) {
        Print(HError, "more than one event");
        std::sort(Octets.begin(), Octets.end());
        Octets.erase(Octets.begin() + 1, Octets.end());
    }

    std::sort(Jets.begin(), Jets.end(), SortJetsByBdt());
    float MaxBBdt = 0;
    for (int i = 0; i < std::min(3, int(Jets.size())); ++i) {
        MaxBBdt += Jets.at(i).user_info<hanalysis::HJetInfo>().Bdt() / std::min(3, int(Jets.size()));
        Print(HInformation, "BDt", Jets.at(i).user_info<hanalysis::HJetInfo>().Bdt(), MaxBBdt);
    }

//     float ThirdBBdt = 0;
//     if (Jets.size() > 2) ThirdBBdt = Jets.at(2).user_info<hanalysis::HJetInfo>().Bdt();

    for (auto & Octet : Octets) {
//         HEventStruct EventStruct;
//         EventStruct.LeptonNumber = Event.GetLeptons()->GetLeptonJets().size();
//         EventStruct.JetNumber = Event.GetJets()->GetJets().size();
//         EventStruct.BottomNumber = Event.GetJets()->GetBottomJets().size();
//         EventStruct.ScalarHt = Event.GetJets()->GetScalarHt();
//         EventStruct.MaxBBdt = MaxBBdt;
//         EventStruct.ThirdBBdt = ThirdBBdt;
//         fastjet::PseudoJet RestJet(0., 0., 0., 0.);
//         int  RestNumber = 0;
//         for (const auto & Jet : Jets) {
//             EventStruct.TotalBBdt  += Jet.user_info<hanalysis::HJetInfo>().Bdt() / Jets.size();
//             if (Octet.Sextet().Triplet1().Singlet() == Jet) continue;
//             if (Octet.Sextet().Triplet2().Singlet() == Jet) continue;
//             if (Octet.Sextet().Triplet2().Doublet().Singlet1() == Jet) continue;
//             if (Octet.Sextet().Triplet2().Doublet().Singlet2() == Jet) continue;
//             if (Octet.Doublet().Singlet1() == Jet) continue;
//             if (Octet.Doublet().Singlet2() == Jet) continue;
//             ++RestNumber;
//             EventStruct.RestHt += Jet.pt();
//             EventStruct.RestBTag += Jet.user_info<hanalysis::HJetInfo>().BTag();
//             Print(HInformation, "Rest BTag", EventStruct.RestBTag);
//             EventStruct.RestBBdt += Jet.user_info<hanalysis::HJetInfo>().Bdt();
//             RestJet += Jet;
//         }
//         EventStruct.RestBBdt /= RestNumber;
//         if (RestJet != fastjet::PseudoJet(0, 0, 0, 0)) {
//             EventStruct.RestM = RestJet.m();
//             EventStruct.RestPt = RestJet.pt();
//             EventStruct.RestRap = RestJet.rap();
//             EventStruct.RestPhi = RestJet.phi();
//         }
//         Octet.SetEventStruct(EventStruct);
    }

    std::vector<hheavyhiggs::HEventLeptonicBranch *> EventLeptonicBranches;
    for (auto & Octet : Octets) {
        hheavyhiggs::HEventLeptonicBranch *EventLeptonicBranch = new hheavyhiggs::HEventLeptonicBranch();
        Octet.SetTag(tag);
        FillBranch(EventLeptonicBranch, Octet);
        EventLeptonicBranches.emplace_back(EventLeptonicBranch);
    }

    return EventLeptonicBranches;

}


hanalysis::HObject::Tag hheavyhiggs::HEventLeptonicTagger::GetTag(const HOctet &Octet)
{
    Print(HInformation, "Get Sextet Tag");

    hanalysis::HJetInfo JetInfoB1 = Octet.Sextet().Triplet1().Singlet().user_info<hanalysis::HJetInfo>();
    JetInfoB1.ExtractFraction(BottomId, TopId);
    if (std::abs(JetInfoB1.MaximalId()) != BottomId) return kBackground;

    hanalysis::HJetInfo JetInfoL = Octet.Sextet().Triplet1().Doublet().Singlet1().user_info<hanalysis::HJetInfo>();
    JetInfoL.ExtractFraction(WId);
    if (std::abs(JetInfoL.MaximalId()) != WId) return kBackground;
    if (sgn(JetInfoL.MaximalId()) != sgn(JetInfoB1.MaximalId())) return kBackground;

    hanalysis::HJetInfo JetInfoB2 = Octet.Sextet().Triplet2().Singlet().user_info<hanalysis::HJetInfo>();
    JetInfoB2.ExtractFraction(BottomId, TopId);
    if (JetInfoB1.MaximalId() != -JetInfoB2.MaximalId()) return kBackground;

    hanalysis::HJetInfo JetInfoW1 = Octet.Sextet().Triplet2().Doublet().Singlet1().user_info<hanalysis::HJetInfo>();
    JetInfoW1.ExtractFraction(WId, TopId);
    if (std::abs(JetInfoW1.MaximalId()) != WId) return kBackground;
    if (sgn(JetInfoW1.MaximalId()) != sgn(JetInfoB2.MaximalId())) return kBackground;

    hanalysis::HJetInfo JetInfoB3 = Octet.Doublet().Singlet1().user_info<hanalysis::HJetInfo>();
    JetInfoB3.ExtractFraction(BottomId, GluonId);
    if (std::abs(JetInfoB3.MaximalId()) != BottomId) return kBackground;

    hanalysis::HJetInfo JetInfoB4 = Octet.Doublet().Singlet2().user_info<hanalysis::HJetInfo>();
    JetInfoB4.ExtractFraction(BottomId, GluonId);
    if (JetInfoB3.MaximalId() != -JetInfoB4.MaximalId()) return kBackground;

    return kSignal;
}




std::vector<HOctet> hheavyhiggs::HEventLeptonicTagger::GetBdt(const std::vector< hanalysis::HSextet > &Sextets, const std::vector< hanalysis::HDoublet > &Doublets, std::vector<fastjet::PseudoJet> &Jets, HEventStruct &, const hanalysis::Reader & EventLeptonicReader)
{
    Print(HInformation, "Get Event Tags");

    std::vector<HOctet> Octets;
    for (const auto & Doublet : Doublets) {
        for (const auto & Sextet : Sextets) {
            if (Sextet.Triplet1().Singlet() == Doublet.Singlet1()) continue;
            if (Sextet.Triplet1().Singlet() == Doublet.Singlet2()) continue;
            if (Sextet.Triplet2().Singlet() == Doublet.Singlet1()) continue;
            if (Sextet.Triplet2().Singlet() == Doublet.Singlet2()) continue;
//             HOctet Octet(Sextet, Doublet, EventStruct);
            HOctet Octet(Sextet, Doublet);
            FillBranch(Octet);
            Octet.SetBdt(EventLeptonicReader.Bdt());
            Octets.emplace_back(Octet);
        }
    }
    std::sort(Octets.begin(), Octets.end());
    if (Octets.size() > 1)Octets.erase(Octets.begin() + 1, Octets.end());
    Print(HError, "Event Number", Octets.size(), Jets.size());

    std::sort(Jets.begin(), Jets.end(), SortJetsByBdt());
    float MaxBBdt = 0;
    for (int i = 0; i < std::min(3, int(Jets.size())); ++i)
        MaxBBdt += Jets.at(i).user_info<hanalysis::HJetInfo>().Bdt() / std::min(3, int(Jets.size()));

//     float ThirdBBdt = 0;
//     if (Jets.size() > 2) ThirdBBdt = Jets.at(2).user_info<hanalysis::HJetInfo>().Bdt();

    for (auto & Octet : Octets) {
        fastjet::PseudoJet RestJet(0., 0., 0., 0.);
//         int RestNumber = 0;
        for (const auto & Jet : Jets) {
//             Octet.EventStructM.TotalBBdt  += Jet.user_info<hanalysis::HJetInfo>().Bdt() / Jets.size();
//             if (Octet.Sextet().Triplet1().Singlet() == Jet) continue;
//             if (Octet.Sextet().Triplet2().Singlet() == Jet) continue;
//             if (Octet.Sextet().Triplet2().Doublet().Singlet1() == Jet) continue;
//             if (Octet.Sextet().Triplet2().Doublet().Singlet2() == Jet) continue;
//             if (Octet.Doublet().Singlet1() == Jet) continue;
//             if (Octet.Doublet().Singlet2() == Jet) continue;
//             ++RestNumber;
//             Octet.EventStructM.RestHt += Jet.pt();
//             Octet.EventStructM.RestBTag += Jet.user_info<hanalysis::HJetInfo>().BTag();
//             Octet.EventStructM.RestBBdt += Jet.user_info<hanalysis::HJetInfo>().Bdt();
//             Octet.EventStructM.MaxBBdt = MaxBBdt;
//             RestJet += Jet;
//         }
//         Octet.EventStructM.RestBBdt /= RestNumber;
//         Octet.EventStructM.ThirdBBdt = ThirdBBdt;
//         if (RestJet != fastjet::PseudoJet(0, 0, 0, 0)) {
//             Octet.EventStructM.RestM = RestJet.m();
//             Octet.EventStructM.RestPt = RestJet.pt();
//             Octet.EventStructM.RestRap = RestJet.rap();
//             Octet.EventStructM.RestPhi = RestJet.phi();
        }

    }

    return Octets;
}



std::vector<int> hheavyhiggs::HEventLeptonicTagger::ApplyBdt2(const ExRootTreeReader *const TreeReader, const std::string TreeName, const TFile *const ExportFile)
{
  Print(HNotification, "Apply Bdt", branch_name());
  std::string Temp = branch_name(); // TODO remove this dirty trick
  branch_name() += "Reader";

    const int Steps = 20;
    std::vector<int> EventNumbers(Steps, 0);

    const TClonesArray *const EventClonesArray = const_cast<ExRootTreeReader *>(TreeReader)->UseBranch(branch_name().c_str());

    ExRootTreeWriter *TreeWriter = new ExRootTreeWriter(const_cast<TFile *>(ExportFile), TreeName.c_str());
    ExRootTreeBranch *ResultBranch = TreeWriter->NewBranch(branch_name().c_str(), HResultBranch::Class());

    for (const int EventNumber : Range(const_cast<ExRootTreeReader *>(TreeReader)->GetEntries())) {

        const_cast<ExRootTreeReader *>(TreeReader)->ReadEntry(EventNumber);

        for (const int Entry : Range(EventClonesArray->GetEntriesFast())) {


            HEventLeptonicBranch *Test = (HEventLeptonicBranch *) EventClonesArray->At(Entry);
            const float Bdt = Test->Bdt;

            HResultBranch *Export = static_cast<HResultBranch *>(ResultBranch->NewEntry());
            Export->Bdt = Bdt;

            for (int Step = 0; Step < Steps; ++Step) {
                const float CutValue = float(2 * Step) / Steps;
                if (Bdt > CutValue) ++EventNumbers.at(Step);
            }

        }

        TreeWriter->Fill();
        TreeWriter->Clear();
    }

    TreeWriter->Write();
    delete TreeWriter;
//     SetBranchName(Temp);

    return EventNumbers;

}




// std::vector<int> hheavyhiggs::HEventLeptonicTagger::ApplyBdt2(const ExRootTreeReader *const TreeReader, const std::string TreeName, const TFile *const ExportFile, const TMVA::Reader &Reader)
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
//             const float Bdt = const_cast<TMVA::Reader *>(&Reader)->EvaluateMVA(BdtMethodName);
//             const float Error = Reader->GetMVAError();
//             const float Rarity = Reader->GetRarity(GetBdtMethodName());
//             const int Steps1 = 10;
//             std::vector<float> Probabilities;
//             for (int Step = Steps1; Step > 0; --Step) {
//                 const float SignalFraction = float(Step) / Steps1;
//                 const float Probability = Reader->GetProba(GetBdtMethodName(), SignalFraction);
//                 Probabilities.emplace_back(Probability);
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






