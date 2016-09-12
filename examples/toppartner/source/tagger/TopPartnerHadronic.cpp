#include "toppartner/tagger/TopPartnerHadronic.hh"
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

int TopPartnerHadronic::Train(boca::Event const &event, PreCuts const &, Tag tag)
{
    INFO0;
//     std::vector<boca::Jet> leptons{};
    return SaveEntries(Quintets(event, [&](Quintet & quintet) {
        quintet.SetTag(tag);
        return quintet;
    }, [&](Triplet & quintet, std::vector<boca::Jet>const &) {
        quintet.SetTag(tag);
        return quintet;
    }), Particles(event), tag);
}

std::vector<Quintet> TopPartnerHadronic::Multiplets(boca::Event const &event, boca::PreCuts const &, TMVA::Reader const &reader)
{
    INFO0;
//     std::vector<boca::Jet> leptons{};
    return Quintets(event, [&](Quintet & quintet) {
        quintet.SetBdt(Bdt(quintet, reader));
        return quintet;
    }, [&](Triplet & quintet, std::vector<boca::Jet>const &) {
        quintet.SetBdt(Bdt(Map(quintet), reader));
        return quintet;
    });
}

std::vector<Quintet> TopPartnerHadronic::Quintets(boca::Event const &event, std::function<Quintet(Quintet &)> const &function_1, standardmodel::tagger::TopHadronic::Function const &function_2)
{
    INFO0;
    return Combine(neutral_.Tagger().Quintets(event, function_1), Transform(charged_.Tagger().Triplets(event, function_2), [](Triplet const & triplet) {
        return Map(triplet);
    }));
}

std::vector<Particle> TopPartnerHadronic::Particles(boca::Event const &event) const
{
    return Combine(charged_.Tagger().Particles(event), neutral_.Tagger().Particles(event));
}

std::string TopPartnerHadronic::Name() const
{
    return "TopPartnerHadronic";
}

latex::String TopPartnerHadronic::LatexName() const
{
    return {"T_{h}", true};
}

}

}
