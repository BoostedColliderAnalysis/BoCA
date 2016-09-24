#include "toppartner/tagger/TopPartnerLeptonic.hh"
#include "boca/generic/DEBUG_MACROS.hh"

namespace toppartner
{

namespace tagger
{

namespace
{
Quintet Map(Triplet const &triplet)
{
    Quintet quintet;
    quintet.Doublet() = triplet.Doublet();
    quintet.Triplet().Enforce(triplet.Singlet());
    quintet.SetBdt(triplet.Bdt());
    return quintet;
}
}

int TopPartnerLeptonic::Train(boca::Event const& event, PreCuts const&, Tag tag)
{
    INFO0;
    return SaveEntries(Quintets(event, [&](Quintet & quintet) {
        quintet.SetTag(tag);
        return quintet;
    }, [&](Triplet & quintet) {
        quintet.SetTag(tag);
        return quintet;
    }), Particles(event), tag);
}

std::vector<Quintet> TopPartnerLeptonic::Multiplets(boca::Event const &event, boca::PreCuts const &, TMVA::Reader const &reader)
{
    INFO0;
    return Quintets(event, [&](Quintet & quintet) {
        quintet.SetBdt(Bdt(quintet, reader));
        return quintet;
    }, [&](Triplet & quintet) {
        quintet.SetBdt(Bdt(Map(quintet), reader));
        return quintet;
    });
}

std::vector<Quintet> TopPartnerLeptonic::Quintets(boca::Event const &event, std::function<Quintet(Quintet &)> const &function_1, std::function<Triplet(Triplet&)> const &function_2)
{
    INFO0;
    return Combine(neutral_.Quintets(event, function_1), Transform(charged_.Triplets(event, function_2), [](Triplet const & triplet) {
        return Map(triplet);
    }));
}

std::vector<Particle> TopPartnerLeptonic::Particles(boca::Event const& event) const
{
    return Combine(charged_.Particles(event), neutral_.Particles(event));
}

std::string TopPartnerLeptonic::Name() const
{
    return "TopPartnerLeptonic";
}

latex::String TopPartnerLeptonic::LatexName() const
{
    return "T_{h}";
}

}

}
