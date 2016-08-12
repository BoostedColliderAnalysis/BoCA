#include "include/tagger/TopPartnerPair.hh"
#include "boca/generic/Exception.hh"
#include "boca/plotting/Font.hh"
#include "boca/generic/DEBUG.hh"

namespace toppartner
{

namespace tagger
{

int TopPartnerPair::Train(boca::Event const& event, PreCuts const&, Tag tag)
{
    INFO0;
    return SaveEntries(Decuplets(event, [&](Decuplet55 & decuplet) {
        decuplet.SetTag(tag);
        return decuplet;
    }), 1);
}

std::vector<Decuplet55> TopPartnerPair::Multiplets(boca::Event const& event, PreCuts const&, TMVA::Reader const& reader)
{
    INFO0;
    return Decuplets(event, [&](Decuplet55 & decuplet) {
        decuplet.SetBdt(Bdt(decuplet, reader));
        return decuplet;
    });
}

std::vector<Decuplet55> TopPartnerPair::Decuplets(boca::Event const& event, std::function<Decuplet55(Decuplet55&)> const& function)
{
    INFO0;
    return Pairs(top_partner_hadronic_reader_.Multiplets(event), top_partner_leptonic_reader_.Multiplets(event), [&](Quintet const & quintet_1, Quintet const & quintet_2) {
        Decuplet55 decuplet(quintet_1, quintet_2);
        if (decuplet.Overlap()) throw Overlap();
        return function(decuplet);
    });
}

std::string TopPartnerPair::Name() const
{
    return "TopPartnerPair";
}

latex::String TopPartnerPair::LatexName() const
{
    return "T_{h} T_{l}";
}

}

}
