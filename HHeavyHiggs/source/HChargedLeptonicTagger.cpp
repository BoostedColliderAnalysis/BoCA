# include "HChargedLeptonicTagger.hh"

hheavyhiggs::HChargedLeptonicTagger::HChargedLeptonicTagger(hanalysis::HBottomTagger *const NewBottomTagger, hanalysis::HTopLeptonicTagger *const NewTopTagger, hanalysis::HHeavyHiggsLeptonicTagger *const NewHeavyHiggsTagger)
{

    Print(HNotification , "Constructor");

    BottomTagger = NewBottomTagger;
    BottomReader.set_tagger(BottomTagger);
    TopLeptonicTagger = NewTopTagger;
    TopLeptonicReader.set_tagger(TopLeptonicTagger);
    ChargedHiggsLeptonicTagger = NewHeavyHiggsTagger;
    ChargedHiggsLeptonicReader.set_tagger(ChargedHiggsLeptonicTagger);

    SetTaggerName("EventLeptonic");

//     Branch = new hheavyhiggs::HChargedLeptonicBranch();

    DefineVariables();

}

hheavyhiggs::HChargedLeptonicTagger::HChargedLeptonicTagger()
{

    Print(HNotification , "Constructor");

    SetTaggerName("ChargedLeptonic");
//     Branch = new hheavyhiggs::HChargedLeptonicBranch();

    DefineVariables();

}


hheavyhiggs::HChargedLeptonicTagger::~HChargedLeptonicTagger()
{

    Print(HNotification , "Constructor");

    // delete Branch;
    delete BottomReader;
    delete TopLeptonicReader;
    delete ChargedHiggsLeptonicReader;

}

void hheavyhiggs::HChargedLeptonicTagger::FillBranch(hheavyhiggs::HChargedLeptonicBranch *EventLeptonicBranch, const HOctet44 &Octet)
{
    Print(HInformation, "FillPairTagger", Octet.Bdt());

    EventLeptonicBranch->LeptonNumber = Octet.GetLeptonNumber();
    EventLeptonicBranch->JetNumber = Octet.GetJetNumber();
    EventLeptonicBranch->BottomNumber = Octet.GetBottomNumber();

    EventLeptonicBranch->ScalarHt = Octet.GetScalarHt();
    EventLeptonicBranch->HeavyParticleBdt = Octet.Bdt();

    EventLeptonicBranch->HeavyHiggsBdt = Octet.Quartet1().Bdt();
    EventLeptonicBranch->HeavyHiggsMass = Octet.GetQuartet1Jet().m();
    EventLeptonicBranch->HeavyHiggsPt = Octet.GetQuartet1Jet().pt();

    EventLeptonicBranch->BottomSumPt = Octet.GetQuartet2Jet().pt();
    EventLeptonicBranch->BottomDeltaPt = Octet.Quartet2().DeltaPt();

    EventLeptonicBranch->BottomDeltaRap = Octet.Quartet2().DeltaRap();
    EventLeptonicBranch->BottomDeltaPhi = Octet.Quartet2().GetPhiDelta();
    EventLeptonicBranch->BottomDeltaR = Octet.Quartet2().DeltaR();

    EventLeptonicBranch->HbSumDeltaRap = Octet.GetHbSumDeltaRap();
    EventLeptonicBranch->HbSumDeltaPhi = Octet.GetHbSumDeltaPhi();
    EventLeptonicBranch->HbSumDeltaR = Octet.GetHbSumDeltaR();

    EventLeptonicBranch->HbDeltaDeltaRap = Octet.GetHbDeltaDeltaRap();
    EventLeptonicBranch->HbDeltaDeltaPhi = Octet.GetHbDeltaDeltaPhi();
    EventLeptonicBranch->HbDeltaDeltaR = Octet.GetHbDeltaDeltaR();

    EventLeptonicBranch->EventTag = Octet.Tag();
}

void hheavyhiggs::HChargedLeptonicTagger::FillBranch(const HOctet44 &Octet)
{
    Print(HInformation, "FillPairTagger");
    FillBranch(&Branch, Octet);
}

