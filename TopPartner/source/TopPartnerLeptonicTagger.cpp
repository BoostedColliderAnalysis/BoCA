#include "TopPartnerLeptonicTagger.hh"
#include "Debug.hh"

namespace boca
{

namespace naturalness
{

TopPartnerLeptonicTagger::TopPartnerLeptonicTagger()
{
    Info();
    DefineVariables();
}

int TopPartnerLeptonicTagger::Train(Event const& event, PreCuts const&, Tag tag) const
{
    Info();
    std::vector<Quintet> quintets = pairs(top_reader_.Multiplets(event), boson_reader_.Multiplets(event), [&](Triplet const & triplet, Doublet const & doublet) {
        Quintet quintet(triplet, doublet);
        if (quintet.Overlap()) throw "overlap";
        quintet.SetTag(tag);
        return quintet;
    });
    return SaveEntries(quintets, CopyIfParticle(event.Partons().GenParticles(),Id::top_partner), tag);
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

}

}
