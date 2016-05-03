#include "boca/TopPartnerHadronicNeutralTagger.hh"
#include "boca/Event.hh"
#include "boca/generic/Exception.hh"
#include "boca/multiplets/Particles.hh"
#include "boca/generic/DEBUG.hh"

namespace boca
{

namespace naturalness
{

int TopPartnerHadronicNeutralTagger::Train(Event const& event, PreCuts const&, Tag tag)
{
    INFO0;
    return SaveEntries(Quintets(event, [&](Quintet & quintet) {
        quintet.SetTag(tag);
        return quintet;
    }), Particles(event), tag);
}

std::vector<Quintet> TopPartnerHadronicNeutralTagger::Multiplets(Event const& event, boca::PreCuts const&, TMVA::Reader const& reader)
{
    INFO0;
    return Quintets(event, [&](Quintet & quintet) {
        quintet.SetBdt(Bdt(quintet, reader));
        return quintet;
    });
}

std::vector<Quintet> TopPartnerHadronicNeutralTagger::Quintets(Event const& event, std::function<Quintet(Quintet&)> const& function)
{
    INFO0;
    return Pairs(top_reader_.Multiplets(event,8), boson_reader_.Multiplets(event,8), [&](Triplet const & triplet, Doublet const & doublet) {
        Quintet quintet(triplet, doublet);
        if (quintet.Overlap()) throw Overlap();
        return function(quintet);
    });
}

std::vector<Particle> TopPartnerHadronicNeutralTagger::Particles(Event const& event) const
{
    INFO0;
    auto particles = event.Partons().GenParticles();
    auto quarks = CopyIfQuark(particles);
    auto candidate = CopyIfGreatGrandMother(quarks, Id::top_partner);
    int id;
    if (candidate.empty()) {
        candidate = CopyIfGrandMother(quarks, Id::top_partner);
        candidate = CopyIfMother(candidate, Id::W);
        if (candidate.empty()) return {};
        id = candidate.front().Info().Family().Member(Relative::grand_mother).Id();
    } else id = candidate.front().Info().Family().Member(Relative::great_grand_mother).Id();
    return CopyIfExactParticle(particles, id);
}

std::string TopPartnerHadronicNeutralTagger::Name() const
{
    return "TopPartnerHadronicNeutral";
}

latex::String TopPartnerHadronicNeutralTagger::LatexName() const
{
    return "T_{h}";
}

}

}