void hheavyhiggs::HChargedLeptonicTagger::DefineVariables()
{

    Print(HNotification , "Define Variables");

    AddObservable(Branch.JetNumber, "JetNumber");
    AddObservable(Branch.BottomNumber, "BottomNumber");

    AddObservable(Branch.ScalarHt, "ScalarHt");
    AddObservable(Branch.HeavyParticleBdt, "HeavyParticleBdt");

    AddObservable(Branch.HeavyHiggsBdt, "HeavyHiggsBdt");
    AddObservable(Branch.HeavyHiggsPt, "HeavyHiggsPt");

    AddObservable(Branch.BottomSumPt, "BottomSumPt");
    AddObservable(Branch.BottomDeltaPt, "BottomDeltaPt");

    AddObservable(Branch.BottomDeltaRap, "BottomDeltaRap");
    AddObservable(Branch.BottomDeltaPhi, "BottomDeltaPhi");
    AddObservable(Branch.BottomDeltaR, "BottomDeltaR");

    AddObservable(Branch.HbSumDeltaRap, "HbSumDeltaRap");
    AddObservable(Branch.HbSumDeltaPhi, "HbSumDeltaPhi");
    AddObservable(Branch.HbSumDeltaR, "HbSumDeltaR");

    AddObservable(Branch.HbDeltaDeltaRap, "HbDeltaDeltaRap");
    AddObservable(Branch.HbDeltaDeltaPhi, "HbDeltaDeltaPhi");
    AddObservable(Branch.HbDeltaDeltaR, "HbDeltaDeltaR");

    AddSpectator(Branch.LeptonNumber, "LeptonNumber");
    AddSpectator(Branch.EventTag, "EventTag");
    AddSpectator(Branch.HeavyHiggsMass, "HeavyHiggsMass");

    Print(HNotification, "Variables defined");

}

