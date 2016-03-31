/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#include "VetoTopPartnerLeptonicTagger.hh"
#include "Decuplet.hh"
#include "Particles.hh"
// #define DEBUGGING
// #define INFORMATION
#include "DEBUG.hh"

namespace boca
{

namespace naturalness
{

int VetoTopPartnerLeptonicTagger::Train(Event const& event, PreCuts const& , Tag tag) const
{
    INFO0;
    return SaveEntries(Quintets(event, [&](Quintet & quintet) {
        quintet.SetTag(tag);
        return quintet;
    }), Particles(event), tag);
}

std::vector<Quintet> VetoTopPartnerLeptonicTagger::Multiplets(Event const& event, boca::PreCuts const& , TMVA::Reader const& reader) const
{
    INFO0;
    return Quintets(event, [&](Quintet & quintet) {
        quintet.SetBdt(Bdt(quintet, reader));
        return quintet;
    });
}

std::vector<Particle> VetoTopPartnerLeptonicTagger::Particles(Event const& event) const
{
    auto particles = event.Partons().GenParticles();
    auto leptons = CopyIfLepton(particles);
    auto candidate = CopyIfGreatGrandMother(leptons, Id::top_partner);
    int id;
    if (candidate.empty()) {
        candidate = CopyIfMother(CopyIfGrandMother(leptons, Id::top_partner), Id::W);
        if (candidate.empty()) return {};
        id = candidate.front().Info().Family().Member(Relative::grand_mother).Id();
    } else id = candidate.front().Info().Family().Member(Relative::great_grand_mother).Id();
    return CopyIfExactParticle(particles, id);
}

std::vector<Quintet> VetoTopPartnerLeptonicTagger::Quintets(Event const& event, std::function<Quintet(Quintet&)> const& function) const
{
    INFO0;
    auto quintets = partner_reader_.Multiplets(event);
    auto triplets = top_reader_.Multiplets(event);
    std::vector<Quintet> vetos;
    for (auto const & doublet : higgs_reader_.Multiplets(event,6)) {
        for (auto const & triplet : triplets) {
            Quintet veto(triplet, doublet);
            if (veto.Overlap()) continue;
            for (auto const & quintet : quintets) {
                Decuplet55 decuplet(quintet, veto);
                if (decuplet.Overlap()) continue;
                vetos.emplace_back(function(veto));
                break;
            }
        }
    }
    return vetos;
}

std::string VetoTopPartnerLeptonicTagger::Name() const
{
    return "VetoTopPartnerLeptonic";
}

std::string VetoTopPartnerLeptonicTagger::LatexName() const
{
    return "#slash{T}_{l}";
}


}

}
