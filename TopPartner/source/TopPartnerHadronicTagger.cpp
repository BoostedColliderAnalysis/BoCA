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
    Info();
    return SaveEntries(Quintets(event, [&](Quintet & quintet) {
        quintet.SetTag(tag);
        return quintet;
    }), Particles(event), tag);
}

std::vector<Quintet> TopPartnerHadronicTagger::Multiplets(Event const& event, boca::PreCuts const&, TMVA::Reader const& reader) const
{
    Info();
    return ReduceResult(Quintets(event, [&](Quintet & quintet) {
        quintet.SetBdt(Bdt(quintet, reader));
        return quintet;
    }));
}

std::vector<Quintet> TopPartnerHadronicTagger::Quintets(Event const& event, std::function<Quintet(Quintet&)> const& function) const
{
    Info();
    return pairs(top_reader_.Multiplets(event), boson_reader_.Multiplets(event), [&](Triplet const & triplet, Doublet const & doublet) {
        Quintet quintet(triplet, doublet);
        if (quintet.Overlap()) throw Overlap();
        return function(quintet);
    });
}

Jets TopPartnerHadronicTagger::Particles(Event const& event) const
{
    Info();
    Jets particles = event.Partons().GenParticles();
    Jets quarks = CopyIfQuark(particles);
    Jets candidate = CopyIfGrandGrandMother(quarks, Id::top_partner);
    if (!candidate.empty()) {
        int grand_grand_mother = candidate.front().user_info<ParticleInfo>().Family().grand_grand_mother().id();
        return CopyIfExactParticle(particles, grand_grand_mother);
    } else {
        candidate = CopyIfGrandMother(quarks, Id::top_partner);
        candidate = CopyIfMother(candidate, Id::W);
        if (candidate.empty()) return {};
        int grand_mother = candidate.front().user_info<ParticleInfo>().Family().grand_mother().id();
        return CopyIfExactParticle(particles, grand_mother);
    }
}

}

}

