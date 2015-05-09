# include "HChargedJetPairTagger.hh"

hanalysis::HChargedJetPairTagger::HChargedJetPairTagger()
{
    Print(HNotification, "Constructor");
    DefineVariables();
}

void hanalysis::HChargedJetPairTagger::SetTagger(const BottomTagger &NewBottomTagger, const HWSemiTagger &NewWSemiTagger, const HWHadronicTagger &NewWTagger, const HTopSemiTagger &NewTopSemiTagger, const HTopHadronicTagger &NewTopHadronicTagger)
{
    Print(HNotification, "Set Tagger", NewBottomTagger.tagger_name());

    bottom_tagger_ = NewBottomTagger;
    WSemiTagger = NewWSemiTagger;
    WTagger = NewWTagger;
    TopSemiTagger = NewTopSemiTagger;
    TopHadronicTagger = NewTopHadronicTagger;

//     TopHadronicTagger.bottom_tagger_ = NewBottomTagger;
//     TopHadronicTagger.WTagger = NewWTagger;
//     TopHadronicTagger.BottomReader.set_tagger(bottom_tagger_);
//     TopHadronicTagger.WReader.set_tagger(WTagger);

    DefineVariables();
}

void hanalysis::HChargedJetPairTagger::DefineVariables()
{

    Print(HNotification , "Define Variables");
    set_tagger_name("ChargedJetPair");

    ClearVectors();


    AddVariable(Branch.Mass, "Mass");
    AddVariable(Branch.Pt, "Pt");
    AddVariable(Branch.Rap, "Rap");
    AddVariable(Branch.Phi, "Phi");
    AddVariable(Branch.Ht, "Ht");

    AddVariable(Branch.DeltaM, "DeltaM");
    AddVariable(Branch.DeltaPt, "DeltaPt");
    AddVariable(Branch.DeltaPhi, "DeltaPhi");
    AddVariable(Branch.DeltaRap, "DeltaRap");
    AddVariable(Branch.DeltaR, "DeltaR");

    AddVariable(Branch.BottomMass, "BottomMass");
    AddVariable(Branch.BottomPt, "BottomPt");
    AddVariable(Branch.BottomRap, "BottomRap");
    AddVariable(Branch.BottomPhi, "BottomPhi");
    AddVariable(Branch.BottomBdt, "BottomBdt");

    AddVariable(Branch.TopMass, "TopMass");
    AddVariable(Branch.TopPt, "TopPt");
    AddVariable(Branch.TopRap, "TopRap");
    AddVariable(Branch.TopPhi, "TopPhi");
    AddVariable(Branch.TopBdt, "TopBdt");

    AddVariable(Branch.Bdt, "Bdt");
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
    Jets jets = GetJets(Event);
    //     jets = bottom_tagger_.GetJetBdt(jets, BottomReader); // TODO reenable this
//     std::vector<HDoublet> Doublets = WTagger.GetBdt(jets, WReader);
    //     std::vector<HTriplet> Triplets = TopHadronicTagger.GetBdt(Doublets, jets, TopHadronicReader);
    std::vector<HTriplet> Triplets = TopHadronicTagger.GetBdt(jets, TopHadronicReader, WTagger, WReader, bottom_tagger_, BottomReader);
    Print(HDebug, "Number of Hadronic Tops", Triplets.size());

    for (const auto & Jet : jets) {
        Jets Pieces = WTagger.GetSubJets(Jet, 2);
//         Pieces = bottom_tagger_.GetJetBdt(Pieces, BottomReader); // TODO reenable this
        std::vector<hanalysis::HDoublet> PieceDoublets = WTagger.GetBdt(Pieces, WReader);
        std::vector<hanalysis::HTriplet> PieceTriplets = TopHadronicTagger.GetBdt(PieceDoublets, jets, TopHadronicReader);
        Triplets.insert(Triplets.end(), PieceTriplets.begin(), PieceTriplets.end());
    }

    for (const auto & Jet : jets) {
        Jets Pieces = WTagger.GetSubJets(Jet, 3);
        //         Pieces = bottom_tagger_.GetJetBdt(Pieces, BottomReader); // TODO reenable this
        std::vector<hanalysis::HDoublet> PieceDoublets = WTagger.GetBdt(Pieces, WReader);
        std::vector<hanalysis::HTriplet> PieceTriplets = TopHadronicTagger.GetBdt(PieceDoublets, jets, TopHadronicReader);
        Triplets.insert(Triplets.end(), PieceTriplets.begin(), PieceTriplets.end());
    }

    if (Triplets.size() > 3) {
        std::sort(Triplets.begin(), Triplets.end());
        Triplets.erase(Triplets.begin() + std::min(max_combi(), int(Triplets.size())), Triplets.end());
    }
//     std::vector<HTriplet> Triplets = TopHadronicTagger.GetBdt(jets, TopHadronicReader);

    Jets TopParticles = Event.GetParticles()->Generator();
    TopParticles = RemoveIfWrongAbsFamily(TopParticles, TopId, GluonId);
    if (TopParticles.size() != 1 && Tag == kSignal) Print(HError, "Where is the Top?", TopParticles.size());

    std::vector<hanalysis::HTriplet> FinalTriplets;
    if (Tag == kSignal) for (const auto & Triplet : Triplets) if (Triplet.Jet().delta_R(TopParticles.front()) < detector_geometry().JetConeSize) FinalTriplets.emplace_back(Triplet);
            else FinalTriplets = Triplets;

//     std::sort(Triplets.begin(), Triplets.end(), MinDeltaR(TopParticles.front()));
//     if (Tag == kSignal && Triplets.size() > 1) Triplets.erase(Triplets.begin() + 1, Triplets.end());
//     if (Tag == HBackground && Triplets.size() > 0) Triplets.erase(Triplets.begin());

    Jets BottomParticles = Event.GetParticles()->Generator();
    BottomParticles = RemoveIfWrongAbsFamily(BottomParticles, BottomId, GluonId);
    if (BottomParticles.size() != 1 && Tag == kSignal) Print(HError, "Where is the Bottom?", BottomParticles.size());

    Jets FinalJets;
    if (Tag == kSignal) for (const auto & Jet : jets) if (Jet.delta_R(BottomParticles.front()) < detector_geometry().JetConeSize) FinalJets.emplace_back(Jet);
            else FinalJets = jets;

//     std::sort(jets.begin(), jets.end(), MinDeltaR(BottomParticles.front()));
//     if (Tag == kSignal && Triplets.size() > 1) jets.erase(jets.begin() + 1, jets.end());
//     if (Tag == HBackground && jets.size() > 0) jets.erase(jets.begin());


    std::vector<HQuartet31> Quartets;
    for (const auto & Triplet : Triplets)
        for (const auto & Jet : jets) {
            if (Triplet.Singlet().delta_R(Jet) < detector_geometry().JetConeSize) continue;
            if (Triplet.Doublet().Singlet1().delta_R(Jet) < detector_geometry().JetConeSize) continue;
            if (Triplet.Doublet().Singlet2().delta_R(Jet) < detector_geometry().JetConeSize) continue;
            HQuartet31 Quartet(Triplet, Jet);
//             if (Quartet.DeltaR() < 2) continue;
//             Quartet.SetTag(GetTag(Quartet));
//             if (Quartet.Tag() != Tag) continue;
            Quartets.emplace_back(Quartet);
        }

    Print(HDebug, "Number of Jet Pairs", Quartets.size());

    if (Tag == kSignal && Quartets.size() > 1) {
        std::sort(Quartets.begin(), Quartets.end(), SortQuartetByDeltaRap());
        if (Quartets.size() > 1)Quartets.erase(Quartets.begin() + 1, Quartets.end());
    }

    std::vector<HChargedJetPairBranch> JetPairBranches;
    for (const auto & Quartet : Quartets) JetPairBranches.emplace_back(GetBranch(Quartet));

    return JetPairBranches;

}

