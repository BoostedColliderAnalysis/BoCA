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

analysis::HHeavyHiggsLeptonicBranch analysis::HHeavyHiggsLeptonicTagger::GetBranch(const Sextet &sextet)
{
    Print(kInformation, "FillPairTagger", sextet.Bdt());

    HHeavyHiggsLeptonicBranch HeavyHiggsBranch;
    HeavyHiggsBranch.Mass = sextet.Jet().m();
    HeavyHiggsBranch.Pt = sextet.Jet().pt();
    HeavyHiggsBranch.Rap = sextet.Jet().rap();
    HeavyHiggsBranch.Phi = sextet.Jet().phi();

    HeavyHiggsBranch.DeltaR = sextet.DeltaR();
    HeavyHiggsBranch.DeltaRap = sextet.DeltaRap();
    HeavyHiggsBranch.DeltaPhi = sextet.DeltaPhi();
    HeavyHiggsBranch.DeltaPt = sextet.DeltaPt();

    HeavyHiggsBranch.LargerWDeltaR = sextet.GetLargertripletDeltaR();
    HeavyHiggsBranch.LargerWDeltaRap = sextet.GetLargertripletDeltaRap();
    HeavyHiggsBranch.LargerWDeltaPhi = sextet.GetLargerTripleDeltaPhi();

    HeavyHiggsBranch.SmallerWDeltaR = sextet.GetSmallertripletDeltaR();
    HeavyHiggsBranch.SmallerWDeltaRap = sextet.GetSmallertripletDeltaRap();
    HeavyHiggsBranch.SmallerWDeltaPhi = sextet.GetSmallertripletDeltaPhi();

    HeavyHiggsBranch.LargerNeutrinoDeltaR = sextet.GetLargertripletDeltaR();
    HeavyHiggsBranch.LargerNeutrinoDeltaRap = sextet.GetLargertripletDeltaRap();
    HeavyHiggsBranch.LargerNeutrinoDeltaPhi = sextet.GetLargerTripleDeltaPhi();

    HeavyHiggsBranch.SmallerNeutrinoDeltaR = sextet.GetSmallertripletDeltaR();
    HeavyHiggsBranch.SmallerNeutrinoDeltaRap = sextet.GetSmallertripletDeltaRap();
    HeavyHiggsBranch.SmallerNeutrinoDeltaPhi = sextet.GetSmallertripletDeltaPhi();

    HeavyHiggsBranch.Bdt = sextet.Bdt();
    HeavyHiggsBranch.Tag = sextet.Tag();

    return HeavyHiggsBranch;

}

struct SortsextetByMass {
  inline bool operator()(const analysis::Sextet &sextet1, const analysis::Sextet &sextet2) {
    return (sextet1.Jet().m() > sextet2.Jet().m());
  }
};


std::vector< analysis::HHeavyHiggsLeptonicBranch> analysis::HHeavyHiggsLeptonicTagger::GetBranches(Event &event, const Object::Tag Tag)
{
  Print(kInformation, "Higgs Tags");

  float Mass = event.mass();

//     jet_tag.HeavyParticles = {TopId, HeavyHiggsId,CPOddHiggsId};
    Jets jets = event.hadrons().Jets();

//     jets = bottom_tagger_.GetJetBdt(jets, BottomReader); // TODO reenable this

    Jets Leptons = event.leptons().leptons();
    Print(kInformation, "Numeber of Jets", jets.size(), Leptons.size());

    std::vector<Doublet> doublets = TopLeptonicTagger.GetBdt(jets, Leptons, TopLeptonicReader);

    fastjet::PseudoJet MissingEt = event.hadrons().MissingEt();
    Jets Neutrinos ;//= event.partons().GetNeutrinos(); // TODO fix this!!

    Print(kInformation, "Number of doublets", doublets.size());

    std::vector<Sextet> sextets;
    for (const auto & doublet1 : doublets) {
        for (const auto & doublet2 : doublets) {
            if (doublet1.Singlet1() == doublet2.Singlet1()) continue;
            if (doublet1.Singlet2() == doublet2.Singlet2()) continue;
            Quartet22 quartet(doublet1, doublet2);
            quartet.SetTag(GetTag(quartet));
            if (quartet.Tag() != Tag) continue;
            std::vector<Sextet> Presextets;
//             if (Tag == kSignal)
            Presextets = Getsextet(quartet, MissingEt, Neutrinos, Tag);
//             else Presextets = Getsextets(quartet, MissingEt);
            for (const auto & sextet : Presextets) {
//                 if (sextet.GetsextetJet().m() < 10) continue; // TODO do we need this
            if (Tag == kSignal && sextet.Jet().m() < Mass / 2)continue;
                sextets.emplace_back(sextet);
            }
        }
    }
    Print(kInformation, "Numeber of sextets", sextets.size());


    if (Tag == kSignal && sextets.size() > 1) {
        Print(kError, "Higgs Candidates", sextets.size());
        std::sort(sextets.begin(), sextets.end(), SortsextetByMass());
        sextets.erase(sextets.begin() + 1, sextets.end());
    }

    std::vector<HHeavyHiggsLeptonicBranch> HeavyHiggsBranches;
    for (const auto & sextet : sextets) HeavyHiggsBranches.emplace_back(GetBranch(sextet));

    return HeavyHiggsBranches;

}

