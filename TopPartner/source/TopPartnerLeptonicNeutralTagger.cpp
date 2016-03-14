#include "TopPartnerLeptonicNeutralTagger.hh"
#include "plotting/Font.hh"
#include "Particles.hh"
#include "Exception.hh"
#include "DEBUG.hh"

namespace boca
{

namespace naturalness
{

int TopPartnerLeptonicNeutralTagger::Train(Event const& event, PreCuts const&, Tag tag) const
{
    INFO0;
    return SaveEntries(Quintets(event, [&](Quintet & quintet) {
        quintet.SetTag(tag);
        return quintet;
    }), Particles(event, tag), tag);
}

std::vector<Quintet> TopPartnerLeptonicNeutralTagger::Quintets(Event const& event, std::function<Quintet(Quintet&)> const& function) const
{
    return Pairs(top_reader_.Multiplets(event), boson_reader_.Multiplets(event), [&](Triplet const & triplet, Doublet const & doublet) {
        Quintet quintet(triplet, doublet);
        if (quintet.Overlap()) throw Overlap();
        return function(quintet);
    });
}

std::vector<Quintet> TopPartnerLeptonicNeutralTagger::Multiplets(Event const& event, boca::PreCuts const&, TMVA::Reader const& reader) const
{
    return ReduceResult(Quintets(event, [&](Quintet & quintet) {
        quintet.SetBdt(Bdt(quintet, reader));
        return quintet;
    }));
}

std::vector<Particle> TopPartnerLeptonicNeutralTagger::Particles(Event const& event, Tag tag) const
{
    auto particles = event.Partons().GenParticles();
    auto leptons = CopyIfLepton(particles);
    auto candidate = CopyIfGreatGrandMother(leptons, Id::top_partner);
    int id;
    if (candidate.empty()) { // this is necessary because madspin doesnt label relations correctly
        candidate = CopyIfGrandMother(leptons, Id::top_partner);
        candidate = CopyIfMother(candidate, Id::W);
        if (candidate.empty()) {
            if(tag == Tag::signal) ERROR("no leptonic top partners");
            return {};
        }
        id = candidate.front().Info().Family().Member(Relative::grand_mother).Id();
    } else id = candidate.front().Info().Family().Member(Relative::great_grand_mother).Id();
    auto top_partners = CopyIfExactParticle(particles, id);
    if(tag == Tag::signal) CHECK(top_partners.size() == 1, top_partners.size())
    return top_partners;
}

std::string TopPartnerLeptonicNeutralTagger::Name() const
{
    return "TopPartnerLeptonicNeutral";
}

std::string TopPartnerLeptonicNeutralTagger::LatexName() const
{
    return Formula("T_{l}");
}

}

}

