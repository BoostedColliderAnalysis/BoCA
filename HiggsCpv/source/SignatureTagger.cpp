#include "../include/SignatureTagger.hh"
#include "Event.hh"
#include "Debug.hh"

namespace analysis {

namespace higgscpv {

SignatureTagger::SignatureTagger()
{
    Note();
    DefineVariables();
}

int SignatureTagger::Train(const Event& event, const analysis::PreCuts&, const analysis::Tag tag) const
{
    Info();
    std::vector<Sextet> sextets = triplet_pair_reader_.tagger().TruthLevel(event,triplet_pair_reader_.Multiplets(event),tag);
    Debug(sextets.size());
    std::vector<Doublet> doublets = higgs_reader_.Multiplets(event);
    Jets higgses = CopyIfParticles(event.Partons().GenParticles(), Id::higgs, Id::CP_violating_higgs);
    std::vector<Doublet> final_doublets = BestMatches(doublets,higgses,tag);
    Debug(final_doublets.size());
    std::vector<Octet62> octets;
    for (const auto& doublet : final_doublets) {
        for (const auto& sextet : sextets) {
            Octet62 octet(sextet, doublet);
            if (octet.Overlap()) continue;
            octet.SetTag(tag);
            octets.emplace_back(octet);
        }
    }
//     if (tag == Tag::signal && octets.size() != 1)
Debug(octets.size());
    if (tag == Tag::signal) octets = ReduceResult(octets, 1);
    return SaveEntries(octets);
}

std::vector<Octet62> SignatureTagger::Multiplets(const Event& event, const PreCuts&, const TMVA::Reader& reader) const
{
    Info();
    std::vector<Doublet> doublets = higgs_reader_.Multiplets(event);
    Info(doublets.size());
    std::vector<Sextet> sextets = triplet_pair_reader_.Multiplets(event);
    Info(sextets.size());
    std::vector<Octet62> octets;
    for (const auto& doublet : doublets) {
        for (const auto& sextet : sextets) {
            Octet62 octet(sextet, doublet);
            if (octet.Overlap()) continue;
            octet.SetBdt(Bdt(octet, reader));
            octets.emplace_back(octet);
        }
    }
    return ReduceResult(octets);
}

}

}