analysis::Object::Tag analysis::HHeavyHiggsLeptonicTagger::GetTag(const Quartet22 &quartet)
{
    Print(kInformation, "quartet Tag");

    JetInfo jet_infoB1 = quartet.Getdoublet1().Singlet1().user_info<JetInfo>();
    jet_infoB1.ExtractFraction(BottomId);
    JetInfo jet_infoL1 = quartet.Getdoublet1().Singlet2().user_info<JetInfo>();
    jet_infoL1.ExtractFraction(WId);
    JetInfo jet_infoB2 = quartet.Getdoublet2().Singlet1().user_info<JetInfo>();
    jet_infoB2.ExtractFraction(BottomId);
    JetInfo jet_infoL2 = quartet.Getdoublet2().Singlet2().user_info<JetInfo>();
    jet_infoL2.ExtractFraction(WId);

    if (std::abs(jet_infoB1.MaximalId()) != BottomId) return kBackground;
    if (jet_infoB1.MaximalId() != -jet_infoB2.MaximalId()) return kBackground;

    if (std::abs(jet_infoL1.MaximalId()) != WId) return kBackground;
    if (sgn(jet_infoL1.MaximalId()) != sgn(jet_infoB1.MaximalId())) return kBackground;

    if (jet_infoL2.MaximalId() != -jet_infoL1.MaximalId()) return kBackground;
    return kSignal;
}

std::vector<analysis::Sextet>  analysis::HHeavyHiggsLeptonicTagger::GetBdt(const std::vector<Doublet> &doublets , const fastjet::PseudoJet &MissingEt, const Reader &Reader)
{
    Print(kInformation, "Bdt");

    std::vector<Sextet> sextets;
    for (const auto & doublet1 : doublets) {
        for (const auto & doublet2 : doublets) {
            if (doublet1.Singlet1() == doublet2.Singlet1()) continue;
            if (doublet1.Singlet2() == doublet2.Singlet2()) continue;
            Quartet22 quartet(doublet1, doublet2);
            std::vector<Sextet> Presextets;
            Presextets = Getsextets(quartet, MissingEt);
            for (auto & sextet : Presextets) {
                Branch = GetBranch(sextet);
                sextet.SetBdt(Reader.Bdt());
                sextets.emplace_back(sextet);
            }
        }
    }
    std::sort(sextets.begin(), sextets.end());
    sextets.erase(sextets.begin() + std::min(max_combi(), int(sextets.size())), sextets.end());
    return sextets;
}


void analysis::HHeavyHiggsLeptonicTagger::SetMomentum(double Momentum[4], const fastjet::PseudoJet &Jet)
{
    Momentum[0] = Jet.E();
    Momentum[1] = Jet.px();
    Momentum[2] = Jet.py();
    Momentum[3] = Jet.pz();
}

