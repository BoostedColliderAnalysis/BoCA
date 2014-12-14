# include "HHeavyHiggsLeptonicTagger.hh"

hanalysis::HHeavyHiggsLeptonicTagger::HHeavyHiggsLeptonicTagger(HBottomTagger *const NewBottomTagger, HTopLeptonicTagger *const NewTopLeptonicTagger)
{
//     DebugLevel = hanalysis::HObject::HDebug;

    Print(HNotification, "Constructor");

    BottomTagger = NewBottomTagger;
    BottomReader = new HReader(BottomTagger);
    TopLeptonicTagger = NewTopLeptonicTagger;
    TopLeptonicReader = new HReader(TopLeptonicTagger);

    SetTaggerName("HeavyHiggsLeptonic");

    Branch = new HHeavyHiggsLeptonicBranch();
    JetTag = new HJetTag();

    DefineVariables();
}

hanalysis::HHeavyHiggsLeptonicTagger::~HHeavyHiggsLeptonicTagger()
{
    Print(HNotification, "Destructor");
    delete Branch;
    delete JetTag;
    delete BottomReader;
    delete TopLeptonicReader;

}

void hanalysis::HHeavyHiggsLeptonicTagger::FillBranch(const hanalysis::HSextet &TriplePair)
{
    Print(HInformation, "FillPairTagger", TriplePair.GetBdt());
    FillBranch(Branch, TriplePair);
}

void hanalysis::HHeavyHiggsLeptonicTagger::FillBranch(HHeavyHiggsLeptonicBranch *HeavyHiggsBranch, const HSextet &Sextet)
{
    Print(HInformation, "FillPairTagger", Sextet.GetBdt());

    HeavyHiggsBranch->HeavyHiggsMass = Sextet.GetSextetJet().m();
    HeavyHiggsBranch->HeavyHiggsPt = Sextet.GetSextetJet().m();

    HeavyHiggsBranch->TopDeltaR = Sextet.GetDeltaR();
    HeavyHiggsBranch->TopDeltaRap = Sextet.GetDeltaRap();
    HeavyHiggsBranch->TopDeltaPhi = Sextet.GetDeltaPhi();

    HeavyHiggsBranch->LargerWDeltaR = Sextet.GetLargerTripletDeltaR();
    HeavyHiggsBranch->LargerWDeltaRap = Sextet.GetLargerTripletDeltaRap();
    HeavyHiggsBranch->LargerWDeltaPhi = Sextet.GetLargerTripleDeltaPhi();

    HeavyHiggsBranch->SmallerWDeltaR = Sextet.GetSmallerTripletDeltaR();
    HeavyHiggsBranch->SmallerWDeltaRap = Sextet.GetSmallerTripletDeltaRap();
    HeavyHiggsBranch->SmallerWDeltaPhi = Sextet.GetSmallerTripletDeltaPhi();

    HeavyHiggsBranch->LargerNeutrinoDeltaR = Sextet.GetLargerTripletDeltaR();
    HeavyHiggsBranch->LargerNeutrinoDeltaRap = Sextet.GetLargerTripletDeltaRap();
    HeavyHiggsBranch->LargerNeutrinoDeltaPhi = Sextet.GetLargerTripleDeltaPhi();

    HeavyHiggsBranch->SmallerNeutrinoDeltaR = Sextet.GetSmallerTripletDeltaR();
    HeavyHiggsBranch->SmallerNeutrinoDeltaRap = Sextet.GetSmallerTripletDeltaRap();
    HeavyHiggsBranch->SmallerNeutrinoDeltaPhi = Sextet.GetSmallerTripletDeltaPhi();

    HeavyHiggsBranch->TopBdt = Sextet.GetBdt();
    HeavyHiggsBranch->HeavyHiggsTag = Sextet.GetTag();

}

