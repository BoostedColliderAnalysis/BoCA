#include "toppartner/tagger/TopPartnerLeptonicNeutral.hh"
#include "boca/plotting/Font.hh"
#include "boca/multiplets/Particles.hh"
#include "boca/generic/Exception.hh"
#include "boca/generic/DEBUG_MACROS.hh"

namespace toppartner
{

namespace tagger
{

int TopPartnerLeptonicNeutral::Train(boca::Event const &event, PreCuts const &, Tag tag)
{
    INFO0;
    auto particles = Particles(event, tag);
    return particles.empty()  ?  0 : SaveEntries(Quintets(event, [&](Quintet & quintet) {
        quintet.SetTag(tag);
        return quintet;
    }), particles, tag);
}

std::vector<Quintet> TopPartnerLeptonicNeutral::Quintets(boca::Event const &event, std::function<Quintet(Quintet &)> const &function)
{
    return Pairs(top_reader_.Multiplets(event, 8), boson_reader_.Multiplets(event, 8), [&](Triplet const & triplet, Doublet const & doublet) {
        Quintet quintet(triplet, doublet);
        if (quintet.Overlap()) throw Overlap();
        return function(quintet);
    });
}

std::vector<Quintet> TopPartnerLeptonicNeutral::Multiplets(boca::Event const &event, boca::PreCuts const &, TMVA::Reader const &reader)
{
    return Quintets(event, [&](Quintet & quintet) {
        quintet.SetBdt(Bdt(quintet, reader));
        return quintet;
    });
}

std::vector<Particle> TopPartnerLeptonicNeutral::Particles(boca::Event const &event, Tag tag) const
{
    ERROR0;

    static int events = 0;
    ++events;
    auto particles = event.GenParticles();
    auto leptons = CopyIfLepton(particles);
    ERROR(leptons.size());
    if (leptons.empty()) return {};

    for (const auto &lepton :  leptons) {
        auto family = lepton.Info().Family();
        ERROR(boca::Name(family.Member(Relative::mother).Id()));
        ERROR(boca::Name(family.Member(Relative::step_mother).Id()));
        ERROR(boca::Name(family.Member(Relative::grand_mother).Id()));
        ERROR(boca::Name(family.Member(Relative::great_grand_mother).Id()));
    }

    auto candidates = CopyIfMother(leptons, Id::W);
    candidates = CopyIfGrandMother(candidates, Id::top);
    candidates = CopyIfGreatGrandMother(candidates, Id::top_partner);
    ERROR(candidates.size());

    auto test = CopyIfAncestor(leptons, Id::top_partner);

    if (candidates.empty() && !test.empty()) ERROR("WHAT IS WRONG??????????????????????????????");

    if (candidates.empty()) return {};

    auto position = 0;
    if (auto member = candidates.front().Info().Family().Member(Id::top_partner)) position = (*member).Position();
    else {
        ERROR("no top partner");
        return {};
    }
    ERROR(position);
    auto top_partners = CopyIfPosition(particles, position);
    if (tag == Tag::signal) CHECK(top_partners.size() == 1, top_partners.size());

    static int tags = 0;
    ++tags;

        ERROR(events,  tags,  top_partners.size(), "we got partners !!!!!!!!!!!!!!!!!!!!!!!");
    return top_partners;
}

std::string TopPartnerLeptonicNeutral::Name() const
{
    return "TopPartnerLeptonicNeutral";
}

latex::String TopPartnerLeptonicNeutral::LatexName() const
{
    return "T_{l}";
}

}

}

