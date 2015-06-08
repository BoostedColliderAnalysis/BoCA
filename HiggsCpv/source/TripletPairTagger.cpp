# include "TripletPairTagger.hh"
# include "Predicate.hh"

higgscpv::TripletPairTagger::TripletPairTagger()
{
    Print(kNotification, "Constructor");
    set_tagger_name("TripletJetJetPair");
    top_semi_reader_.set_tagger(top_semi_tagger_);
    top_hadronic_reader_.set_tagger(top_hadronic_tagger);
    DefineVariables();
}

void higgscpv::TripletPairTagger::DefineVariables()
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

    AddVariable(branch_.Bdt, "Bdt");
    AddSpectator(branch_.Tag, "Tag");
}

int higgscpv::TripletPairTagger::Train(analysis::Event &event, const Tag tag)
{
    Print(kInformation, "W Tags");
    std::vector<analysis::Triplet> triplets_hadronic = top_hadronic_reader_.Multiplets<analysis::TopHadronicTagger>(event);
    std::vector<analysis::Triplet> triplets_semi = top_semi_reader_.Multiplets<analysis::TopSemiTagger>(event);

    analysis::Jets TopParticles = event.Partons().GenParticles();
    TopParticles = analysis::RemoveIfWrongAbsFamily(TopParticles, TopId, GluonId);
    if (TopParticles.size() != 1 && tag == kSignal) Print(kError, "Where is the Top?", TopParticles.size());

    std::vector<analysis::Triplet> final_triplets_hadronic;
    if (tag == kSignal) for (const auto & triplet : triplets_hadronic) if (triplet.Jet().delta_R(TopParticles.front()) < detector_geometry().JetConeSize) final_triplets_hadronic.emplace_back(triplet);
            else final_triplets_hadronic = triplets_hadronic;


    std::vector<analysis::Triplet> final_triplets_semi;
    if (tag == kSignal) for (const auto & triplet : triplets_semi) if (triplet.Jet().delta_R(TopParticles.front()) < detector_geometry().JetConeSize) final_triplets_semi.emplace_back(triplet);
            else final_triplets_semi = triplets_semi;

    std::vector<analysis::Sextet> sextets;
    for (const auto & triplet_hadronic : triplets_hadronic)
        for (const auto & triplet_semi : triplets_semi) {
            analysis::Sextet sextet(triplet_hadronic, triplet_semi);
            if(sextet.overlap()) continue;
            sextets.emplace_back(sextet);
        }

    Print(kDebug, "Number of Jet Pairs", sextets.size());
    if (tag == kSignal && sextets.size() > 1) {
        sextets = analysis::SortByMaxDeltaRap(sextets);
        if (sextets.size() > 1)sextets.erase(sextets.begin() + 1, sextets.end());
    }
    return SaveEntries<TripletPairBranch>(sextets);
}

std::vector< analysis::Sextet > higgscpv::TripletPairTagger::Multiplets(analysis::Event& event, const TMVA::Reader& reader)
{
    std::vector<analysis::Triplet> triplets_semi = top_semi_reader_.Multiplets<analysis::TopSemiTagger>(event);
    std::vector<analysis::Triplet> triplets_hadronic = top_hadronic_reader_.Multiplets<analysis::TopHadronicTagger>(event);
    std::vector<analysis::Sextet>  sextets;
    for (const auto & triplet_hadronic : triplets_hadronic)
        for (const auto & triplet_semi : triplets_semi)  {
            analysis::Sextet sextet(triplet_hadronic, triplet_semi);
            branch_ = branch<TripletPairBranch>(sextet);
            if(sextet.overlap()) continue;
            sextet.SetBdt(Bdt(reader));
            sextets.emplace_back(sextet);
        }
    return ReduceResult(sextets);
}
