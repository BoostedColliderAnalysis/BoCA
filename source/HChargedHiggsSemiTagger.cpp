# include "HChargedHiggsSemiTagger.hh"

hanalysis::HChargedHiggsSemiTagger::HChargedHiggsSemiTagger(
    hanalysis::HBottomTagger *const NewBottomTagger,
    hanalysis::HWSemiTagger *const NewWSemiTagger,
    hanalysis::HWTagger *const NewWTagger,
    hanalysis::HTopSemiTagger *const NewTopSemiTagger,
    hanalysis::HTopHadronicTagger *const NewTopHadronicTagger)
{
//     DebugLevel = hanalysis::HObject::HDebug;

    Print(HNotification, "Constructor");

    BottomTagger = NewBottomTagger;
    BottomReader = new HReader(BottomTagger);
    WSemiTagger = NewWSemiTagger;
    WSemiReader = new HReader(WSemiTagger);
    WTagger = NewWTagger;
    WReader = new HReader(WTagger);
    TopSemiTagger = NewTopSemiTagger;
    TopSemiReader = new HReader(TopSemiTagger);
    TopHadronicTagger = NewTopHadronicTagger;
    TopHadronicReader = new HReader(TopHadronicTagger);

    SetTaggerName("ChargedHiggsSemi");

    Branch = new HChargedHiggsSemiBranch();
    JetTag = new HJetTag();

    DefineVariables();
}

hanalysis::HChargedHiggsSemiTagger::~HChargedHiggsSemiTagger()
{
    Print(HNotification, "Destructor");
    delete Branch;
    delete JetTag;
    delete BottomReader;
    delete WReader;
    delete WSemiReader;
    delete TopHadronicReader;
    delete TopSemiReader;

}

void hanalysis::HChargedHiggsSemiTagger::FillBranch(const hanalysis::HQuartet31 &HQuartet)
{
    Print(HInformation, "FillPairTagger", HQuartet.Bdt());
    FillBranch(Branch, HQuartet);
}

void hanalysis::HChargedHiggsSemiTagger::FillBranch(HChargedHiggsSemiBranch *ChargedHiggsBranch, const HQuartet31 &Quartet)
{
    Print(HInformation, "FillPairTagger", Quartet.Bdt());

    ChargedHiggsBranch->HeavyHiggsMass = Quartet.GetQuartetJet().m();
    ChargedHiggsBranch->HeavyHiggsPt = Quartet.GetQuartetJet().pt();

    ChargedHiggsBranch->TopDeltaR = Quartet.GetDeltaR();
    ChargedHiggsBranch->TopDeltaRap = Quartet.GetDeltaRap();
    ChargedHiggsBranch->TopDeltaPhi = Quartet.GetDeltaPhi();

//     HeavyHiggsBranch->LargerWDeltaR = TriplePair.GetLargerTripleDeltaR();
//     HeavyHiggsBranch->LargerWDeltaRap = TriplePair.GetLargerTripleDeltaRap();
//     HeavyHiggsBranch->LargerWDeltaPhi = TriplePair.GetLargerTripleDeltaPhi();
//
//     HeavyHiggsBranch->SmallerWDeltaR = TriplePair.GetSmallerTripleDeltaR();
//     HeavyHiggsBranch->SmallerWDeltaRap = TriplePair.GetSmallerTripleDeltaRap();
//     HeavyHiggsBranch->SmallerWDeltaPhi = TriplePair.GetSmallerTripleDeltaPhi();
//
//     HeavyHiggsBranch->LargerNeutrinoDeltaR = TriplePair.GetLargerTripleDeltaR();
//     HeavyHiggsBranch->LargerNeutrinoDeltaRap = TriplePair.GetLargerTripleDeltaRap();
//     HeavyHiggsBranch->LargerNeutrinoDeltaPhi = TriplePair.GetLargerTripleDeltaPhi();
//
//     HeavyHiggsBranch->SmallerNeutrinoDeltaR = TriplePair.GetSmallerTripleDeltaR();
//     HeavyHiggsBranch->SmallerNeutrinoDeltaRap = TriplePair.GetSmallerTripleDeltaRap();
//     HeavyHiggsBranch->SmallerNeutrinoDeltaPhi = TriplePair.GetSmallerTripleDeltaPhi();

    ChargedHiggsBranch->TopBdt = Quartet.Bdt();
    ChargedHiggsBranch->HeavyHiggsTag = Quartet.Tag();

}

