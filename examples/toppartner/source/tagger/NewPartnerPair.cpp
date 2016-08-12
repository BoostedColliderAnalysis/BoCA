#include "boca/generic/Exception.hh"
#include "boca/generic/DEBUG.hh"

#include "include/tagger/NewPartnerPair.hh"

namespace toppartner
{

namespace tagger
{

int NewPartnerPair::Train(boca::Event const& event, PreCuts const&, Tag tag)
{
    INFO0;
    auto decuplets = Pairs(top_partner_hadronic_reader_.Multiplets(event), top_partner_leptonic_reader_.Multiplets(event), [&](Quintet const & quintet_1, Quintet const & quintet_2) {
        Decuplet55 decuplet(quintet_1, quintet_2);
        if (decuplet.Overlap()) throw Overlap();
        decuplet.SetTag(tag);
        return decuplet;
    });
    return SaveEntries(decuplets, 1);
}

std::vector<Decuplet55> NewPartnerPair::Multiplets(boca::Event const& event, boca::PreCuts const&, TMVA::Reader const& reader)
{
    INFO0;
    return Pairs(top_partner_hadronic_reader_.Multiplets(event), top_partner_leptonic_reader_.Multiplets(event), [&](Quintet const & quintet_1, Quintet const & quintet_2) {
        Decuplet55 decuplet(quintet_1, quintet_2);
        if (decuplet.Overlap()) throw Overlap();
        decuplet.SetBdt(Bdt(decuplet, reader));
        return decuplet;
    });
}
std::string NewPartnerPair::Name() const
{
    return "NewPartnerPair";
}
latex::String NewPartnerPair::LatexName() const
{
    return "T_{h} T_{l}";
}

}

}
