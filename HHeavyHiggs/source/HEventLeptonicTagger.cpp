# include "HEventLeptonicTagger.hh"

// hheavyhiggs::EventLeptonicTagger::EventLeptonicTagger()
// {
//   Print(kNotification , "Constructor");
//   SetTaggerName("eventLeptonic");
// }

hheavyhiggs::EventLeptonicTagger::EventLeptonicTagger(
    const analysis::BottomTagger &NewBottomTagger,
    const analysis::HJetPairTagger &NewJetPairTagger,
    const analysis::HTopLeptonicTagger &NewTopTagger,
    const analysis::HHeavyHiggsLeptonicTagger &NewHeavyHiggsTagger)
{
    DebugLevel = kError;
    Print(kNotification , "Constructor");
    set_tagger_name("eventLeptonic");
    bottom_tagger_ = NewBottomTagger;
    BottomReader.set_tagger(bottom_tagger_);
    TopLeptonicTagger = NewTopTagger;
    TopLeptonicReader.set_tagger(TopLeptonicTagger);
    HeavyHiggsLeptonicTagger = NewHeavyHiggsTagger;
    HeavyHiggsLeptonicReader.set_tagger(HeavyHiggsLeptonicTagger);
    JetPairTagger = NewJetPairTagger;
    JetPairReader.set_tagger(JetPairTagger);
//     Branch = new hheavyhiggs::EventLeptonicBranch();
    //JetTag = new analysis::HJetTag();
    DefineVariables();
}

hheavyhiggs::EventLeptonicTagger::EventLeptonicTagger()
{
    Print(kNotification , "Constructor");
    set_tagger_name("eventLeptonic");
//     Branch = new hheavyhiggs::EventLeptonicBranch();
    DefineVariables();
}


hheavyhiggs::EventLeptonicTagger::~EventLeptonicTagger()
{
    Print(kNotification , "Constructor");
    // delete Branch;
    //delete JetTag;
//     delete BottomReader;
//     delete TopLeptonicReader;
//     delete HeavyHiggsLeptonicReader;
//     delete JetPairReader;
}

void hheavyhiggs::EventLeptonicTagger::DefineVariables()
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

void hheavyhiggs::EventLeptonicTagger::FillBranch(hheavyhiggs::EventLeptonicBranch *eventLeptonicBranch, const HOctet &Octet)
{
    Print(kInformation, "Fill Branch", Octet.Bdt());

//     eventLeptonicBranch->LeptonNumber = Octet.LeptonNumber();
//     eventLeptonicBranch->JetNumber = Octet.JetNumber();
//     eventLeptonicBranch->BottomNumber = Octet.BottomNumber();
//     eventLeptonicBranch->ScalarHt = Octet.ScalarHt();

    eventLeptonicBranch->Mass = Octet.Jet().m();
    eventLeptonicBranch->Pt = Octet.Jet().pt();
    eventLeptonicBranch->Rap = Octet.Jet().rap();
    eventLeptonicBranch->Phi = Octet.Jet().phi();

    eventLeptonicBranch->DeltaPt = Octet.doublet().DeltaPt();
    eventLeptonicBranch->DeltaRap = Octet.doublet().DeltaRap();
    eventLeptonicBranch->DeltaPhi = Octet.doublet().DeltaPhi();
    eventLeptonicBranch->DeltaR = Octet.doublet().DeltaR();

    eventLeptonicBranch->DeltaPt1 = Octet.GetDeltaPt1();
    eventLeptonicBranch->DeltaRap1 = Octet.GetDeltaRap1();
    eventLeptonicBranch->DeltaPhi1 = Octet.GetDeltaPhi1();
    eventLeptonicBranch->DeltaR1 = Octet.GetDeltaR1();

    eventLeptonicBranch->DeltaPt2 = Octet.GetDeltaPt2();
    eventLeptonicBranch->DeltaRap2 = Octet.GetDeltaRap2();
    eventLeptonicBranch->DeltaPhi2 = Octet.GetDeltaPhi2();
    eventLeptonicBranch->DeltaR2 = Octet.GetDeltaR2();

    eventLeptonicBranch->HiggsMass = Octet.Sextet().Jet().m();
    eventLeptonicBranch->PairRap = Octet.doublet().DeltaRap();

//     eventLeptonicBranch->RestM = Octet.eventStruct().RestM;
//     eventLeptonicBranch->RestPt = Octet.eventStruct().RestPt;
//     eventLeptonicBranch->RestHt = Octet.eventStruct().RestHt;
//     eventLeptonicBranch->RestRap = Octet.eventStruct().RestRap;
//     eventLeptonicBranch->RestPhi = Octet.eventStruct().RestPhi;
//     eventLeptonicBranch->RestBTag = Octet.eventStruct().RestBTag;
//     eventLeptonicBranch->RestBBdt = Octet.eventStruct().RestBBdt;
//     eventLeptonicBranch->MaxBBdt = Octet.eventStruct().MaxBBdt;
//     eventLeptonicBranch->TotalBBdt = Octet.eventStruct().TotalBBdt;
//     eventLeptonicBranch->ThirdBBdt = Octet.eventStruct().ThirdBBdt;

    eventLeptonicBranch->Bdt = Octet.Bdt();
    Print(kError, "Bdt", Octet.Bdt(), eventLeptonicBranch->Bdt);
    eventLeptonicBranch->Tag = Octet.Tag();
}

