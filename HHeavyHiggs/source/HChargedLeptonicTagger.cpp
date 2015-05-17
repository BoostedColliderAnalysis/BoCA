# include "HChargedLeptonicTagger.hh"

hheavyhiggs::HChargedLeptonicTagger::HChargedLeptonicTagger(analysis::BottomTagger *const NewBottomTagger, analysis::HTopLeptonicTagger *const NewTopTagger, analysis::HHeavyHiggsLeptonicTagger *const NewHeavyHiggsTagger)
{

    Print(kNotification , "Constructor");

    bottom_tagger_ = NewBottomTagger;
    BottomReader.set_tagger(bottom_tagger_);
    TopLeptonicTagger = NewTopTagger;
    TopLeptonicReader.set_tagger(TopLeptonicTagger);
    ChargedHiggsLeptonicTagger = NewHeavyHiggsTagger;
    ChargedHiggsLeptonicReader.set_tagger(ChargedHiggsLeptonicTagger);

    set_tagger_name("eventLeptonic");

//     Branch = new hheavyhiggs::HChargedLeptonicBranch();

    DefineVariables();

}

hheavyhiggs::HChargedLeptonicTagger::HChargedLeptonicTagger()
{

    Print(kNotification , "Constructor");

    set_tagger_name("ChargedLeptonic");
//     Branch = new hheavyhiggs::HChargedLeptonicBranch();

    DefineVariables();

}


hheavyhiggs::HChargedLeptonicTagger::~HChargedLeptonicTagger()
{

    Print(kNotification , "Constructor");

    // delete Branch;
    delete BottomReader;
    delete TopLeptonicReader;
    delete ChargedHiggsLeptonicReader;

}

void hheavyhiggs::HChargedLeptonicTagger::FillBranch(hheavyhiggs::HChargedLeptonicBranch *eventLeptonicBranch, const HOctet44 &Octet)
{
    Print(kInformation, "FillPairTagger", Octet.Bdt());

    eventLeptonicBranch->LeptonNumber = Octet.GetLeptonNumber();
    eventLeptonicBranch->JetNumber = Octet.GetJetNumber();
    eventLeptonicBranch->BottomNumber = Octet.GetBottomNumber();

    eventLeptonicBranch->ScalarHt = Octet.GetScalarHt();
    eventLeptonicBranch->HeavyParticleBdt = Octet.Bdt();

    eventLeptonicBranch->HeavyHiggsBdt = Octet.Quartet1().Bdt();
    eventLeptonicBranch->HeavyHiggsMass = Octet.GetQuartet1Jet().m();
    eventLeptonicBranch->HeavyHiggsPt = Octet.GetQuartet1Jet().pt();

    eventLeptonicBranch->BottomSumPt = Octet.GetQuartet2Jet().pt();
    eventLeptonicBranch->BottomDeltaPt = Octet.Quartet2().DeltaPt();

    eventLeptonicBranch->BottomDeltaRap = Octet.Quartet2().DeltaRap();
    eventLeptonicBranch->BottomDeltaPhi = Octet.Quartet2().GetPhiDelta();
    eventLeptonicBranch->BottomDeltaR = Octet.Quartet2().DeltaR();

    eventLeptonicBranch->HbSumDeltaRap = Octet.GetHbSumDeltaRap();
    eventLeptonicBranch->HbSumDeltaPhi = Octet.GetHbSumDeltaPhi();
    eventLeptonicBranch->HbSumDeltaR = Octet.GetHbSumDeltaR();

    eventLeptonicBranch->HbDeltaDeltaRap = Octet.GetHbDeltaDeltaRap();
    eventLeptonicBranch->HbDeltaDeltaPhi = Octet.GetHbDeltaDeltaPhi();
    eventLeptonicBranch->HbDeltaDeltaR = Octet.GetHbDeltaDeltaR();

    eventLeptonicBranch->eventTag = Octet.Tag();
}

