#include "TopPartnerLeptonicTagger.hh"
#include "ParticleInfo.hh"
#include "Debug.hh"

namespace boca
{

namespace naturalness
{

int TopPartnerLeptonicTagger::Train(Event const& event, PreCuts const&, Tag tag) const
{
    Info();
    std::vector<Quintet> quintets = pairs(top_reader_.Multiplets(event), boson_reader_.Multiplets(event), [&](Triplet const & triplet, Doublet const & doublet) {
        Quintet quintet(triplet, doublet);
        if (quintet.Overlap()) throw "overlap";
        quintet.SetTag(tag);
        return quintet;
    });
    Jets particles = Particles(event);
    Debug(particles.size());
    if(tag == Tag::signal) Check(!particles.empty(), particles.size());
    return SaveEntries(quintets, particles, tag);
}

std::vector<Quintet> TopPartnerLeptonicTagger::Multiplets(Event const& event, boca::PreCuts const&, TMVA::Reader const& reader) const
{
    std::vector<Quintet> quintets = pairs(top_reader_.Multiplets(event), boson_reader_.Multiplets(event), [&](Triplet const & triplet, Doublet const & doublet) {
        Quintet quintet(triplet, doublet);
        if (quintet.Overlap()) throw "overlap";
        quintet.SetBdt(Bdt(quintet, reader));
        return quintet;
    });
    return ReduceResult(quintets);
}

Jets TopPartnerLeptonicTagger::Particles(Event const& event) const
{
  Jets particles = event.Partons().GenParticles();
  Jets leptons = CopyIfLepton(particles);
  Jets candidate = CopyIfGrandGrandMother(leptons, Id::top_partner);
  if(!candidate.empty()) {
    Check(leptons.size() == 1, leptons.size());
    int grand_grand_mother = candidate.front().user_info<ParticleInfo>().Family().grand_grand_mother().id();
    return CopyIfExactParticle(particles, grand_grand_mother);
  } else { // this is necessary because madspin doesnt label relations correctly
    candidate = CopyIfGrandMother(leptons, Id::top_partner);
    candidate = CopyIfMother(candidate, Id::W);
    if(candidate.empty()) return {};
    int grand_mother = candidate.front().user_info<ParticleInfo>().Family().grand_mother().id();
    return CopyIfExactParticle(particles, grand_mother);
  }
}


}

}
