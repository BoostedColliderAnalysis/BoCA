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

void hheavyhiggs::EventLeptonicTagger::FillBranch(hheavyhiggs::EventLeptonicBranch *eventLeptonicBranch, const Octet62 &octet)
{
    Print(kInformation, "Fill Branch", octet.Bdt());

//     eventLeptonicBranch->LeptonNumber = octet.LeptonNumber();
//     eventLeptonicBranch->JetNumber = octet.JetNumber();
//     eventLeptonicBranch->BottomNumber = octet.BottomNumber();
//     eventLeptonicBranch->ScalarHt = octet.ScalarHt();

    eventLeptonicBranch->Mass = octet.Jet().m();
    eventLeptonicBranch->Pt = octet.Jet().pt();
    eventLeptonicBranch->Rap = octet.Jet().rap();
    eventLeptonicBranch->Phi = octet.Jet().phi();

    eventLeptonicBranch->DeltaPt = octet.doublet().DeltaPt();
    eventLeptonicBranch->DeltaRap = octet.doublet().DeltaRap();
    eventLeptonicBranch->DeltaPhi = octet.doublet().DeltaPhi();
    eventLeptonicBranch->DeltaR = octet.doublet().DeltaR();

    eventLeptonicBranch->DeltaPt1 = octet.GetDeltaPt1();
    eventLeptonicBranch->DeltaRap1 = octet.GetDeltaRap1();
    eventLeptonicBranch->DeltaPhi1 = octet.GetDeltaPhi1();
    eventLeptonicBranch->DeltaR1 = octet.GetDeltaR1();

    eventLeptonicBranch->DeltaPt2 = octet.GetDeltaPt2();
    eventLeptonicBranch->DeltaRap2 = octet.GetDeltaRap2();
    eventLeptonicBranch->DeltaPhi2 = octet.GetDeltaPhi2();
    eventLeptonicBranch->DeltaR2 = octet.GetDeltaR2();

    eventLeptonicBranch->HiggsMass = octet.sextet().Jet().m();
    eventLeptonicBranch->PairRap = octet.doublet().DeltaRap();

//     eventLeptonicBranch->RestM = octet.global_observables().RestM;
//     eventLeptonicBranch->RestPt = octet.global_observables().RestPt;
//     eventLeptonicBranch->RestHt = octet.global_observables().RestHt;
//     eventLeptonicBranch->RestRap = octet.global_observables().RestRap;
//     eventLeptonicBranch->RestPhi = octet.global_observables().RestPhi;
//     eventLeptonicBranch->RestBTag = octet.global_observables().RestBTag;
//     eventLeptonicBranch->RestBBdt = octet.global_observables().RestBBdt;
//     eventLeptonicBranch->MaxBBdt = octet.global_observables().MaxBBdt;
//     eventLeptonicBranch->TotalBBdt = octet.global_observables().TotalBBdt;
//     eventLeptonicBranch->ThirdBBdt = octet.global_observables().ThirdBBdt;

    eventLeptonicBranch->Bdt = octet.Bdt();
    Print(kError, "Bdt", octet.Bdt(), eventLeptonicBranch->Bdt);
    eventLeptonicBranch->Tag = octet.Tag();
}

