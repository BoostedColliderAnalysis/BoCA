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

int SignatureSingleTagger::Train(Event const& event, PreCuts const&, Tag tag) const
{
    Info();
    return SaveEntries(Decuplets(event, [&](Decuplet82 & decuplet) {
        decuplet.SetTag(tag);
        return decuplet;
    }));
}

std::vector<Decuplet82> SignatureSingleTagger::Multiplets(Event const& event, analysis::PreCuts const&, TMVA::Reader const& reader) const
{
    Info();
    return ReduceResult(Decuplets(event, [&](Decuplet82 & decuplet) {
        decuplet.SetBdt(Bdt(decuplet, reader));
        return decuplet;
    }));
}

std::vector<Decuplet82> SignatureSingleTagger::Decuplets(analysis::Event const& event, const std::function< Decuplet82(Decuplet82&)>& function) const
{
    return pairs(pair_reader_.Multiplets(event), higgs_reader_.Multiplets(event), [&](const Octet53 & octet, Doublet const& doublet) {
        Decuplet82 decuplet(octet, doublet);
        if (decuplet.Overlap()) throw "overlap";
        return function(decuplet);
    });
}

}

}
