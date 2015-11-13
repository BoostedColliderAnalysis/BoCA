/**
 * Copyright (C) 2015 Jan Hajer
 */
#include "VetoTopPartnerHadronicTagger.hh"
#include "Decuplet.hh"
#include "ParticleInfo.hh"
// #define DEBUG
// #define INFORMATION
#include "Debug.hh"

namespace boca
{

namespace naturalness
{

int VetoTopPartnerHadronicTagger::Train(Event const& event, PreCuts const& , Tag tag) const
{
    Info0;
    return SaveEntries(Quintets(event, [&](Quintet & quintet) {
        quintet.SetTag(tag);
        return quintet;
    }), Particles(event), tag);
}

std::vector<Quintet> VetoTopPartnerHadronicTagger::Multiplets(Event const& event, boca::PreCuts const& , TMVA::Reader const& reader) const
{
    Info0;
    return ReduceResult(Quintets(event, [&](Quintet & quintet) {
        quintet.SetBdt(Bdt(quintet, reader));
        return quintet;
    }));
}

Jets VetoTopPartnerHadronicTagger::Particles(Event const& event) const
{
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

std::vector<Quintet> VetoTopPartnerHadronicTagger::Quintets(Event const& event, std::function<Quintet(Quintet&)> const& function) const
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

std::string VetoTopPartnerHadronicTagger::Name() const {
  return "VetoTopPartnerHadronic";
}

std::string VetoTopPartnerHadronicTagger::NiceName() const {
  return "#slash{T}_{h}";
}


}

}
