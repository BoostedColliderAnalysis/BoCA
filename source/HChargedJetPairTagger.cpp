# include "HChargedJetPairTagger.hh"

hanalysis::HChargedJetPairTagger::HChargedJetPairTagger()
{
    Print(HNotification, "Constructor");
    DefineVariables();
}

void hanalysis::HChargedJetPairTagger::SetTagger(const HBottomTagger &NewBottomTagger, const HWSemiTagger &NewWSemiTagger, const HWTagger &NewWTagger, const HTopSemiTagger &NewTopSemiTagger, const HTopHadronicTagger &NewTopHadronicTagger)
{
    Print(HNotification, "Set Tagger", NewBottomTagger.tagger_name());

    BottomTagger = NewBottomTagger;
    WSemiTagger = NewWSemiTagger;
    WTagger = NewWTagger;
    TopSemiTagger = NewTopSemiTagger;
    TopHadronicTagger = NewTopHadronicTagger;

//     TopHadronicTagger.BottomTagger = NewBottomTagger;
//     TopHadronicTagger.WTagger = NewWTagger;
//     TopHadronicTagger.BottomReader.SetMva(BottomTagger);
//     TopHadronicTagger.WReader.SetMva(WTagger);

    DefineVariables();
}

void hanalysis::HChargedJetPairTagger::DefineVariables()
{

    Print(HNotification , "Define Variables");
    SetTaggerName("ChargedJetPair");

    ClearVectors();


    AddObservable(Branch.Mass, "Mass");
    AddObservable(Branch.Pt, "Pt");
    AddObservable(Branch.Rap, "Rap");
    AddObservable(Branch.Phi, "Phi");
    AddObservable(Branch.Ht, "Ht");

    AddObservable(Branch.DeltaM, "DeltaM");
    AddObservable(Branch.DeltaPt, "DeltaPt");
    AddObservable(Branch.DeltaPhi, "DeltaPhi");
    AddObservable(Branch.DeltaRap, "DeltaRap");
    AddObservable(Branch.DeltaR, "DeltaR");

    AddObservable(Branch.BottomMass, "BottomMass");
    AddObservable(Branch.BottomPt, "BottomPt");
    AddObservable(Branch.BottomRap, "BottomRap");
    AddObservable(Branch.BottomPhi, "BottomPhi");
    AddObservable(Branch.BottomBdt, "BottomBdt");

    AddObservable(Branch.TopMass, "TopMass");
    AddObservable(Branch.TopPt, "TopPt");
    AddObservable(Branch.TopRap, "TopRap");
    AddObservable(Branch.TopPhi, "TopPhi");
    AddObservable(Branch.TopBdt, "TopBdt");

    AddObservable(Branch.Bdt, "Bdt");
    AddSpectator(Branch.Tag, "Tag");

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

    JetPairBranch.TopPt = Quartet.Triplet().Jet().pt();
    JetPairBranch.TopRap = std::abs(Quartet.Triplet().Jet().rap());
    JetPairBranch.TopPhi = Quartet.Triplet().Jet().phi();
    JetPairBranch.TopMass = Quartet.Triplet().Jet().m();
    JetPairBranch.TopBdt = Quartet.Triplet().Bdt();

    JetPairBranch.Bdt = Quartet.Bdt();
    JetPairBranch.Tag = Quartet.Tag();
    return JetPairBranch;
}

struct SortQuartetByDeltaRap {
    inline bool operator()(const hanalysis::HQuartet31 &Quartet1, const hanalysis::HQuartet31 &Quartet2) {
        return (Quartet1.DeltaRap() > Quartet2.DeltaRap());
    }
};

std::vector<HChargedJetPairBranch> hanalysis::HChargedJetPairTagger::GetBranches(hanalysis::HEvent &Event, const hanalysis::HObject::Tag Tag)
{
    Print(HInformation, "Get W Tags");
    HJets Jets = GetJets(Event);
    Jets = BottomTagger.GetJetBdt(Jets, BottomReader);
//     std::vector<HDoublet> Doublets = WTagger.GetBdt(Jets, WReader);
    //     std::vector<HTriplet> Triplets = TopHadronicTagger.GetBdt(Doublets, Jets, TopHadronicReader);
    std::vector<HTriplet> Triplets = TopHadronicTagger.GetBdt(Jets, TopHadronicReader, WTagger, WReader, BottomTagger, BottomReader);
    Print(HDebug, "Number of Hadronic Tops", Triplets.size());

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
        Triplets.erase(Triplets.begin() + std::min(max_combi(), int(Triplets.size())), Triplets.end());
    }