void hheavyhiggs::EventLeptonicTagger::FillBranch(const HOctet &Octet)
{
    Print(kInformation, "Fill Branch");
    FillBranch(&Branch, Octet);
}

struct SortJetsByBdt {
    inline bool operator()(const fastjet::PseudoJet &Jet1, const fastjet::PseudoJet &Jet2) {
        return (Jet1.user_info<analysis::JetInfo>().Bdt() > Jet2.user_info<analysis::JetInfo>().Bdt());
    }
};


std::vector<hheavyhiggs::EventLeptonicBranch *> hheavyhiggs::EventLeptonicTagger::GetBranches(analysis::Event &event, const Object::Tag tag)
{
    Print(kInformation, "Get Branches");

    JetTag.HeavyParticles = {GluonId, TopId};
    Jets jets = event.hadrons().GetStructuredTaggedJets(JetTag);

    //     jets = bottom_tagger_.GetJetBdt(jets, BottomReader); // TODO reenable this

    Jets Leptons = event.Leptons().GetTaggedJets(JetTag);
    Print(kInformation, "Numeber of Jets", jets.size(), Leptons.size());

    std::vector<analysis::Doublet> Topdoublets = TopLeptonicTagger.GetBdt(jets, Leptons, TopLeptonicReader);

    fastjet::PseudoJet MissingEt = event.hadrons().GetMissingEt();

    std::vector<analysis::HSextet> Sextets = HeavyHiggsLeptonicTagger.GetBdt(Topdoublets, MissingEt, HeavyHiggsLeptonicReader);

    std::vector<analysis::Doublet> doublets = JetPairTagger.GetBdt(jets, JetPairReader);

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
        MaxBBdt += jets.at(i).user_info<analysis::JetInfo>().Bdt() / std::min(3, int(jets.size()));
        Print(kInformation, "BDt", jets.at(i).user_info<analysis::JetInfo>().Bdt(), MaxBBdt);
    }

//     float ThirdBBdt = 0;
//     if (jets.size() > 2) ThirdBBdt = jets.at(2).user_info<analysis::JetInfo>().Bdt();

    for (auto & Octet : Octets) {
//         EventStruct eventStruct;
//         eventStruct.LeptonNumber = event.Leptons().GetLeptonJets().size();
//         eventStruct.JetNumber = event.hadrons().GetJets().size();
//         eventStruct.BottomNumber = event.hadrons().GetBottomJets().size();
//         eventStruct.ScalarHt = event.hadrons().GetScalarHt();
//         eventStruct.MaxBBdt = MaxBBdt;
//         eventStruct.ThirdBBdt = ThirdBBdt;
//         fastjet::PseudoJet RestJet(0., 0., 0., 0.);
//         int  RestNumber = 0;
//         for (const auto & Jet : jets)  {
//             eventStruct.TotalBBdt  += Jet.user_info<analysis::JetInfo>().Bdt() / jets.size();
//             if (Octet.Sextet().triplet1().singlet() == Jet) continue;
//             if (Octet.Sextet().triplet2().singlet() == Jet) continue;
//             if (Octet.Sextet().triplet2().doublet().Singlet1() == Jet) continue;
//             if (Octet.Sextet().triplet2().doublet().Singlet2() == Jet) continue;
//             if (Octet.doublet().Singlet1() == Jet) continue;
//             if (Octet.doublet().Singlet2() == Jet) continue;
//             ++RestNumber;
//             eventStruct.RestHt += Jet.pt();
//             eventStruct.RestBTag += Jet.user_info<analysis::JetInfo>().BTag();
//             Print(kInformation, "Rest BTag", eventStruct.RestBTag);
//             eventStruct.RestBBdt += Jet.user_info<analysis::JetInfo>().Bdt();
//             RestJet += Jet;
//         }
//         eventStruct.RestBBdt /= RestNumber;
//         if (RestJet != fastjet::PseudoJet(0, 0, 0, 0)) {
//             eventStruct.RestM = RestJet.m();
//             eventStruct.RestPt = RestJet.pt();
//             eventStruct.RestRap = RestJet.rap();
//             eventStruct.RestPhi = RestJet.phi();
//         }
//         Octet.SeteventStruct(eventStruct);
    }

    std::vector<hheavyhiggs::EventLeptonicBranch *> eventLeptonicBranches;
    for (auto & Octet : Octets) {
        hheavyhiggs::EventLeptonicBranch *eventLeptonicBranch = new hheavyhiggs::EventLeptonicBranch();
        Octet.SetTag(tag);
        FillBranch(eventLeptonicBranch, Octet);
        eventLeptonicBranches.emplace_back(eventLeptonicBranch);
    }

    return eventLeptonicBranches;

}


