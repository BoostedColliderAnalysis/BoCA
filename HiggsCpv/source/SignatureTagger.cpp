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

int SignatureTagger::Train(const Event& event, analysis::PreCuts&, const analysis::Tag tag) const
{
    Info();
    std::vector<Sextet> sextets = triplet_pair_reader_.Multiplets(event);
    if (sextets.empty()) return 0;
    std::vector<Doublet> doublets = higgs_reader_.Multiplets(event);
    if (doublets.empty()) Info("No doublets", doublets.size());
    std::vector<Doublet> final_doublets;
    switch (tag) {
    case Tag::signal : {
        Jets higgs = event.Partons().GenParticles();
        Jets even = CopyIfParticle(higgs, Id::higgs);
        Jets odd = CopyIfParticle(higgs, Id::CP_violating_higgs);
        higgs = Join(even, odd);
        final_doublets = CopyIfClose(doublets, higgs);
        break;
    }
    case Tag::background :
        final_doublets = doublets;
        break;
    }
    if (final_doublets.empty()) return 0;
    std::vector<Octet62> octets;
    for (const auto& doublet : final_doublets) {
        for (const auto& sextet : sextets) {
            Octet62 octet(sextet, doublet);
            if (octet.Overlap()) continue;
            octet.SetTag(tag);
            octets.emplace_back(octet);
        }
    }
    if (octets.empty()) Info("No octets", octets.size());
    if (tag == Tag::signal) octets = ReduceResult(octets, 1);
    return SaveEntries(octets);
}

std::vector<Octet62> SignatureTagger::Multiplets(const Event& event, PreCuts&, const TMVA::Reader& reader) const
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
