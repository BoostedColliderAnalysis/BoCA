# include "WimpMass.hh"
# include "WIMPMASS.h"
# include "Predicate.hh"

namespace analysis
{

WimpMass::WimpMass()
{
//     debug_level_ = Severity::Debug;
    Print(Severity::Debug, "Constructor");
}

void WimpMass::Momentum(double momentum[4], const fastjet::PseudoJet &jet)
{
    momentum[0] = jet.E();
    momentum[1] = jet.px();
    momentum[2] = jet.py();
    momentum[3] = jet.pz();
}

std::vector<analysis::Sextet> WimpMass::Sextets(const std::vector<Quartet22> &quartets, const fastjet::PseudoJet &missing_et)
{
    std::vector<analysis::Sextet> sextets;
    for (const auto quartet : quartets) Join(sextets, Sextets(quartet, missing_et));
    return sextets;
}

std::vector<analysis::Sextet> WimpMass::Sextets(const Quartet22 &quartet, const fastjet::PseudoJet &missing_et)
{
    Print(Severity::Information, "Triple Pairs");

    event22 structure;

    Momentum(structure.p3, quartet.Doublet1().SingletJet2());
    Momentum(structure.p4, quartet.Doublet2().SingletJet2());
    Momentum(structure.p5, quartet.Doublet1().SingletJet1());
    Momentum(structure.p6, quartet.Doublet2().SingletJet1());
    Momentum(structure.pmiss, missing_et);

    Print(Severity::Debug, "Lepton 1 (p3)", PseudoJet(structure.p3));
    Print(Severity::Debug, "Lepton 2 (p4)" , PseudoJet(structure.p4));
    Print(Severity::Debug, "Jet 1 (p5)" , PseudoJet(structure.p5));
    Print(Severity::Debug, "Jet 2 (p6)" , PseudoJet(structure.p6));
    Print(Severity::Debug, "PMiss" , PseudoJet(structure.pmiss));

    double momentum_1[4][4], momentum_2[4][4];
    int solution_sum;
    solve22(structure, Mass(Id::ElectronNeutrino), Mass(Id::W), Mass(Id::Top), solution_sum, momentum_1, momentum_2);
    Print(Severity::Debug, "Number solutions", solution_sum);

    std::vector<analysis::Sextet> sextets;
    for (const int solution_number : Range(solution_sum)) {
        Print(Severity::Debug, "Solution ", solution_number);
        Print(Severity::Debug, "Neutrino 1 (p1)" , PseudoJet(momentum_1[solution_number]));
        Print(Severity::Debug, "Neutrino 2 (p2)" , PseudoJet(momentum_2[solution_number]));

        Doublet doublet_1(quartet.Doublet1().SingletJet2(), PseudoJet(momentum_1[solution_number]));
        if (doublet_1.Jet().m() <= 0) continue;
        Doublet doublet_2(quartet.Doublet2().SingletJet2(), PseudoJet(momentum_2[solution_number]));
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

        Print(Severity::Debug, "TriplePair Bdt", sextet.Bdt(), quartet.Bdt());
        //         Print(Severity::Debug, "Neutrino masses", Jet1.m(), Jet2.m());
        Print(Severity::Debug, "W masses", (PseudoJet(momentum_1[solution_number]) + quartet.Doublet1().SingletJet2()).m(), (PseudoJet(momentum_2[solution_number]) + quartet.Doublet2().SingletJet2()).m());
        Print(Severity::Debug, "top masses", (PseudoJet(momentum_1[solution_number]) + quartet.Doublet1().SingletJet2() + quartet.Doublet1().SingletJet1()).m(), (PseudoJet(momentum_2[solution_number]) + quartet.Doublet2().SingletJet2() + quartet.Doublet2().SingletJet1()).m());
        //         Print(Severity::Debug, "Higg mass", (Jet1 + Pair1.PseudoJet2() + Pair1.PseudoJet1() + Jet2 + Pair2.PseudoJet2() + Pair1.PseudoJet1()).m());
    }
    if (solution_sum == 0) {
//         if (counter_ == 10) {
//             Print(Severity::Error, "No Solution", counter_);
//             return sextets;
//         }
//         ++counter_;
//         sextets = Sextets(quartet, missing_et - 0.1 * (quartet.Jet() - missing_et));
      sextets.emplace_back(Fake(quartet));

    }
    return sextets;
}

std::vector<analysis::Sextet> WimpMass::Sextet(const Quartet22 &quartet, const fastjet::PseudoJet &missing_et, const Jets &neutrinos, const Tag tag)
{
    Print(Severity::Information, "Triple Pair");

    std::vector<analysis::Sextet> sextets = Sextets(quartet, missing_et);
    Print(Severity::Debug, "Number Solutions", sextets.size());

    if (sextets.empty()) return sextets;
//     if (Neutrinos.size() < 2) return sextets;

    for (const auto & Neutrino : neutrinos) Print(Severity::Debug, "Neutrino", Neutrino);
    Print(Severity::Debug, "Neutrino Sum", neutrinos[0] + neutrinos[1]);
    Print(Severity::Debug, "MET", missing_et);

    std::map<float, analysis::Sextet> map;
    for (const auto & sextet : sextets) {
        fastjet::PseudoJet Neutrino1 = sextet.Triplet1().Doublet().SingletJet2();
        fastjet::PseudoJet Neutrino2 = sextet.Triplet2().Doublet().SingletJet2();

        std::vector<float> Neutrino1Errors, Neutrino2Errors;
        for (const auto & Neutrino : neutrinos) {
            //             Print(Severity::Error, "Neutrino Mass", Neutrino.m());
            Neutrino1Errors.emplace_back((Neutrino + Neutrino1).m());
            Print(Severity::Debug, "Neutrino 1 Error", (Neutrino + Neutrino1).m());
            Neutrino2Errors.emplace_back((Neutrino + Neutrino2).m());
            Print(Severity::Debug, "Neutrino 2 Error", (Neutrino + Neutrino2).m());
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
        Print(Severity::Debug, "TriplePair Bdt", sextet.Bdt());
    }

    for (const auto & pair : map) Print(Severity::Debug, "Neutrino Error Sum", pair.first);
    if (tag == Tag::Signal) map.erase(std::next(map.begin()), map.end());
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

Sextet WimpMass::Fake(const Quartet22 &quartet) const
{
  Triplet triplet_1(Doublet(quartet.Doublet1().SingletJet2()),quartet.Doublet1().SingletJet1());
  triplet_1.SetBdt(quartet.Doublet1().Bdt());
  Triplet triplet_2(Doublet(quartet.Doublet2().SingletJet2()),quartet.Doublet2().SingletJet1());
  triplet_2.SetBdt(quartet.Doublet2().Bdt());
  return analysis::Sextet(triplet_1,triplet_2);
}


}
