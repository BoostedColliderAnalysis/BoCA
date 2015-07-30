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
    std::vector<Decuplet82> decuplets = pairs(pair_reader_.Multiplets(event), higgs_reader_.Multiplets(event), [tag](const Octet53 & octet, const Doublet & doublet) {
        Decuplet82 decuplet(octet, doublet);
        if (decuplet.Overlap()) throw "overlap";
        decuplet.SetTag(tag);
        return decuplet;
    });
    return SaveEntries(decuplets);
}

std::vector<Decuplet82> SignatureSingleTagger::Multiplets(const Event& event, const analysis::PreCuts&, const TMVA::Reader& reader) const
{
    Info();
    std::vector<Decuplet82> decuplets = pairs(pair_reader_.Multiplets(event), higgs_reader_.Multiplets(event), [&](const Octet53 & octet, const Doublet & doublet){
            Decuplet82 decuplet(octet, doublet);
            if (decuplet.Overlap()) throw "overlap";
            decuplet.SetBdt(Bdt(decuplet, reader));
            return decuplet;
        });
    return ReduceResult(decuplets);
}

}

}
