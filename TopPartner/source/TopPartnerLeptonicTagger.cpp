#include "TopPartnerLeptonicTagger.hh"
#include "ParticleInfo.hh"
#include "Exception.hh"
#include "Debug.hh"

namespace boca
{

namespace naturalness
{

int TopPartnerLeptonicTagger::Train(Event const& event, PreCuts const&, Tag tag) const
{
    Info();
    return SaveEntries(Quintets(event, [&](Quintet & quintet) {
        quintet.SetTag(tag);
        return quintet;
    }), Particles(event), tag);
}

std::vector<Quintet> TopPartnerLeptonicTagger::Quintets(Event const& event, std::function<Quintet(Quintet&)> const& function) const
{
    return pairs(top_reader_.Multiplets(event), boson_reader_.Multiplets(event), [&](Triplet const & triplet, Doublet const & doublet) {
        Quintet quintet(triplet, doublet);
        if (quintet.Overlap()) throw Overlap();
        return function(quintet);
    });
}

std::vector<Quintet> TopPartnerLeptonicTagger::Multiplets(Event const& event, boca::PreCuts const&, TMVA::Reader const& reader) const
{
    return ReduceResult(Quintets(event, [&](Quintet & quintet) {
        quintet.SetBdt(Bdt(quintet, reader));
        return quintet;
    }));
}

Jets TopPartnerLeptonicTagger::Particles(Event const& event) const
{
    Jets particles = event.Partons().GenParticles();
    Jets leptons = CopyIfLepton(particles);
    Jets candidate = CopyIfGrandGrandMother(leptons, Id::top_partner);
    if (!candidate.empty()) {
        Check(leptons.size() == 1, leptons.size());
        int grand_grand_mother = candidate.front().user_info<ParticleInfo>().Family().grand_grand_mother().id();
        return CopyIfExactParticle(particles, grand_grand_mother);
    } else { // this is necessary because madspin doesnt label relations correctly
        candidate = CopyIfGrandMother(leptons, Id::top_partner);
        candidate = CopyIfMother(candidate, Id::W);
        if (candidate.empty()) return {};
        int grand_mother = candidate.front().user_info<ParticleInfo>().Family().grand_mother().id();
        return CopyIfExactParticle(particles, grand_mother);
    }
}
std::string TopPartnerLeptonicTagger::Name() const
{
    return "TopPartnerLeptonic";
}
std::string TopPartnerLeptonicTagger::NiceName() const
{
    return "T_{l}";
}

}

}

