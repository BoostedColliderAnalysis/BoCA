#include "boca/external/Mt2.hh"
#include "boca/generic/Exception.hh"

#include "tthh/tagger/Signature.hh"
// #define DEBUGGING
#include "boca/generic/DEBUG_MACROS.hh"

namespace tthh
{

namespace tagger
{

int Signature::Train(boca::Event const& event, PreCuts const&, Tag tag)
{
    INFO0;
    return SaveEntries(Duodecuplets(event, [&](Duodecuplet633 & duodecuplet) {
        duodecuplet.SetTag(tag);
        return duodecuplet;
    }), tag);
}

std::vector<Duodecuplet633> Signature::Multiplets(boca::Event const& event, boca::PreCuts const&, TMVA::Reader const& reader)
{
    INFO0;
    return ReduceResult(Duodecuplets(event, [&](Duodecuplet633 & duodecuplet) {
        duodecuplet.SetBdt(Bdt(duodecuplet, reader));
        return duodecuplet;
    }), 1);
}

std::vector<Duodecuplet633> Signature::Duodecuplets(boca::Event const& event, std::function< Duodecuplet633(Duodecuplet633&)> const& function)
{
    INFO0;
    auto hadronic = top_hadronic_reader_.Multiplets(event);
    auto leptonic = top_leptonic_reader_.Multiplets(event);
    auto higgs = higgs_reader_.Multiplets(event);
    auto signatures = Triples(hadronic, leptonic, higgs,  [&](Triplet const & triplet_1, Triplet const & triplet_2) {
        Sextet33 sextet(triplet_1, triplet_2);
        if (sextet.Overlap()) throw Overlap();
        return sextet;
    }, [&](Sextet33 const & sextet_1, Sextet42 const & sextet_2) {
        Duodecuplet633 duodecuplet;
        duodecuplet.SetMultiplets23(sextet_1, sextet_2);
        wimpmass::Mt2 mt2;
        duodecuplet.SetVetoBdt(mt2.Get(duodecuplet.Sextet().Quartet().Doublet2().Singlet1(), duodecuplet.Triplet2().Doublet().Singlet1(), event.MissingEt()));
        if (duodecuplet.Overlap()) throw Overlap();
        return function(duodecuplet);
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



