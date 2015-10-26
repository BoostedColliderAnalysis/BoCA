#include "TopPartnerHiggsPairTagger.hh"
#include "Vector.hh"
#include "Exception.hh"
#include "Debug.hh"

namespace boca
{

namespace naturalness
{

int TopPartnerHiggsPairTagger::Train(Event const& event, PreCuts const&, Tag tag) const
{
    Info();
    std::vector<Septet> septets = pairs(top_partner_hadronic_reader_.Multiplets(event), higgs_reader_.Multiplets(event), [&](Quintet const & quintet, Doublet const & doublet) {
        Septet septet(quintet, doublet);
        if (septet.Overlap()) throw Overlap();
        septet.SetTag(tag);
        return septet;
    });
    return SaveEntries(septets);
}

std::vector<Septet> TopPartnerHiggsPairTagger::Multiplets(Event const& event, boca::PreCuts const&, TMVA::Reader const& reader) const
{
    return ReduceResult(pairs(top_partner_hadronic_reader_.Multiplets(event), higgs_reader_.Multiplets(event), [&](Quintet const & quintet, Doublet const & doublet) {
        Septet septet(quintet, doublet);
        if (septet.Overlap()) throw Overlap();
        septet.SetBdt(Bdt(septet, reader));
        return septet;
    }));
}
std::string TopPartnerHiggsPairTagger::Name() const
{
    return "TopPartnerHiggsPair";
}

}

}
