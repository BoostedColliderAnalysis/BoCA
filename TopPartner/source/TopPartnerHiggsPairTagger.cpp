#include "TopPartnerHiggsPairTagger.hh"
#include "Vector.hh"
#include "Debug.hh"

namespace boca
{

namespace naturalness
{

TopPartnerHiggsPairTagger::TopPartnerHiggsPairTagger()
{
    Info();
    DefineVariables();
}

int TopPartnerHiggsPairTagger::Train(Event const& event, PreCuts const&, Tag tag) const
{
    Info();
    std::vector<Septet> septets = pairs(top_partner_hadronic_reader_.Multiplets(event), higgs_reader_.Multiplets(event), [&](Quintet const & quintet, Doublet const & doublet) {
        Septet septet(quintet, doublet);
        if (septet.Overlap()) throw "overlap";
        septet.SetTag(tag);
        return septet;
    });
    return SaveEntries(septets);
}

std::vector<Septet> TopPartnerHiggsPairTagger::Multiplets(Event const& event, boca::PreCuts const&, TMVA::Reader const& reader) const
{
    return ReduceResult(pairs(top_partner_hadronic_reader_.Multiplets(event), higgs_reader_.Multiplets(event), [&](Quintet const & quintet, Doublet const & doublet) {
        Septet septet(quintet, doublet);
        if (septet.Overlap()) throw "overlap";
        septet.SetBdt(Bdt(septet, reader));
        return septet;
    }));
}

}

}
