# include "HChargedHiggsLeptonicTagger.hh"

hanalysis::HChargedHiggsLeptonicTagger::HChargedHiggsLeptonicTagger(HBottomTagger *const NewBottomTagger, HTopLeptonicTagger *const NewTopLeptonicTagger)
{
//     DebugLevel = hanalysis::HObject::HDebug;

    Print(HNotification, "Constructor");

    BottomTagger = NewBottomTagger;
    BottomReader = new HReader(BottomTagger);
    TopLeptonicTagger = NewTopLeptonicTagger;
    TopLeptonicReader = new HReader(TopLeptonicTagger);

    SetTaggerName("ChargedHiggsLeptonic");

    Branch = new HChargedHiggsLeptonicBranch();
    JetTag = new HJetTag();

    DefineVariables();
}

hanalysis::HChargedHiggsLeptonicTagger::~HChargedHiggsLeptonicTagger()
{
    Print(HNotification, "Destructor");
    delete Branch;
    delete JetTag;
    delete BottomReader;
    delete TopLeptonicReader;

}

void hanalysis::HChargedHiggsLeptonicTagger::FillBranch(const hanalysis::HTriplet &Triplet)
{
    Print(HInformation, "FillPairTagger", Triplet.GetBdt());
    FillBranch(Branch, Triplet);
}

void hanalysis::HChargedHiggsLeptonicTagger::FillBranch(HChargedHiggsLeptonicBranch *ChargedHiggsBranch, const HTriplet &Triplet)
{
    Print(HInformation, "FillPairTagger", Triplet.GetBdt());

    ChargedHiggsBranch->HeavyHiggsMass = Triplet.GetTripletJet().m();
    ChargedHiggsBranch->HeavyHiggsPt = Triplet.GetTripletJet().m();

    ChargedHiggsBranch->TopDeltaR = Triplet.GetDeltaR();
    ChargedHiggsBranch->TopDeltaRap = Triplet.GetDeltaRap();
    ChargedHiggsBranch->TopDeltaPhi = Triplet.GetDeltaPhi();

//     HeavyHiggsBranch->LargerWDeltaR = Quartet.GetLargerTripletDeltaR();
//     HeavyHiggsBranch->LargerWDeltaRap = Quartet.GetLargerTripletDeltaRap();
//     HeavyHiggsBranch->LargerWDeltaPhi = Quartet.GetLargerTripleDeltaPhi();
//
//     HeavyHiggsBranch->SmallerWDeltaR = Quartet.GetSmallerTripletDeltaR();
//     HeavyHiggsBranch->SmallerWDeltaRap = Quartet.GetSmallerTripletDeltaRap();
//     HeavyHiggsBranch->SmallerWDeltaPhi = Quartet.GetSmallerTripletDeltaPhi();
//
//     HeavyHiggsBranch->LargerNeutrinoDeltaR = Quartet.GetLargerTripletDeltaR();
//     HeavyHiggsBranch->LargerNeutrinoDeltaRap = Quartet.GetLargerTripletDeltaRap();
//     HeavyHiggsBranch->LargerNeutrinoDeltaPhi = Quartet.GetLargerTripleDeltaPhi();
//
//     HeavyHiggsBranch->SmallerNeutrinoDeltaR = Quartet.GetSmallerTripletDeltaR();
//     HeavyHiggsBranch->SmallerNeutrinoDeltaRap = Quartet.GetSmallerTripletDeltaRap();
//     HeavyHiggsBranch->SmallerNeutrinoDeltaPhi = Quartet.GetSmallerTripletDeltaPhi();

    ChargedHiggsBranch->TopBdt = Triplet.GetBdt();
    ChargedHiggsBranch->HeavyHiggsTag = Triplet.GetTag();

}

