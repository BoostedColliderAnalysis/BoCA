#include "NewPartnerLeptonicTagger.hh"
#include "Particles.hh"
#include "Exception.hh"
#include "DEBUG.hh"

namespace boca
{

namespace naturalness
{

int NewPartnerLeptonicTagger::Train(Event const& event, PreCuts const&, Tag tag) const
{
    INFO0;
    return SaveEntries(Quintets(event, [&](Quintet & quintet) {
        quintet.SetTag(tag);
        return quintet;
    }), Particles(event), tag);
}

std::vector<Quintet> NewPartnerLeptonicTagger::Quintets(Event const& event, std::function<Quintet(Quintet&)> const& function) const
{
    return Pairs(top_reader_.Multiplets(event), boson_reader_.Multiplets(event), [&](Triplet const & triplet, Doublet const & doublet) {
        Quintet quintet(triplet, doublet);
        if (quintet.Overlap()) throw Overlap();
        return function(quintet);
    });
}

std::vector<Quintet> NewPartnerLeptonicTagger::Multiplets(Event const& event, boca::PreCuts const&, TMVA::Reader const& reader) const
{
    return Quintets(event, [&](Quintet & quintet) {
        quintet.SetBdt(Bdt(quintet, reader));
        return quintet;
    });
}

std::vector<Particle> NewPartnerLeptonicTagger::Particles(Event const& event) const
{
    std::vector<Particle> particles = event.Partons().GenParticles();
    std::vector<Particle> leptons = CopyIfLepton(particles);
    std::vector<Particle>candidate = CopyIfGreatGrandMother(leptons, Id::top_partner);
    if (!candidate.empty()) {
        CHECK(leptons.size() == 1, leptons.size());
        int grand_grand_mother = candidate.front().Info().Family().Member(Relative::great_grand_mother).Id();
        return CopyIfExactParticle(particles, grand_grand_mother);
    } else { // this is necessary because madspin doesnt label relations correctly
        candidate = CopyIfGrandMother(leptons, Id::top_partner);
        candidate = CopyIfMother(candidate, Id::W);
        if (candidate.empty()) return {};
        int grand_mother = candidate.front().Info().Family().Member(Relative::grand_mother).Id();
        return CopyIfExactParticle(particles, grand_mother);
    }
}
std::string NewPartnerLeptonicTagger::Name() const
{
    return "TopPartnerLeptonic";
}
std::string NewPartnerLeptonicTagger::LatexName() const
{
    return "T_{l}";
}

}

}

