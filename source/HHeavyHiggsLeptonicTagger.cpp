# include "HHeavyHiggsLeptonicTagger.hh"

hanalysis::HHeavyHiggsLeptonicTagger::HHeavyHiggsLeptonicTagger()
{
  //     DebugLevel = hanalysis::HObject::HDebug;

  Print(HNotification, "Constructor");
  set_tagger_name("HeavyHiggsLeptonic");
}

hanalysis::HHeavyHiggsLeptonicTagger::HHeavyHiggsLeptonicTagger(const BottomTagger &NewBottomTagger, const HTopLeptonicTagger &NewTopLeptonicTagger)
{
//     DebugLevel = hanalysis::HObject::HDebug;

    Print(HNotification, "Constructor");

    bottom_tagger_ = NewBottomTagger;
    BottomReader.set_tagger(bottom_tagger_);
    TopLeptonicTagger = NewTopLeptonicTagger;
    TopLeptonicReader.set_tagger(TopLeptonicTagger);

    set_tagger_name("HeavyHiggsLeptonic");
    DefineVariables();
}

hanalysis::HHeavyHiggsLeptonicTagger::~HHeavyHiggsLeptonicTagger()
{
    Print(HNotification, "Destructor");
}

void hanalysis::HHeavyHiggsLeptonicTagger::DefineVariables()
{

  Print(HNotification , "Define Variables");


  ClearVectors();

  AddSpectator(Branch.Mass, "Mass");
  AddVariable(Branch.Pt, "Pt");
  AddVariable(Branch.Rap, "Rap");
  AddVariable(Branch.Phi, "Phi");

  AddVariable(Branch.DeltaPt, "DeltaPt");
  AddVariable(Branch.DeltaR, "DeltaR");
  AddVariable(Branch.DeltaRap, "DeltaRap");
  AddVariable(Branch.DeltaPhi, "DeltaPhi");

  AddVariable(Branch.LargerWDeltaR, "LargerWDeltaR");
  AddVariable(Branch.LargerWDeltaRap, "LargerWDeltaRap");
  AddVariable(Branch.LargerWDeltaPhi, "LargerWDeltaPhi");

  AddVariable(Branch.SmallerWDeltaR, "SmallerWDeltaR");
  AddVariable(Branch.SmallerWDeltaRap, "SmallerWDeltaRap");
  AddVariable(Branch.SmallerWDeltaPhi, "SmallerWDeltaPhi");

  AddVariable(Branch.LargerNeutrinoDeltaR, "LargerNeutrinoDeltaR");
  AddVariable(Branch.LargerNeutrinoDeltaRap, "LargerNeutrinoDeltaRap");
  AddVariable(Branch.LargerNeutrinoDeltaPhi, "LargerNeutrinoDeltaPhi");

  AddVariable(Branch.SmallerNeutrinoDeltaR, "SmallerNeutrinoDeltaR");
  AddVariable(Branch.SmallerNeutrinoDeltaRap, "SmallerNeutrinoDeltaRap");
  AddVariable(Branch.SmallerNeutrinoDeltaPhi, "SmallerNeutrinoDeltaPhi");

  AddVariable(Branch.Bdt, "Bdt");
  AddSpectator(Branch.Tag, "Tag");

  Print(HNotification, "Variables defined");

}