void hanalysis::HChargedHiggsLeptonicTagger::DefineVariables()
{

    Print(HNotification , "Define Variables");

    Observables.push_back(NewObservable(&Branch->HeavyHiggsPt, "HeavyHiggsPt"));

    Observables.push_back(NewObservable(&Branch->TopDeltaR, "TopDeltaR"));
    Observables.push_back(NewObservable(&Branch->TopDeltaRap, "TopDeltaRap"));
    Observables.push_back(NewObservable(&Branch->TopDeltaPhi, "TopDeltaPhi"));

//     Observables.push_back(NewObservable(&Branch->LargerWDeltaR, "LargerWDeltaR"));
//     Observables.push_back(NewObservable(&Branch->LargerWDeltaRap, "LargerWDeltaRap"));
//     Observables.push_back(NewObservable(&Branch->LargerWDeltaPhi, "LargerWDeltaPhi"));
//
//     Observables.push_back(NewObservable(&Branch->SmallerWDeltaR, "SmallerWDeltaR"));
//     Observables.push_back(NewObservable(&Branch->SmallerWDeltaRap, "SmallerWDeltaRap"));
//     Observables.push_back(NewObservable(&Branch->SmallerWDeltaPhi, "SmallerWDeltaPhi"));
//
//     Observables.push_back(NewObservable(&Branch->LargerNeutrinoDeltaR, "LargerNeutrinoDeltaR"));
//     Observables.push_back(NewObservable(&Branch->LargerNeutrinoDeltaRap, "LargerNeutrinoDeltaRap"));
//     Observables.push_back(NewObservable(&Branch->LargerNeutrinoDeltaPhi, "LargerNeutrinoDeltaPhi"));
//
//     Observables.push_back(NewObservable(&Branch->SmallerNeutrinoDeltaR, "SmallerNeutrinoDeltaR"));
//     Observables.push_back(NewObservable(&Branch->SmallerNeutrinoDeltaRap, "SmallerNeutrinoDeltaRap"));
//     Observables.push_back(NewObservable(&Branch->SmallerNeutrinoDeltaPhi, "SmallerNeutrinoDeltaPhi"));

    Observables.push_back(NewObservable(&Branch->TopBdt, "TopBdt"));

    Spectators.push_back(NewObservable(&Branch->HeavyHiggsTag, "HeavyHiggsTag"));
    Spectators.push_back(NewObservable(&Branch->HeavyHiggsMass, "HeavyHiggsMass"));

    Print(HNotification, "Variables defined");

}


std::vector< HChargedHiggsLeptonicBranch * > hanalysis::HChargedHiggsLeptonicTagger::GetBranches(HEvent *const Event, const HObject::HTag Tag)
{
    Print(HInformation, "Get Higgs Tags");

    JetTag->HeavyParticles = {TopId, ChargedHiggsId};
    HJets Jets = Event->GetJets()->GetStructuredTaggedJets(JetTag);

    Jets = BottomTagger->GetTruthBdt(Jets, BottomReader);

    HJets Leptons = Event->GetLeptons()->GetTaggedJets(JetTag);
    Print(HInformation, "Numeber of Jets", Jets.size(), Leptons.size());

    std::vector<HDoublet> Doublets = TopLeptonicTagger->GetBdt(Jets, Leptons, TopLeptonicReader);

//     fastjet::PseudoJet MissingEt = Event->GetJets()->GetMissingEt();
//     HJets Neutrinos = Event->GetParticles()->GetNeutrinos();

    Print(HInformation, "Number of Doublets", Doublets.size());

    std::vector<HTriplet> Triplets;
    for (const auto & Doublet : Doublets) {
        for (const auto & Jet : Jets) {
            if (Doublet.GetJet1() == Jet) continue;
            HTriplet Triplet(Doublet, Jet);
            Triplet.SetTag(GetTag(Triplet));
            if (Triplet.GetTag() != Tag) continue;
//             std::vector<HQuartet31> PreQuartets;
//             PreQuartets = GetQuartet(Quartet, MissingEt, Neutrinos, Tag);
//             for (auto & Quartet : PreQuartets) {
                Triplets.push_back(Triplet);
//             }
        }
    }
    Print(HInformation, "Numeber of Triplets", Triplets.size());


    if (Tag == HSignal && Triplets.size() > 1) {
        Print(HError, "Higgs Candidates", Triplets.size());
        std::sort(Triplets.begin(), Triplets.end(), SortByBdt());
        Triplets.erase(Triplets.begin() + 1, Triplets.end());
    }

    std::vector<HChargedHiggsLeptonicBranch *> ChargedHiggsBranches;
    for (const auto & Triplet : Triplets) {
        HChargedHiggsLeptonicBranch *ChargedHiggsLeptonicBranch = new HChargedHiggsLeptonicBranch();
        FillBranch(ChargedHiggsLeptonicBranch, Triplet);
        ChargedHiggsBranches.push_back(ChargedHiggsLeptonicBranch);
    }

    return ChargedHiggsBranches;

}

hanalysis::HObject::HTag hanalysis::HChargedHiggsLeptonicTagger::GetTag(const HTriplet &Triplet)
{
    Print(HInformation, "Get Triple Tag");

    if (Triplet.GetDoublet().GetTag() == HBackground) return HBackground;
//     if (Quartet.GetDoublet2().GetTag() == HBackground) return HBackground;
    // TODO check the following
    if (Triplet.GetDoublet().GetJet1().user_index() != -Triplet.GetJet().user_index()) return HBackground;
    return HSignal;
}

