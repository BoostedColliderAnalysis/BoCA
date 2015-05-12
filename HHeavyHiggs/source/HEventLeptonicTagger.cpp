# include "HEventLeptonicTagger.hh"

// hheavyhiggs::HEventLeptonicTagger::HEventLeptonicTagger()
// {
//   Print(kNotification , "Constructor");
//   SetTaggerName("EventLeptonic");
// }

hheavyhiggs::HEventLeptonicTagger::HEventLeptonicTagger(
    const hanalysis::BottomTagger &NewBottomTagger,
    const hanalysis::HJetPairTagger &NewJetPairTagger,
    const hanalysis::HTopLeptonicTagger &NewTopTagger,
    const hanalysis::HHeavyHiggsLeptonicTagger &NewHeavyHiggsTagger)
{
    DebugLevel = kError;
    Print(kNotification , "Constructor");
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
    Print(kNotification , "Constructor");
    set_tagger_name("EventLeptonic");
//     Branch = new hheavyhiggs::HEventLeptonicBranch();
    DefineVariables();
}


hheavyhiggs::HEventLeptonicTagger::~HEventLeptonicTagger()
{
    Print(kNotification , "Constructor");
    // delete Branch;
    //delete JetTag;
//     delete BottomReader;
//     delete TopLeptonicReader;
//     delete HeavyHiggsLeptonicReader;
//     delete JetPairReader;
}

void hheavyhiggs::HEventLeptonicTagger::DefineVariables()
{

    Print(kNotification , "Define Variables");

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

    Print(kNotification, "Variables defined");

}

void hheavyhiggs::HEventLeptonicTagger::FillBranch(hheavyhiggs::HEventLeptonicBranch *EventLeptonicBranch, const HOctet &Octet)
{
    Print(kInformation, "Fill Branch", Octet.Bdt());

//     EventLeptonicBranch->LeptonNumber = Octet.LeptonNumber();
//     EventLeptonicBranch->JetNumber = Octet.JetNumber();
//     EventLeptonicBranch->BottomNumber = Octet.BottomNumber();
//     EventLeptonicBranch->ScalarHt = Octet.ScalarHt();

    EventLeptonicBranch->Mass = Octet.Jet().m();
    EventLeptonicBranch->Pt = Octet.Jet().pt();
    EventLeptonicBranch->Rap = Octet.Jet().rap();
    EventLeptonicBranch->Phi = Octet.Jet().phi();

    EventLeptonicBranch->DeltaPt = Octet.doublet().DeltaPt();
    EventLeptonicBranch->DeltaRap = Octet.doublet().DeltaRap();
    EventLeptonicBranch->DeltaPhi = Octet.doublet().DeltaPhi();
    EventLeptonicBranch->DeltaR = Octet.doublet().DeltaR();

    EventLeptonicBranch->DeltaPt1 = Octet.GetDeltaPt1();
    EventLeptonicBranch->DeltaRap1 = Octet.GetDeltaRap1();
    EventLeptonicBranch->DeltaPhi1 = Octet.GetDeltaPhi1();
    EventLeptonicBranch->DeltaR1 = Octet.GetDeltaR1();

    EventLeptonicBranch->DeltaPt2 = Octet.GetDeltaPt2();
    EventLeptonicBranch->DeltaRap2 = Octet.GetDeltaRap2();
    EventLeptonicBranch->DeltaPhi2 = Octet.GetDeltaPhi2();
    EventLeptonicBranch->DeltaR2 = Octet.GetDeltaR2();

    EventLeptonicBranch->HiggsMass = Octet.Sextet().Jet().m();
    EventLeptonicBranch->PairRap = Octet.doublet().DeltaRap();

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
    Print(kError, "Bdt", Octet.Bdt(), EventLeptonicBranch->Bdt);
    EventLeptonicBranch->Tag = Octet.Tag();
}

void hheavyhiggs::HEventLeptonicTagger::FillBranch(const HOctet &Octet)
{
    Print(kInformation, "Fill Branch");
    FillBranch(&Branch, Octet);
}

struct SortJetsByBdt {
    inline bool operator()(const fastjet::PseudoJet &Jet1, const fastjet::PseudoJet &Jet2) {
        return (Jet1.user_info<hanalysis::JetInfo>().Bdt() > Jet2.user_info<hanalysis::JetInfo>().Bdt());
    }
};


