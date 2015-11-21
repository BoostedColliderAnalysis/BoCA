#include "../include/SignatureTagger.hh"
#include "Event.hh"
#include "Debug.hh"

namespace boca {

namespace higgscpv {

int SignatureTagger::Train(Event const& event, boca::PreCuts const&, Tag tag) const
{
    Info0;
    std::vector<Sextet> sextets = triplet_pair_reader_.Tagger().TruthLevel(event,triplet_pair_reader_.Multiplets(event),tag);
    Debug(sextets.size());
    std::vector<Doublet> doublets = higgs_reader_.Multiplets(event);
   std::vector<Jet> higgses = CopyIfParticles(event.Partons().GenParticles(), Id::higgs, Id::CP_violating_higgs);
    std::vector<Doublet> final_doublets = BestMatches(doublets,higgses,tag);
    Debug(final_doublets.size());
    std::vector<MultipletSignature<Octet62>> octets;
    for (auto const& doublet : final_doublets) {
        for (auto const& sextet : sextets) {
            Octet62 octet(sextet, doublet);
            if (octet.Overlap()) continue;
            octet.SetTag(tag);
            octets.emplace_back(MultipletSignature<Octet62>(octet));
        }
    }
//     if (tag == Tag::signal && octets.size() != 1)
    Debug(octets.size());
    if (tag == Tag::signal) octets = ReduceResult(octets, 1);
    return SaveEntries(octets);
}

std::vector<MultipletSignature<Octet62>> SignatureTagger::Multiplets(Event const& event, PreCuts const&, TMVA::Reader const& reader) const
{
    Info0;
    std::vector<Doublet> doublets = higgs_reader_.Multiplets(event);
    INFO(doublets.size());
    std::vector<Sextet> sextets = triplet_pair_reader_.Multiplets(event);
    INFO(sextets.size());
    std::vector<MultipletSignature<Octet62>> octets;
    for (auto const& doublet : doublets) {
        for (auto const& sextet : sextets) {
            Octet62 octet(sextet, doublet);
            if (octet.Overlap()) continue;
            MultipletSignature<Octet62> octet_signature(octet);
            octet_signature.SetBdt(Bdt(octet_signature, reader));
            octets.emplace_back(octet_signature);
        }
    }
    return ReduceResult(octets);
}
std::string SignatureTagger::Name() const
{
    return "Signature";
}

}

}
