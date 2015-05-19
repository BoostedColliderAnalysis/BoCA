# include "HChargedJetPairTagger.hh"

analysis::HChargedJetPairTagger::HChargedJetPairTagger()
{
    Print(kNotification, "Constructor");
    DefineVariables();
}

void analysis::HChargedJetPairTagger::SetTagger(const BottomTagger &NewBottomTagger, const WSemiTagger &Neww_semi_tagger, const WHadronicTagger &NewWTagger, const TopSemiTagger &Newtop_semi_tagger, const TopHadronicTagger &Newtop_hadronic_tagger)
{
    Print(kNotification, "Set Tagger", NewBottomTagger.tagger_name());

    bottom_tagger_ = NewBottomTagger;
    w_semi_tagger = Neww_semi_tagger;
    WTagger = NewWTagger;
    top_semi_tagger = Newtop_semi_tagger;
    top_hadronic_tagger = Newtop_hadronic_tagger;

//     top_hadronic_tagger.bottom_tagger_ = NewBottomTagger;
//     top_hadronic_tagger.WTagger = NewWTagger;
//     top_hadronic_tagger.BottomReader.set_tagger(bottom_tagger_);
//     top_hadronic_tagger.WReader.set_tagger(WTagger);

    DefineVariables();
}

void analysis::HChargedJetPairTagger::DefineVariables()
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

analysis::HChargedJetPairBranch analysis::HChargedJetPairTagger::GetBranch(const Quartet31 &quartet) const
{

    Print(kInformation, "FillPairTagger", quartet.Bdt());

    HChargedJetPairBranch JetPairBranch;

    JetPairBranch.Mass = quartet.Jet().m();
    JetPairBranch.Pt = quartet.Jet().pt();
    JetPairBranch.Rap = quartet.Jet().rap();
    JetPairBranch.Phi = quartet.Jet().phi();
    JetPairBranch.Ht = quartet.Ht();

    JetPairBranch.DeltaM = quartet.DeltaM();
    JetPairBranch.DeltaPt = quartet.DeltaPt();
    JetPairBranch.DeltaR = quartet.DeltaR();
    JetPairBranch.DeltaRap = quartet.DeltaRap();
    JetPairBranch.DeltaPhi = quartet.DeltaPhi();

    JetPairBranch.BottomPt = quartet.singlet().pt();
    JetPairBranch.BottomRap = std::abs(quartet.singlet().rap());
    JetPairBranch.BottomPhi = quartet.singlet().phi();
    JetPairBranch.BottomMass = quartet.singlet().m();
    JetPairBranch.BottomBdt = quartet.singlet().user_info<JetInfo>().Bdt();

    JetPairBranch.TopPt = quartet.triplet().Jet().pt();
    JetPairBranch.TopRap = std::abs(quartet.triplet().Jet().rap());
    JetPairBranch.TopPhi = quartet.triplet().Jet().phi();
    JetPairBranch.TopMass = quartet.triplet().Jet().m();
    JetPairBranch.TopBdt = quartet.triplet().Bdt();

    JetPairBranch.Bdt = quartet.Bdt();
    JetPairBranch.Tag = quartet.Tag();
    return JetPairBranch;
}

struct SortquartetByDeltaRap {
    inline bool operator()(const analysis::Quartet31 &quartet1, const analysis::Quartet31 &quartet2) {
        return (quartet1.DeltaRap() > quartet2.DeltaRap());
    }
};