hanalysis::HObject::Tag hanalysis::HChargedJetPairTagger::GetTag(const HQuartet31 &)
{
    Print(HInformation, "Get Quartet Tag");

    return kSignal;
}



std::vector<hanalysis::HQuartet31>  hanalysis::HChargedJetPairTagger::GetBdt(const std::vector<HTriplet> &Triplets, const Jets &jets, const hanalysis::Reader &JetPairReader)
{
    std::vector<HQuartet31>  Quartets;
    for (const auto & Triplet : Triplets)
        for (const auto & Jet : jets)  {
            if (Triplet.Singlet().delta_R(Jet) < detector_geometry().JetConeSize) continue;
            if (Triplet.Doublet().Singlet1().delta_R(Jet) < detector_geometry().JetConeSize) continue;
            if (Triplet.Doublet().Singlet2().delta_R(Jet) < detector_geometry().JetConeSize) continue;
            HQuartet31 Quartet(Triplet, Jet);
            Branch = GetBranch(Quartet);
            Quartet.SetBdt(JetPairReader.Bdt());
            Quartets.emplace_back(Quartet);
        }
    std::sort(Quartets.begin(), Quartets.end());
    Quartets.erase(Quartets.begin() + std::min(max_combi(), int(Quartets.size())), Quartets.end());
    return Quartets;
}

