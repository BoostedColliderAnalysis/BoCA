#include "SignatureSingleTagger.hh"
#include "Event.hh"
#include "Debug.hh"

namespace boca
{

namespace naturalness
{

SignatureSingleTagger::SignatureSingleTagger()
{
    Info();
    DefineVariables();
}

int SignatureSingleTagger::Train(Event const& event, PreCuts const&, Tag tag) const
{
    Info();
    return SaveEntries(Decuplets(event, [&](Decuplet532 & decuplet) {
        decuplet.SetTag(tag);
        return decuplet;
    }));
}

std::vector<Decuplet532> SignatureSingleTagger::Multiplets(Event const& event, boca::PreCuts const&, TMVA::Reader const& reader) const
{
    Info();
    return ReduceResult(Decuplets(event, [&](Decuplet532 & decuplet) {
        decuplet.SetBdt(Bdt(decuplet, reader));
        return decuplet;
    }));
}

std::vector<Decuplet532> SignatureSingleTagger::Decuplets(boca::Event const& event, std::function< Decuplet532(Decuplet532&)> const& function) const
{
    return triples(partner_reader_.Multiplets(event) , top_reader_.Multiplets(event), higgs_reader_.Multiplets(event), [&](Quintet const & quintet, Triplet const & triplet, Doublet const & doublet) {
        Decuplet532 decuplet(quintet, triplet, doublet);
        if (decuplet.Overlap()) throw "overlap";
        decuplet.SetVetoBdt(veto_reader_.Bdt(Quintet(decuplet.Triplet(), decuplet.Doublet())));
        return function(decuplet);
    });
}

}

}
