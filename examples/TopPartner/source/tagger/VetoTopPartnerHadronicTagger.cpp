/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#include "boca/multiplets/Particles.hh"
#include "include/tagger/VetoTopPartnerHadronicTagger.hh"
#include "include/multiplets/Decuplet.hh"
// #define DEBUGGING
// #define INFORMATION
#include "boca/generic/DEBUG.hh"

namespace toppartner
{

int VetoTopPartnerHadronicTagger::Train(boca::Event const& event, PreCuts const& , Tag tag)
{
    INFO0;
    return SaveEntries(Quintets(event, [&](Quintet & quintet) {
        quintet.SetTag(tag);
        return quintet;
    }), Particles(event), tag);
}

std::vector<Quintet> VetoTopPartnerHadronicTagger::Multiplets(boca::Event const& event, boca::PreCuts const& , TMVA::Reader const& reader)
{
    INFO0;
    return Quintets(event, [&](Quintet & quintet) {
        quintet.SetBdt(Bdt(quintet, reader));
        return quintet;
    });
}

std::vector<Particle> VetoTopPartnerHadronicTagger::Particles(boca::Event const& event) const
{
    auto particles = event.GenParticles();
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

std::vector<Quintet> VetoTopPartnerHadronicTagger::Quintets(boca::Event const& event, std::function<Quintet(Quintet&)> const& function)
{
    INFO0;
    auto triplets = top_reader_.Multiplets(event);
    auto quintets = partner_reader_.Multiplets(event);
    std::vector<Quintet> vetos;
    for (auto const & doublet : higgs_reader_.Multiplets(event)) {
        for (auto const & triplet : triplets) {
            Quintet veto(triplet, doublet);
            if (veto.Overlap()) continue;
            for (auto const & quintet : quintets) {
                Decuplet532 decuplet(quintet, triplet, doublet);
                if (decuplet.Overlap()) continue;
                vetos.emplace_back(function(veto));
                break;
            }
        }
    }
    return vetos;
}

std::string VetoTopPartnerHadronicTagger::Name() const
{
    return "VetoTopPartnerHadronic";
}

latex::String VetoTopPartnerHadronicTagger::LatexName() const
{
    return "#slash{T}_{h}";
}

}
