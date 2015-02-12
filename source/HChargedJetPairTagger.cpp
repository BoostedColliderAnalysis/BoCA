# include "HChargedJetPairTagger.hh"

hanalysis::HChargedJetPairTagger::HChargedJetPairTagger()
{
    //     DebugLevel = hanalysis::HObject::HDebug;
    Print(HNotification, "Constructor");
    SetTaggerName("ChargedJetPair");
    DefineVariables();
}

hanalysis::HChargedJetPairTagger::~HChargedJetPairTagger()
{
    Print(HNotification, "Destructor");
}

void hanalysis::HChargedJetPairTagger::SetTagger(const HBottomTagger &NewBottomTagger, const HWSemiTagger &NewWSemiTagger, const HWTagger &NewWTagger, const HTopSemiTagger &NewTopSemiTagger, const HTopHadronicTagger &NewTopHadronicTagger)
{
    Print(HNotification, "Set Tagger", NewBottomTagger.GetTaggerName());

    BottomTagger = NewBottomTagger;
//     BottomTagger.SetTagger();
//     BottomReader.SetMva(BottomTagger);

    WSemiTagger = NewWSemiTagger;
//     WSemiTagger.SetTagger();
//     WSemiReader.SetMva(WSemiTagger);

    WTagger = NewWTagger;
//     WTagger.SetTagger(BottomTagger);
//     WReader.SetMva(WTagger);

    TopSemiTagger = NewTopSemiTagger;
//     TopSemiTagger.SetTagger(BottomTagger, WSemiTagger);
//     TopSemiReader.SetMva(TopSemiTagger);

    TopHadronicTagger = NewTopHadronicTagger;
//     TopHadronicTagger.SetTagger(BottomTagger, WTagger);
//     TopHadronicReader.SetMva(TopHadronicTagger);


    SetTaggerName("ChargedJetPair");
    DefineVariables();
}

void hanalysis::HChargedJetPairTagger::DefineVariables()
{

    Print(HNotification , "Define Variables");

    Observables.clear();
    Spectators.clear();

    Observables.push_back(NewObservable(&Branch.Mass, "Mass"));
    Observables.push_back(NewObservable(&Branch.Pt, "Pt"));
    Observables.push_back(NewObservable(&Branch.Rap, "Rap"));
    Observables.push_back(NewObservable(&Branch.Phi, "Phi"));
    Observables.push_back(NewObservable(&Branch.Ht, "Ht"));

    Observables.push_back(NewObservable(&Branch.DeltaM, "DeltaM"));
    Observables.push_back(NewObservable(&Branch.DeltaPt, "DeltaPt"));
    Observables.push_back(NewObservable(&Branch.DeltaPhi, "DeltaPhi"));
    Observables.push_back(NewObservable(&Branch.DeltaRap, "DeltaRap"));
    Observables.push_back(NewObservable(&Branch.DeltaR, "DeltaR"));

    Observables.push_back(NewObservable(&Branch.BottomMass, "BottomMass"));
    Observables.push_back(NewObservable(&Branch.BottomPt, "BottomPt"));
    Observables.push_back(NewObservable(&Branch.BottomRap, "BottomRap"));
    Observables.push_back(NewObservable(&Branch.BottomPhi, "BottomPhi"));
    Observables.push_back(NewObservable(&Branch.BottomBdt, "BottomBdt"));
//     Observables.push_back(NewObservable(&Branch.BottomBTag, "BottomBTag"));

    Observables.push_back(NewObservable(&Branch.TopMass, "TopMass"));
    Observables.push_back(NewObservable(&Branch.TopPt, "TopPt"));
    Observables.push_back(NewObservable(&Branch.TopRap, "TopRap"));
    Observables.push_back(NewObservable(&Branch.TopPhi, "TopPhi"));
    Observables.push_back(NewObservable(&Branch.TopBdt, "TopBdt"));
//     Observables.push_back(NewObservable(&Branch.TopBTag, "TopBTag"));

    Observables.push_back(NewObservable(&Branch.Bdt, "Bdt"));
    Spectators.push_back(NewObservable(&Branch.Tag, "Tag"));

    Print(HNotification, "Variables defined");

}