std::vector<analysis::HChargedJetPairBranch> analysis::HChargedJetPairTagger::GetBranches(analysis::Event &event, const analysis::Object::Tag Tag)
{
    Print(kInformation, "Get W Tags");
    Jets jets = GetJets(event);
    //     jets = bottom_tagger_.GetJetBdt(jets, BottomReader); // TODO reenable this
//     std::vector<Doublet> doublets = WTagger.GetBdt(jets, WReader);
    //     std::vector<Triplet> triplets = top_hadronic_tagger.GetBdt(doublets, jets, TopHadronicReader);
    std::vector<Triplet> triplets = top_hadronic_tagger.GetBdt(jets, TopHadronicReader, WTagger, WReader, bottom_tagger_, BottomReader);
    Print(kDebug, "Number of Hadronic Tops", triplets.size());

    for (const auto & Jet : jets) {
        Jets Pieces = WTagger.GetSubJets(Jet, 2);
//         Pieces = bottom_tagger_.GetJetBdt(Pieces, BottomReader); // TODO reenable this
        std::vector<analysis::Doublet> Piecedoublets = WTagger.GetBdt(Pieces, WReader);
        std::vector<analysis::Triplet> Piecetriplets = top_hadronic_tagger.GetBdt(Piecedoublets, jets, TopHadronicReader);
        triplets.insert(triplets.end(), Piecetriplets.begin(), Piecetriplets.end());
    }

    for (const auto & Jet : jets) {
        Jets Pieces = WTagger.GetSubJets(Jet, 3);
        //         Pieces = bottom_tagger_.GetJetBdt(Pieces, BottomReader); // TODO reenable this
        std::vector<analysis::Doublet> Piecedoublets = WTagger.GetBdt(Pieces, WReader);
        std::vector<analysis::Triplet> Piecetriplets = top_hadronic_tagger.GetBdt(Piecedoublets, jets, TopHadronicReader);
        triplets.insert(triplets.end(), Piecetriplets.begin(), Piecetriplets.end());
    }

    if (triplets.size() > 3) {
        std::sort(triplets.begin(), triplets.end());
        triplets.erase(triplets.begin() + std::min(max_combi(), int(triplets.size())), triplets.end());
    }
//     std::vector<Triplet> triplets = top_hadronic_tagger.GetBdt(jets, TopHadronicReader);

    Jets TopParticles = event.partons().Generator();
    TopParticles = RemoveIfWrongAbsFamily(TopParticles, TopId, GluonId);
    if (TopParticles.size() != 1 && Tag == kSignal) Print(kError, "Where is the Top?", TopParticles.size());

    std::vector<analysis::Triplet> Finaltriplets;
    if (Tag == kSignal) for (const auto & triplet : triplets) if (triplet.Jet().delta_R(TopParticles.front()) < detector_geometry().JetConeSize) Finaltriplets.emplace_back(triplet);
            else Finaltriplets = triplets;

//     std::sort(triplets.begin(), triplets.end(), MinDeltaR(TopParticles.front()));
//     if (Tag == kSignal && triplets.size() > 1) triplets.erase(triplets.begin() + 1, triplets.end());
//     if (Tag == HBackground && triplets.size() > 0) triplets.erase(triplets.begin());

    Jets BottomParticles = event.partons().Generator();
    BottomParticles = RemoveIfWrongAbsFamily(BottomParticles, BottomId, GluonId);
    if (BottomParticles.size() != 1 && Tag == kSignal) Print(kError, "Where is the Bottom?", BottomParticles.size());

    Jets FinalJets;
    if (Tag == kSignal) for (const auto & Jet : jets) if (Jet.delta_R(BottomParticles.front()) < detector_geometry().JetConeSize) FinalJets.emplace_back(Jet);
            else FinalJets = jets;

//     std::sort(jets.begin(), jets.end(), MinDeltaR(BottomParticles.front()));
//     if (Tag == kSignal && triplets.size() > 1) jets.erase(jets.begin() + 1, jets.end());
//     if (Tag == HBackground && jets.size() > 0) jets.erase(jets.begin());


    std::vector<Quartet31> quartets;
    for (const auto & triplet : triplets)
        for (const auto & Jet : jets) {
            if (triplet.singlet().delta_R(Jet) < detector_geometry().JetConeSize) continue;
            if (triplet.doublet().Singlet1().delta_R(Jet) < detector_geometry().JetConeSize) continue;
            if (triplet.doublet().Singlet2().delta_R(Jet) < detector_geometry().JetConeSize) continue;
            Quartet31 quartet(triplet, Jet);
//             if (quartet.DeltaR() < 2) continue;
//             quartet.SetTag(GetTag(quartet));
//             if (quartet.Tag() != Tag) continue;
            quartets.emplace_back(quartet);
        }

    Print(kDebug, "Number of Jet Pairs", quartets.size());

    if (Tag == kSignal && quartets.size() > 1) {
        std::sort(quartets.begin(), quartets.end(), SortquartetByDeltaRap());
        if (quartets.size() > 1)quartets.erase(quartets.begin() + 1, quartets.end());
    }

    std::vector<HChargedJetPairBranch> JetPairBranches;
    for (const auto & quartet : quartets) JetPairBranches.emplace_back(GetBranch(quartet));

    return JetPairBranches;

}

analysis::Object::Tag analysis::HChargedJetPairTagger::GetTag(const Quartet31 &)
{
    Print(kInformation, "Get quartet Tag");

    return kSignal;
}



std::vector<analysis::Quartet31>  analysis::HChargedJetPairTagger::GetBdt(const std::vector<Triplet> &triplets, const Jets &jets, const analysis::Reader &JetPairReader)
{
    std::vector<Quartet31>  quartets;
    for (const auto & triplet : triplets)
        for (const auto & Jet : jets)  {
            if (triplet.singlet().delta_R(Jet) < detector_geometry().JetConeSize) continue;
            if (triplet.doublet().Singlet1().delta_R(Jet) < detector_geometry().JetConeSize) continue;
            if (triplet.doublet().Singlet2().delta_R(Jet) < detector_geometry().JetConeSize) continue;
            Quartet31 quartet(triplet, Jet);
            Branch = GetBranch(quartet);
            quartet.SetBdt(JetPairReader.Bdt());
            quartets.emplace_back(quartet);
        }
    std::sort(quartets.begin(), quartets.end());
    quartets.erase(quartets.begin() + std::min(max_combi(), int(quartets.size())), quartets.end());
    return quartets;
}