struct SortByQuartetBdt {
    inline bool operator()(const HOctet44 &Octet1, const HOctet44 &Octet2) {
        return (Octet1.GetQuartet1().Bdt() > Octet2.GetQuartet1().Bdt();
    }
};


std::vector<hheavyhiggs::HChargedLeptonicBranch *> hheavyhiggs::HChargedLeptonicTagger::GetBranches(hanalysis::HEvent &Event, const HObject::Tag Tag)
{

    HJets Jets = Event.GetJets()->GetStructuredJets();

    Jets = BottomTagger->GetTruthBdt(Jets, BottomReader);

    HJets Leptons = Event.GetLeptons()->GetLeptonJets();
    Print(HInformation, "Numeber of Jets", Jets.size(), Leptons.size());

    std::vector<hanalysis::HDoublet> TopDoublets = TopLeptonicTagger->GetBdt(Jets, Leptons, TopLeptonicReader);

    fastjet::PseudoJet MissingEt = Event.GetJets()->GetMissingEt();
    HJets Neutrinos = Event.GetParticles()->GetNeutrinos();

    std::vector<hanalysis::HTriplet> Triplets1 = ChargedHiggsLeptonicTagger->GetBdt(TopDoublets, ChargedHiggsLeptonicReader);

    std::vector<hanalysis::HTriplet> Triplets2;
    for (const auto Jet : Jets)
        for (const auto Doulbet : TopDoublets) {
            hanalysis::HTriplet Triplet(Doulbet, Jet); // TODO Implemetn pair bdt here
            Triplets2.emplace_back(Triplet);
        }

    std::vector<HOctet44> Octets;
    for (const auto & Triplet2 : Triplets2) {
        for (const auto & Triplet1 : Triplets1) {
            if (Triplet1.GetTriplet1().GetJet() == Triplet2.GetJet1()) continue;
            if (Triplet1.GetTriplet1().GetJet() == Triplet2.GetJet2()) continue;
            if (Triplet1.GetTriplet2().GetJet() == Triplet2.GetJet1()) continue;
            if (Triplet1.GetTriplet2().GetJet() == Triplet2.GetJet2()) continue;
            hanalysis::HSextet Sextet(Triplet1, Triplet2);
            HOctet44 PreOctets = GetOctet(Sextet, MissingEt, Neutrinos, Tag);
            for (auto & Octet : PreOctets) Octets.emplace_back(Octet);
        }
    }

    if (Octets.size() > 1) {
        Print(HError, "more than one event");
        std::sort(Octets.begin(), Octets.end(), SortByQuartetBdt());
        Octets.erase(Octets.begin() + 1, Octets.end());
    }

    std::vector<hheavyhiggs::HChargedLeptonicBranch *> EventLeptonicBranches;
    for (auto & Octet : Octets) {
        hheavyhiggs::HChargedLeptonicBranch *EventLeptonicBranch = new hheavyhiggs::HChargedLeptonicBranch();
        Octet.SetLeptonNumber(Event.GetLeptons()->GetLeptonJets().size());
        Octet.SetJetNumber(Event.GetJets()->GetJets().size());
        Octet.SetBottomNumber(Event.GetJets()->GetBottomJets().size());
        Octet.SetScalarHt(Event.GetJets()->GetScalarHt());
        Octet.SetTag(Tag);
        FillBranch(EventLeptonicBranch, Octet);
        EventLeptonicBranches.emplace_back(EventLeptonicBranch);
    }

    return EventLeptonicBranches;

}


void hheavyhiggs::HChargedLeptonicTagger::SetMomentum(double Momentum[4], const fastjet::PseudoJet &Jet)
{
    Momentum[0] = Jet.E();
    Momentum[1] = Jet.px();
    Momentum[2] = Jet.py();
    Momentum[3] = Jet.pz();
}


std::vector<HOctet44> hheavyhiggs::HChargedLeptonicTagger::GetOctets(const hanalysis::HSextet &Sextet, const fastjet::PseudoJet &MissingEt)
{

    Print(HInformation, "Get Triple Pairs");

    SetMomentum(Structure.p3, Sextet.Triplet1().GetDoublet().Singlet2());
    SetMomentum(Structure.p4, Sextet.Triplet2().GetDoublet().Singlet2());
    SetMomentum(Structure.p5, Sextet.Triplet1().GetDoublet().Singlet1());
    SetMomentum(Structure.p6, Sextet.Triplet2().GetDoublet().Singlet1());
    SetMomentum(Structure.pmiss, MissingEt);

    Print(HDebug, "Lepton 1 (p3)", GetJet(Structure.p3));
    Print(HDebug, "Lepton 2 (p4)" , GetJet(Structure.p4));
    Print(HDebug, "Jet 1 (p5)" , GetJet(Structure.p5));
    Print(HDebug, "Jet 2 (p6)" , GetJet(Structure.p6));
    Print(HDebug, "PMiss" , GetJet(Structure.pmiss));

    double P1[4][4], P2[4][4];
    int SolutionSum;
    solve22(Structure, NeutrinoMass, WMass, TopMass, SolutionSum, P1, P2);
    Print(HDebug, "Number solutions", SolutionSum);

    std::vector<HOctet44> Octets;
    for (const int SolutionNumber : HRange(SolutionSum)) {
        Print(HDebug, "Solution ", SolutionNumber);
        Print(HDebug, "Neutrino 1 (p1)" , GetJet(P1[SolutionNumber]));
        Print(HDebug, "Neutrino 2 (p2)" , GetJet(P2[SolutionNumber]));

        hanalysis::HDoublet Doublet1(Sextet.Triplet1().GetDoublet().Singlet2(), GetJet(P1[SolutionNumber]));
        if (Doublet1.Jet().m() <= 0) continue;
        hanalysis::HDoublet Doublet2(Sextet.Triplet2().GetDoublet().Singlet2(), GetJet(P2[SolutionNumber]));
        if (Doublet2.GetJet().m() <= 0) continue;

        hanalysis::HTriplet Triplet1(Doublet1, Sextet.Triplet1().GetDoublet().Singlet1());
        if (Triplet1.GetTripletJet().m() <= 0) continue;
        hanalysis::HTriplet Triplet2(Doublet2, Sextet.Triplet2().GetDoublet().Singlet1());
        if (Triplet2.GetTripletJet().m() <= 0) continue;

        hanalysis::HQuartet31 Quartet1(Triplet1, Sextet.Triplet1().GetJet());
        if (Quartet1.Jet().m() <= 0) continue;
        hanalysis::HQuartet31 Quartet2(Triplet2, Sextet.Triplet2().GetJet());
        if (Quartet2.Jet().m() <= 0) continue;

        HOctet44 Octet(Quartet1, Quartet2);
        if (Octet.GetJet().m() <= 0) continue;
        Octet.SetTag(Sextet.Tag());
        Octet.SetBdt(Sextet.Bdt());
        Octets.emplace_back(Octet);

        Print(HDebug, "TriplePair Bdt", Octet.Bdt(), Sextet.Bdt());
        //         Print(HDebug, "Neutrino masses", Jet1.m(), Jet2.m());
        Print(HDebug, "W masses", (GetJet(P1[SolutionNumber]) + Sextet.Triplet1().GetDoublet().Singlet2()).m(), (GetJet(P2[SolutionNumber]) + Sextet.Triplet2().GetDoublet().Singlet2()).m());
        Print(HDebug, "top masses", (GetJet(P1[SolutionNumber]) + Sextet.Triplet1().GetDoublet().Singlet2() + Sextet.Triplet1().GetDoublet().Singlet1()).m(), (GetJet(P2[SolutionNumber]) + Sextet.Triplet2().GetDoublet().Singlet2() + Sextet.Triplet2().GetDoublet().Singlet1()).m());
        //         Print(HDebug, "Higg mass", (Jet1 + Pair1.GetJet2() + Pair1.GetJet1() + Jet2 + Pair2.GetJet2() + Pair1.GetJet1()).m());
    }

    return Octets;

}


HOctet44 hheavyhiggs::HChargedLeptonicTagger::GetOctet(hanalysis::HSextet Sextet, fastjet::PseudoJet MissingEt, const HJets &Neutrinos, const hanalysis::HObject::Tag Tag)
{

    Print(HInformation, "Get Triple Pair");

    std::vector<HOctet44> Octets = GetOctets(Sextet, MissingEt);
    Print(HDebug, "Number Solutions", Octets.size());

    if (Octets.empty()) return Octets;

    for (const auto & Neutrino : Neutrinos) Print(HDebug, "Neutrino", Neutrino);
    Print(HDebug, "Neutrino Sum", Neutrinos[0] + Neutrinos[1]);
    Print(HDebug, "MET", MissingEt);

    std::map<float, HOctet44> Map;
    for (const auto & Octet : Octets) {
        fastjet::PseudoJet Neutrino1 = Octet.GetQuartet1().GetTriplet().Doublet().Singlet2();
        fastjet::PseudoJet Neutrino2 = Octet.GetQuartet2().GetTriplet().Doublet().Singlet2();

        std::vector<float> Neutrino1Errors, Neutrino2Errors;
        for (const auto & Neutrino : Neutrinos) {
            Neutrino1Errors.emplace_back((Neutrino + Neutrino1).m());
            Print(HDebug, "Neutrino 1 Error", (Neutrino + Neutrino1).m());
            Neutrino2Errors.emplace_back((Neutrino + Neutrino2).m());
            Print(HDebug, "Neutrino 2 Error", (Neutrino + Neutrino2).m());
        }

        float Error = LargeNumber;
        for (const auto Neutrino1Error : Neutrino1Errors)
            for (const auto Neutrino2Error : Neutrino2Errors) {
                if (&Neutrino1Error - &Neutrino1Errors[0] == &Neutrino2Error - &Neutrino2Errors[0]) continue;
                if (Neutrino1Error + Neutrino2Error < Error) Error = Neutrino1Error + Neutrino2Error;

            }

        Map[Error] = Octet;
        Print(HDebug, "TriplePair Bdt", Octet.Bdt());
    }

    for (const auto & Pair : Map) Print(HDebug, "Neutrino Error Sum", Pair.first);
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
    Print(HNotification, "Apply Bdt", branch_name_);

    const int Steps2 = 10;
    std::vector<int> EventNumbers(Steps2);

    const TClonesArray *const EventClonesArray = const_cast<ExRootTreeReader *>(TreeReader)->UseBranch(branch_name_.c_str());

    ExRootTreeWriter *TreeWriter = new ExRootTreeWriter(const_cast<TFile *>(ExportFile), TreeName.c_str());
    ExRootTreeBranch *BdtBranch = TreeWriter->NewBranch(branch_name_.c_str(), HBdtBranch::Class());

    for (const int EventNumber : HRange(const_cast<ExRootTreeReader *>(TreeReader)->GetEntries())) {

        const_cast<ExRootTreeReader *>(TreeReader)->ReadEntry(EventNumber);

        for (const int Entry : HRange(EventClonesArray->GetEntriesFast())) {

            (*Branch) = *((HChargedLeptonicBranch *) EventClonesArray->At(Entry));

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
            Print(HDebug, "Bdt", Bdt, Error, Rarity);
            Export->Mass = Branch->HeavyHiggsMass;
            Export->EventTag = Branch->EventTag;
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
                if (Bdt > Cut) ++EventNumbers.at(Step);
            }

        }

        TreeWriter->Fill();
        TreeWriter->Clear();

    }

    TreeWriter->Write();
    delete TreeWriter;

    return EventNumbers;
}