std::vector<analysis::Sextet> analysis::HHeavyHiggsLeptonicTagger::Getsextets(const Quartet22 &quartet, const fastjet::PseudoJet &MissingEt)
{
    Print(kInformation, "Triple Pairs");

    SetMomentum(Structure.p3, quartet.Getdoublet1().Singlet2());
    SetMomentum(Structure.p4, quartet.Getdoublet2().Singlet2());
    SetMomentum(Structure.p5, quartet.Getdoublet1().Singlet1());
    SetMomentum(Structure.p6, quartet.Getdoublet2().Singlet1());
    SetMomentum(Structure.pmiss, MissingEt);

    Print(kDebug, "Lepton 1 (p3)", GetJet(Structure.p3));
    Print(kDebug, "Lepton 2 (p4)" , GetJet(Structure.p4));
    Print(kDebug, "Jet 1 (p5)" , GetJet(Structure.p5));
    Print(kDebug, "Jet 2 (p6)" , GetJet(Structure.p6));
    Print(kDebug, "PMiss" , GetJet(Structure.pmiss));

    double P1[4][4], P2[4][4];
    int SolutionSum;
    solve22(Structure, Mass(ElectronNeutrinoId), Mass(WId), Mass(TopId), SolutionSum, P1, P2);
    Print(kDebug, "Number solutions", SolutionSum);

    std::vector<analysis::Sextet> sextets;
    for (const int SolutionNumber : Range(SolutionSum)) {
        Print(kDebug, "Solution ", SolutionNumber);
        Print(kDebug, "Neutrino 1 (p1)" , GetJet(P1[SolutionNumber]));
        Print(kDebug, "Neutrino 2 (p2)" , GetJet(P2[SolutionNumber]));

        Doublet doublet1(quartet.Getdoublet1().Singlet2(), GetJet(P1[SolutionNumber]));
        if (doublet1.Jet().m() <= 0) continue;
        Doublet doublet2(quartet.Getdoublet2().Singlet2(), GetJet(P2[SolutionNumber]));
        if (doublet2.Jet().m() <= 0) continue;

        Triplet triplet1(doublet1, quartet.Getdoublet1().Singlet1());
        if (triplet1.Jet().m() <= 0) continue;
        Triplet triplet2(doublet2, quartet.Getdoublet2().Singlet1());
        if (triplet2.Jet().m() <= 0) continue;

        Sextet sextet(triplet1, triplet2);
        if (sextet.Jet().m() <= 0) continue;
        sextet.SetTag(quartet.Tag());
        sextet.SetBdt(quartet.Bdt());
        sextets.emplace_back(sextet);

        Print(kDebug, "TriplePair Bdt", sextet.Bdt(), quartet.Bdt());
        //         Print(kDebug, "Neutrino masses", Jet1.m(), Jet2.m());
        Print(kDebug, "W masses", (GetJet(P1[SolutionNumber]) + quartet.Getdoublet1().Singlet2()).m(), (GetJet(P2[SolutionNumber]) + quartet.Getdoublet2().Singlet2()).m());
        Print(kDebug, "top masses", (GetJet(P1[SolutionNumber]) + quartet.Getdoublet1().Singlet2() + quartet.Getdoublet1().Singlet1()).m(), (GetJet(P2[SolutionNumber]) + quartet.Getdoublet2().Singlet2() + quartet.Getdoublet2().Singlet1()).m());
        //         Print(kDebug, "Higg mass", (Jet1 + Pair1.GetJet2() + Pair1.GetJet1() + Jet2 + Pair2.GetJet2() + Pair1.GetJet1()).m());
    }

    return sextets;

}

std::vector<analysis::Sextet> analysis::HHeavyHiggsLeptonicTagger::Getsextet(const Quartet22 &quartet, const fastjet::PseudoJet &MissingEt, const Jets &Neutrinos, const Tag Tag)
{
    Print(kInformation, "Triple Pair");

    std::vector<Sextet> sextets = Getsextets(quartet, MissingEt);
    Print(kDebug, "Number Solutions", sextets.size());

    if (sextets.empty()) return sextets;
//     if (Neutrinos.size() < 2) return sextets;

    for (const auto & Neutrino : Neutrinos) Print(kDebug, "Neutrino", Neutrino);
    Print(kDebug, "Neutrino Sum", Neutrinos[0] + Neutrinos[1]);
    Print(kDebug, "MET", MissingEt);

    std::map<float, Sextet> Map;
    for (const auto & sextet : sextets) {
        fastjet::PseudoJet Neutrino1 = sextet.triplet1().doublet().Singlet2();
        fastjet::PseudoJet Neutrino2 = sextet.triplet2().doublet().Singlet2();

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
        Map[Error] = sextet;
        Print(kDebug, "TriplePair Bdt", sextet.Bdt());
    }

    for (const auto & Pair : Map) Print(kDebug, "Neutrino Error Sum", Pair.first);
    if (Tag == kSignal) Map.erase(std::next(Map.begin()), Map.end());
    else Map.erase(Map.begin());

    std::vector<Sextet> Finalsextet;
    for (const auto Pair : Map) {
        Sextet sextet = Pair.second;
        Finalsextet.emplace_back(sextet);
    }

//     std::pair<float , Hsextet> Pair = *(Map.begin());
//     Hsextet sextet = Pair.second;
//     Finalsextet.emplace_back(sextet);

//     Finalsextet.emplace_back(*(Map.begin()).second);

    return Finalsextet;
}




