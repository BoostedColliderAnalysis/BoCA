# include "HeavyHiggsLeptonicTagger.hh"
# include "WIMPMASS.h"
# include "Predicate.hh"

heavyhiggs::HeavyHiggsLeptonicTagger::HeavyHiggsLeptonicTagger()
{
    //     DebugLevel = analysis::Object::kDebug;

    Print(kNotification, "Constructor");
    set_tagger_name("HeavyHiggsLeptonic");
    top_leptonic_reader_.set_tagger(top_leptonic_tagger_);
    DefineVariables();
}

void heavyhiggs::HeavyHiggsLeptonicTagger::DefineVariables()
{

    Print(kNotification , "Define Variables");

    AddSpectator(branch_.Mass, "Mass");
    AddVariable(branch_.Pt, "Pt");
    AddVariable(branch_.Rap, "Rap");
    AddVariable(branch_.Phi, "Phi");

    AddVariable(branch_.DeltaPt, "DeltaPt");
    AddVariable(branch_.DeltaR, "DeltaR");
    AddVariable(branch_.DeltaRap, "DeltaRap");
    AddVariable(branch_.DeltaPhi, "DeltaPhi");

    AddVariable(branch_.LargerWDeltaR, "LargerWDeltaR");
    AddVariable(branch_.LargerWDeltaRap, "LargerWDeltaRap");
    AddVariable(branch_.LargerWDeltaPhi, "LargerWDeltaPhi");

    AddVariable(branch_.SmallerWDeltaR, "SmallerWDeltaR");
    AddVariable(branch_.SmallerWDeltaRap, "SmallerWDeltaRap");
    AddVariable(branch_.SmallerWDeltaPhi, "SmallerWDeltaPhi");

    AddVariable(branch_.LargerNeutrinoDeltaR, "LargerNeutrinoDeltaR");
    AddVariable(branch_.LargerNeutrinoDeltaRap, "LargerNeutrinoDeltaRap");
    AddVariable(branch_.LargerNeutrinoDeltaPhi, "LargerNeutrinoDeltaPhi");

    AddVariable(branch_.SmallerNeutrinoDeltaR, "SmallerNeutrinoDeltaR");
    AddVariable(branch_.SmallerNeutrinoDeltaRap, "SmallerNeutrinoDeltaRap");
    AddVariable(branch_.SmallerNeutrinoDeltaPhi, "SmallerNeutrinoDeltaPhi");

    AddVariable(branch_.Bdt, "Bdt");
    AddSpectator(branch_.Tag, "Tag");
}

int heavyhiggs::HeavyHiggsLeptonicTagger::Train(analysis::Event &event, const Object::Tag tag)
{
    Print(kInformation, "Higgs Tags");

    float Mass = event.mass();

    std::vector<analysis::Doublet> doublets = top_leptonic_reader_.Multiplets<analysis::TopLeptonicTagger>(event);

    fastjet::PseudoJet missing_et = event.hadrons().MissingEt();
    analysis::Jets neutrinos ;//= event.partons().GetNeutrinos(); // TODO fix this!!

    Print(kInformation, "Number of doublets", doublets.size());

    std::vector<analysis::Sextet> sextets;
    for (const auto & doublet1 : doublets) {
        for (const auto & doublet2 : doublets) {
            if (doublet1.Singlet1() == doublet2.Singlet1()) continue;
            if (doublet1.Singlet2() == doublet2.Singlet2()) continue;
            analysis::Quartet22 quartet(doublet1, doublet2);
//             quartet.SetTag(GetTag(quartet));
            if (quartet.Tag() != tag) continue;
            std::vector<analysis::Sextet> Presextets;
//             if (Tag == kSignal)
            Presextets = sextet(quartet, missing_et, neutrinos, tag);
//             else Presextets = Getsextets(quartet, MissingEt);
            for (const auto & sextet : Presextets) {
//                 if (sextet.GetsextetJet().m() < 10) continue; // TODO do we need this
                if (tag == kSignal && sextet.Jet().m() < Mass / 2)continue;
                sextets.emplace_back(sextet);
            }
        }
    }
    Print(kInformation, "Numeber of sextets", sextets.size());


    if (tag == kSignal && sextets.size() > 1) {
        Print(kError, "Higgs Candidates", sextets.size());
        sextets = SortedByMassTo(sextets,Mass);
        sextets.erase(sextets.begin() + 1, sextets.end());
    }

    return SaveEntries<HeavyHiggsLeptonicBranch>(sextets);
}