analysis::Object::Tag hheavyhiggs::EventLeptonicTagger::GetTag(const HOctet &Octet)
{
    Print(kInformation, "Get Sextet Tag");

    analysis::JetInfo jet_infoB1 = Octet.Sextet().triplet1().singlet().user_info<analysis::JetInfo>();
    jet_infoB1.ExtractFraction(BottomId, TopId);
    if (std::abs(jet_infoB1.MaximalId()) != BottomId) return kBackground;

    analysis::JetInfo jet_infoL = Octet.Sextet().triplet1().doublet().Singlet1().user_info<analysis::JetInfo>();
    jet_infoL.ExtractFraction(WId);
    if (std::abs(jet_infoL.MaximalId()) != WId) return kBackground;
    if (sgn(jet_infoL.MaximalId()) != sgn(jet_infoB1.MaximalId())) return kBackground;

    analysis::JetInfo jet_infoB2 = Octet.Sextet().triplet2().singlet().user_info<analysis::JetInfo>();
    jet_infoB2.ExtractFraction(BottomId, TopId);
    if (jet_infoB1.MaximalId() != -jet_infoB2.MaximalId()) return kBackground;

    analysis::JetInfo jet_infoW1 = Octet.Sextet().triplet2().doublet().Singlet1().user_info<analysis::JetInfo>();
    jet_infoW1.ExtractFraction(WId, TopId);
    if (std::abs(jet_infoW1.MaximalId()) != WId) return kBackground;
    if (sgn(jet_infoW1.MaximalId()) != sgn(jet_infoB2.MaximalId())) return kBackground;

    analysis::JetInfo jet_infoB3 = Octet.doublet().Singlet1().user_info<analysis::JetInfo>();
    jet_infoB3.ExtractFraction(BottomId, GluonId);
    if (std::abs(jet_infoB3.MaximalId()) != BottomId) return kBackground;

    analysis::JetInfo jet_infoB4 = Octet.doublet().Singlet2().user_info<analysis::JetInfo>();
    jet_infoB4.ExtractFraction(BottomId, GluonId);
    if (jet_infoB3.MaximalId() != -jet_infoB4.MaximalId()) return kBackground;

    return kSignal;
}




std::vector<HOctet> hheavyhiggs::EventLeptonicTagger::GetBdt(const std::vector< analysis::HSextet > &Sextets, const std::vector< analysis::Doublet > &doublets, Jets &jets, EventStruct &, const analysis::Reader & eventLeptonicReader)
{
    Print(kInformation, "Get event Tags");

    std::vector<HOctet> Octets;
    for (const auto & doublet : doublets) {
        for (const auto & Sextet : Sextets) {
            if (Sextet.triplet1().singlet() == doublet.Singlet1()) continue;
            if (Sextet.triplet1().singlet() == doublet.Singlet2()) continue;
            if (Sextet.triplet2().singlet() == doublet.Singlet1()) continue;
            if (Sextet.triplet2().singlet() == doublet.Singlet2()) continue;
//             HOctet Octet(Sextet, doublet, eventStruct);
            HOctet Octet(Sextet, doublet);
            FillBranch(Octet);
            Octet.SetBdt(eventLeptonicReader.Bdt());
            Octets.emplace_back(Octet);
        }
    }
    std::sort(Octets.begin(), Octets.end());
    if (Octets.size() > 1)Octets.erase(Octets.begin() + 1, Octets.end());
    Print(kError, "event Number", Octets.size(), jets.size());

    std::sort(jets.begin(), jets.end(), SortJetsByBdt());
    float MaxBBdt = 0;
    for (int i = 0; i < std::min(3, int(jets.size())); ++i)
        MaxBBdt += jets.at(i).user_info<analysis::JetInfo>().Bdt() / std::min(3, int(jets.size()));

//     float ThirdBBdt = 0;
//     if (jets.size() > 2) ThirdBBdt = jets.at(2).user_info<analysis::JetInfo>().Bdt();

    for (auto & Octet : Octets) {
        fastjet::PseudoJet RestJet(0., 0., 0., 0.);
//         int RestNumber = 0;
        for (const auto & Jet : jets)  {
//             Octet.eventStructM.TotalBBdt  += Jet.user_info<analysis::JetInfo>().Bdt() / jets.size();
//             if (Octet.Sextet().triplet1().singlet() == Jet) continue;
//             if (Octet.Sextet().triplet2().singlet() == Jet) continue;
//             if (Octet.Sextet().triplet2().doublet().Singlet1() == Jet) continue;
//             if (Octet.Sextet().triplet2().doublet().Singlet2() == Jet) continue;
//             if (Octet.doublet().Singlet1() == Jet) continue;
//             if (Octet.doublet().Singlet2() == Jet) continue;
//             ++RestNumber;
//             Octet.eventStructM.RestHt += Jet.pt();
//             Octet.eventStructM.RestBTag += Jet.user_info<analysis::JetInfo>().BTag();
//             Octet.eventStructM.RestBBdt += Jet.user_info<analysis::JetInfo>().Bdt();
//             Octet.eventStructM.MaxBBdt = MaxBBdt;
//             RestJet += Jet;
//         }
//         Octet.eventStructM.RestBBdt /= RestNumber;
//         Octet.eventStructM.ThirdBBdt = ThirdBBdt;
//         if (RestJet != fastjet::PseudoJet(0, 0, 0, 0)) {
//             Octet.eventStructM.RestM = RestJet.m();
//             Octet.eventStructM.RestPt = RestJet.pt();
//             Octet.eventStructM.RestRap = RestJet.rap();
//             Octet.eventStructM.RestPhi = RestJet.phi();
        }

    }

    return Octets;
}



