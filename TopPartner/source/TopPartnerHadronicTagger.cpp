#include "TopPartnerHadronicTagger.hh"
#include "Event.hh"
#include "ParticleInfo.hh"
#include "Exception.hh"
#include "Debug.hh"

namespace boca
{

namespace naturalness
{

int TopPartnerHadronicTagger::Train(Event const& event, PreCuts const&, Tag tag) const
{
    Info();
    std::vector<Triplet> triplets = top_reader_.Multiplets(event);
    Info(triplets.size());
    std::vector<Doublet> doublets = boson_reader_.Multiplets(event);
    Info(doublets.size());
    std::vector<Quintet> quintets;
    for (auto const & doublet : doublets)
        for (auto const & triplet : triplets) {
            Quintet quintet(triplet, doublet);
            if (quintet.Overlap()) continue;
            quintet.SetTag(tag);
            quintets.emplace_back(quintet);
        }
    Debug(quintets.size());
    Jets particles = Particles(event);
    if (tag == Tag::signal) {
        Check(!particles.empty(), particles.size())
    } else Check(!particles.empty(), particles.size());
    int size = particles.size();
    std::string particle = "";
    if (size > 0) particle = boca::Name(particles.front().user_info<ParticleInfo>().Family().particle().id());
    Error(size, particle);
    return SaveEntries(quintets, particles, tag);
}

std::vector<Quintet> TopPartnerHadronicTagger::Multiplets(Event const& event, boca::PreCuts const&, TMVA::Reader const& reader) const
{
    std::vector<Quintet> quintets = pairs(top_reader_.Multiplets(event), boson_reader_.Multiplets(event), [&](Triplet const & triplet, Doublet const & doublet) {
        Quintet quintet(triplet, doublet);
        if (quintet.Overlap()) throw Overlap();
        quintet.SetBdt(Bdt(quintet, reader));
        return quintet;
    });
    return ReduceResult(quintets);
}

Jets TopPartnerHadronicTagger::Particles(Event const& event) const
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

}

}