void hanalysis::HHeavyHiggsLeptonicTagger::DefineVariables()
{

    Print(HNotification , "Define Variables");

    Observables.push_back(NewObservable(&Branch->HeavyHiggsPt, "HeavyHiggsPt"));

    Observables.push_back(NewObservable(&Branch->TopDeltaR, "TopDeltaR"));
    Observables.push_back(NewObservable(&Branch->TopDeltaRap, "TopDeltaRap"));
    Observables.push_back(NewObservable(&Branch->TopDeltaPhi, "TopDeltaPhi"));

    Observables.push_back(NewObservable(&Branch->LargerWDeltaR, "LargerWDeltaR"));
    Observables.push_back(NewObservable(&Branch->LargerWDeltaRap, "LargerWDeltaRap"));
    Observables.push_back(NewObservable(&Branch->LargerWDeltaPhi, "LargerWDeltaPhi"));

    Observables.push_back(NewObservable(&Branch->SmallerWDeltaR, "SmallerWDeltaR"));
    Observables.push_back(NewObservable(&Branch->SmallerWDeltaRap, "SmallerWDeltaRap"));
    Observables.push_back(NewObservable(&Branch->SmallerWDeltaPhi, "SmallerWDeltaPhi"));

    Observables.push_back(NewObservable(&Branch->LargerNeutrinoDeltaR, "LargerNeutrinoDeltaR"));
    Observables.push_back(NewObservable(&Branch->LargerNeutrinoDeltaRap, "LargerNeutrinoDeltaRap"));
    Observables.push_back(NewObservable(&Branch->LargerNeutrinoDeltaPhi, "LargerNeutrinoDeltaPhi"));

    Observables.push_back(NewObservable(&Branch->SmallerNeutrinoDeltaR, "SmallerNeutrinoDeltaR"));
    Observables.push_back(NewObservable(&Branch->SmallerNeutrinoDeltaRap, "SmallerNeutrinoDeltaRap"));
    Observables.push_back(NewObservable(&Branch->SmallerNeutrinoDeltaPhi, "SmallerNeutrinoDeltaPhi"));

    Observables.push_back(NewObservable(&Branch->TopBdt, "TopBdt"));

    Spectators.push_back(NewObservable(&Branch->HeavyHiggsTag, "HeavyHiggsTag"));
    Spectators.push_back(NewObservable(&Branch->HeavyHiggsMass, "HeavyHiggsMass"));

    Print(HNotification, "Variables defined");

}


std::vector< HHeavyHiggsLeptonicBranch * > hanalysis::HHeavyHiggsLeptonicTagger::GetBranches(HEvent *const Event, const HObject::HTag Tag)
{
    Print(HInformation, "Get Higgs Tags");

    JetTag->HeavyParticles = {TopId, HeavyHiggsId, WId};
    HJets Jets = Event->GetJets()->GetStructuredTaggedJets(JetTag);

    Jets = BottomTagger->GetBdt(Jets, BottomReader);

    HJets Leptons = Event->GetLeptons()->GetTaggedJets(JetTag);
    Print(HInformation, "Numeber of Jets", Jets.size(), Leptons.size());

    std::vector<HDoublet> Doublets = TopLeptonicTagger->GetBdt(Jets, Leptons, TopLeptonicReader);

    fastjet::PseudoJet MissingEt = Event->GetJets()->GetMissingEt();
    HJets Neutrinos = Event->GetParticles()->GetNeutrinos();

    Print(HInformation, "Number of Doublets", Doublets.size());

    std::vector<HSextet> Sextets;
    for (const auto & Doublet1 : Doublets) {
        Print(HInformation, "Doublet 1", GetParticleName(Doublet1.GetJet1().user_index()), GetParticleName(Doublet1.GetJet2().user_index()));
        for (const auto & Doublet2 : Doublets) {
            Print(HInformation, "Doublet 2", GetParticleName(Doublet2.GetJet1().user_index()), GetParticleName(Doublet2.GetJet2().user_index()));
            if (Doublet1.GetJet1() == Doublet2.GetJet1()) continue;
            if (Doublet1.GetJet2() == Doublet2.GetJet2()) continue;
            HQuartet Quartet(Doublet1, Doublet2);
            Quartet.SetTag(GetTag(Quartet));
            if (Quartet.GetTag() != Tag) continue;
            std::vector<HSextet> PreSextets;
            if (Tag == HSignal) PreSextets = GetSextet(Quartet, MissingEt, Neutrinos);
            else PreSextets = GetSextets(Quartet, MissingEt);
            for (auto & Sextet : PreSextets) {
                if (Sextet.GetSextetJet().m() < 10) continue; // TODO do we need this
                Sextets.push_back(Sextet);
            }
        }
    }
    Print(HInformation, "Numeber of Sextets", Sextets.size());


    if (Tag == HSignal && Sextets.size() > 1) {
        Print(HError, "Higgs Candidates", Sextets.size());
        std::sort(Sextets.begin(), Sextets.end(), SortByBdt());
        Sextets.erase(Sextets.begin() + 1, Sextets.end());
    }

    std::vector<HHeavyHiggsLeptonicBranch *> HeavyHiggsBranches;
    for (const auto & Sextet : Sextets) {
        HHeavyHiggsLeptonicBranch *HeavyHiggsLeptonicBranch = new HHeavyHiggsLeptonicBranch();
        FillBranch(HeavyHiggsLeptonicBranch, Sextet);
        HeavyHiggsBranches.push_back(HeavyHiggsLeptonicBranch);
    }

    return HeavyHiggsBranches;

}