std::vector<hanalysis::HTriplet>  hanalysis::HChargedHiggsLeptonicTagger::GetBdt(const std::vector<HDoublet> &Doublets,const std::vector<fastjet::PseudoJet> Jets, const HReader *const Reader)
{
    Print(HInformation, "Get Bdt");

    std::vector<HTriplet> Triplets;
    for (const auto & Doublet : Doublets) {
        for (const auto & Jet : Jets) {
            if (Doublet.GetJet1() == Jet) continue;
            HTriplet Triplet(Doublet, Jet);
            Triplet.SetTag(GetTag(Triplet));
//             std::vector<HQuartet31> PreQuartets;
//             PreQuartets = GetQuartets(Quartet, MissingEt);
//             for (auto & Quartet : PreQuartets) {
                FillBranch(Triplet);
                Triplet.SetBdt(Reader->GetBdt());
                Triplets.push_back(Triplet);
//             }
        }
    }
    return Triplets;
}


// void hanalysis::HChargedHiggsLeptonicTagger::SetMomentum(double Momentum[4], const fastjet::PseudoJet &Jet)
// {
//     Momentum[0] = Jet.E();
//     Momentum[1] = Jet.px();
//     Momentum[2] = Jet.py();
//     Momentum[3] = Jet.pz();
// }

// std::vector<hanalysis::HQuartet31> hanalysis::HChargedHiggsLeptonicTagger::GetQuartets(const HQuartet &Quartet, const fastjet::PseudoJet &MissingEt)
// {
//     Print(HInformation, "Get Triple Pairs");
//
//     SetMomentum(Structure.p3, Quartet.GetDoublet1().GetJet2());
//     SetMomentum(Structure.p4, Quartet.GetDoublet2().GetJet2());
//     SetMomentum(Structure.p5, Quartet.GetDoublet1().GetJet1());
//     SetMomentum(Structure.p6, Quartet.GetDoublet2().GetJet1());
//     SetMomentum(Structure.pmiss, MissingEt);
//
//     Print(HDebug, "Lepton 1 (p3)", GetJet(Structure.p3));
//     Print(HDebug, "Lepton 2 (p4)" , GetJet(Structure.p4));
//     Print(HDebug, "Jet 1 (p5)" , GetJet(Structure.p5));
//     Print(HDebug, "Jet 2 (p6)" , GetJet(Structure.p6));
//     Print(HDebug, "PMiss" , GetJet(Structure.pmiss));
//
//     double P1[4][4], P2[4][4];
//     int SolutionSum;
//     solve22(Structure, NeutrinoMass, WMass, TopMass, SolutionSum, P1, P2);
//     Print(HDebug, "Number solutions", SolutionSum);
//
//     std::vector<hanalysis::HQuartet31> Quartets;
//     for (const int SolutionNumber : HRange(SolutionSum)) {
//         Print(HDebug, "Solution ", SolutionNumber);
//         Print(HDebug, "Neutrino 1 (p1)" , GetJet(P1[SolutionNumber]));
//         Print(HDebug, "Neutrino 2 (p2)" , GetJet(P2[SolutionNumber]));
//
//         HDoublet Doublet1(Quartet.GetDoublet1().GetJet2(), GetJet(P1[SolutionNumber]));
//         if (Doublet1.GetDoubletJet().m() <= 0) continue;
//         HDoublet Doublet2(Quartet.GetDoublet2().GetJet2(), GetJet(P2[SolutionNumber]));
//         if (Doublet2.GetDoubletJet().m() <= 0) continue;
//
//         HTriplet Triplet1(Doublet1, Quartet.GetDoublet1().GetJet1());
//         if (Triplet1.GetTripletJet().m() <= 0) continue;
//         HTriplet Triplet2(Doublet2, Quartet.GetDoublet2().GetJet1());
//         if (Triplet2.GetTripletJet().m() <= 0) continue;
//
//         HQuartet31 Quartet(Triplet1, Triplet2);
//         if (Quartet.GetQuartetJet().m() <= 0) continue;
//         Quartet.SetTag(Quartet.GetTag());
//         Quartet.SetBdt(Quartet.GetBdt());
//         Quartets.push_back(Quartet);
//
//         Print(HDebug, "TriplePair Bdt", Quartet.GetBdt(), Quartet.GetBdt());
//         //         Print(HDebug, "Neutrino masses", Jet1.m(), Jet2.m());
//         Print(HDebug, "W masses", (GetJet(P1[SolutionNumber]) + Quartet.GetDoublet1().GetJet2()).m(), (GetJet(P2[SolutionNumber]) + Quartet.GetDoublet2().GetJet2()).m());
//         Print(HDebug, "top masses", (GetJet(P1[SolutionNumber]) + Quartet.GetDoublet1().GetJet2() + Quartet.GetDoublet1().GetJet1()).m(), (GetJet(P2[SolutionNumber]) + Quartet.GetDoublet2().GetJet2() + Quartet.GetDoublet1().GetJet1()).m());
//         //         Print(HDebug, "Higg mass", (Jet1 + Pair1.GetJet2() + Pair1.GetJet1() + Jet2 + Pair2.GetJet2() + Pair1.GetJet1()).m());
//     }
//
//     return Quartets;
//
// }