HHeavyHiggsLeptonicBranch hanalysis::HHeavyHiggsLeptonicTagger::GetBranch(const HSextet &Sextet)
{
    Print(HInformation, "FillPairTagger", Sextet.Bdt());

    HHeavyHiggsLeptonicBranch HeavyHiggsBranch;
    HeavyHiggsBranch.Mass = Sextet.Jet().m();
    HeavyHiggsBranch.Pt = Sextet.Jet().pt();
    HeavyHiggsBranch.Rap = Sextet.Jet().rap();
    HeavyHiggsBranch.Phi = Sextet.Jet().phi();

    HeavyHiggsBranch.DeltaR = Sextet.DeltaR();
    HeavyHiggsBranch.DeltaRap = Sextet.DeltaRap();
    HeavyHiggsBranch.DeltaPhi = Sextet.DeltaPhi();
    HeavyHiggsBranch.DeltaPt = Sextet.DeltaPt();

    HeavyHiggsBranch.LargerWDeltaR = Sextet.GetLargerTripletDeltaR();
    HeavyHiggsBranch.LargerWDeltaRap = Sextet.GetLargerTripletDeltaRap();
    HeavyHiggsBranch.LargerWDeltaPhi = Sextet.GetLargerTripleDeltaPhi();

    HeavyHiggsBranch.SmallerWDeltaR = Sextet.GetSmallerTripletDeltaR();
    HeavyHiggsBranch.SmallerWDeltaRap = Sextet.GetSmallerTripletDeltaRap();
    HeavyHiggsBranch.SmallerWDeltaPhi = Sextet.GetSmallerTripletDeltaPhi();

    HeavyHiggsBranch.LargerNeutrinoDeltaR = Sextet.GetLargerTripletDeltaR();
    HeavyHiggsBranch.LargerNeutrinoDeltaRap = Sextet.GetLargerTripletDeltaRap();
    HeavyHiggsBranch.LargerNeutrinoDeltaPhi = Sextet.GetLargerTripleDeltaPhi();

    HeavyHiggsBranch.SmallerNeutrinoDeltaR = Sextet.GetSmallerTripletDeltaR();
    HeavyHiggsBranch.SmallerNeutrinoDeltaRap = Sextet.GetSmallerTripletDeltaRap();
    HeavyHiggsBranch.SmallerNeutrinoDeltaPhi = Sextet.GetSmallerTripletDeltaPhi();

    HeavyHiggsBranch.Bdt = Sextet.Bdt();
    HeavyHiggsBranch.Tag = Sextet.Tag();

    return HeavyHiggsBranch;

}

struct SortSextetByMass {
  inline bool operator()(const hanalysis::HSextet &Sextet1, const hanalysis::HSextet &Sextet2) {
    return (Sextet1.Jet().m() > Sextet2.Jet().m());
  }
};


std::vector< HHeavyHiggsLeptonicBranch> hanalysis::HHeavyHiggsLeptonicTagger::GetBranches(HEvent &Event, const HObject::Tag Tag)
{
  Print(HInformation, "Get Higgs Tags");

  float Mass = Event.GetMass();

    JetTag.HeavyParticles = {TopId, HeavyHiggsId,CPOddHiggsId};
    HJets Jets = Event.GetJets()->GetStructuredTaggedJets(JetTag);

//     Jets = bottom_tagger_.GetJetBdt(Jets, BottomReader); // TODO reenable this

    HJets Leptons = Event.GetLeptons()->GetTaggedJets(JetTag);
    Print(HInformation, "Numeber of Jets", Jets.size(), Leptons.size());

    std::vector<HDoublet> Doublets = TopLeptonicTagger.GetBdt(Jets, Leptons, TopLeptonicReader);

    fastjet::PseudoJet MissingEt = Event.GetJets()->GetMissingEt();
    HJets Neutrinos = Event.GetParticles()->GetNeutrinos();

    Print(HInformation, "Number of Doublets", Doublets.size());

    std::vector<HSextet> Sextets;
    for (const auto & Doublet1 : Doublets) {
        for (const auto & Doublet2 : Doublets) {
            if (Doublet1.Singlet1() == Doublet2.Singlet1()) continue;
            if (Doublet1.Singlet2() == Doublet2.Singlet2()) continue;
            HQuartet Quartet(Doublet1, Doublet2);
            Quartet.SetTag(GetTag(Quartet));
            if (Quartet.Tag() != Tag) continue;
            std::vector<HSextet> PreSextets;
//             if (Tag == kSignal)
            PreSextets = GetSextet(Quartet, MissingEt, Neutrinos, Tag);
//             else PreSextets = GetSextets(Quartet, MissingEt);
            for (const auto & Sextet : PreSextets) {
//                 if (Sextet.GetSextetJet().m() < 10) continue; // TODO do we need this
            if (Tag == kSignal && Sextet.Jet().m() < Mass / 2)continue;
                Sextets.emplace_back(Sextet);
            }
        }
    }
    Print(HInformation, "Numeber of Sextets", Sextets.size());


    if (Tag == kSignal && Sextets.size() > 1) {
        Print(HError, "Higgs Candidates", Sextets.size());
        std::sort(Sextets.begin(), Sextets.end(), SortSextetByMass());
        Sextets.erase(Sextets.begin() + 1, Sextets.end());
    }

    std::vector<HHeavyHiggsLeptonicBranch> HeavyHiggsBranches;
    for (const auto & Sextet : Sextets) HeavyHiggsBranches.emplace_back(GetBranch(Sextet));

    return HeavyHiggsBranches;

}