void hheavyhiggs::HChargedLeptonicTagger::FillBranch(const HOctet44 &Octet)
{
    Print(kInformation, "FillPairTagger");
    FillBranch(&Branch, Octet);
}

void hheavyhiggs::HChargedLeptonicTagger::DefineVariables()
{

    Print(kNotification , "Define Variables");

    AddVariable(Branch.JetNumber, "JetNumber");
    AddVariable(Branch.BottomNumber, "BottomNumber");

    AddVariable(Branch.ScalarHt, "ScalarHt");
    AddVariable(Branch.HeavyParticleBdt, "HeavyParticleBdt");

    AddVariable(Branch.HeavyHiggsBdt, "HeavyHiggsBdt");
    AddVariable(Branch.HeavyHiggsPt, "HeavyHiggsPt");

    AddVariable(Branch.BottomSumPt, "BottomSumPt");
    AddVariable(Branch.BottomDeltaPt, "BottomDeltaPt");

    AddVariable(Branch.BottomDeltaRap, "BottomDeltaRap");
    AddVariable(Branch.BottomDeltaPhi, "BottomDeltaPhi");
    AddVariable(Branch.BottomDeltaR, "BottomDeltaR");

    AddVariable(Branch.HbSumDeltaRap, "HbSumDeltaRap");
    AddVariable(Branch.HbSumDeltaPhi, "HbSumDeltaPhi");
    AddVariable(Branch.HbSumDeltaR, "HbSumDeltaR");

    AddVariable(Branch.HbDeltaDeltaRap, "HbDeltaDeltaRap");
    AddVariable(Branch.HbDeltaDeltaPhi, "HbDeltaDeltaPhi");
    AddVariable(Branch.HbDeltaDeltaR, "HbDeltaDeltaR");

    AddSpectator(Branch.LeptonNumber, "LeptonNumber");
    AddSpectator(Branch.eventTag, "eventTag");
    AddSpectator(Branch.HeavyHiggsMass, "HeavyHiggsMass");

    Print(kNotification, "Variables defined");

}