// std::vector<hanalysis::HQuartet31> hanalysis::HChargedHiggsLeptonicTagger::GetQuartet(const HQuartet &Quartet, const fastjet::PseudoJet &MissingEt, const HJets &Neutrinos, const HTag Tag)
// {
//     Print(HInformation, "Get Triple Pair");
//
//     std::vector<HQuartet31> Quartets = GetQuartets(Quartet, MissingEt);
//     Print(HDebug, "Number Solutions", Quartets.size());
//
//     if (Quartets.size() < 1) return Quartets;
// //     if (Neutrinos.size() < 2) return Quartets;
//
//     for (const auto & Neutrino : Neutrinos) Print(HDebug, "Neutrino", Neutrino);
//     Print(HDebug, "Neutrino Sum", Neutrinos[0] + Neutrinos[1]);
//     Print(HDebug, "MET", MissingEt);
//
//     std::map<float, HQuartet31> Map;
//     for (const auto & Quartet : Quartets) {
//         fastjet::PseudoJet Neutrino1 = Quartet.GetTriplet1().GetDoublet().GetJet2();
//         fastjet::PseudoJet Neutrino2 = Quartet.GetTriplet2().GetDoublet().GetJet2();
//
//         std::vector<float> Neutrino1Errors, Neutrino2Errors;
//         for (const auto & Neutrino : Neutrinos) {
//             //             Print(HError, "Neutrino Mass", Neutrino.m());
//             Neutrino1Errors.push_back((Neutrino + Neutrino1).m());
//             Print(HDebug, "Neutrino 1 Error", (Neutrino + Neutrino1).m());
//             Neutrino2Errors.push_back((Neutrino + Neutrino2).m());
//             Print(HDebug, "Neutrino 2 Error", (Neutrino + Neutrino2).m());
//         }
//
//         float Error = LargeNumber;
//         for (const auto Neutrino1Error : Neutrino1Errors)
//             for (const auto Neutrino2Error : Neutrino2Errors) {
//                 if (&Neutrino1Error - &Neutrino1Errors[0] == &Neutrino2Error - &Neutrino2Errors[0]) continue;
//                 if (Neutrino1Error + Neutrino2Error < Error) Error = Neutrino1Error + Neutrino2Error;
//
//             }
//
// //         for (size_t i = 0; i < Neutrino1Errors.size(); ++i) {
// //             for (size_t j = i + 1; j < Neutrino2Errors.size(); ++j) {
// //                 if (Neutrino1Errors[i] + Neutrino2Errors[j] < Error) Error = Neutrino1Errors[i] + Neutrino2Errors[j];
// //             }
// //         }
// //         for (size_t j = 0; j < Neutrino2Errors.size(); ++j) {
// //             for (size_t i = j + 1; i < Neutrino1Errors.size(); ++i) {
// //                 if (Neutrino1Errors[i] + Neutrino2Errors[j] < Error) Error = Neutrino1Errors[i] + Neutrino2Errors[j];
// //             }
// //         }
//         Map[Error] = Quartet;
//         Print(HDebug, "TriplePair Bdt", Quartet.GetBdt());
//     }
//
//     for (const auto & Pair : Map) Print(HDebug, "Neutrino Error Sum", Pair.first);
//     if (Tag == HSignal) Map.erase(std::next(Map.begin()), Map.end());
//     else Map.erase(Map.begin());
//
//     std::vector<HQuartet31> FinalQuartet;
//     for (const auto Pair : Map) {
//         HQuartet31 Quartet = Pair.second;
//         FinalQuartet.push_back(Quartet);
//     }
//
// //     std::pair<float , HQuartet31> Pair = *(Map.begin());
// //     HQuartet31 Quartet = Pair.second;
// //     FinalQuartet.push_back(Quartet);
//
// //     FinalQuartet.push_back(*(Map.begin()).second);
//
//     return FinalQuartet;
// }