void hheavyhiggs::EventLeptonicTagger::FillBranch(const Octet62 &octet)
{
    Print(kInformation, "Fill Branch");
    FillBranch(&Branch, octet);
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

    Jets Leptons = event.leptons().GetTaggedJets(JetTag);
    Print(kInformation, "Numeber of Jets", jets.size(), Leptons.size());

    std::vector<analysis::Doublet> Topdoublets = TopLeptonicTagger.GetBdt(jets, Leptons, TopLeptonicReader);

    fastjet::PseudoJet MissingEt = event.hadrons().GetMissingEt();

    std::vector<analysis::Sextet> sextets = HeavyHiggsLeptonicTagger.GetBdt(Topdoublets, MissingEt, HeavyHiggsLeptonicReader);

    std::vector<analysis::Doublet> doublets = JetPairTagger.GetBdt(jets, JetPairReader);

    std::vector<Octet62> octets;
    for (const auto & doublet : doublets) {
        for (const auto & sextet : sextets) {
            if (sextet.triplet1().singlet() == doublet.Singlet1()) continue;
            if (sextet.triplet1().singlet() == doublet.Singlet2()) continue;
            if (sextet.triplet2().singlet() == doublet.Singlet1()) continue;
            if (sextet.triplet2().singlet() == doublet.Singlet2()) continue;
            Octet62 octet(sextet, doublet);
            octet.SetTag(GetTag(octet));
            if (octet.Tag() != tag) continue;
            octets.emplace_back(octet);
        }
    }

    if (tag == kSignal && octets.size() > 1) {
        Print(kError, "more than one event");
        std::sort(octets.begin(), octets.end());
        octets.erase(octets.begin() + 1, octets.end());
    }

    std::sort(jets.begin(), jets.end(), SortJetsByBdt());
    float MaxBBdt = 0;
    for (int i = 0; i < std::min(3, int(jets.size())); ++i) {
        MaxBBdt += jets.at(i).user_info<analysis::JetInfo>().Bdt() / std::min(3, int(jets.size()));
        Print(kInformation, "BDt", jets.at(i).user_info<analysis::JetInfo>().Bdt(), MaxBBdt);
    }

//     float ThirdBBdt = 0;
//     if (jets.size() > 2) ThirdBBdt = jets.at(2).user_info<analysis::JetInfo>().Bdt();

    for (auto & octet : octets) {
//         EventStruct global_observables;
//         global_observables.LeptonNumber = event.leptons().GetLeptonJets().size();
//         global_observables.JetNumber = event.hadrons().GetJets().size();
//         global_observables.BottomNumber = event.hadrons().GetBottomJets().size();
//         global_observables.ScalarHt = event.hadrons().GetScalarHt();
//         global_observables.MaxBBdt = MaxBBdt;
//         global_observables.ThirdBBdt = ThirdBBdt;
//         fastjet::PseudoJet RestJet(0., 0., 0., 0.);
//         int  RestNumber = 0;
//         for (const auto & Jet : jets)  {
//             global_observables.TotalBBdt  += Jet.user_info<analysis::JetInfo>().Bdt() / jets.size();
//             if (octet.sextet().triplet1().singlet() == Jet) continue;
//             if (octet.sextet().triplet2().singlet() == Jet) continue;
//             if (octet.sextet().triplet2().doublet().Singlet1() == Jet) continue;
//             if (octet.sextet().triplet2().doublet().Singlet2() == Jet) continue;
//             if (octet.doublet().Singlet1() == Jet) continue;
//             if (octet.doublet().Singlet2() == Jet) continue;
//             ++RestNumber;
//             global_observables.RestHt += Jet.pt();
//             global_observables.RestBTag += Jet.user_info<analysis::JetInfo>().BTag();
//             Print(kInformation, "Rest BTag", global_observables.RestBTag);
//             global_observables.RestBBdt += Jet.user_info<analysis::JetInfo>().Bdt();
//             RestJet += Jet;
//         }
//         global_observables.RestBBdt /= RestNumber;
//         if (RestJet != fastjet::PseudoJet(0, 0, 0, 0)) {
//             global_observables.RestM = RestJet.m();
//             global_observables.RestPt = RestJet.pt();
//             global_observables.RestRap = RestJet.rap();
//             global_observables.RestPhi = RestJet.phi();
//         }
//         octet.Setglobal_observables(global_observables);
    }

    std::vector<hheavyhiggs::EventLeptonicBranch *> eventLeptonicBranches;
    for (auto & octet : octets) {
        hheavyhiggs::EventLeptonicBranch *eventLeptonicBranch = new hheavyhiggs::EventLeptonicBranch();
        octet.SetTag(tag);
        FillBranch(eventLeptonicBranch, octet);
        eventLeptonicBranches.emplace_back(eventLeptonicBranch);
    }

    return eventLeptonicBranches;

}


analysis::Object::Tag hheavyhiggs::EventLeptonicTagger::GetTag(const Octet62 &octet)
{
    Print(kInformation, "Get sextet Tag");

    analysis::JetInfo jet_infoB1 = octet.sextet().triplet1().singlet().user_info<analysis::JetInfo>();
    jet_infoB1.ExtractFraction(BottomId, TopId);
    if (std::abs(jet_infoB1.MaximalId()) != BottomId) return kBackground;

    analysis::JetInfo jet_infoL = octet.sextet().triplet1().doublet().Singlet1().user_info<analysis::JetInfo>();
    jet_infoL.ExtractFraction(WId);
    if (std::abs(jet_infoL.MaximalId()) != WId) return kBackground;
    if (sgn(jet_infoL.MaximalId()) != sgn(jet_infoB1.MaximalId())) return kBackground;

    analysis::JetInfo jet_infoB2 = octet.sextet().triplet2().singlet().user_info<analysis::JetInfo>();
    jet_infoB2.ExtractFraction(BottomId, TopId);
    if (jet_infoB1.MaximalId() != -jet_infoB2.MaximalId()) return kBackground;

    analysis::JetInfo jet_infoW1 = octet.sextet().triplet2().doublet().Singlet1().user_info<analysis::JetInfo>();
    jet_infoW1.ExtractFraction(WId, TopId);
    if (std::abs(jet_infoW1.MaximalId()) != WId) return kBackground;
    if (sgn(jet_infoW1.MaximalId()) != sgn(jet_infoB2.MaximalId())) return kBackground;

    analysis::JetInfo jet_infoB3 = octet.doublet().Singlet1().user_info<analysis::JetInfo>();
    jet_infoB3.ExtractFraction(BottomId, GluonId);
    if (std::abs(jet_infoB3.MaximalId()) != BottomId) return kBackground;

    analysis::JetInfo jet_infoB4 = octet.doublet().Singlet2().user_info<analysis::JetInfo>();
    jet_infoB4.ExtractFraction(BottomId, GluonId);
    if (jet_infoB3.MaximalId() != -jet_infoB4.MaximalId()) return kBackground;

    return kSignal;
}




