#include "TopPartnerPairTagger.hh"
#include "Exception.hh"
#include "Debug.hh"

namespace boca
{

namespace naturalness
{

int TopPartnerPairTagger::Train(Event const& event, PreCuts const&, Tag tag) const
{
    Info0;
    std::vector<Decuplet55> decuplets = pairs(top_partner_hadronic_reader_.Multiplets(event), top_partner_leptonic_reader_.Multiplets(event), [&](Quintet const & quintet_1, Quintet const & quintet_2) {
        Decuplet55 decuplet(quintet_1, quintet_2);
        if (decuplet.Overlap()) throw Overlap();
        decuplet.SetTag(tag);
        return decuplet;
    });
    return SaveEntries(decuplets, 1);
}

std::vector<Decuplet55> TopPartnerPairTagger::Multiplets(Event const& event, boca::PreCuts const&, TMVA::Reader const& reader) const
{
    Info0;
    return ReduceResult(pairs(top_partner_hadronic_reader_.Multiplets(event), top_partner_leptonic_reader_.Multiplets(event), [&](Quintet const & quintet_1, Quintet const & quintet_2) {
        Decuplet55 decuplet(quintet_1, quintet_2);
        if (decuplet.Overlap()) throw Overlap();
        decuplet.SetBdt(Bdt(decuplet, reader));
        return decuplet;
    }));
}
std::string TopPartnerPairTagger::Name() const
{
    return "TopPartnerPair";
}
std::string TopPartnerPairTagger::NiceName() const
{
    return "T_{h} T_{l}";
}

}

}