hanalysis::HObject::Tag hanalysis::HHeavyHiggsLeptonicTagger::GetTag(const HQuartet &Quartet)
{
    Print(HInformation, "Get Quartet Tag");

    HJetInfo JetInfoB1 = Quartet.GetDoublet1().Singlet1().user_info<HJetInfo>();
    JetInfoB1.ExtractFraction(BottomId);
    HJetInfo JetInfoL1 = Quartet.GetDoublet1().Singlet2().user_info<HJetInfo>();
    JetInfoL1.ExtractFraction(WId);
    HJetInfo JetInfoB2 = Quartet.GetDoublet2().Singlet1().user_info<HJetInfo>();
    JetInfoB2.ExtractFraction(BottomId);
    HJetInfo JetInfoL2 = Quartet.GetDoublet2().Singlet2().user_info<HJetInfo>();
    JetInfoL2.ExtractFraction(WId);

    if (std::abs(JetInfoB1.MaximalId()) != BottomId) return kBackground;
    if (JetInfoB1.MaximalId() != -JetInfoB2.MaximalId()) return kBackground;

    if (std::abs(JetInfoL1.MaximalId()) != WId) return kBackground;
    if (sgn(JetInfoL1.MaximalId()) != sgn(JetInfoB1.MaximalId())) return kBackground;

    if (JetInfoL2.MaximalId() != -JetInfoL1.MaximalId()) return kBackground;
    return kSignal;
}

std::vector<hanalysis::HSextet>  hanalysis::HHeavyHiggsLeptonicTagger::GetBdt(const std::vector<HDoublet> &Doublets , const fastjet::PseudoJet &MissingEt, const Reader &Reader)
{
    Print(HInformation, "Get Bdt");

    std::vector<HSextet> Sextets;
    for (const auto & Doublet1 : Doublets) {
        for (const auto & Doublet2 : Doublets) {
            if (Doublet1.Singlet1() == Doublet2.Singlet1()) continue;
            if (Doublet1.Singlet2() == Doublet2.Singlet2()) continue;
            HQuartet Quartet(Doublet1, Doublet2);
            std::vector<HSextet> PreSextets;
            PreSextets = GetSextets(Quartet, MissingEt);
            for (auto & Sextet : PreSextets) {
                Branch = GetBranch(Sextet);
                Sextet.SetBdt(Reader.Bdt());
                Sextets.emplace_back(Sextet);
            }
        }
    }
    std::sort(Sextets.begin(), Sextets.end());
    Sextets.erase(Sextets.begin() + std::min(max_combi(), int(Sextets.size())), Sextets.end());
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

    SetMomentum(Structure.p3, Quartet.GetDoublet1().Singlet2());
    SetMomentum(Structure.p4, Quartet.GetDoublet2().Singlet2());
    SetMomentum(Structure.p5, Quartet.GetDoublet1().Singlet1());
    SetMomentum(Structure.p6, Quartet.GetDoublet2().Singlet1());
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
    for (const int SolutionNumber : Range(SolutionSum)) {
        Print(HDebug, "Solution ", SolutionNumber);
        Print(HDebug, "Neutrino 1 (p1)" , GetJet(P1[SolutionNumber]));
        Print(HDebug, "Neutrino 2 (p2)" , GetJet(P2[SolutionNumber]));

        HDoublet Doublet1(Quartet.GetDoublet1().Singlet2(), GetJet(P1[SolutionNumber]));
        if (Doublet1.Jet().m() <= 0) continue;
        HDoublet Doublet2(Quartet.GetDoublet2().Singlet2(), GetJet(P2[SolutionNumber]));
        if (Doublet2.Jet().m() <= 0) continue;

        HTriplet Triplet1(Doublet1, Quartet.GetDoublet1().Singlet1());
        if (Triplet1.Jet().m() <= 0) continue;
        HTriplet Triplet2(Doublet2, Quartet.GetDoublet2().Singlet1());
        if (Triplet2.Jet().m() <= 0) continue;

        HSextet Sextet(Triplet1, Triplet2);
        if (Sextet.Jet().m() <= 0) continue;
        Sextet.SetTag(Quartet.Tag());
        Sextet.SetBdt(Quartet.Bdt());
        Sextets.emplace_back(Sextet);

        Print(HDebug, "TriplePair Bdt", Sextet.Bdt(), Quartet.Bdt());
        //         Print(HDebug, "Neutrino masses", Jet1.m(), Jet2.m());
        Print(HDebug, "W masses", (GetJet(P1[SolutionNumber]) + Quartet.GetDoublet1().Singlet2()).m(), (GetJet(P2[SolutionNumber]) + Quartet.GetDoublet2().Singlet2()).m());
        Print(HDebug, "top masses", (GetJet(P1[SolutionNumber]) + Quartet.GetDoublet1().Singlet2() + Quartet.GetDoublet1().Singlet1()).m(), (GetJet(P2[SolutionNumber]) + Quartet.GetDoublet2().Singlet2() + Quartet.GetDoublet2().Singlet1()).m());
        //         Print(HDebug, "Higg mass", (Jet1 + Pair1.GetJet2() + Pair1.GetJet1() + Jet2 + Pair2.GetJet2() + Pair1.GetJet1()).m());
    }

    return Sextets;

}