std::vector<hheavyhiggs::HEventLeptonicBranch *> hheavyhiggs::HEventLeptonicTagger::GetBranches(hanalysis::HEvent &Event, const HObject::Tag tag)
{
    Print(kInformation, "Get Branches");

    JetTag.HeavyParticles = {GluonId, TopId};
    Jets jets = Event.GetJets()->GetStructuredTaggedJets(JetTag);

    //     jets = bottom_tagger_.GetJetBdt(jets, BottomReader); // TODO reenable this

    Jets Leptons = Event.GetLeptons()->GetTaggedJets(JetTag);
    Print(kInformation, "Numeber of Jets", jets.size(), Leptons.size());

    std::vector<hanalysis::Doublet> Topdoublets = TopLeptonicTagger.GetBdt(jets, Leptons, TopLeptonicReader);

    fastjet::PseudoJet MissingEt = Event.GetJets()->GetMissingEt();

    std::vector<hanalysis::HSextet> Sextets = HeavyHiggsLeptonicTagger.GetBdt(Topdoublets, MissingEt, HeavyHiggsLeptonicReader);

    std::vector<hanalysis::Doublet> doublets = JetPairTagger.GetBdt(jets, JetPairReader);

    std::vector<HOctet> Octets;
    for (const auto & doublet : doublets) {
        for (const auto & Sextet : Sextets) {
            if (Sextet.triplet1().singlet() == doublet.Singlet1()) continue;
            if (Sextet.triplet1().singlet() == doublet.Singlet2()) continue;
            if (Sextet.triplet2().singlet() == doublet.Singlet1()) continue;
            if (Sextet.triplet2().singlet() == doublet.Singlet2()) continue;
            HOctet Octet(Sextet, doublet);
            Octet.SetTag(GetTag(Octet));
            if (Octet.Tag() != tag) continue;
            Octets.emplace_back(Octet);
        }
    }

    if (tag == kSignal && Octets.size() > 1) {
        Print(kError, "more than one event");
        std::sort(Octets.begin(), Octets.end());
        Octets.erase(Octets.begin() + 1, Octets.end());
    }

    std::sort(jets.begin(), jets.end(), SortJetsByBdt());
    float MaxBBdt = 0;
    for (int i = 0; i < std::min(3, int(jets.size())); ++i) {
        MaxBBdt += jets.at(i).user_info<hanalysis::JetInfo>().Bdt() / std::min(3, int(jets.size()));
        Print(kInformation, "BDt", jets.at(i).user_info<hanalysis::JetInfo>().Bdt(), MaxBBdt);
    }

//     float ThirdBBdt = 0;
//     if (jets.size() > 2) ThirdBBdt = jets.at(2).user_info<hanalysis::JetInfo>().Bdt();

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
//         for (const auto & Jet : jets)  {
//             EventStruct.TotalBBdt  += Jet.user_info<hanalysis::JetInfo>().Bdt() / jets.size();
//             if (Octet.Sextet().triplet1().singlet() == Jet) continue;
//             if (Octet.Sextet().triplet2().singlet() == Jet) continue;
//             if (Octet.Sextet().triplet2().doublet().Singlet1() == Jet) continue;
//             if (Octet.Sextet().triplet2().doublet().Singlet2() == Jet) continue;
//             if (Octet.doublet().Singlet1() == Jet) continue;
//             if (Octet.doublet().Singlet2() == Jet) continue;
//             ++RestNumber;
//             EventStruct.RestHt += Jet.pt();
//             EventStruct.RestBTag += Jet.user_info<hanalysis::JetInfo>().BTag();
//             Print(kInformation, "Rest BTag", EventStruct.RestBTag);
//             EventStruct.RestBBdt += Jet.user_info<hanalysis::JetInfo>().Bdt();
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
    Print(kInformation, "Get Sextet Tag");

    hanalysis::JetInfo jet_infoB1 = Octet.Sextet().triplet1().singlet().user_info<hanalysis::JetInfo>();
    jet_infoB1.ExtractFraction(BottomId, TopId);
    if (std::abs(jet_infoB1.MaximalId()) != BottomId) return kBackground;

    hanalysis::JetInfo jet_infoL = Octet.Sextet().triplet1().doublet().Singlet1().user_info<hanalysis::JetInfo>();
    jet_infoL.ExtractFraction(WId);
    if (std::abs(jet_infoL.MaximalId()) != WId) return kBackground;
    if (sgn(jet_infoL.MaximalId()) != sgn(jet_infoB1.MaximalId())) return kBackground;

    hanalysis::JetInfo jet_infoB2 = Octet.Sextet().triplet2().singlet().user_info<hanalysis::JetInfo>();
    jet_infoB2.ExtractFraction(BottomId, TopId);
    if (jet_infoB1.MaximalId() != -jet_infoB2.MaximalId()) return kBackground;

    hanalysis::JetInfo jet_infoW1 = Octet.Sextet().triplet2().doublet().Singlet1().user_info<hanalysis::JetInfo>();
    jet_infoW1.ExtractFraction(WId, TopId);
    if (std::abs(jet_infoW1.MaximalId()) != WId) return kBackground;
    if (sgn(jet_infoW1.MaximalId()) != sgn(jet_infoB2.MaximalId())) return kBackground;

    hanalysis::JetInfo jet_infoB3 = Octet.doublet().Singlet1().user_info<hanalysis::JetInfo>();
    jet_infoB3.ExtractFraction(BottomId, GluonId);
    if (std::abs(jet_infoB3.MaximalId()) != BottomId) return kBackground;

    hanalysis::JetInfo jet_infoB4 = Octet.doublet().Singlet2().user_info<hanalysis::JetInfo>();
    jet_infoB4.ExtractFraction(BottomId, GluonId);
    if (jet_infoB3.MaximalId() != -jet_infoB4.MaximalId()) return kBackground;

    return kSignal;
}




