# include "TopSemiPairTagger.hh"
# include "Predicate.hh"

namespace analysis
{

namespace higgscpv {

TopSemiPairTagger::TopSemiPairTagger()
{
    Print(kNotification, "Constructor");
    set_tagger_name("TripletJetJetPair");
    top_semi_reader_.set_tagger(top_semi_tagger_);
    top_hadronic_reader_.set_tagger(top_hadronic_tagger);
    DefineVariables();
}

int TopSemiPairTagger::Train(Event &event, const Tag tag)
{
    Print(kInformation, "W Tags");
    std::vector<Triplet> triplets_hadronic = top_hadronic_reader_.Multiplets<TopHadronicTagger>(event);
    std::vector<Triplet> triplets_semi = top_semi_reader_.Multiplets<TopSemiTagger>(event);

    Jets TopParticles = event.Partons().GenParticles();
    TopParticles = RemoveIfWrongAbsFamily(TopParticles, TopId, GluonId);
    if (TopParticles.size() != 1 && tag == kSignal) Print(kError, "Where is the Top?", TopParticles.size());

    std::vector<Triplet> final_triplets_hadronic;
    switch(tag) {
    case kSignal :
        for (const auto & triplet : triplets_hadronic) if (triplet.Jet().delta_R(TopParticles.front()) < detector_geometry().JetConeSize) final_triplets_hadronic.emplace_back(triplet);
        break;
    case kBackground      :
        final_triplets_hadronic = triplets_hadronic;
        break;
    }

    std::vector<Triplet> final_triplets_semi;
    switch (tag) {
    case kSignal :
        for (const auto & triplet : triplets_semi) if (triplet.Jet().delta_R(TopParticles.front()) < detector_geometry().JetConeSize) final_triplets_semi.emplace_back(triplet);
        break;
    case kBackground :
        final_triplets_semi = triplets_semi;
        break;
    }

    std::vector<Sextet> sextets;
    for (const auto & triplet_hadronic : triplets_hadronic)
        for (const auto & triplet_semi : triplets_semi) {
            Sextet sextet(triplet_hadronic, triplet_semi);
            if(sextet.Overlap()) continue;
            sextets.emplace_back(sextet);
        }

    Print(kDebug, "Number of Jet Pairs", sextets.size());
    if (tag == kSignal && sextets.size() > 1) {
        sextets = SortByMaxDeltaRap(sextets);
        if (sextets.size() > 1)sextets.erase(sextets.begin() + 1, sextets.end());
    }
    return SaveEntries(sextets);
}

std::vector< Sextet > TopSemiPairTagger::Multiplets(Event& event, const TMVA::Reader& reader)
{
    std::vector<Triplet> triplets_semi = top_semi_reader_.Multiplets<TopSemiTagger>(event);
    std::vector<Triplet> triplets_hadronic = top_hadronic_reader_.Multiplets<TopHadronicTagger>(event);
    std::vector<Sextet>  sextets;
    for (const auto & triplet_hadronic : triplets_hadronic)
        for (const auto & triplet_semi : triplets_semi)  {
            Sextet sextet(triplet_hadronic, triplet_semi);
            if(sextet.Overlap()) continue;
            sextet.SetBdt(Bdt(sextet,reader));
            sextets.emplace_back(sextet);
        }
    return ReduceResult(sextets);
}

}

}