std::vector<analysis::Sextet>  heavyhiggs::HeavyHiggsLeptonicTagger::Multiplets(analysis::Event &event, const TMVA::Reader &reader)
{
    Print(kInformation, "Bdt");
    std::vector<analysis::Doublet> doublets = top_leptonic_reader_.Multiplets<analysis::TopLeptonicTagger>(event);
    fastjet::PseudoJet missing_et = event.hadrons().MissingEt();

    std::vector<analysis::Sextet> sextets;
    for (const auto & doublet1 : doublets) {
        for (const auto & doublet2 : doublets) {
            if (doublet1.Singlet1() == doublet2.Singlet1()) continue;
            if (doublet1.Singlet2() == doublet2.Singlet2()) continue;
            analysis::Quartet22 quartet(doublet1, doublet2);
            std::vector<analysis::Sextet> pre_sextets;
            pre_sextets = Sextets(quartet, missing_et);
            for (auto & sextet : pre_sextets) {
                branch_ = branch<HeavyHiggsLeptonicBranch>(sextet);
                sextet.SetBdt(Bdt(reader));
                sextets.emplace_back(sextet);
            }
        }
    }
    return ReduceResult(sextets);
}

void heavyhiggs::HeavyHiggsLeptonicTagger::SetMomentum(double momentum[4], const fastjet::PseudoJet &jet)
{
    momentum[0] = jet.E();
    momentum[1] = jet.px();
    momentum[2] = jet.py();
    momentum[3] = jet.pz();
}

std::vector<analysis::Sextet> heavyhiggs::HeavyHiggsLeptonicTagger::Sextets(const analysis::Quartet22& quartet, const fastjet::PseudoJet& missing_et)
{
    Print(kInformation, "Triple Pairs");

    event22 structure;

    SetMomentum(structure.p3, quartet.Getdoublet1().Singlet2());
    SetMomentum(structure.p4, quartet.Getdoublet2().Singlet2());
    SetMomentum(structure.p5, quartet.Getdoublet1().Singlet1());
    SetMomentum(structure.p6, quartet.Getdoublet2().Singlet1());
    SetMomentum(structure.pmiss, missing_et);

    Print(kDebug, "Lepton 1 (p3)", GetJet(structure.p3));
    Print(kDebug, "Lepton 2 (p4)" , GetJet(structure.p4));
    Print(kDebug, "Jet 1 (p5)" , GetJet(structure.p5));
    Print(kDebug, "Jet 2 (p6)" , GetJet(structure.p6));
    Print(kDebug, "PMiss" , GetJet(structure.pmiss));

    double P1[4][4], P2[4][4];
    int SolutionSum;
    solve22(structure, Mass(ElectronNeutrinoId), Mass(WId), Mass(TopId), SolutionSum, P1, P2);
    Print(kDebug, "Number solutions", SolutionSum);

    std::vector<analysis::Sextet> sextets;
    for (const int SolutionNumber : analysis::Range(SolutionSum)) {
        Print(kDebug, "Solution ", SolutionNumber);
        Print(kDebug, "Neutrino 1 (p1)" , GetJet(P1[SolutionNumber]));
        Print(kDebug, "Neutrino 2 (p2)" , GetJet(P2[SolutionNumber]));

        analysis::Doublet doublet1(quartet.Getdoublet1().Singlet2(), GetJet(P1[SolutionNumber]));
        if (doublet1.Jet().m() <= 0) continue;
        analysis::Doublet doublet2(quartet.Getdoublet2().Singlet2(), GetJet(P2[SolutionNumber]));
        if (doublet2.Jet().m() <= 0) continue;

        analysis::Triplet triplet1(doublet1, quartet.Getdoublet1().Singlet1());
        if (triplet1.Jet().m() <= 0) continue;
        analysis::Triplet triplet2(doublet2, quartet.Getdoublet2().Singlet1());
        if (triplet2.Jet().m() <= 0) continue;

        analysis::Sextet sextet(triplet1, triplet2);
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

std::vector<analysis::Sextet> heavyhiggs::HeavyHiggsLeptonicTagger::sextet(const analysis::Quartet22& quartet, const fastjet::PseudoJet& missing_et, const analysis::Jets& neutrinos, const analysis::Object::Tag tag)
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
        fastjet::PseudoJet Neutrino1 = sextet.triplet1().doublet().Singlet2();
        fastjet::PseudoJet Neutrino2 = sextet.triplet2().doublet().Singlet2();

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