std::vector<HOctet> hheavyhiggs::HEventLeptonicTagger::GetBdt(const std::vector< hanalysis::HSextet > &Sextets, const std::vector< hanalysis::Doublet > &doublets, Jets &jets, HEventStruct &, const hanalysis::Reader & EventLeptonicReader)
{
    Print(kInformation, "Get Event Tags");

    std::vector<HOctet> Octets;
    for (const auto & doublet : doublets) {
        for (const auto & Sextet : Sextets) {
            if (Sextet.triplet1().singlet() == doublet.Singlet1()) continue;
            if (Sextet.triplet1().singlet() == doublet.Singlet2()) continue;
            if (Sextet.triplet2().singlet() == doublet.Singlet1()) continue;
            if (Sextet.triplet2().singlet() == doublet.Singlet2()) continue;
//             HOctet Octet(Sextet, doublet, EventStruct);
            HOctet Octet(Sextet, doublet);
            FillBranch(Octet);
            Octet.SetBdt(EventLeptonicReader.Bdt());
            Octets.emplace_back(Octet);
        }
    }
    std::sort(Octets.begin(), Octets.end());
    if (Octets.size() > 1)Octets.erase(Octets.begin() + 1, Octets.end());
    Print(kError, "Event Number", Octets.size(), jets.size());

    std::sort(jets.begin(), jets.end(), SortJetsByBdt());
    float MaxBBdt = 0;
    for (int i = 0; i < std::min(3, int(jets.size())); ++i)
        MaxBBdt += jets.at(i).user_info<hanalysis::JetInfo>().Bdt() / std::min(3, int(jets.size()));

//     float ThirdBBdt = 0;
//     if (jets.size() > 2) ThirdBBdt = jets.at(2).user_info<hanalysis::JetInfo>().Bdt();

    for (auto & Octet : Octets) {
        fastjet::PseudoJet RestJet(0., 0., 0., 0.);
//         int RestNumber = 0;
        for (const auto & Jet : jets)  {
//             Octet.EventStructM.TotalBBdt  += Jet.user_info<hanalysis::JetInfo>().Bdt() / jets.size();
//             if (Octet.Sextet().triplet1().singlet() == Jet) continue;
//             if (Octet.Sextet().triplet2().singlet() == Jet) continue;
//             if (Octet.Sextet().triplet2().doublet().Singlet1() == Jet) continue;
//             if (Octet.Sextet().triplet2().doublet().Singlet2() == Jet) continue;
//             if (Octet.doublet().Singlet1() == Jet) continue;
//             if (Octet.doublet().Singlet2() == Jet) continue;
//             ++RestNumber;
//             Octet.EventStructM.RestHt += Jet.pt();
//             Octet.EventStructM.RestBTag += Jet.user_info<hanalysis::JetInfo>().BTag();
//             Octet.EventStructM.RestBBdt += Jet.user_info<hanalysis::JetInfo>().Bdt();
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
  Print(kNotification, "Apply Bdt", branch_name());
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
//     Print(kNotification, "Apply Bdt", EventBranchName);
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
//             Print(kDebug, "Bdt", Bdt, Error, Rarity);
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
//                 Print(kDebug, "Bdt", Bdt, Cut, EventNumbers.at(Step));
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






