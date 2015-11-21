#include "TopPartnerHadronicTagger.hh"
#include "Event.hh"
#include "ParticleInfo.hh"
#include "Exception.hh"
#include "Debug.hh"

namespace boca
{

namespace naturalness
{

int TopPartnerHadronicTagger::Train(Event const& event, PreCuts const&, Tag tag) const
{
    Info0;
    return SaveEntries(Quintets(event, [&](Quintet & quintet) {
        quintet.SetTag(tag);
        return quintet;
    }), Particles(event), tag);
}

std::vector<Quintet> TopPartnerHadronicTagger::Multiplets(Event const& event, boca::PreCuts const&, TMVA::Reader const& reader) const
{
    Info0;
    return ReduceResult(Quintets(event, [&](Quintet & quintet) {
        quintet.SetBdt(Bdt(quintet, reader));
        return quintet;
    }));
}

std::vector<Quintet> TopPartnerHadronicTagger::Quintets(Event const& event, std::function<Quintet(Quintet&)> const& function) const
{
    Info0;
    return pairs(top_reader_.Multiplets(event), boson_reader_.Multiplets(event), [&](Triplet const & triplet, Doublet const & doublet) {
        Quintet quintet(triplet, doublet);
        if (quintet.Overlap()) throw Overlap();
        return function(quintet);
    });
}

std::vector<Particle> TopPartnerHadronicTagger::Particles(Event const& event) const
{
    Info0;
    std::vector<Particle> particles = event.Partons().GenParticles();
    std::vector<Particle> quarks = CopyIfQuark(particles);
    std::vector<Particle>candidate = CopyIfGrandGrandMother(quarks, Id::top_partner);
    if (!candidate.empty()) {
        int great_grand_mother = candidate.front().Info().Family().GreatGrandMother().Id();
        return CopyIfExactParticle(particles, great_grand_mother);
    } else {
        candidate = CopyIfGrandMother(quarks, Id::top_partner);
        candidate = CopyIfMother(candidate, Id::W);
        if (candidate.empty()) return {};
        int grand_mother = candidate.front().Info().Family().GrandMother().Id();
        return CopyIfExactParticle(particles, grand_mother);
    }
}
std::string TopPartnerHadronicTagger::Name() const
{
    return "TopPartnerHadronic";
}
std::string TopPartnerHadronicTagger::NiceName() const
{
    return "T_{h}";
}

}

}