std::vector<int> hheavyhiggs::EventLeptonicTagger::ApplyBdt2(const ExRootTreeReader *const TreeReader, const std::string TreeName, const TFile *const ExportFile)
{
  Print(kNotification, "Apply Bdt", branch_name());
  std::string Temp = branch_name(); // TODO remove this dirty trick
  branch_name() += "Reader";

    const int Steps = 20;
    std::vector<int> eventNumbers(Steps, 0);

    const TClonesArray *const eventClonesArray = const_cast<ExRootTreeReader *>(TreeReader)->UseBranch(branch_name().c_str());

    ExRootTreeWriter *TreeWriter = new ExRootTreeWriter(const_cast<TFile *>(ExportFile), TreeName.c_str());
    ExRootTreeBranch *ResultBranch = TreeWriter->NewBranch(branch_name().c_str(), HResultBranch::Class());

    for (const int eventNumber : Range(const_cast<ExRootTreeReader *>(TreeReader)->GetEntries())) {

        const_cast<ExRootTreeReader *>(TreeReader)->ReadEntry(eventNumber);

        for (const int Entry : Range(eventClonesArray->GetEntriesFast())) {


            EventLeptonicBranch *Test = (EventLeptonicBranch *) eventClonesArray->At(Entry);
            const float Bdt = Test->Bdt;

            HResultBranch *Export = static_cast<HResultBranch *>(ResultBranch->NewEntry());
            Export->Bdt = Bdt;

            for (int Step = 0; Step < Steps; ++Step) {
                const float CutValue = float(2 * Step) / Steps;
                if (Bdt > CutValue) ++eventNumbers.at(Step);
            }

        }

        TreeWriter->Fill();
        TreeWriter->Clear();
    }

    TreeWriter->Write();
    delete TreeWriter;
//     SetBranchName(Temp);

    return eventNumbers;

}




// std::vector<int> hheavyhiggs::EventLeptonicTagger::ApplyBdt2(const ExRootTreeReader *const TreeReader, const std::string TreeName, const TFile *const ExportFile, const TMVA::Reader &Reader)
// {
//     Print(kNotification, "Apply Bdt", eventBranchName);
//
//     const int Steps = 10;
//     std::vector<int> eventNumbers(Steps);
//
//     const TClonesArray *const eventClonesArray = const_cast<ExRootTreeReader *>(TreeReader)->UseBranch(eventBranchName.c_str());
//
//     ExRootTreeWriter *TreeWriter = new ExRootTreeWriter(const_cast<TFile *>(ExportFile), TreeName.c_str());
//     ExRootTreeBranch *BdtBranch = TreeWriter->NewBranch(eventBranchName.c_str(), HBdtBranch::Class());
//
//     for (const int eventNumber : HRange(const_cast<ExRootTreeReader *>(TreeReader)->GetEntries())) {
//
//         const_cast<ExRootTreeReader *>(TreeReader)->ReadEntry(eventNumber);
//
//         for (const int Entry : HRange(eventClonesArray->GetEntriesFast())) {
//
//             (*Branch) = *((EventLeptonicBranch *) eventClonesArray->At(Entry));
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
//             Export->eventTag = Branch->Tag;
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
//                 if (Bdt > Cut) ++eventNumbers.at(Step);
//                 Print(kDebug, "Bdt", Bdt, Cut, eventNumbers.at(Step));
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
//     return eventNumbers;
// }






