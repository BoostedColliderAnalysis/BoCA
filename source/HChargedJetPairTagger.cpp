# include "HChargedJetPairTagger.hh"

hanalysis::HChargedJetPairTagger::HChargedJetPairTagger()
{
    Print(kNotification, "Constructor");
    DefineVariables();
}

void hanalysis::HChargedJetPairTagger::SetTagger(const BottomTagger &NewBottomTagger, const HWSemiTagger &NewWSemiTagger, const HWHadronicTagger &NewWTagger, const HTopSemiTagger &NewTopSemiTagger, const HTopHadronicTagger &NewTopHadronicTagger)
{
    Print(kNotification, "Set Tagger", NewBottomTagger.tagger_name());

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

    Print(kNotification , "Define Variables");
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

    Print(kNotification, "Variables defined");

}

HChargedJetPairBranch hanalysis::HChargedJetPairTagger::GetBranch(const HQuartet31 &Quartet) const
{

    Print(kInformation, "FillPairTagger", Quartet.Bdt());

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

    JetPairBranch.BottomPt = Quartet.singlet().pt();
    JetPairBranch.BottomRap = std::abs(Quartet.singlet().rap());
    JetPairBranch.BottomPhi = Quartet.singlet().phi();
    JetPairBranch.BottomMass = Quartet.singlet().m();
    JetPairBranch.BottomBdt = Quartet.singlet().user_info<JetInfo>().Bdt();

    JetPairBranch.TopPt = Quartet.triplet().Jet().pt();
    JetPairBranch.TopRap = std::abs(Quartet.triplet().Jet().rap());
    JetPairBranch.TopPhi = Quartet.triplet().Jet().phi();
    JetPairBranch.TopMass = Quartet.triplet().Jet().m();
    JetPairBranch.TopBdt = Quartet.triplet().Bdt();

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
    Print(kInformation, "Get W Tags");
    Jets jets = GetJets(Event);
    //     jets = bottom_tagger_.GetJetBdt(jets, BottomReader); // TODO reenable this
//     std::vector<Doublet> doublets = WTagger.GetBdt(jets, WReader);
    //     std::vector<Triplet> triplets = TopHadronicTagger.GetBdt(doublets, jets, TopHadronicReader);
    std::vector<Triplet> triplets = TopHadronicTagger.GetBdt(jets, TopHadronicReader, WTagger, WReader, bottom_tagger_, BottomReader);
    Print(kDebug, "Number of Hadronic Tops", triplets.size());

    for (const auto & Jet : jets) {
        Jets Pieces = WTagger.GetSubJets(Jet, 2);
//         Pieces = bottom_tagger_.GetJetBdt(Pieces, BottomReader); // TODO reenable this
        std::vector<hanalysis::Doublet> Piecedoublets = WTagger.GetBdt(Pieces, WReader);
        std::vector<hanalysis::Triplet> Piecetriplets = TopHadronicTagger.GetBdt(Piecedoublets, jets, TopHadronicReader);
        triplets.insert(triplets.end(), Piecetriplets.begin(), Piecetriplets.end());
    }

    for (const auto & Jet : jets) {
        Jets Pieces = WTagger.GetSubJets(Jet, 3);
        //         Pieces = bottom_tagger_.GetJetBdt(Pieces, BottomReader); // TODO reenable this
        std::vector<hanalysis::Doublet> Piecedoublets = WTagger.GetBdt(Pieces, WReader);
        std::vector<hanalysis::Triplet> Piecetriplets = TopHadronicTagger.GetBdt(Piecedoublets, jets, TopHadronicReader);
        triplets.insert(triplets.end(), Piecetriplets.begin(), Piecetriplets.end());
    }

    if (triplets.size() > 3) {
        std::sort(triplets.begin(), triplets.end());
        triplets.erase(triplets.begin() + std::min(max_combi(), int(triplets.size())), triplets.end());
    }
//     std::vector<Triplet> triplets = TopHadronicTagger.GetBdt(jets, TopHadronicReader);

    Jets TopParticles = Event.GetParticles()->Generator();
    TopParticles = RemoveIfWrongAbsFamily(TopParticles, TopId, GluonId);
    if (TopParticles.size() != 1 && Tag == kSignal) Print(kError, "Where is the Top?", TopParticles.size());

    std::vector<hanalysis::Triplet> Finaltriplets;
    if (Tag == kSignal) for (const auto & triplet : triplets) if (triplet.Jet().delta_R(TopParticles.front()) < detector_geometry().JetConeSize) Finaltriplets.emplace_back(triplet);
            else Finaltriplets = triplets;

//     std::sort(triplets.begin(), triplets.end(), MinDeltaR(TopParticles.front()));
//     if (Tag == kSignal && triplets.size() > 1) triplets.erase(triplets.begin() + 1, triplets.end());
//     if (Tag == HBackground && triplets.size() > 0) triplets.erase(triplets.begin());

    Jets BottomParticles = Event.GetParticles()->Generator();
    BottomParticles = RemoveIfWrongAbsFamily(BottomParticles, BottomId, GluonId);
    if (BottomParticles.size() != 1 && Tag == kSignal) Print(kError, "Where is the Bottom?", BottomParticles.size());

    Jets FinalJets;
    if (Tag == kSignal) for (const auto & Jet : jets) if (Jet.delta_R(BottomParticles.front()) < detector_geometry().JetConeSize) FinalJets.emplace_back(Jet);
            else FinalJets = jets;

//     std::sort(jets.begin(), jets.end(), MinDeltaR(BottomParticles.front()));
//     if (Tag == kSignal && triplets.size() > 1) jets.erase(jets.begin() + 1, jets.end());
//     if (Tag == HBackground && jets.size() > 0) jets.erase(jets.begin());


    std::vector<HQuartet31> Quartets;
    for (const auto & triplet : triplets)
        for (const auto & Jet : jets) {
            if (triplet.singlet().delta_R(Jet) < detector_geometry().JetConeSize) continue;
            if (triplet.doublet().Singlet1().delta_R(Jet) < detector_geometry().JetConeSize) continue;
            if (triplet.doublet().Singlet2().delta_R(Jet) < detector_geometry().JetConeSize) continue;
            HQuartet31 Quartet(triplet, Jet);
//             if (Quartet.DeltaR() < 2) continue;
//             Quartet.SetTag(GetTag(Quartet));
//             if (Quartet.Tag() != Tag) continue;
            Quartets.emplace_back(Quartet);
        }

    Print(kDebug, "Number of Jet Pairs", Quartets.size());

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
    Print(kInformation, "Get Quartet Tag");

    return kSignal;
}



std::vector<hanalysis::HQuartet31>  hanalysis::HChargedJetPairTagger::GetBdt(const std::vector<Triplet> &triplets, const Jets &jets, const hanalysis::Reader &JetPairReader)
{
    std::vector<HQuartet31>  Quartets;
    for (const auto & triplet : triplets)
        for (const auto & Jet : jets)  {
            if (triplet.singlet().delta_R(Jet) < detector_geometry().JetConeSize) continue;
            if (triplet.doublet().Singlet1().delta_R(Jet) < detector_geometry().JetConeSize) continue;
            if (triplet.doublet().Singlet2().delta_R(Jet) < detector_geometry().JetConeSize) continue;
            HQuartet31 Quartet(triplet, Jet);
            Branch = GetBranch(Quartet);
            Quartet.SetBdt(JetPairReader.Bdt());
            Quartets.emplace_back(Quartet);
        }
    std::sort(Quartets.begin(), Quartets.end());
    Quartets.erase(Quartets.begin() + std::min(max_combi(), int(Quartets.size())), Quartets.end());
    return Quartets;
}