hanalysis::HObject::HTag hanalysis::HHeavyHiggsLeptonicTagger::GetTag(const HQuartet &Quartet)
{
    Print(HInformation, "Get Triple Tag");

    if(Quartet.GetDoublet1().GetTag() == HBackground) return HBackground;
    if(Quartet.GetDoublet2().GetTag() == HBackground) return HBackground;
    if (Quartet.GetDoublet1().GetJet1().user_index() != -Quartet.GetDoublet2().GetJet1().user_index()) return HBackground;
    return HSignal;
}

std::vector<hanalysis::HSextet>  hanalysis::HHeavyHiggsLeptonicTagger::GetBdt(const std::vector<HDoublet> &Doublets , const fastjet::PseudoJet &MissingEt, const HReader *const Reader)
{
    Print(HInformation, "Get Bdt");

    std::vector<HSextet> Sextets;
    for (const auto & Doublet1 : Doublets) {
        for (const auto & Doublet2 : Doublets) {
            if (Doublet1.GetJet1() == Doublet2.GetJet1()) continue;
            if (Doublet1.GetJet2() == Doublet2.GetJet2()) continue;
            HQuartet Quartet(Doublet1, Doublet2);
            Quartet.SetTag(GetTag(Quartet));
            std::vector<HSextet> PreSextets;
            PreSextets = GetSextets(Quartet, MissingEt);
            for (auto & Sextet : PreSextets) {
                if (Sextet.GetSextetJet().m() < 10) continue; // TODO do we need this
                FillBranch(Sextet);
                Sextet.SetBdt(Reader->GetBdt());
                Sextets.push_back(Sextet);
            }
        }
    }
    return Sextets;
}


void hanalysis::HHeavyHiggsLeptonicTagger::SetMomentum(double Momentum[4], const fastjet::PseudoJet &Jet)
{
    Momentum[0] = Jet.E();
    Momentum[1] = Jet.px();
    Momentum[2] = Jet.py();
    Momentum[3] = Jet.pz();
}

std::vector<hanalysis::HSextet> hanalysis::HHeavyHiggsLeptonicTagger::GetSextets(const HQuartet &Quartet, const fastjet::PseudoJet &MissingEt)
{
    Print(HInformation, "Get Triple Pairs");

    SetMomentum(Structure.p3, Quartet.GetDoublet1().GetJet2());
    SetMomentum(Structure.p4, Quartet.GetDoublet2().GetJet2());
    SetMomentum(Structure.p5, Quartet.GetDoublet1().GetJet1());
    SetMomentum(Structure.p6, Quartet.GetDoublet2().GetJet1());
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

    std::vector<hanalysis::HSextet> Sextets;
    for (const int SolutionNumber : HRange(SolutionSum)) {
        Print(HDebug, "Solution ", SolutionNumber);
        Print(HDebug, "Neutrino 1 (p1)" , GetJet(P1[SolutionNumber]));
        Print(HDebug, "Neutrino 2 (p2)" , GetJet(P2[SolutionNumber]));

        HDoublet Doublet1(Quartet.GetDoublet1().GetJet2(), GetJet(P1[SolutionNumber]));
        if (Doublet1.GetDoubletJet().m() <= 0) continue;
        HDoublet Doublet2(Quartet.GetDoublet2().GetJet2(), GetJet(P2[SolutionNumber]));
        if (Doublet2.GetDoubletJet().m() <= 0) continue;

        HTriplet Triplet1(Doublet1, Quartet.GetDoublet1().GetJet1());
        if (Triplet1.GetTripletJet().m() <= 0) continue;
        HTriplet Triplet2(Doublet2, Quartet.GetDoublet2().GetJet1());
        if (Triplet2.GetTripletJet().m() <= 0) continue;

        HSextet Sextet(Triplet1, Triplet2);
        if (Sextet.GetSextetJet().m() <= 0) continue;
        Sextet.SetTag(Quartet.GetTag());
        Sextet.SetBdt(Quartet.GetBdt());
        Sextets.push_back(Sextet);

        Print(HDebug, "TriplePair Bdt", Sextet.GetBdt(), Quartet.GetBdt());
        //         Print(HDebug, "Neutrino masses", Jet1.m(), Jet2.m());
        Print(HDebug, "W masses", (GetJet(P1[SolutionNumber]) + Quartet.GetDoublet1().GetJet2()).m(), (GetJet(P2[SolutionNumber]) + Quartet.GetDoublet2().GetJet2()).m());
        Print(HDebug, "top masses", (GetJet(P1[SolutionNumber]) + Quartet.GetDoublet1().GetJet2() + Quartet.GetDoublet1().GetJet1()).m(), (GetJet(P2[SolutionNumber]) + Quartet.GetDoublet2().GetJet2() + Quartet.GetDoublet1().GetJet1()).m());
        //         Print(HDebug, "Higg mass", (Jet1 + Pair1.GetJet2() + Pair1.GetJet1() + Jet2 + Pair2.GetJet2() + Pair1.GetJet1()).m());
    }

    return Sextets;

}