//     std::vector<HTriplet> Triplets = TopHadronicTagger.GetBdt(Jets, TopHadronicReader);

    HJets TopParticles = Event.GetParticles()->Generator();
    TopParticles = RemoveIfWrongAbsFamily(TopParticles, TopId, GluonId);
    if (TopParticles.size() != 1 && Tag == kSignal) Print(HError, "Where is the Top?", TopParticles.size());

    std::vector<hanalysis::HTriplet> FinalTriplets;
    if (Tag == kSignal) for (const auto & Triplet : Triplets) if (Triplet.Jet().delta_R(TopParticles.front()) < DetectorGeometry.JetConeSize) FinalTriplets.push_back(Triplet);
            else FinalTriplets = Triplets;

//     std::sort(Triplets.begin(), Triplets.end(), MinDeltaR(TopParticles.front()));
//     if (Tag == HSignal && Triplets.size() > 1) Triplets.erase(Triplets.begin() + 1, Triplets.end());
//     if (Tag == HBackground && Triplets.size() > 0) Triplets.erase(Triplets.begin());

    HJets BottomParticles = Event.GetParticles()->Generator();
    BottomParticles = RemoveIfWrongAbsFamily(BottomParticles, BottomId, GluonId);
    if (BottomParticles.size() != 1 && Tag == kSignal) Print(HError, "Where is the Bottom?", BottomParticles.size());

    HJets FinalJets;
    if (Tag == kSignal) for (const auto & Jet : Jets) if (Jet.delta_R(BottomParticles.front()) < DetectorGeometry.JetConeSize) FinalJets.push_back(Jet);
            else FinalJets = Jets;

//     std::sort(Jets.begin(), Jets.end(), MinDeltaR(BottomParticles.front()));
//     if (Tag == HSignal && Triplets.size() > 1) Jets.erase(Jets.begin() + 1, Jets.end());
//     if (Tag == HBackground && Jets.size() > 0) Jets.erase(Jets.begin());


    std::vector<HQuartet31> Quartets;
    for (const auto & Triplet : Triplets)
        for (const auto & Jet : Jets) {
            if (Triplet.Singlet().delta_R(Jet) < DetectorGeometry.JetConeSize) continue;
            if (Triplet.Doublet().Singlet1().delta_R(Jet) < DetectorGeometry.JetConeSize) continue;
            if (Triplet.Doublet().Singlet2().delta_R(Jet) < DetectorGeometry.JetConeSize) continue;
            HQuartet31 Quartet(Triplet, Jet);
//             if (Quartet.DeltaR() < 2) continue;
//             Quartet.SetTag(GetTag(Quartet));
//             if (Quartet.Tag() != Tag) continue;
            Quartets.push_back(Quartet);
        }

    Print(HDebug, "Number of Jet Pairs", Quartets.size());

    if (Tag == kSignal && Quartets.size() > 1) {
        std::sort(Quartets.begin(), Quartets.end(), SortQuartetByDeltaRap());
        if (Quartets.size() > 1)Quartets.erase(Quartets.begin() + 1, Quartets.end());
    }

    std::vector<HChargedJetPairBranch> JetPairBranches;
    for (const auto & Quartet : Quartets) JetPairBranches.push_back(GetBranch(Quartet));

    return JetPairBranches;

}

hanalysis::HObject::Tag hanalysis::HChargedJetPairTagger::GetTag(const HQuartet31 &)
{
    Print(HInformation, "Get Quartet Tag");

    return kSignal;
}



std::vector<hanalysis::HQuartet31>  hanalysis::HChargedJetPairTagger::GetBdt(const std::vector<HTriplet> &Triplets, const HJets &Jets, const hanalysis::HReader &JetPairReader)
{
    std::vector<HQuartet31>  Quartets;
    for (const auto & Triplet : Triplets)
        for (const auto & Jet : Jets) {
            if (Triplet.Singlet().delta_R(Jet) < DetectorGeometry.JetConeSize) continue;
            if (Triplet.Doublet().Singlet1().delta_R(Jet) < DetectorGeometry.JetConeSize) continue;
            if (Triplet.Doublet().Singlet2().delta_R(Jet) < DetectorGeometry.JetConeSize) continue;
            HQuartet31 Quartet(Triplet, Jet);
            Branch = GetBranch(Quartet);
            Quartet.SetBdt(JetPairReader.Bdt());
            Quartets.push_back(Quartet);
        }
    std::sort(Quartets.begin(), Quartets.end());
    Quartets.erase(Quartets.begin() + std::min(max_combi(), int(Quartets.size())), Quartets.end());
    return Quartets;
}