std::vector<hanalysis::HSextet> hanalysis::HHeavyHiggsLeptonicTagger::GetSextet(const HQuartet &Quartet, const fastjet::PseudoJet &MissingEt, const HJets &Neutrinos, const Tag Tag)
{
    Print(HInformation, "Get Triple Pair");

    std::vector<HSextet> Sextets = GetSextets(Quartet, MissingEt);
    Print(HDebug, "Number Solutions", Sextets.size());

    if (Sextets.empty()) return Sextets;
//     if (Neutrinos.size() < 2) return Sextets;

    for (const auto & Neutrino : Neutrinos) Print(HDebug, "Neutrino", Neutrino);
    Print(HDebug, "Neutrino Sum", Neutrinos[0] + Neutrinos[1]);
    Print(HDebug, "MET", MissingEt);

    std::map<float, HSextet> Map;
    for (const auto & Sextet : Sextets) {
        fastjet::PseudoJet Neutrino1 = Sextet.Triplet1().Doublet().Singlet2();
        fastjet::PseudoJet Neutrino2 = Sextet.Triplet2().Doublet().Singlet2();

        std::vector<float> Neutrino1Errors, Neutrino2Errors;
        for (const auto & Neutrino : Neutrinos) {
            //             Print(HError, "Neutrino Mass", Neutrino.m());
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

//         for (size_t i = 0; i < Neutrino1Errors.size(); ++i) {
//             for (size_t j = i + 1; j < Neutrino2Errors.size(); ++j) {
//                 if (Neutrino1Errors[i] + Neutrino2Errors[j] < Error) Error = Neutrino1Errors[i] + Neutrino2Errors[j];
//             }
//         }
//         for (size_t j = 0; j < Neutrino2Errors.size(); ++j) {
//             for (size_t i = j + 1; i < Neutrino1Errors.size(); ++i) {
//                 if (Neutrino1Errors[i] + Neutrino2Errors[j] < Error) Error = Neutrino1Errors[i] + Neutrino2Errors[j];
//             }
//         }
        Map[Error] = Sextet;
        Print(HDebug, "TriplePair Bdt", Sextet.Bdt());
    }

    for (const auto & Pair : Map) Print(HDebug, "Neutrino Error Sum", Pair.first);
    if (Tag == kSignal) Map.erase(std::next(Map.begin()), Map.end());
    else Map.erase(Map.begin());

    std::vector<HSextet> FinalSextet;
    for (const auto Pair : Map) {
        HSextet Sextet = Pair.second;
        FinalSextet.emplace_back(Sextet);
    }

//     std::pair<float , HSextet> Pair = *(Map.begin());
//     HSextet Sextet = Pair.second;
//     FinalSextet.emplace_back(Sextet);

//     FinalSextet.emplace_back(*(Map.begin()).second);

    return FinalSextet;
}