std::vector<hanalysis::HSextet> hanalysis::HHeavyHiggsLeptonicTagger::GetSextet(const HQuartet &Quartet, const fastjet::PseudoJet &MissingEt, const HJets &Neutrinos)
{
    Print(HInformation, "Get Triple Pair");

    std::vector<HSextet> Sextets = GetSextets(Quartet, MissingEt);
    Print(HDebug, "Number Solutions", Sextets.size());

    if (Sextets.size() < 1) return Sextets;
//     if (Neutrinos.size() < 2) return Sextets;

    fastjet::PseudoJet NeutrinoSum = Neutrinos[0] + Neutrinos[1];
    for (const auto & Neutrino : Neutrinos) Print(HDebug, "Neutrino", Neutrino);
    Print(HDebug, "Neutrino Sum", NeutrinoSum);
    Print(HDebug, "MET", MissingEt);

    std::map<float, HSextet> Map;
    for (const auto & Sextet : Sextets) {
        fastjet::PseudoJet Neutrino1 = Sextet.GetTriplet1().GetDoublet().GetJet2();
        fastjet::PseudoJet Neutrino2 = Sextet.GetTriplet2().GetDoublet().GetJet2();

        std::vector<float> Error1, Error2;
        for (const auto & Neutrino : Neutrinos) {
            //             Print(HError, "Neutrino Mass", Neutrino.m());
            Error1.push_back((Neutrino + Neutrino1).m());
            Print(HDebug, "Neutrino 1 Error", (Neutrino + Neutrino1).m());
            Error2.push_back((Neutrino + Neutrino2).m());
            Print(HDebug, "Neutrino 2 Error", (Neutrino + Neutrino2).m());
        }

        float Error = LargeNumber;
        for (size_t i = 0; i < Error1.size(); ++i) {
            for (size_t j = i + 1; j < Error2.size(); ++j) {
                if (Error1[i] + Error2[j] < Error) Error = Error1[i] + Error2[j];
            }
        }
        for (size_t j = 0; j < Error2.size(); ++j) {
            for (size_t i = j + 1; i < Error1.size(); ++i) {
                if (Error1[i] + Error2[j] < Error) Error = Error1[i] + Error2[j];
            }
        }
        Map[Error] = Sextet;
//         Sextet.SetError(Error);
        Print(HDebug, "TriplePair Bdt", Sextet.GetBdt());
    }

    for (const auto & Pair : Map) Print(HDebug, "Neutrino Error Sum", Pair.first);

    std::vector<HSextet> FinalSextet;
    std::pair<float , HSextet> Pair = *(Map.begin());
    HSextet Sextet = Pair.second;
    FinalSextet.push_back(Sextet);
//     FinalSextet.push_back(*(Map.begin()).second);

    return FinalSextet;
}




