# include "WimpMass.hh"
# include "WIMPMASS.h"
# include "Predicate.hh"

analysis::WimpMass::WimpMass()
{
//     debug_level_ = kDebug;
    Print(kDebug, "Constructor");
}

void analysis::WimpMass::SetMomentum(double momentum[4], const fastjet::PseudoJet &jet)
{
    momentum[0] = jet.E();
    momentum[1] = jet.px();
    momentum[2] = jet.py();
    momentum[3] = jet.pz();
}

std::vector<analysis::Sextet> analysis::WimpMass::Sextets(const std::vector<analysis::Quartet22> &quartets, const fastjet::PseudoJet &missing_et)
{
    std::vector<analysis::Sextet> sextets;
    for (const auto quartet : quartets) JoinVectors(sextets, Sextets(quartet, missing_et));
    return sextets;
}

std::vector<analysis::Sextet> analysis::WimpMass::Sextets(const analysis::Quartet22 &quartet, const fastjet::PseudoJet &missing_et)
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
    int solution_sum;
    solve22(structure, Mass(ElectronNeutrinoId), Mass(WId), Mass(TopId), solution_sum, P1, P2);
    Print(kDebug, "Number solutions", solution_sum);

    std::vector<analysis::Sextet> sextets;
    for (const int solution_number : Range(solution_sum)) {
        Print(kDebug, "Solution ", solution_number);
        Print(kDebug, "Neutrino 1 (p1)" , PseudoJet(P1[solution_number]));
        Print(kDebug, "Neutrino 2 (p2)" , PseudoJet(P2[solution_number]));

        Doublet doublet_1(quartet.Doublet1().SingletJet2(), PseudoJet(P1[solution_number]));
        if (doublet_1.Jet().m() <= 0) continue;
        Doublet doublet_2(quartet.Doublet2().SingletJet2(), PseudoJet(P2[solution_number]));
        if (doublet_2.Jet().m() <= 0) continue;

        Triplet triplet_1(doublet_1, quartet.Doublet1().SingletJet1());
        if (triplet_1.Jet().m() <= 0) continue;
        triplet_1.SetBdt(quartet.Doublet1().Bdt());
        Triplet triplet_2(doublet_2, quartet.Doublet2().SingletJet1());
        if (triplet_2.Jet().m() <= 0) continue;
        triplet_2.SetBdt(quartet.Doublet2().Bdt());

        analysis::Sextet sextet(triplet_1, triplet_2);
        if (sextet.Jet().m() <= 0) continue;
        sextet.SetTag(quartet.Tag());
        sextet.SetBdt(quartet.Bdt());
        sextets.emplace_back(sextet);

        Print(kDebug, "TriplePair Bdt", sextet.Bdt(), quartet.Bdt());
        //         Print(kDebug, "Neutrino masses", Jet1.m(), Jet2.m());
        Print(kDebug, "W masses", (PseudoJet(P1[solution_number]) + quartet.Doublet1().SingletJet2()).m(), (PseudoJet(P2[solution_number]) + quartet.Doublet2().SingletJet2()).m());
        Print(kDebug, "top masses", (PseudoJet(P1[solution_number]) + quartet.Doublet1().SingletJet2() + quartet.Doublet1().SingletJet1()).m(), (PseudoJet(P2[solution_number]) + quartet.Doublet2().SingletJet2() + quartet.Doublet2().SingletJet1()).m());
        //         Print(kDebug, "Higg mass", (Jet1 + Pair1.PseudoJet2() + Pair1.PseudoJet1() + Jet2 + Pair2.PseudoJet2() + Pair1.PseudoJet1()).m());
    }
    return sextets;
}

std::vector<analysis::Sextet> analysis::WimpMass::Sextet(const analysis::Quartet22 &quartet, const fastjet::PseudoJet &missing_et, const analysis::Jets &neutrinos, const analysis::Object::Tag tag)
{
    Print(kInformation, "Triple Pair");

    std::vector<analysis::Sextet> sextets = Sextets(quartet, missing_et);
    Print(kDebug, "Number Solutions", sextets.size());

    if (sextets.empty()) return sextets;
//     if (Neutrinos.size() < 2) return sextets;

    for (const auto & Neutrino : neutrinos) Print(kDebug, "Neutrino", Neutrino);
    Print(kDebug, "Neutrino Sum", neutrinos[0] + neutrinos[1]);
    Print(kDebug, "MET", missing_et);

    std::map<float, analysis::Sextet> map;
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

        float Error = LargeNumber();
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
        map[Error] = sextet;
        Print(kDebug, "TriplePair Bdt", sextet.Bdt());
    }

    for (const auto & pair : map) Print(kDebug, "Neutrino Error Sum", pair.first);
    if (tag == kSignal) map.erase(std::next(map.begin()), map.end());
    else map.erase(map.begin());

    std::vector<analysis::Sextet> final_sextets;
    for (const auto pair : map) {
        analysis::Sextet sextet = pair.second;
        final_sextets.emplace_back(sextet);
    }

//     std::pair<float , Hsextet> Pair = *(Map.begin());
//     Hsextet sextet = Pair.second;
//     Finalsextet.emplace_back(sextet);

//     Finalsextet.emplace_back(*(Map.begin()).second);

    return final_sextets;
}