HChargedJetPairBranch hanalysis::HChargedJetPairTagger::GetBranch(const HQuartet31 &Quartet) const
{

    Print(HInformation, "FillPairTagger", Quartet.Bdt());

    HChargedJetPairBranch JetPairBranch;

    JetPairBranch.Mass = Quartet.Jet().m();
    JetPairBranch.Pt = Quartet.Jet().pt();
    JetPairBranch.Rap = Quartet.Jet().rap();
    JetPairBranch.Phi = Quartet.Jet().phi();
    JetPairBranch.Ht = Quartet.Ht();

    JetPairBranch.DeltaM = Quartet.DeltaM();
    JetPairBranch.DeltaPt = Quartet.DeltaPt();
    JetPairBranch.DeltaR = Quartet.DeltaR();
    JetPairBranch.DeltaRap = Quartet.DeltaRap();
    JetPairBranch.DeltaPhi = Quartet.DeltaPhi();

    JetPairBranch.BottomPt = Quartet.Singlet().pt();
    JetPairBranch.BottomRap = std::abs(Quartet.Singlet().rap());
    JetPairBranch.BottomPhi = Quartet.Singlet().phi();
    JetPairBranch.BottomMass = Quartet.Singlet().m();
    JetPairBranch.BottomBdt = Quartet.Singlet().user_info<HJetInfo>().Bdt();
//     JetPairBranch.BottomBTag = Quartet.Singlet().user_info<HJetInfo>().BTag();

    JetPairBranch.TopPt = Quartet.Triplet().Jet().pt();
    JetPairBranch.TopRap = std::abs(Quartet.Triplet().Jet().rap());
    JetPairBranch.TopPhi = Quartet.Triplet().Jet().phi();
    JetPairBranch.TopMass = Quartet.Triplet().Jet().m();
    JetPairBranch.TopBdt = Quartet.Triplet().Bdt();
//     JetPairBranch.TopBTag = Quartet.Triplet().Jet().user_info<HJetInfo>().BTag();

    JetPairBranch.Bdt = Quartet.Bdt();
    JetPairBranch.Tag = Quartet.Tag();
    return JetPairBranch;
}

struct SortQuartetByDeltaRap {
    inline bool operator()(const hanalysis::HQuartet31 &Quartet1, const hanalysis::HQuartet31 &Quartet2) {
        return (Quartet1.DeltaRap() > Quartet2.DeltaRap());
    }
};

std::vector<HChargedJetPairBranch> hanalysis::HChargedJetPairTagger::GetBranches(hanalysis::HEvent &Event, const hanalysis::HObject::HTag Tag)
{
    Print(HInformation, "Get W Tags");
    JetTag.HeavyParticles = {GluonId};
    HJets Jets = GetJets(Event, JetTag);
    Jets = BottomTagger.GetJetBdt(Jets, BottomReader);

//     HJets Leptons = Event.GetLeptons()->GetTaggedJets(JetTag);
//     fastjet::PseudoJet MissingEt = Event.GetJets()->GetMissingEt();
//     std::vector<HDoublet> DoubletsSemi = WSemiTagger.GetBdt(Leptons, MissingEt, WSemiReader);
//     std::vector<HTriplet> Triplets = TopSemiTagger.GetBdt(DoubletsSemi, Jets, TopSemiReader);
//     Print(HDebug, "Number of Semi Tops", Triplets.size());
//     Triplets.insert(Triplets.end(), TripletsHadronic.begin(), TripletsHadronic.end());

    std::vector<HDoublet> Doublets = WTagger.GetBdt(Jets, WReader);
    std::vector<HTriplet> Triplets = TopHadronicTagger.GetBdt(Doublets, Jets, TopHadronicReader);
//     Print(HDebug, "Number of Hadronic Tops", TripletsHadronic.size());


    for (const auto & Jet : Jets) {
        HJets Pieces = WTagger.GetSubJets(Jet, 2);
        Pieces = BottomTagger.GetJetBdt(Pieces, BottomReader);
        std::vector<hanalysis::HDoublet> PieceDoublets = WTagger.GetBdt(Pieces, WReader);
        std::vector<hanalysis::HTriplet> PieceTriplets = TopHadronicTagger.GetBdt(PieceDoublets, Jets, TopHadronicReader);
        Triplets.insert(Triplets.end(), PieceTriplets.begin(), PieceTriplets.end());
    }

    for (const auto & Jet : Jets) {
        HJets Pieces = WTagger.GetSubJets(Jet, 3);
        Pieces = BottomTagger.GetJetBdt(Pieces, BottomReader);
        std::vector<hanalysis::HDoublet> PieceDoublets = WTagger.GetBdt(Pieces, WReader);
        std::vector<hanalysis::HTriplet> PieceTriplets = TopHadronicTagger.GetBdt(PieceDoublets, Jets, TopHadronicReader);
        Triplets.insert(Triplets.end(), PieceTriplets.begin(), PieceTriplets.end());
    }

    if (Triplets.size() > 3) {
      std::sort(Triplets.begin(), Triplets.end());
      Triplets.erase(Triplets.begin() + std::min(MaxCombi, int(Triplets.size())), Triplets.end());
    }

    HJets TopParticles = Event.GetParticles()->Generator();
    TopParticles.erase(std::remove_if(TopParticles.begin(), TopParticles.end(), WrongAbsFamily(TopId, GluonId)), TopParticles.end());
    if (TopParticles.size() != 1 && Tag == HSignal) Print(HError, "Where is the Top?", TopParticles.size());
    std::sort(Triplets.begin(), Triplets.end(), MinDeltaR(TopParticles.front()));
    if (Tag == HSignal && Triplets.size() > 1) Triplets.erase(Triplets.begin() + 1, Triplets.end());
    if (Tag == HBackground && Triplets.size() > 0) Triplets.erase(Triplets.begin());

    HJets BottomParticles = Event.GetParticles()->Generator();
    BottomParticles.erase(std::remove_if(BottomParticles.begin(), BottomParticles.end(), WrongAbsFamily(BottomId, GluonId)), BottomParticles.end());
    if (BottomParticles.size() != 1 && Tag == HSignal) Print(HError, "Where is the Bottom?", BottomParticles.size());
    std::sort(Jets.begin(), Jets.end(), MinDeltaR(BottomParticles.front()));
    if (Tag == HSignal && Triplets.size() > 1) Jets.erase(Jets.begin() + 1, Jets.end());
    if (Tag == HBackground && Jets.size() > 0) Jets.erase(Jets.begin());


    std::vector<HQuartet31> Quartets;
    for (const auto & Triplet : Triplets)
        for (const auto & Jet : Jets) {
            if (Triplet.Singlet() == Jet) continue;
            if (Triplet.Doublet().Singlet1() == Jet) continue;
            if (Triplet.Doublet().Singlet2() == Jet) continue;
            HQuartet31 Quartet(Triplet, Jet);
            if (Quartet.DeltaR() < 2) continue;
//             Quartet.SetTag(GetTag(Quartet));
//             if (Quartet.Tag() != Tag) continue;
            Quartets.push_back(Quartet);
        }

    Print(HDebug, "Number of Jet Pairs", Quartets.size());

    if (Tag == HSignal && Quartets.size() > 1) {
        std::sort(Quartets.begin(), Quartets.end(), SortQuartetByDeltaRap());
        if (Quartets.size() > 1)Quartets.erase(Quartets.begin() + 1, Quartets.end());
    }

    std::vector<HChargedJetPairBranch> JetPairBranches;
    for (const auto & Quartet : Quartets) JetPairBranches.push_back(GetBranch(Quartet));

    return JetPairBranches;

}

