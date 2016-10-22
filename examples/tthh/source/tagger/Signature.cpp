#include "wimpmass/Mt2.hh"
#include "boca/generic/Exception.hh"

#include "tthh/tagger/Signature.hh"
#define INFORMATION
#include "boca/generic/DEBUG_MACROS.hh"

namespace tthh
{

namespace tagger
{

int Signature::Train(boca::Event const &event, PreCuts const &, Tag tag)
{
    INFO0;
    return SaveEntries(Duodecuplets(event, [&](Duodecuplet633 & duodecuplet) {
        duodecuplet.SetTag(tag);
        return duodecuplet;
    }), tag);
}

std::vector<Duodecuplet633> Signature::Multiplets(boca::Event const &event, boca::PreCuts const &, TMVA::Reader const &reader)
{
    INFO0;
    return ReduceResult(Duodecuplets(event, [&](Duodecuplet633 & duodecuplet) {
        duodecuplet.SetBdt(Bdt(duodecuplet, reader));
        return duodecuplet;
    }), 1);
}

std::vector<Duodecuplet633> Signature::Duodecuplets(boca::Event const &event, std::function< Duodecuplet633(Duodecuplet633 &)> const &function)
{
    INFO0;
    return Triples(top_hadronic_reader_.Multiplets(event), top_leptonic_reader_.Multiplets(event), higgs_reader_.Multiplets(event),  [&](auto const & triplet_1, auto const & triplet_2) {
        Sextet33 sextet(triplet_1, triplet_2);
        INFO("sextet");
        if (sextet.Overlap()) throw Overlap();
        INFO("sextet non-overlapping");
        return sextet;
    }, [&](auto const & sextet_1, auto const & sextet_2) {
        Duodecuplet633 duodecuplet;
        INFO("duodecuplet");
        duodecuplet.SetMultiplets23(sextet_1, sextet_2);
        wimpmass::Mt2 mt2;
        INFO("mt2");
        duodecuplet.SetVetoBdt(mt2.Get(duodecuplet.Sextet().Quartet().Doublet2().Singlet1(), duodecuplet.Triplet2().Doublet().Singlet1(), event.MissingEt()));
        INFO("mt2", duodecuplet.VetoBdt());
        if (duodecuplet.Overlap()) throw Overlap();
        INFO("non-overlapping");
        return function(duodecuplet);
    });
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



