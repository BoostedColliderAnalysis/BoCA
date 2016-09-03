#include "boca/generic/Exception.hh"

#include "include/tagger/SignatureSubDom.hh"
#include "include/multiplets/Decuplet.hh"

// #define DEBUGGING
#include "boca/generic/DEBUG_MACROS.hh"

namespace toppartner
{

namespace tagger
{

int SignatureSubDom::Train(boca::Event const& event, PreCuts const&, Tag tag)
{
    INFO0;
    return SaveEntries(Quattuordecuplets(event, [&](Duodecuplet552 & duodecuplet) {
        duodecuplet.SetTag(tag);
        return duodecuplet;
    }), tag);
}

std::vector<Duodecuplet552> SignatureSubDom::Multiplets(boca::Event const& event, boca::PreCuts const&, TMVA::Reader const& reader)
{
    INFO0;
    return ReduceResult(Quattuordecuplets(event, [&](Duodecuplet552 & duodecuplet) {
        duodecuplet.SetBdt(Bdt(duodecuplet, reader));
        return duodecuplet;
    }), 1);
}

std::vector<Duodecuplet552> SignatureSubDom::Quattuordecuplets(boca::Event const& event, std::function< Duodecuplet552(Duodecuplet552&)> const& function)
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

std::string SignatureSubDom::Name() const
{
    return "SubDom";
}

latex::String SignatureSubDom::LatexName() const
{
    return "T_{h} T_{l} h";
}

}

}



