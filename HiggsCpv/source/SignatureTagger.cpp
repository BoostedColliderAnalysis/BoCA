# include "../include/SignatureTagger.hh"

namespace analysis
{

namespace higgscpv
{

SignatureTagger::SignatureTagger()
{
//    debug_level_ = Severity::Debug;
    Print(Severity::Notification , "Constructor");
    set_tagger_name("Signature");
    higgs_reader_.SetTagger(higgs_tagger_);
    triplet_pair_reader_.SetTagger(triplet_pair_tagger_);
    DefineVariables();
}

int SignatureTagger::Train(Event &event, PreCuts &, const Tag tag)
{
    Print(Severity::Information, "Train");
    std::vector<Sextet> sextets = triplet_pair_reader_.Multiplets<TopLeptonicPairTagger>(event);
    if (sextets.empty()) {
        Print(Severity::Information, "No sextets", sextets.size());
        return 0;
    }

    std::vector<Doublet> doublets = higgs_reader_.Multiplets<HiggsTagger>(event);
    if (doublets.empty()) Print(Severity::Information, "No doublets", doublets.size());

    std::vector<Doublet> final_doublets;
    switch (tag) {
    case Tag::Signal : {
        Jets HiggsParticles = event.Partons().GenParticles();
        Jets Even = copy_if_abs_particle(HiggsParticles, Id::Higgs);
        Jets Odd = copy_if_abs_particle(HiggsParticles, Id::CpvHiggs);
        HiggsParticles = Join(Even, Odd);
        final_doublets = CopyIfClose(doublets, HiggsParticles);
        break;
    }
    case Tag::Background :
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
    if (octets.empty()) Print(Severity::Information, "No octets", octets.size());

    if (tag == Tag::Signal) octets = ReduceResult(octets, 1);
    return SaveEntries(octets);
}


std::vector< Octet62 > SignatureTagger::Multiplets(Event &event, PreCuts &, const TMVA::Reader &reader)
{
    Print(Severity::Information, "Multiplets");
    std::vector<Doublet> doublets = higgs_reader_.Multiplets<HiggsTagger>(event);
    Print(Severity::Information, "Doublets", doublets.size());
    std::vector<Sextet> sextets = triplet_pair_reader_.Multiplets<TopLeptonicPairTagger>(event);
    Print(Severity::Information, "Sextets", sextets.size());
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
