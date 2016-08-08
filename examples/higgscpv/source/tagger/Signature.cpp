#include "boca/multiplets/Particles.hh"
#include "boca/Event.hh"

#include "include/tagger/Signature.hh"

#include "boca/generic/DEBUG.hh"

namespace higgscpv {

namespace tagger {

int Signature::Train(boca::Event const& event, boca::PreCuts const&, Tag tag)
{
    INFO0;
    std::vector<Sextet> sextets = triplet_pair_reader_.Tagger().Truth(event, triplet_pair_reader_.Multiplets(event), tag);
    DEBUG(sextets.size());
    std::vector<Doublet> doublets = higgs_reader_.Multiplets(event);
    std::vector<Particle> higgses = CopyIfParticles(event.GenParticles(), {Id::higgs, Id::CP_violating_higgs});
    std::vector<Doublet> final_doublets = BestMatches(doublets,higgses,tag);
    DEBUG(final_doublets.size());
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
    DEBUG(octets.size());
    return SaveEntries(octets, tag);
}

std::vector<MultipletSignature<Octet62>> Signature::Multiplets(boca::Event const& event, PreCuts const&, TMVA::Reader const& reader)
{
    INFO0;
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
    return octets;
}
std::string Signature::Name() const
{
    return "Signature";
}

}

}