std::vector<Octet62> hheavyhiggs::EventLeptonicTagger::GetBdt(const std::vector< analysis::Sextet > &sextets, const std::vector< analysis::Doublet > &doublets, Jets &jets, analysis::GlobalObservables &, const analysis::Reader & eventLeptonicReader)
{
    Print(kInformation, "Get event Tags");

    std::vector<Octet62> octets;
    for (const auto & doublet : doublets) {
        for (const auto & sextet : sextets) {
            if (sextet.triplet1().singlet() == doublet.Singlet1()) continue;
            if (sextet.triplet1().singlet() == doublet.Singlet2()) continue;
            if (sextet.triplet2().singlet() == doublet.Singlet1()) continue;
            if (sextet.triplet2().singlet() == doublet.Singlet2()) continue;
//             HOctet octet(sextet, doublet, global_observables);
            Octet62 octet(sextet, doublet);
            FillBranch(octet);
            octet.SetBdt(eventLeptonicReader.Bdt());
            octets.emplace_back(octet);
        }
    }
    std::sort(octets.begin(), octets.end());
    if (octets.size() > 1) octets.erase(octets.begin() + 1, octets.end());
    Print(kError, "event Number", octets.size(), jets.size());

    std::sort(jets.begin(), jets.end(), SortJetsByBdt());
    float MaxBBdt = 0;
    for (int i = 0; i < std::min(3, int(jets.size())); ++i)
        MaxBBdt += jets.at(i).user_info<analysis::JetInfo>().Bdt() / std::min(3, int(jets.size()));

//     float ThirdBBdt = 0;
//     if (jets.size() > 2) ThirdBBdt = jets.at(2).user_info<analysis::JetInfo>().Bdt();

    for (auto & octet : octets) {
        fastjet::PseudoJet RestJet(0., 0., 0., 0.);
//         int RestNumber = 0;
        for (const auto & Jet : jets)  {
//             octet.global_observablesM.TotalBBdt  += Jet.user_info<analysis::JetInfo>().Bdt() / jets.size();
//             if (octet.sextet().triplet1().singlet() == Jet) continue;
//             if (octet.sextet().triplet2().singlet() == Jet) continue;
//             if (octet.sextet().triplet2().doublet().Singlet1() == Jet) continue;
//             if (octet.sextet().triplet2().doublet().Singlet2() == Jet) continue;
//             if (octet.doublet().Singlet1() == Jet) continue;
//             if (octet.doublet().Singlet2() == Jet) continue;
//             ++RestNumber;
//             octet.global_observablesM.RestHt += Jet.pt();
//             octet.global_observablesM.RestBTag += Jet.user_info<analysis::JetInfo>().BTag();
//             octet.global_observablesM.RestBBdt += Jet.user_info<analysis::JetInfo>().Bdt();
//             octet.global_observablesM.MaxBBdt = MaxBBdt;
//             RestJet += Jet;
//         }
//         octet.global_observablesM.RestBBdt /= RestNumber;
//         octet.global_observablesM.ThirdBBdt = ThirdBBdt;
//         if (RestJet != fastjet::PseudoJet(0, 0, 0, 0)) {
//             octet.global_observablesM.RestM = RestJet.m();
//             octet.global_observablesM.RestPt = RestJet.pt();
//             octet.global_observablesM.RestRap = RestJet.rap();
//             octet.global_observablesM.RestPhi = RestJet.phi();
        }

    }

    return octets;
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
    ExRootTreeBranch *ResultBranch = TreeWriter->NewBranch(branch_name().c_str(), analysis::HResultBranch::Class());

    for (const int eventNumber : Range(const_cast<ExRootTreeReader *>(TreeReader)->GetEntries())) {

        const_cast<ExRootTreeReader *>(TreeReader)->ReadEntry(eventNumber);

        for (const int Entry : Range(eventClonesArray->GetEntriesFast())) {


            EventLeptonicBranch *Test = (EventLeptonicBranch *) eventClonesArray->At(Entry);
            const float Bdt = Test->Bdt;

            analysis::HResultBranch *Export = static_cast<analysis::HResultBranch *>(ResultBranch->NewEntry());
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






