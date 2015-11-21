/**
 * Copyright (C) 2015 Jan Hajer
 */
#include "VetoTopPartnerLeptonicTagger.hh"
#include "Decuplet.hh"
#include "ParticleInfo.hh"
// #define DEBUG
// #define INFORMATION
#include "Debug.hh"

namespace boca
{

namespace naturalness
{

int VetoTopPartnerLeptonicTagger::Train(Event const& event, PreCuts const& , Tag tag) const
{
    Info0;
    return SaveEntries(Quintets(event, [&](Quintet & quintet) {
        quintet.SetTag(tag);
        return quintet;
    }), Particles(event), tag);
}

std::vector<Quintet> VetoTopPartnerLeptonicTagger::Multiplets(Event const& event, boca::PreCuts const& , TMVA::Reader const& reader) const
{
    Info0;
    return ReduceResult(Quintets(event, [&](Quintet & quintet) {
        quintet.SetBdt(Bdt(quintet, reader));
        return quintet;
    }));
}

std::vector<Particle> VetoTopPartnerLeptonicTagger::Particles(Event const& event) const
{
    std::vector<Particle> particles = event.Partons().GenParticles();
    std::vector<Particle> leptons = CopyIfLepton(particles);
    std::vector<Particle>candidate = CopyIfGrandGrandMother(leptons, Id::top_partner);
    if (!candidate.empty()) {
        int great_grand_mother = candidate.front().Info().Family().GreatGrandMother().Id();
        return CopyIfExactParticle(particles, great_grand_mother);
    } else {
        candidate = CopyIfGrandMother(leptons, Id::top_partner);
        candidate = CopyIfMother(candidate, Id::W);
        if (candidate.empty()) return {};
        int grand_mother = candidate.front().Info().Family().GrandMother().Id();
        return CopyIfExactParticle(particles, grand_mother);
    }
}

std::vector<Quintet> VetoTopPartnerLeptonicTagger::Quintets(Event const& event, std::function<Quintet(Quintet&)> const& function) const
{
    Info0;
    std::vector<Triplet> triplets = top_reader_.Multiplets(event);
    std::vector<Quintet> quintets = partner_reader_.Multiplets(event);
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

std::string VetoTopPartnerLeptonicTagger::Name() const
{
    return "VetoTopPartnerLeptonic";
}

std::string VetoTopPartnerLeptonicTagger::NiceName() const
{
    return "#slash{T}_{l}";
}


}

}
