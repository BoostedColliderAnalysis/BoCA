#include "boca/fastjet/Particles.hh"
#include "boca/generic/Exception.hh"
#include "boca/generic/DEBUG_MACROS.hh"

#include "toppartner/tagger/NewPartnerLeptonic.hh"

namespace toppartner
{

namespace tagger
{

int NewPartnerLeptonic::Train(boca::Event const& event, PreCuts const&, Tag tag)
{
    INFO0;
    return SaveEntries(Quintets(event, [&](Quintet & quintet) {
        quintet.SetTag(tag);
        return quintet;
    }), Particles(event), tag);
}

std::vector<Quintet> NewPartnerLeptonic::Quintets(boca::Event const& event, std::function<Quintet(Quintet&)> const& function)
{
    return Pairs(top_reader_.Multiplets(event), boson_reader_.Multiplets(event), [&](Triplet const & triplet, Doublet const & doublet) {
        Quintet quintet(triplet, doublet);
        if (quintet.Overlap()) throw Overlap();
        return function(quintet);
    });
}

std::vector<Quintet> NewPartnerLeptonic::Multiplets(boca::Event const& event, boca::PreCuts const&, TMVA::Reader const& reader)
{
    return Quintets(event, [&](Quintet & quintet) {
        quintet.SetBdt(Bdt(quintet, reader));
        return quintet;
    });
}

std::vector<Particle> NewPartnerLeptonic::Particles(boca::Event const& event) const
{
    auto particles = event.GenParticles();
    auto leptons = CopyIfLepton(particles);
    auto candidate = CopyIfGreatGrandMother(leptons, Id::top_partner);
    if (!candidate.empty()) {
        CHECK(leptons.size() == 1, leptons.size());
        auto grand_grand_mother = candidate.front().Info().Family().Member(Relative::great_grand_mother).Id();
        return CopyIfExactParticle(particles, grand_grand_mother);
    } else { // this is necessary because madspin doesnt label relations correctly
        candidate = CopyIfGrandMother(leptons, Id::top_partner);
        candidate = CopyIfMother(candidate, Id::W);
        if (candidate.empty()) return {};
        auto grand_mother = candidate.front().Info().Family().Member(Relative::grand_mother).Id();
        return CopyIfExactParticle(particles, grand_mother);
    }
}
std::string NewPartnerLeptonic::Name() const
{
    return "TopPartnerLeptonic";
}
latex::String NewPartnerLeptonic::LatexName() const
{
    return "T_{l}";
}

}

}

