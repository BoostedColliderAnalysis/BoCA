#include "TopSemiPairTagger.hh"
#include "Predicate.hh"
#include "Event.hh"
#include "Debug.hh"

namespace analysis
{

namespace higgscpv {

TopSemiPairTagger::TopSemiPairTagger()
{
    Note();
    DefineVariables();
}

int TopSemiPairTagger::Train(const Event &event, const Tag tag)
{
    Info("W Tags");
    std::vector<Triplet> triplets_hadronic = top_hadronic_reader_.Multiplets(event);
    std::vector<Triplet> triplets_semi = top_semi_reader_.Multiplets(event);

    Jets TopParticles = event.Partons().GenParticles();
    TopParticles = RemoveIfWrongAbsFamily(TopParticles, Id::top, Id::gluon);
    if (TopParticles.size() != 1 && tag == Tag::signal) Error("Where is the Top?", TopParticles.size());

    std::vector<Triplet> final_triplets_hadronic;
    switch(tag) {
    case Tag::signal :
        for (const auto & triplet : triplets_hadronic) if (triplet.Jet().delta_R(TopParticles.front()) < DetectorGeometry().JetConeSize()) final_triplets_hadronic.emplace_back(triplet);
        break;
    case Tag::background      :
        final_triplets_hadronic = triplets_hadronic;
        break;
    }

    std::vector<Triplet> final_triplets_semi;
    switch (tag) {
    case Tag::signal :
      for (const auto & triplet : triplets_semi) if (triplet.Jet().delta_R(TopParticles.front()) < DetectorGeometry().JetConeSize()) final_triplets_semi.emplace_back(triplet);
        break;
    case Tag::background :
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

    Debug("Number of Jet Pairs", sextets.size());
    if (tag == Tag::signal && sextets.size() > 1) {
        sextets = SortByMaxDeltaRap(sextets);
        if (sextets.size() > 1)sextets.erase(sextets.begin() + 1, sextets.end());
    }
    return SaveEntries(sextets);
}

std::vector< Sextet > TopSemiPairTagger::Multiplets(const Event& event, const TMVA::Reader& reader) const
{
    std::vector<Triplet> triplets_semi = top_semi_reader_.Multiplets(event);
    std::vector<Triplet> triplets_hadronic = top_hadronic_reader_.Multiplets(event);
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
