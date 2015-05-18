# include "HHeavyHiggsLeptonicTagger.hh"

analysis::HHeavyHiggsLeptonicTagger::HHeavyHiggsLeptonicTagger()
{
  //     DebugLevel = analysis::Object::kDebug;

  Print(kNotification, "Constructor");
  set_tagger_name("HeavyHiggsLeptonic");
}

analysis::HHeavyHiggsLeptonicTagger::HHeavyHiggsLeptonicTagger(const BottomTagger &NewBottomTagger, const HTopLeptonicTagger &NewTopLeptonicTagger)
{
//     DebugLevel = analysis::Object::kDebug;

    Print(kNotification, "Constructor");

    bottom_tagger_ = NewBottomTagger;
    BottomReader.set_tagger(bottom_tagger_);
    TopLeptonicTagger = NewTopLeptonicTagger;
    TopLeptonicReader.set_tagger(TopLeptonicTagger);

    set_tagger_name("HeavyHiggsLeptonic");
    DefineVariables();
}

analysis::HHeavyHiggsLeptonicTagger::~HHeavyHiggsLeptonicTagger()
{
    Print(kNotification, "Destructor");
}

void analysis::HHeavyHiggsLeptonicTagger::DefineVariables()
{

  Print(kNotification , "Define Variables");


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

  Print(kNotification, "Variables defined");

}

analysis::HHeavyHiggsLeptonicBranch analysis::HHeavyHiggsLeptonicTagger::GetBranch(const HSextet &Sextet)
{
    Print(kInformation, "FillPairTagger", Sextet.Bdt());

    HHeavyHiggsLeptonicBranch HeavyHiggsBranch;
    HeavyHiggsBranch.Mass = Sextet.Jet().m();
    HeavyHiggsBranch.Pt = Sextet.Jet().pt();
    HeavyHiggsBranch.Rap = Sextet.Jet().rap();
    HeavyHiggsBranch.Phi = Sextet.Jet().phi();

    HeavyHiggsBranch.DeltaR = Sextet.DeltaR();
    HeavyHiggsBranch.DeltaRap = Sextet.DeltaRap();
    HeavyHiggsBranch.DeltaPhi = Sextet.DeltaPhi();
    HeavyHiggsBranch.DeltaPt = Sextet.DeltaPt();

    HeavyHiggsBranch.LargerWDeltaR = Sextet.GetLargertripletDeltaR();
    HeavyHiggsBranch.LargerWDeltaRap = Sextet.GetLargertripletDeltaRap();
    HeavyHiggsBranch.LargerWDeltaPhi = Sextet.GetLargerTripleDeltaPhi();

    HeavyHiggsBranch.SmallerWDeltaR = Sextet.GetSmallertripletDeltaR();
    HeavyHiggsBranch.SmallerWDeltaRap = Sextet.GetSmallertripletDeltaRap();
    HeavyHiggsBranch.SmallerWDeltaPhi = Sextet.GetSmallertripletDeltaPhi();

    HeavyHiggsBranch.LargerNeutrinoDeltaR = Sextet.GetLargertripletDeltaR();
    HeavyHiggsBranch.LargerNeutrinoDeltaRap = Sextet.GetLargertripletDeltaRap();
    HeavyHiggsBranch.LargerNeutrinoDeltaPhi = Sextet.GetLargerTripleDeltaPhi();

    HeavyHiggsBranch.SmallerNeutrinoDeltaR = Sextet.GetSmallertripletDeltaR();
    HeavyHiggsBranch.SmallerNeutrinoDeltaRap = Sextet.GetSmallertripletDeltaRap();
    HeavyHiggsBranch.SmallerNeutrinoDeltaPhi = Sextet.GetSmallertripletDeltaPhi();

    HeavyHiggsBranch.Bdt = Sextet.Bdt();
    HeavyHiggsBranch.Tag = Sextet.Tag();

    return HeavyHiggsBranch;

}

struct SortSextetByMass {
  inline bool operator()(const analysis::HSextet &Sextet1, const analysis::HSextet &Sextet2) {
    return (Sextet1.Jet().m() > Sextet2.Jet().m());
  }
};


