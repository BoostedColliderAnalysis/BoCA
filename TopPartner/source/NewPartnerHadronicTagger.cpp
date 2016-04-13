#include "NewPartnerHadronicTagger.hh"
#include "Event.hh"
#include "multiplets/Particles.hh"
#include "generic/Exception.hh"
#include "generic/DEBUG.hh"

namespace boca
{

namespace naturalness
{

int NewPartnerHadronicTagger::Train(Event const& event, PreCuts const&, Tag tag)
{
    INFO0;
    return SaveEntries(Quintets(event, [&](Quintet & quintet) {
        quintet.SetTag(tag);
        return quintet;
    }), Particles(event), tag);
}

std::vector<Quintet> NewPartnerHadronicTagger::Multiplets(Event const& event, boca::PreCuts const&, TMVA::Reader const& reader)
{
    INFO0;
    return Quintets(event, [&](Quintet & quintet) {
        quintet.SetBdt(Bdt(quintet, reader));
        return quintet;
    });
}

std::vector<Quintet> NewPartnerHadronicTagger::Quintets(Event const& event, std::function<Quintet(Quintet&)> const& function)
{
    INFO0;
    return Pairs(top_reader_.Multiplets(event), resonance_reader_.Multiplets(event), [&](Triplet const & triplet, Doublet const & doublet) {
        Quintet quintet(triplet, doublet);
        if (quintet.Overlap()) throw Overlap();
        return function(quintet);
    });
}

std::vector<Particle> NewPartnerHadronicTagger::Particles(Event const& event) const
{
    INFO0;
    auto particles = event.Partons().GenParticles();
    auto quarks = CopyIfQuark(particles);
    auto candidate = CopyIfGreatGrandMother(quarks, Id::top_partner);
    if (!candidate.empty()) {
        auto great_grand_mother = candidate.front().Info().Family().Member(Relative::great_grand_mother).Id();
        return CopyIfExactParticle(particles, great_grand_mother);
    } else {
        candidate = CopyIfGrandMother(quarks, Id::top_partner);
        candidate = CopyIfMother(candidate, Id::W);
        if (candidate.empty()) return {};
        auto grand_mother = candidate.front().Info().Family().Member(Relative::grand_mother).Id();
        return CopyIfExactParticle(particles, grand_mother);
    }
}
std::string NewPartnerHadronicTagger::Name() const
{
    return "TopPartnerHadronic";
}
std::string NewPartnerHadronicTagger::LatexName() const
{
    return "T_{h}";
}

}

}