struct SortByQuartetBdt {
    inline bool operator()(const HOctet44 &Octet1, const HOctet44 &Octet2) {
        return (Octet1.GetQuartet1().Bdt() > Octet2.GetQuartet1().Bdt();
    }
};


std::vector<hheavyhiggs::HChargedLeptonicBranch *> hheavyhiggs::HChargedLeptonicTagger::GetBranches(analysis::Event &event, const Object::Tag Tag)
{

    Jets jets = event.Hadrons().GetStructuredJets();

    jets = BottomTagger->GetTruthBdt(jets, BottomReader);

    Jets Leptons = event.Leptons().GetLeptonJets();
    Print(kInformation, "Numeber of Jets", jets.size(), Leptons.size());

    std::vector<analysis::Doublet> Topdoublets = TopLeptonicTagger->GetBdt(jets, Leptons, TopLeptonicReader);

    fastjet::PseudoJet MissingEt = event.Hadrons().GetMissingEt();
    Jets Neutrinos = event.Partons().GetNeutrinos();

    std::vector<analysis::Triplet> triplets1 = ChargedHiggsLeptonicTagger->GetBdt(Topdoublets, ChargedHiggsLeptonicReader);

    std::vector<analysis::Triplet> triplets2;
    for (const auto Jet : jets) 
        for (const auto Doulbet : Topdoublets) {
            analysis::Triplet triplet(Doulbet, Jet); // TODO Implemetn pair bdt here
            triplets2.emplace_back(triplet);
        }

    std::vector<HOctet44> Octets;
    for (const auto & triplet2 : triplets2) {
        for (const auto & triplet1 : triplets1) {
            if (triplet1.Gettriplet1().GetJet() == triplet2.GetJet1()) continue;
            if (triplet1.Gettriplet1().GetJet() == triplet2.GetJet2()) continue;
            if (triplet1.Gettriplet2().GetJet() == triplet2.GetJet1()) continue;
            if (triplet1.Gettriplet2().GetJet() == triplet2.GetJet2()) continue;
            analysis::HSextet Sextet(triplet1, triplet2);
            HOctet44 PreOctets = GetOctet(Sextet, MissingEt, Neutrinos, Tag);
            for (auto & Octet : PreOctets) Octets.emplace_back(Octet);
        }
    }

    if (Octets.size() > 1) {
        Print(kError, "more than one event");
        std::sort(Octets.begin(), Octets.end(), SortByQuartetBdt());
        Octets.erase(Octets.begin() + 1, Octets.end());
    }

    std::vector<hheavyhiggs::HChargedLeptonicBranch *> eventLeptonicBranches;
    for (auto & Octet : Octets) {
        hheavyhiggs::HChargedLeptonicBranch *eventLeptonicBranch = new hheavyhiggs::HChargedLeptonicBranch();
        Octet.SetLeptonNumber(event.Leptons().GetLeptonJets().size());
        Octet.SetJetNumber(event.Hadrons().GetJets().size());
        Octet.SetBottomNumber(event.Hadrons().GetBottomJets().size());
        Octet.SetScalarHt(event.Hadrons().GetScalarHt());
        Octet.SetTag(Tag);
        FillBranch(eventLeptonicBranch, Octet);
        eventLeptonicBranches.emplace_back(eventLeptonicBranch);
    }

    return eventLeptonicBranches;

}


void hheavyhiggs::HChargedLeptonicTagger::SetMomentum(double Momentum[4], const fastjet::PseudoJet &Jet)
{
    Momentum[0] = Jet.E();
    Momentum[1] = Jet.px();
    Momentum[2] = Jet.py();
    Momentum[3] = Jet.pz();
}


std::vector<HOctet44> hheavyhiggs::HChargedLeptonicTagger::GetOctets(const analysis::HSextet &Sextet, const fastjet::PseudoJet &MissingEt)
{

    Print(kInformation, "Get Triple Pairs");

    SetMomentum(Structure.p3, Sextet.triplet1().Getdoublet().Singlet2());
    SetMomentum(Structure.p4, Sextet.triplet2().Getdoublet().Singlet2());
    SetMomentum(Structure.p5, Sextet.triplet1().Getdoublet().Singlet1());
    SetMomentum(Structure.p6, Sextet.triplet2().Getdoublet().Singlet1());
    SetMomentum(Structure.pmiss, MissingEt);

    Print(kDebug, "Lepton 1 (p3)", GetJet(Structure.p3));
    Print(kDebug, "Lepton 2 (p4)" , GetJet(Structure.p4));
    Print(kDebug, "Jet 1 (p5)" , GetJet(Structure.p5));
    Print(kDebug, "Jet 2 (p6)" , GetJet(Structure.p6));
    Print(kDebug, "PMiss" , GetJet(Structure.pmiss));

    double P1[4][4], P2[4][4];
    int SolutionSum;
    solve22(Structure, NeutrinoMass, WMass, TopMass, SolutionSum, P1, P2);
    Print(kDebug, "Number solutions", SolutionSum);

    std::vector<HOctet44> Octets;
    for (const int SolutionNumber : HRange(SolutionSum)) {
        Print(kDebug, "Solution ", SolutionNumber);
        Print(kDebug, "Neutrino 1 (p1)" , GetJet(P1[SolutionNumber]));
        Print(kDebug, "Neutrino 2 (p2)" , GetJet(P2[SolutionNumber]));

        analysis::Doublet doublet1(Sextet.triplet1().Getdoublet().Singlet2(), GetJet(P1[SolutionNumber]));
        if (doublet1.Jet().m() <= 0) continue;
        analysis::Doublet doublet2(Sextet.triplet2().Getdoublet().Singlet2(), GetJet(P2[SolutionNumber]));
        if (doublet2.GetJet().m() <= 0) continue;

        analysis::Triplet triplet1(doublet1, Sextet.triplet1().Getdoublet().Singlet1());
        if (triplet1.GettripletJet().m() <= 0) continue;
        analysis::Triplet triplet2(doublet2, Sextet.triplet2().Getdoublet().Singlet1());
        if (triplet2.GettripletJet().m() <= 0) continue;

        analysis::HQuartet31 Quartet1(triplet1, Sextet.triplet1().GetJet());
        if (Quartet1.Jet().m() <= 0) continue;
        analysis::HQuartet31 Quartet2(triplet2, Sextet.triplet2().GetJet());
        if (Quartet2.Jet().m() <= 0) continue;

        HOctet44 Octet(Quartet1, Quartet2);
        if (Octet.GetJet().m() <= 0) continue;
        Octet.SetTag(Sextet.Tag());
        Octet.SetBdt(Sextet.Bdt());
        Octets.emplace_back(Octet);

        Print(kDebug, "TriplePair Bdt", Octet.Bdt(), Sextet.Bdt());
        //         Print(kDebug, "Neutrino masses", Jet1.m(), Jet2.m());
        Print(kDebug, "W masses", (GetJet(P1[SolutionNumber]) + Sextet.triplet1().Getdoublet().Singlet2()).m(), (GetJet(P2[SolutionNumber]) + Sextet.triplet2().Getdoublet().Singlet2()).m());
        Print(kDebug, "top masses", (GetJet(P1[SolutionNumber]) + Sextet.triplet1().Getdoublet().Singlet2() + Sextet.triplet1().Getdoublet().Singlet1()).m(), (GetJet(P2[SolutionNumber]) + Sextet.triplet2().Getdoublet().Singlet2() + Sextet.triplet2().Getdoublet().Singlet1()).m());
        //         Print(kDebug, "Higg mass", (Jet1 + Pair1.GetJet2() + Pair1.GetJet1() + Jet2 + Pair2.GetJet2() + Pair1.GetJet1()).m());
    }

    return Octets;

}


HOctet44 hheavyhiggs::HChargedLeptonicTagger::GetOctet(analysis::HSextet Sextet, fastjet::PseudoJet MissingEt, const Jets &Neutrinos, const analysis::Object::Tag Tag)
{

    Print(kInformation, "Get Triple Pair");

    std::vector<HOctet44> Octets = GetOctets(Sextet, MissingEt);
    Print(kDebug, "Number Solutions", Octets.size());

    if (Octets.empty()) return Octets;

    for (const auto & Neutrino : Neutrinos) Print(kDebug, "Neutrino", Neutrino);
    Print(kDebug, "Neutrino Sum", Neutrinos[0] + Neutrinos[1]);
    Print(kDebug, "MET", MissingEt);

    std::map<float, HOctet44> Map;
    for (const auto & Octet : Octets) {
        fastjet::PseudoJet Neutrino1 = Octet.GetQuartet1().Gettriplet().doublet().Singlet2();
        fastjet::PseudoJet Neutrino2 = Octet.GetQuartet2().Gettriplet().doublet().Singlet2();

        std::vector<float> Neutrino1Errors, Neutrino2Errors;
        for (const auto & Neutrino : Neutrinos) {
            Neutrino1Errors.emplace_back((Neutrino + Neutrino1).m());
            Print(kDebug, "Neutrino 1 Error", (Neutrino + Neutrino1).m());
            Neutrino2Errors.emplace_back((Neutrino + Neutrino2).m());
            Print(kDebug, "Neutrino 2 Error", (Neutrino + Neutrino2).m());
        }

        float Error = LargeNumber;
        for (const auto Neutrino1Error : Neutrino1Errors)
            for (const auto Neutrino2Error : Neutrino2Errors) {
                if (&Neutrino1Error - &Neutrino1Errors[0] == &Neutrino2Error - &Neutrino2Errors[0]) continue;
                if (Neutrino1Error + Neutrino2Error < Error) Error = Neutrino1Error + Neutrino2Error;

            }

        Map[Error] = Octet;
        Print(kDebug, "TriplePair Bdt", Octet.Bdt());
    }

    for (const auto & Pair : Map) Print(kDebug, "Neutrino Error Sum", Pair.first);
    if (Tag == kSignal) Map.erase(std::next(Map.begin()), Map.end());
    else Map.erase(Map.begin());

    std::vector<HOctet44> FinalOctet;
    for (const auto Pair : Map) {
        HOctet44 Octet = Pair.second;
        FinalOctet.emplace_back(Octet);
    }

    return FinalOctet;

}

std::vector<int> hheavyhiggs::HChargedLeptonicTagger::ApplyBdt2(const ExRootTreeReader *const TreeReader, const std::string TreeName, const TFile *const ExportFile, const TMVA::Reader &Reader)
{
    Print(kNotification, "Apply Bdt", branch_name_);

    const int Steps2 = 10;
    std::vector<int> eventNumbers(Steps2);

    const TClonesArray *const eventClonesArray = const_cast<ExRootTreeReader *>(TreeReader)->UseBranch(branch_name_.c_str());

    ExRootTreeWriter *TreeWriter = new ExRootTreeWriter(const_cast<TFile *>(ExportFile), TreeName.c_str());
    ExRootTreeBranch *BdtBranch = TreeWriter->NewBranch(branch_name_.c_str(), HBdtBranch::Class());

    for (const int eventNumber : HRange(const_cast<ExRootTreeReader *>(TreeReader)->GetEntries())) {

        const_cast<ExRootTreeReader *>(TreeReader)->ReadEntry(eventNumber);

        for (const int Entry : HRange(eventClonesArray->GetEntriesFast())) {

            (*Branch) = *((HChargedLeptonicBranch *) eventClonesArray->At(Entry));

            HBdtBranch *Export = static_cast<HBdtBranch *>(BdtBranch->NewEntry());

            const float Bdt = const_cast<TMVA::Reader *>(&Reader)->EvaluateMVA(bdt_method_name_);
            const float Error = Reader->GetMVAError();
            const float Rarity = Reader->GetRarity(GetBdtMethodName());
            const int Steps = 10;
            std::vector<float> Probabilities;
            for (int Step = Steps; Step > 0; --Step) {
                const float SignalFraction = float(Step) / Steps;
                const float Probability = Reader->GetProba(GetBdtMethodName(), SignalFraction);
                Probabilities.emplace_back(Probability);

            }
            Print(kDebug, "Bdt", Bdt, Error, Rarity);
            Export->Mass = Branch->HeavyHiggsMass;
            Export->eventTag = Branch->eventTag;
            Export->Bdt = Bdt;
            Export->Error = Error;
            Export->Rarity = Rarity;
            Export->Probability01 = Probabilities.at(0);
            Export->Probability02 = Probabilities.at(1);
            Export->Probability03 = Probabilities.at(2);
            Export->Probability04 = Probabilities.at(3);
            Export->Probability05 = Probabilities.at(4);
            Export->Probability06 = Probabilities.at(5);
            Export->Probability07 = Probabilities.at(6);
            Export->Probability08 = Probabilities.at(7);
            Export->Probability09 = Probabilities.at(8);
            Export->Probability10 = Probabilities.at(9);



            for (int Step = 0; Step < Steps2; ++Step) {
                const float Cut = float(Step - 5) / Steps2 / 2;
                if (Bdt > Cut) ++eventNumbers.at(Step);
            }

        }

        TreeWriter->Fill();
        TreeWriter->Clear();

    }

    TreeWriter->Write();
    delete TreeWriter;

    return eventNumbers;
}






