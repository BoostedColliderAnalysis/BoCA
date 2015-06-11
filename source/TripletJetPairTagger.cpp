# include "TripletJetPairTagger.hh"
# include "Predicate.hh"

analysis::TripletJetPairTagger::TripletJetPairTagger()
{
    Print(kNotification, "Constructor");
    set_tagger_name("TripletJetJetPair");
    bottom_reader_.set_tagger(bottom_tagger_);
    top_hadronic_reader_.set_tagger(top_hadronic_tagger);
    DefineVariables();
}

void analysis::TripletJetPairTagger::DefineVariables()
{
    Print(kNotification , "Define Variables");
    AddVariable(branch_.Mass, "Mass");
    AddVariable(branch_.Pt, "Pt");
    AddVariable(branch_.Rap, "Rap");
    AddVariable(branch_.Phi, "Phi");
    AddVariable(branch_.Ht, "Ht");

    AddVariable(branch_.DeltaM, "DeltaM");
    AddVariable(branch_.DeltaPt, "DeltaPt");
    AddVariable(branch_.DeltaPhi, "DeltaPhi");
    AddVariable(branch_.DeltaRap, "DeltaRap");
    AddVariable(branch_.DeltaR, "DeltaR");

    AddVariable(branch_.BottomMass, "BottomMass");
    AddVariable(branch_.BottomPt, "BottomPt");
    AddVariable(branch_.BottomRap, "BottomRap");
    AddVariable(branch_.BottomPhi, "BottomPhi");
    AddVariable(branch_.BottomBdt, "BottomBdt");

    AddVariable(branch_.TopMass, "TopMass");
    AddVariable(branch_.TopPt, "TopPt");
    AddVariable(branch_.TopRap, "TopRap");
    AddVariable(branch_.TopPhi, "TopPhi");
    AddVariable(branch_.TopBdt, "TopBdt");

    AddVariable(branch_.Bdt1, "Bdt1");
    AddVariable(branch_.Bdt2, "Bdt2");
    AddSpectator(branch_.Tag, "Tag");
}

// struct SortquartetByDeltaRap {
//     inline bool operator()(const analysis::Quartet31 &quartet1, const analysis::Quartet31 &quartet2) {
//         return (quartet1.DeltaRap() > quartet2.DeltaRap());
//     }
// };

