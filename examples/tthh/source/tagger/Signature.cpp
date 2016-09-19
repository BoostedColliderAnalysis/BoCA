#include "tthh/tagger/Signature.hh"
#include "boca/generic/Exception.hh"
// #define DEBUGGING
#include "boca/generic/DEBUG_MACROS.hh"

namespace tthh
{

namespace tagger
{

int Signature::Train(boca::Event const& event, PreCuts const&, Tag tag)
{
    INFO0;
    return SaveEntries(Duodecuplets(event, [&](Duodecuplet633 & duodecuplets) {
        duodecuplets.SetTag(tag);
        return duodecuplets;
    }), tag);
}

std::vector<Duodecuplet633> Signature::Multiplets(boca::Event const& event, boca::PreCuts const&, TMVA::Reader const& reader)
{
    INFO0;
    return ReduceResult(Duodecuplets(event, [&](Duodecuplet633 & duodecuplets) {
        duodecuplets.SetBdt(Bdt(duodecuplets, reader));
        return duodecuplets;
    }), 1);
}

std::vector<Duodecuplet633> Signature::Duodecuplets(boca::Event const& event, std::function< Duodecuplet633(Duodecuplet633&)> const& function)
{
    INFO0;
    auto higgs = higgs_reader_.Multiplets(event);
    auto leptonic = top_leptonic_reader_.Multiplets(event);
    auto hadronic = top_hadronic_reader_.Multiplets(event);
    auto signatures = Triples(leptonic, hadronic, higgs,  [&](Triplet const & triplet_1, Triplet const & triplet_2) {
        Sextet33 sextet(triplet_1, triplet_2);
        if (sextet.Overlap()) throw Overlap();
        return sextet;
    }, [&](Sextet33 const & sextet_1, Sextet42 const & sextet_2) {
        Duodecuplet633 duodecuplets;
        duodecuplets.SetMultiplets23(sextet_1, sextet_2);
        if (duodecuplets.Overlap()) throw Overlap();
        return function(duodecuplets);
    });
    return signatures;
}

std::string Signature::Name() const
{
    return "Signature";
}

latex::String Signature::LatexName() const
{
    return "t_{h} t_{l} h_{b} h_{l}";
}

}

}



