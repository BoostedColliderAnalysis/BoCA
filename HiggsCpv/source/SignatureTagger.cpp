#include "../include/SignatureTagger.hh"
#include "Event.hh"
#include "Debug.hh"

namespace analysis
{

namespace higgscpv
{

SignatureTagger::SignatureTagger()
{
    Note();
    DefineVariables();
}

int SignatureTagger::Train(const Event &event, analysis::PreCuts &, const analysis::Tag tag) const
{
    Info("Train");
    std::vector<Sextet> sextets = triplet_pair_reader_.Multiplets(event);
    if (sextets.empty()) {
        Info("No sextets", sextets.size());
        return 0;
    }

    std::vector<Doublet> doublets = higgs_reader_.Multiplets(event);
    if (doublets.empty()) Info("No doublets", doublets.size());

    std::vector<Doublet> final_doublets;
    switch (tag) {
    case Tag::signal : {
        Jets HiggsParticles = event.Partons().GenParticles();
        Jets Even = copy_if_abs_particle(HiggsParticles, Id::higgs);
        Jets Odd = copy_if_abs_particle(HiggsParticles, Id::CP_violating_higgs);
        HiggsParticles = Join(Even, Odd);
        final_doublets = CopyIfClose(doublets, HiggsParticles);
        break;
    }
    case Tag::background :
        final_doublets = doublets;
        break;
    }
    if (final_doublets.empty()) return 0;

    std::vector<Octet62> octets;
    for (const auto & doublet : final_doublets) {
        for (const auto & sextet : sextets) {
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


std::vector< Octet62 > SignatureTagger::Multiplets(const Event &event, PreCuts &, const TMVA::Reader &reader) const
{
    Info("Multiplets");
    std::vector<Doublet> doublets = higgs_reader_.Multiplets(event);
    Info("Doublets", doublets.size());
    std::vector<Sextet> sextets = triplet_pair_reader_.Multiplets(event);
    Info("Sextets", sextets.size());
    std::vector<Octet62> octets;
    for (const auto & doublet : doublets) {
        for (const auto & sextet : sextets) {
            Octet62 octet(sextet, doublet);
            if (octet.Overlap()) continue;
            octet.SetBdt(Bdt(octet,reader));
            octets.emplace_back(octet);
        }
    }
    return ReduceResult(octets);
}

}

}
