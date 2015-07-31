#include "../include/SignatureTTagger.hh"
#include "Event.hh"
#include "Debug.hh"

namespace analysis {

namespace higgscpv {

SignatureTTagger::SignatureTTagger()
{
  Info();
    DefineVariables();
}

int SignatureTTagger::Train(const Event& event, const analysis::PreCuts&, Tag tag) const
{
    Info();
    Jets particles = event.Partons().GenParticles();
    std::vector<Triplet> triplets = top_tagger_.Multiplets(event);
    Jets tops = CopyIfParticle(particles, Id::top);
    std::vector<Triplet> final_triplets = BestMatches(triplets,tops,tag);
    Debug(final_triplets.size());

    std::vector<Doublet> doublets = higgs_reader_.Multiplets(event);
    Jets higgses = CopyIfParticles(particles, Id::higgs, Id::CP_violating_higgs);
    std::vector<Doublet> final_doublets = BestMatches(doublets,higgses,tag);
    Debug(final_doublets.size());

    std::vector<MultipletSignature<Octet332>> octets = triples(final_triplets,final_doublets,[&](const auto& triplet_1, const auto& triplet_2, const auto& doublet){
            Octet332 octet(triplet_1, triplet_2, doublet);
            Debug("octet");
            if (octet.Overlap()) throw "overlap";
            octet.SetTag(tag);
            return MultipletSignature<Octet332>(octet);
        });
    Debug(octets.size());
    if (tag == Tag::signal) octets = ReduceResult(octets, 1);
    Debug(octets.size());
    return  SaveEntries(octets);
}

std::vector<MultipletSignature<Octet332>> SignatureTTagger::Multiplets(const Event& event, const PreCuts&, const TMVA::Reader& reader) const
{
    Info();
    std::vector<Doublet> doublets = higgs_reader_.Multiplets(event);
    Info(doublets.size());
    std::vector<Triplet> triplets = top_tagger_.Multiplets(event);
    Info(triplets.size());
    std::vector<MultipletSignature<Octet332>> octets = triples(triplets, doublets,[&](const auto& triplet_1, const auto& triplet_2, const auto& doublet) {
            Octet332 octet(triplet_1, triplet_2, doublet);
            if (octet.Overlap()) throw "overlap";
            MultipletSignature<Octet332> octet_signature(octet);
            octet_signature.SetBdt(Bdt(octet_signature, reader));
            return octet_signature;
    });
    return ReduceResult(octets);
}

}

}
