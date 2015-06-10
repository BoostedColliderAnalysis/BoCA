# include "WimpMass.hh"
# include "WIMPMASS.h"
# include "Predicate.hh"

analysis::WimpMass::WimpMass()
{
    //     DebugLevel = analysis::Object::kDebug;

    Print(kNotification, "Constructor");
}

void analysis::WimpMass::SetMomentum(double momentum[4], const fastjet::PseudoJet &jet)
{
    momentum[0] = jet.E();
    momentum[1] = jet.px();
    momentum[2] = jet.py();
    momentum[3] = jet.pz();
}

std::vector<analysis::Sextet> analysis::WimpMass::Sextets(const std::vector<analysis::Quartet22>& quartets, const fastjet::PseudoJet& missing_et)
{
  std::vector<analysis::Sextet> sextets;
  for(const auto quartet : quartets) JoinVectors(sextets,Sextets(quartet,missing_et));
  return sextets;
}

std::vector<analysis::Sextet> analysis::WimpMass::Sextets(const analysis::Quartet22& quartet, const fastjet::PseudoJet& missing_et)
{
    Print(kInformation, "Triple Pairs");

    event22 structure;

    SetMomentum(structure.p3, quartet.Doublet1().SingletJet2());
    SetMomentum(structure.p4, quartet.Doublet2().SingletJet2());
    SetMomentum(structure.p5, quartet.Doublet1().SingletJet1());
    SetMomentum(structure.p6, quartet.Doublet2().SingletJet1());
    SetMomentum(structure.pmiss, missing_et);

    Print(kDebug, "Lepton 1 (p3)", PseudoJet(structure.p3));
    Print(kDebug, "Lepton 2 (p4)" , PseudoJet(structure.p4));
    Print(kDebug, "Jet 1 (p5)" , PseudoJet(structure.p5));
    Print(kDebug, "Jet 2 (p6)" , PseudoJet(structure.p6));
    Print(kDebug, "PMiss" , PseudoJet(structure.pmiss));

    double P1[4][4], P2[4][4];
    int SolutionSum;
    solve22(structure, Mass(ElectronNeutrinoId), Mass(WId), Mass(TopId), SolutionSum, P1, P2);
    Print(kDebug, "Number solutions", SolutionSum);

    std::vector<analysis::Sextet> sextets;
    for (const int SolutionNumber : analysis::Range(SolutionSum)) {
        Print(kDebug, "Solution ", SolutionNumber);
        Print(kDebug, "Neutrino 1 (p1)" , PseudoJet(P1[SolutionNumber]));
        Print(kDebug, "Neutrino 2 (p2)" , PseudoJet(P2[SolutionNumber]));

        analysis::Doublet doublet1(quartet.Doublet1().SingletJet2(), PseudoJet(P1[SolutionNumber]));
        if (doublet1.Jet().m() <= 0) continue;
        analysis::Doublet doublet2(quartet.Doublet2().SingletJet2(), PseudoJet(P2[SolutionNumber]));
        if (doublet2.Jet().m() <= 0) continue;

        analysis::Triplet triplet1(doublet1, quartet.Doublet1().SingletJet1());
        if (triplet1.Jet().m() <= 0) continue;
        analysis::Triplet triplet2(doublet2, quartet.Doublet2().SingletJet1());
        if (triplet2.Jet().m() <= 0) continue;

        analysis::Sextet sextet(triplet1, triplet2);
        if (sextet.Jet().m() <= 0) continue;
        sextet.SetTag(quartet.Tag());
        sextet.SetBdt(quartet.Bdt());
        sextets.emplace_back(sextet);

        Print(kDebug, "TriplePair Bdt", sextet.Bdt(), quartet.Bdt());
        //         Print(kDebug, "Neutrino masses", Jet1.m(), Jet2.m());
        Print(kDebug, "W masses", (PseudoJet(P1[SolutionNumber]) + quartet.Doublet1().SingletJet2()).m(), (PseudoJet(P2[SolutionNumber]) + quartet.Doublet2().SingletJet2()).m());
        Print(kDebug, "top masses", (PseudoJet(P1[SolutionNumber]) + quartet.Doublet1().SingletJet2() + quartet.Doublet1().SingletJet1()).m(), (PseudoJet(P2[SolutionNumber]) + quartet.Doublet2().SingletJet2() + quartet.Doublet2().SingletJet1()).m());
        //         Print(kDebug, "Higg mass", (Jet1 + Pair1.PseudoJet2() + Pair1.PseudoJet1() + Jet2 + Pair2.PseudoJet2() + Pair1.PseudoJet1()).m());
    }

    return sextets;

}

std::vector<analysis::Sextet> analysis::WimpMass::Sextet(const analysis::Quartet22& quartet, const fastjet::PseudoJet& missing_et, const analysis::Jets& neutrinos, const analysis::Object::Tag tag)
{
    Print(kInformation, "Triple Pair");

    std::vector<analysis::Sextet> sextets = Sextets(quartet, missing_et);
    Print(kDebug, "Number Solutions", sextets.size());

    if (sextets.empty()) return sextets;
//     if (Neutrinos.size() < 2) return sextets;

    for (const auto & Neutrino : neutrinos) Print(kDebug, "Neutrino", Neutrino);
    Print(kDebug, "Neutrino Sum", neutrinos[0] + neutrinos[1]);
    Print(kDebug, "MET", missing_et);

    std::map<float, analysis::Sextet> Map;
    for (const auto & sextet : sextets) {
        fastjet::PseudoJet Neutrino1 = sextet.Triplet1().Doublet().SingletJet2();
        fastjet::PseudoJet Neutrino2 = sextet.Triplet2().Doublet().SingletJet2();

        std::vector<float> Neutrino1Errors, Neutrino2Errors;
        for (const auto & Neutrino : neutrinos) {
            //             Print(kError, "Neutrino Mass", Neutrino.m());
            Neutrino1Errors.emplace_back((Neutrino + Neutrino1).m());
            Print(kDebug, "Neutrino 1 Error", (Neutrino + Neutrino1).m());
            Neutrino2Errors.emplace_back((Neutrino + Neutrino2).m());
            Print(kDebug, "Neutrino 2 Error", (Neutrino + Neutrino2).m());
        }

        float Error = analysis::LargeNumber();
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
    if (tag == kSignal) Map.erase(std::next(Map.begin()), Map.end());
    else Map.erase(Map.begin());

    std::vector<analysis::Sextet> Finalsextet;
    for (const auto Pair : Map) {
      analysis::Sextet sextet = Pair.second;
        Finalsextet.emplace_back(sextet);
    }

//     std::pair<float , Hsextet> Pair = *(Map.begin());
//     Hsextet sextet = Pair.second;
//     Finalsextet.emplace_back(sextet);

//     Finalsextet.emplace_back(*(Map.begin()).second);

    return Finalsextet;
}
