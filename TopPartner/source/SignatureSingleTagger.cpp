#include "SignatureSingleTagger.hh"
#include "Event.hh"
#include "Debug.hh"

namespace analysis {

namespace toppartner {

SignatureSingleTagger::SignatureSingleTagger()
{
    Note();
    DefineVariables();
}

int SignatureSingleTagger::Train(const Event& event, const PreCuts& pre_cuts,  Tag tag) const
{
    Info();
    std::vector<Octet53> octets = pair_reader_.Multiplets(event);
    std::vector<Doublet> doublets = higgs_reader_.Multiplets(event);
    std::vector<Decuplet82> decuplets;
    for (const auto& octet :  octets) {
        for (const auto& doublet : doublets) {
            Decuplet82 decuplet(octet, doublet);
            if (decuplet.Overlap()) continue;
            decuplet.SetTag(tag);
            decuplets.emplace_back(decuplet);
        }
    }
    return SaveEntries(decuplets);
}

std::vector<Decuplet82> SignatureSingleTagger::Multiplets(const Event& event, const analysis::PreCuts& pre_cuts, const TMVA::Reader& reader) const
{
    Info();
    std::vector<Octet53> octets = pair_reader_.Multiplets(event);
    std::vector<Doublet> doublets = higgs_reader_.Multiplets(event);
    std::vector<Decuplet82> decuplets;
    for (const auto& octet :  octets) {
        for (const auto& doublet : doublets) {
            Decuplet82 decuplet(octet, doublet);
            if (decuplet.Overlap()) continue;
            decuplet.SetBdt(Bdt(decuplet, reader));
            decuplets.emplace_back(decuplet);
        }
    }
    return ReduceResult(decuplets);
}

}

}
