#include "boca/SignatureHiggsPartnerPairTagger.hh"
#include "boca/generic/Exception.hh"
// #define DEBUGGING
#include "boca/generic/DEBUG.hh"

namespace boca
{

namespace toppartner
{

int SignatureHiggsPartnerPairTagger::Train(Event const& event, PreCuts const&, Tag tag)
{
    INFO0;
    return SaveEntries(Duodecuplets(event, [&](Duodecuplet552 & quattuordecuplet) {
        quattuordecuplet.SetTag(tag);
        return quattuordecuplet;
    }), tag);
}

std::vector<Duodecuplet552> SignatureHiggsPartnerPairTagger::Multiplets(Event const& event, boca::PreCuts const&, TMVA::Reader const& reader)
{
    INFO0;
    return ReduceResult(Duodecuplets(event, [&](Duodecuplet552 & quattuordecuplet) {
        quattuordecuplet.SetBdt(Bdt(quattuordecuplet, reader));
        return quattuordecuplet;
    }), 1);
}

std::vector<Duodecuplet552> SignatureHiggsPartnerPairTagger::Duodecuplets(boca::Event const& event, std::function< Duodecuplet552(Duodecuplet552&)> const& function)
{
    INFO0;
    auto hadronic = top_partner_hadronic_reader_.Multiplets(event, 8);
    auto leptonic = top_partner_leptonic_reader_.Multiplets(event, 8);
    auto higgses = higgs_reader_.Multiplets(event, 8);
    auto signatures = Triples(hadronic, leptonic, higgses, [&](Quintet const & quintet_1, Quintet const & quintet_2) {
        Decuplet55 decuplet(quintet_1, quintet_2);
        if (decuplet.Overlap()) throw Overlap();
        return decuplet;
    }, [&](Decuplet55 const & decuplet, Doublet const & doublet) {
        Duodecuplet552 duodecuplet;
        duodecuplet.SetMultiplets12(decuplet, doublet);
        if (duodecuplet.Overlap()) throw Overlap();
        return function(duodecuplet);
    });
    return signatures;
}

std::string SignatureHiggsPartnerPairTagger::Name() const
{
    return "Signature";
}

latex::String SignatureHiggsPartnerPairTagger::LatexName() const
{
    return "T_{h} T_{l} h";
}

}

}