void hanalysis::HChargedHiggsSemiTagger::DefineVariables()
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

struct SortQuartetByMass {
    inline bool operator()(const hanalysis::HQuartet31 &Quartet1, const hanalysis::HQuartet31 &Quartet2) {
        return (Quartet1.GetQuartetJet().m() > Quartet2.GetQuartetJet().m());
    }
};

std::vector< HChargedHiggsSemiBranch * > hanalysis::HChargedHiggsSemiTagger::GetBranches(hanalysis::HEvent *const Event, const hanalysis::HObject::HTag Tag)
{
    Print(HInformation, "Get Higgs Tags");

    JetTag->HeavyParticles = {TopId};
    HJets Jets = Event->GetJets()->GetStructuredTaggedJets(JetTag);

    Jets = BottomTagger->GetBdt(Jets, BottomReader);
    HJets Leptons = Event->GetLeptons()->GetTaggedJets(JetTag);
    fastjet::PseudoJet MissingEt = Event->GetJets()->GetMissingEt();
    std::vector<HDoublet> Doublets = WSemiTagger->GetBdt(Leptons, MissingEt, WSemiReader);
    std::vector<HTriplet> Triplets = TopSemiTagger->GetBdt(Doublets, Jets,MissingEt, TopSemiReader);

    std::vector<HDoublet> DoubletsHadronic = WTagger->GetBdt(Jets, WReader);
    std::vector<HTriplet> TripletsHadronic = TopHadronicTagger->GetBdt(DoubletsHadronic, Jets, TopHadronicReader);

    Triplets.insert(Triplets.end(), TripletsHadronic.begin(), TripletsHadronic.end());

    std::vector<HQuartet31 > Quartets;
    for (const auto & Triplet : Triplets)
        for (const auto & Jet : Jets) {
            if (Triplet.Singlet() == Jet) continue;
            if (Triplet.Doublet().Singlet1() == Jet) continue;
            if (Triplet.Doublet().Singlet2() == Jet) continue;
            HQuartet31 Quartet(Triplet, Jet);
            Quartet.SetTag(GetTag(Quartet));
            if (Quartet.Tag() != Tag) continue;
            if (Quartet.GetQuartetJet().m() < 0)continue;
            Quartets.push_back(Quartet);
        }

    Print(HInformation, "Number of Heavy Higgses", Quartets.size());

    if (Tag == HSignal && Quartets.size() > 1) {
        Print(HError, "Higgs Candidates", Quartets.size());
        std::sort(Quartets.begin(), Quartets.end(), SortQuartetByMass());
        Quartets.erase(Quartets.begin() + 1, Quartets.end());
    }

    std::vector<HChargedHiggsSemiBranch *> ChargedHiggsBranches;
    for (const auto & Quartet : Quartets) {
        HChargedHiggsSemiBranch *ChargedHiggsSemiBranch = new HChargedHiggsSemiBranch();
        FillBranch(ChargedHiggsSemiBranch, Quartet);
        ChargedHiggsBranches.push_back(ChargedHiggsSemiBranch);
    }


    return ChargedHiggsBranches;

}


