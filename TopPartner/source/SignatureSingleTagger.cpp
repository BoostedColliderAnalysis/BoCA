#include "SignatureSingleTagger.hh"
#include "Event.hh"
#include "Debug.hh"

namespace analysis
{

namespace toppartner
{

SignatureSingleTagger::SignatureSingleTagger()
{
    Info();
    DefineVariables();
}

int SignatureSingleTagger::Train(const Event& event, const PreCuts&, Tag tag) const
{
    Info();
    return SaveEntries(Decuplets(event, [&](Decuplet82 & decuplet) {
        decuplet.SetTag(tag);
        return decuplet;
    }));
}

std::vector<Decuplet82> SignatureSingleTagger::Multiplets(const Event& event, const analysis::PreCuts&, const TMVA::Reader& reader) const
{
    Info();
    return ReduceResult(Decuplets(event, [&](Decuplet82 & decuplet) {
        decuplet.SetBdt(Bdt(decuplet, reader));
        return decuplet;
    }));
}

std::vector<Decuplet82> SignatureSingleTagger::Decuplets(const analysis::Event& event, const std::function< Decuplet82(Decuplet82&)>& function) const
{
    return pairs(pair_reader_.Multiplets(event), higgs_reader_.Multiplets(event), [&](const Octet53 & octet, const Doublet & doublet) {
        Decuplet82 decuplet(octet, doublet);
        if (decuplet.Overlap()) throw "overlap";
        return function(decuplet);
    });
}

}

}