hanalysis::HObject::HTag hanalysis::HChargedJetPairTagger::GetTag(const HQuartet31 &Quartet)
{
    Print(HInformation, "Get Quartet Tag");


    HJetInfo JetInfoB = Quartet.Singlet().user_info<HJetInfo>();
    JetInfoB.ExtractFraction(BottomId);
    if (std::abs(JetInfoB.MaximalId()) != BottomId) return HBackground;

    HJetInfo JetInfoTopB = Quartet.Triplet().Singlet().user_info<HJetInfo>();
    JetInfoTopB.ExtractFraction(TopId);
    if (std::abs(JetInfoTopB.MaximalId()) != TopId) return HBackground;
//     if (sgn(JetInfoTopB.MaximalId()) != -sgn(JetInfoB.MaximalId())) return HBackground; // TODO reeable this check

    HJetInfo JetInfoTopW1 = Quartet.Triplet().Doublet().Singlet1().user_info<HJetInfo>();
    JetInfoTopW1.ExtractFraction(TopId);
    if (JetInfoTopB.MaximalId() != JetInfoTopW1.MaximalId()) return HBackground;

    if (Quartet.Triplet().Doublet().Singlet2().has_user_info<HJetInfo>()) {
        HJetInfo JetInfoTopW2 = Quartet.Triplet().Doublet().Singlet2().user_info<HJetInfo>();
        JetInfoTopW2.ExtractFraction(TopId);
        if (JetInfoTopB.MaximalId() != JetInfoTopW2.MaximalId()) return HBackground;
    }

    return HSignal;
}



std::vector<hanalysis::HQuartet31>  hanalysis::HChargedJetPairTagger::GetBdt(const std::vector<HTriplet> &Triplets, const HJets &Jets, const hanalysis::HReader &JetPairReader)
{
    std::vector<HQuartet31>  Quartets;
    for (const auto & Triplet : Triplets)
        for (const auto & Jet : Jets) {
            HQuartet31 Quartet(Triplet, Jet);
            if (std::abs(Quartet.DeltaRap()) < .5)continue;
            Branch = GetBranch(Quartet);
            Quartet.SetBdt(JetPairReader.Bdt());
            Quartets.push_back(Quartet);
        }
    std::sort(Quartets.begin(), Quartets.end());
    Quartets.erase(Quartets.begin() + std::min(MaxCombi, int(Quartets.size())), Quartets.end());
    return Quartets;
}