hanalysis::HObject::HTag hanalysis::HChargedHiggsSemiTagger::GetTag(const HQuartet31 &Quartet)
{
    Print(HInformation, "Get Sextet Tag");


    HJetInfo JetInfoB = Quartet.GetSinglet().user_info<HJetInfo>();
    JetInfoB.ExtractFraction(BottomId);
    HJetInfo JetInfoB1 = Quartet.GetTriplet().Singlet().user_info<HJetInfo>();
    JetInfoB1.ExtractFraction(BottomId);
    HJetInfo JetInfoW1 = Quartet.GetTriplet().Doublet().Singlet1().user_info<HJetInfo>();
    JetInfoW1.ExtractFraction(WId);
    HJetInfo JetInfoW2 = Quartet.GetTriplet().Doublet().Singlet2().user_info<HJetInfo>();
    JetInfoW2.ExtractFraction(WId);

    if (std::abs(JetInfoB.MaximalId()) != BottomId) return HBackground;
    if (JetInfoB.MaximalId() != -JetInfoB1.MaximalId()) return HBackground;

    if (std::abs(JetInfoW1.MaximalId()) != WId) return HBackground;
    if (JetInfoW1.MaximalId() != JetInfoW2.MaximalId()) return HBackground;
    if (sgn(JetInfoW1.MaximalId()) != sgn(JetInfoB1.MaximalId())) return HBackground;

    //FIXME how to remove intrinsic background !!

    return HSignal;
}




std::vector<hanalysis::HQuartet31>  hanalysis::HChargedHiggsSemiTagger::GetBdt(std::vector<HTriplet> Triplets , std::vector<fastjet::PseudoJet> Siglets, const HReader *const Reader)
{

    std::vector<HQuartet31> Quartets;
    for (const auto & Triplet : Triplets)
        for (const auto & Jet : Siglets) {
            if (Triplet.Singlet() == Jet) continue;
            if (Triplet.Doublet().Singlet1() == Jet) continue;
            if (Triplet.Doublet().Singlet2() == Jet) continue;
            HQuartet31 Quartet(Triplet, Jet);
            FillBranch(Quartet);
            Quartet.SetBdt(Reader->Bdt());
            Quartets.push_back(Quartet);
        }

    std::sort(Quartets.begin(), Quartets.end());
    Quartets.erase(Quartets.begin() + std::min(MaxCombi, int(Quartets.size())), Quartets.end());
    return Quartets;
}


// std::vector<hanalysis::HQuartet31>  hanalysis::HChargedHiggsSemiTagger::GetQuartets(const HReader *const Reader)
// {
//     // FIXME this is totally wrong and cant work
//     Print(HError, "this is totally wrong and cant work");
//     hanalysis::HEvent *Event;
//
//     HJets Jets = Event->GetJets()->GetStructuredTaggedJets(JetTag);
//     Jets = BottomTagger->GetBdt(Jets, BottomReader);
//     HJets Leptons = Event->GetLeptons()->GetTaggedJets(JetTag);
//     fastjet::PseudoJet MissingEt = Event->GetJets()->GetMissingEt();
//     std::vector<HDoublet> Doublets = WSemiTagger->GetBdt(Leptons, MissingEt, WSemiReader);
//     std::vector<HTriplet> Triplets = TopSemiTagger->GetBdt(Doublets, Jets, TopSemiReader);
// //     std::vector<HTriplet> TripletsHadronic = TopHadronicTagger->GetTriplets(TopHadronicReader);
//
//     std::vector<HQuartet31> Quartets;
//     for (const auto & Triplet : Triplets)
//         for (const auto & Jet : Jets) {
//             if (Triplet.GetSinglet() == Jet) continue;
//             if (Triplet.GetDoublet().Singlet1() == Jet) continue;
//             if (Triplet.GetDoublet().Singlet2() == Jet) continue;
//             HQuartet31 Quartet(Triplet, Jet);
//             Quartet.SetTag(GetTag(Quartet));
//             if (Quartet.GetQuartetJet().m() < 0)continue;
//             FillBranch(Quartet);
//             Quartet.SetBdt(Reader->Bdt());
//             Quartets.push_back(Quartet);
//         }
//
//     return Quartets;
// }
