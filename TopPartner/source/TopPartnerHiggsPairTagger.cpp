#include "boca/TopPartnerHiggsPairTagger.hh"
#include "boca/generic/Exception.hh"
#include "boca/generic/DEBUG.hh"

namespace boca
{

namespace toppartner
{

int TopPartnerHiggsPairTagger::Train(Event const& event, PreCuts const&, Tag tag)
{
    INFO0;
    auto septets = Pairs(top_partner_hadronic_reader_.Multiplets(event), higgs_reader_.Multiplets(event), [&](Quintet const & quintet, Doublet const & doublet) {
        Septet septet(quintet, doublet);
        if (septet.Overlap()) throw Overlap();
        septet.SetTag(tag);
        return septet;
    });
    return SaveEntries(septets);
}

std::vector<Septet> TopPartnerHiggsPairTagger::Multiplets(Event const& event, boca::PreCuts const&, TMVA::Reader const& reader)
{
    return Pairs(top_partner_hadronic_reader_.Multiplets(event), higgs_reader_.Multiplets(event), [&](Quintet const & quintet, Doublet const & doublet) {
        Septet septet(quintet, doublet);
        if (septet.Overlap()) throw Overlap();
        septet.SetBdt(Bdt(septet, reader));
        return septet;
    });
}
std::string TopPartnerHiggsPairTagger::Name() const
{
    return "TopPartnerHiggsPair";
}

}

}