int analysis::TripletJetPairTagger::Train(analysis::Event &event, const Tag tag)
{
  Print(kInformation, "W Tags");
  Jets jets = bottom_reader_.Multiplets<BottomTagger>(event);
    std::vector<Triplet> triplets = top_hadronic_reader_.Multiplets<TopHadronicTagger>(event);
//     Jets jets = GetJets(event);
    //     jets = bottom_tagger_.GetJetBdt(jets, BottomReader); // TODO reenable this
//     std::vector<Doublet> doublets = WTagger.GetBdt(jets, WReader);
    //     std::vector<Triplet> triplets = top_hadronic_tagger.GetBdt(doublets, jets, TopHadronicReader);
//     std::vector<Triplet> triplets = top_hadronic_tagger.GetBdt(jets, top_hadronic_reader_, WTagger, WReader, bottom_tagger_, bottom_reader_);
    Print(kDebug, "Number of Hadronic Tops", triplets.size());

//     for (const auto & Jet : jets) {
//         Jets Pieces = WTagger.GetSubJets(Jet, 2);
//         Pieces = bottom_tagger_.GetJetBdt(Pieces, BottomReader); // TODO reenable this
//         std::vector<analysis::Doublet> Piecedoublets = WTagger.GetBdt(Pieces, WReader);
//         std::vector<analysis::Triplet> Piecetriplets = top_hadronic_tagger.GetBdt(Piecedoublets, jets, top_hadronic_reader_);
//         triplets.insert(triplets.end(), Piecetriplets.begin(), Piecetriplets.end());
//     }

//     for (const auto & Jet : jets) {
//         Jets Pieces = WTagger.GetSubJets(Jet, 3);
        //         Pieces = bottom_tagger_.GetJetBdt(Pieces, BottomReader); // TODO reenable this
//         std::vector<analysis::Doublet> Piecedoublets = WTagger.GetBdt(Pieces, WReader);
//         std::vector<analysis::Triplet> Piecetriplets = top_hadronic_tagger.GetBdt(Piecedoublets, jets, top_hadronic_reader_);
//         triplets.insert(triplets.end(), Piecetriplets.begin(), Piecetriplets.end());
//     }

//     if (triplets.size() > 3) {
//         std::sort(triplets.begin(), triplets.end());
//         triplets.erase(triplets.begin() + std::min(max_combi(), int(triplets.size())), triplets.end());
//     }
//     std::vector<Triplet> triplets = top_hadronic_tagger.GetBdt(jets, TopHadronicReader);

    Jets TopParticles = event.Partons().GenParticles();
    TopParticles = RemoveIfWrongAbsFamily(TopParticles, TopId, GluonId);
    if (TopParticles.size() != 1 && tag == kSignal) Print(kError, "Where is the Top?", TopParticles.size());

    std::vector<analysis::Triplet> Finaltriplets;
    if (tag == kSignal) for (const auto & triplet : triplets) if (triplet.Jet().delta_R(TopParticles.front()) < detector_geometry().JetConeSize) Finaltriplets.emplace_back(triplet);
            else Finaltriplets = triplets;

//     std::sort(triplets.begin(), triplets.end(), MinDeltaR(TopParticles.front()));
//     if (Tag == kSignal && triplets.size() > 1) triplets.erase(triplets.begin() + 1, triplets.end());
//     if (Tag == HBackground && triplets.size() > 0) triplets.erase(triplets.begin());

    Jets BottomParticles = event.Partons().GenParticles();
    BottomParticles = RemoveIfWrongAbsFamily(BottomParticles, BottomId, GluonId);
    if (BottomParticles.size() != 1 && tag == kSignal) Print(kError, "Where is the Bottom?", BottomParticles.size());

    Jets FinalJets;
    if (tag == kSignal) for (const auto & Jet : jets) if (Jet.delta_R(BottomParticles.front()) < detector_geometry().JetConeSize) FinalJets.emplace_back(Jet);
            else FinalJets = jets;

//     std::sort(jets.begin(), jets.end(), MinDeltaR(BottomParticles.front()));
//     if (Tag == kSignal && triplets.size() > 1) jets.erase(jets.begin() + 1, jets.end());
//     if (Tag == HBackground && jets.size() > 0) jets.erase(jets.begin());


    std::vector<Quartet31> quartets;
    for (const auto & triplet : triplets)
        for (const auto & Jet : jets) {
            Quartet31 quartet(triplet, Jet);
            if(quartet.Overlap()) continue;
//             if (quartet.DeltaR() < 2) continue;
//             quartet.SetTag(GetTag(quartet));
//             if (quartet.Tag() != Tag) continue;
            quartets.emplace_back(quartet);
        }

    Print(kDebug, "Number of Jet Pairs", quartets.size());

    if (tag == kSignal && quartets.size() > 1) {
      quartets = SortByMaxDeltaRap(quartets);
//         std::sort(quartets.begin(), quartets.end(), analysis::SortedByDeltaRap());
        if (quartets.size() > 1)quartets.erase(quartets.begin() + 1, quartets.end());
    }

    return SaveEntries(quartets);

//     std::vector<TripletJetPairBranch> JetPairBranches;
//     for (const auto & quartet : quartets) JetPairBranches.emplace_back(GetBranch(quartet));

//     return JetPairBranches;

}

std::vector<analysis::Quartet31>  analysis::TripletJetPairTagger::Multiplets(Event &event, const TMVA::Reader &reader)
{
  Jets jets = bottom_reader_.Multiplets<BottomTagger>(event);
  std::vector<Triplet> triplets = top_hadronic_reader_.Multiplets<TopHadronicTagger>(event);
    std::vector<Quartet31>  quartets;
    for (const auto & triplet : triplets)
        for (const auto & Jet : jets)  {
            Quartet31 quartet(triplet, Jet);
            if(quartet.Overlap()) continue;
            branch_ = branch(quartet);
            quartet.SetBdt(Bdt(reader));
            quartets.emplace_back(quartet);
        }
    std::sort(quartets.begin(), quartets.end());
    quartets.erase(quartets.begin() + std::min(max_combi(), int(quartets.size())), quartets.end());
    return quartets;
}

