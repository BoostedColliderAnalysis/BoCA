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
    return SaveEntries(Duodecuplets(event, [&](auto & duodecuplet) {
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
    return Triples(
        top_hadronic_reader_.Multiplets(event),
        top_leptonic_reader_.Multiplets(event),
        higgs_reader_.Multiplets(event),
        [&](auto const & top_hadronic, auto const & top_leptonic) {
        Sextet33 tops(top_hadronic, top_leptonic);
        INFO("sextet");
        if (tops.Overlap()) throw Overlap();
        INFO("sextet non-overlapping");
        return tops;
    }, [&](auto const & tops, auto const & higgs) {
        Duodecuplet633 duodecuplet;
        INFO("duodecuplet");
        duodecuplet.SetMultiplets23(tops, higgs);
        wimpmass::Mt2 mt2;
        INFO("mt2");
        duodecuplet.SetExtraInfo(mt2.Get(
            duodecuplet.Sextet().Quartet().Doublet2().Singlet1().LorentzVector(),
            duodecuplet.Triplet2().Doublet().Singlet1().LorentzVector(),
            event.MissingEt().LorentzVector()) / GeV);
        INFO("mt2", duodecuplet.ExtraInfo());
        if (duodecuplet.Overlap()) throw Overlap();
        INFO("duodecuplet non-overlapping");
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