std::vector< analysis::HHeavyHiggsLeptonicBranch> analysis::HHeavyHiggsLeptonicTagger::GetBranches(Event &event, const Object::Tag Tag)
{
  Print(kInformation, "Get Higgs Tags");

  float Mass = event.mass();

    JetTag.HeavyParticles = {TopId, HeavyHiggsId,CPOddHiggsId};
    Jets jets = event.hadrons().GetStructuredTaggedJets(JetTag);

//     jets = bottom_tagger_.GetJetBdt(jets, BottomReader); // TODO reenable this

    Jets Leptons = event.leptons().GetTaggedJets(JetTag);
    Print(kInformation, "Numeber of Jets", jets.size(), Leptons.size());

    std::vector<Doublet> doublets = TopLeptonicTagger.GetBdt(jets, Leptons, TopLeptonicReader);

    fastjet::PseudoJet MissingEt = event.hadrons().GetMissingEt();
    Jets Neutrinos = event.partons().GetNeutrinos();

    Print(kInformation, "Number of doublets", doublets.size());

    std::vector<HSextet> Sextets;
    for (const auto & doublet1 : doublets) {
        for (const auto & doublet2 : doublets) {
            if (doublet1.Singlet1() == doublet2.Singlet1()) continue;
            if (doublet1.Singlet2() == doublet2.Singlet2()) continue;
            HQuartet Quartet(doublet1, doublet2);
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
    Print(kInformation, "Numeber of Sextets", Sextets.size());


    if (Tag == kSignal && Sextets.size() > 1) {
        Print(kError, "Higgs Candidates", Sextets.size());
        std::sort(Sextets.begin(), Sextets.end(), SortSextetByMass());
        Sextets.erase(Sextets.begin() + 1, Sextets.end());
    }

    std::vector<HHeavyHiggsLeptonicBranch> HeavyHiggsBranches;
    for (const auto & Sextet : Sextets) HeavyHiggsBranches.emplace_back(GetBranch(Sextet));

    return HeavyHiggsBranches;

}

analysis::Object::Tag analysis::HHeavyHiggsLeptonicTagger::GetTag(const HQuartet &Quartet)
{
    Print(kInformation, "Get Quartet Tag");

    JetInfo jet_infoB1 = Quartet.Getdoublet1().Singlet1().user_info<JetInfo>();
    jet_infoB1.ExtractFraction(BottomId);
    JetInfo jet_infoL1 = Quartet.Getdoublet1().Singlet2().user_info<JetInfo>();
    jet_infoL1.ExtractFraction(WId);
    JetInfo jet_infoB2 = Quartet.Getdoublet2().Singlet1().user_info<JetInfo>();
    jet_infoB2.ExtractFraction(BottomId);
    JetInfo jet_infoL2 = Quartet.Getdoublet2().Singlet2().user_info<JetInfo>();
    jet_infoL2.ExtractFraction(WId);

    if (std::abs(jet_infoB1.MaximalId()) != BottomId) return kBackground;
    if (jet_infoB1.MaximalId() != -jet_infoB2.MaximalId()) return kBackground;

    if (std::abs(jet_infoL1.MaximalId()) != WId) return kBackground;
    if (sgn(jet_infoL1.MaximalId()) != sgn(jet_infoB1.MaximalId())) return kBackground;

    if (jet_infoL2.MaximalId() != -jet_infoL1.MaximalId()) return kBackground;
    return kSignal;
}

std::vector<analysis::HSextet>  analysis::HHeavyHiggsLeptonicTagger::GetBdt(const std::vector<Doublet> &doublets , const fastjet::PseudoJet &MissingEt, const Reader &Reader)
{
    Print(kInformation, "Get Bdt");

    std::vector<HSextet> Sextets;
    for (const auto & doublet1 : doublets) {
        for (const auto & doublet2 : doublets) {
            if (doublet1.Singlet1() == doublet2.Singlet1()) continue;
            if (doublet1.Singlet2() == doublet2.Singlet2()) continue;
            HQuartet Quartet(doublet1, doublet2);
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


void analysis::HHeavyHiggsLeptonicTagger::SetMomentum(double Momentum[4], const fastjet::PseudoJet &Jet)
{
    Momentum[0] = Jet.E();
    Momentum[1] = Jet.px();
    Momentum[2] = Jet.py();
    Momentum[3] = Jet.pz();
}

std::vector<analysis::HSextet> analysis::HHeavyHiggsLeptonicTagger::GetSextets(const HQuartet &Quartet, const fastjet::PseudoJet &MissingEt)
{
    Print(kInformation, "Get Triple Pairs");

    SetMomentum(Structure.p3, Quartet.Getdoublet1().Singlet2());
    SetMomentum(Structure.p4, Quartet.Getdoublet2().Singlet2());
    SetMomentum(Structure.p5, Quartet.Getdoublet1().Singlet1());
    SetMomentum(Structure.p6, Quartet.Getdoublet2().Singlet1());
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

    std::vector<analysis::HSextet> Sextets;
    for (const int SolutionNumber : Range(SolutionSum)) {
        Print(kDebug, "Solution ", SolutionNumber);
        Print(kDebug, "Neutrino 1 (p1)" , GetJet(P1[SolutionNumber]));
        Print(kDebug, "Neutrino 2 (p2)" , GetJet(P2[SolutionNumber]));

        Doublet doublet1(Quartet.Getdoublet1().Singlet2(), GetJet(P1[SolutionNumber]));
        if (doublet1.Jet().m() <= 0) continue;
        Doublet doublet2(Quartet.Getdoublet2().Singlet2(), GetJet(P2[SolutionNumber]));
        if (doublet2.Jet().m() <= 0) continue;

        Triplet triplet1(doublet1, Quartet.Getdoublet1().Singlet1());
        if (triplet1.Jet().m() <= 0) continue;
        Triplet triplet2(doublet2, Quartet.Getdoublet2().Singlet1());
        if (triplet2.Jet().m() <= 0) continue;

        HSextet Sextet(triplet1, triplet2);
        if (Sextet.Jet().m() <= 0) continue;
        Sextet.SetTag(Quartet.Tag());
        Sextet.SetBdt(Quartet.Bdt());
        Sextets.emplace_back(Sextet);

        Print(kDebug, "TriplePair Bdt", Sextet.Bdt(), Quartet.Bdt());
        //         Print(kDebug, "Neutrino masses", Jet1.m(), Jet2.m());
        Print(kDebug, "W masses", (GetJet(P1[SolutionNumber]) + Quartet.Getdoublet1().Singlet2()).m(), (GetJet(P2[SolutionNumber]) + Quartet.Getdoublet2().Singlet2()).m());
        Print(kDebug, "top masses", (GetJet(P1[SolutionNumber]) + Quartet.Getdoublet1().Singlet2() + Quartet.Getdoublet1().Singlet1()).m(), (GetJet(P2[SolutionNumber]) + Quartet.Getdoublet2().Singlet2() + Quartet.Getdoublet2().Singlet1()).m());
        //         Print(kDebug, "Higg mass", (Jet1 + Pair1.GetJet2() + Pair1.GetJet1() + Jet2 + Pair2.GetJet2() + Pair1.GetJet1()).m());
    }

    return Sextets;

}

std::vector<analysis::HSextet> analysis::HHeavyHiggsLeptonicTagger::GetSextet(const HQuartet &Quartet, const fastjet::PseudoJet &MissingEt, const Jets &Neutrinos, const Tag Tag)
{
    Print(kInformation, "Get Triple Pair");

    std::vector<HSextet> Sextets = GetSextets(Quartet, MissingEt);
    Print(kDebug, "Number Solutions", Sextets.size());

    if (Sextets.empty()) return Sextets;
//     if (Neutrinos.size() < 2) return Sextets;

    for (const auto & Neutrino : Neutrinos) Print(kDebug, "Neutrino", Neutrino);
    Print(kDebug, "Neutrino Sum", Neutrinos[0] + Neutrinos[1]);
    Print(kDebug, "MET", MissingEt);

    std::map<float, HSextet> Map;
    for (const auto & Sextet : Sextets) {
        fastjet::PseudoJet Neutrino1 = Sextet.triplet1().doublet().Singlet2();
        fastjet::PseudoJet Neutrino2 = Sextet.triplet2().doublet().Singlet2();

        std::vector<float> Neutrino1Errors, Neutrino2Errors;
        for (const auto & Neutrino : Neutrinos) {
            //             Print(kError, "Neutrino Mass", Neutrino.m());
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

//         for (std::size_t i = 0; i < Neutrino1Errors.size(); ++i) {
//             for (std::size_t j = i + 1; j < Neutrino2Errors.size(); ++j) {
//                 if (Neutrino1Errors[i] + Neutrino2Errors[j] < Error) Error = Neutrino1Errors[i] + Neutrino2Errors[j];
//             }
//         }
//         for (std::size_t j = 0; j < Neutrino2Errors.size(); ++j) {
//             for (std::size_t i = j + 1; i < Neutrino1Errors.size(); ++i) {
//                 if (Neutrino1Errors[i] + Neutrino2Errors[j] < Error) Error = Neutrino1Errors[i] + Neutrino2Errors[j];
//             }
//         }
        Map[Error] = Sextet;
        Print(kDebug, "TriplePair Bdt", Sextet.Bdt());
    }

    for (const auto & Pair : Map) Print(kDebug, "Neutrino Error Sum", Pair.first);
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




