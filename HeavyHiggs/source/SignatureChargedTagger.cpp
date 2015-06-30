#include "SignatureChargedTagger.hh"

namespace analysis
{

namespace heavyhiggs
{

SignatureChargedTagger::SignatureChargedTagger()
{
//       DebugLevel = Severity::detailed;
    Print(Severity::information , "Constructor");
    set_tagger_name("ChargedSignatureSemi");
    DefineVariables();
}

int SignatureChargedTagger::Train(analysis::Event &event, analysis::PreCuts &pre_cuts, const analysis::Tag tag)
{
    Print(Severity::information, "event Tags");

    std::vector<Quartet31> higgs_quartets = charged_higgs_semi_reader_.Multiplets<ChargedHiggsSemiTagger>(event);

    Jets HiggsParticles = event.Partons().GenParticles();
    HiggsParticles = RemoveIfWrongAbsParticle(HiggsParticles, Id::charged_higgs);
    if (tag == Tag::signal && HiggsParticles.size() != 1) Print(Severity::error, "Where is the Higgs?");
    std::sort(higgs_quartets.begin(), higgs_quartets.end(), MinDeltaRTo(HiggsParticles.front()));
    if (tag == Tag::signal && higgs_quartets.size() > 1) higgs_quartets.erase(higgs_quartets.begin() + 1, higgs_quartets.end());

    std::vector<Quartet31> jet_quartets = triplet_jet_pair_reader_.Multiplets<TripletJetPairTagger>(event);

    std::vector<Octet44> octets;
    for (const auto higgs_quartet  : higgs_quartets)
        for (const auto & jet_quartet : jet_quartets) {
            Octet44 octet(higgs_quartet, jet_quartet);
            if (octet.Overlap()) continue;
            octet.SetTag(tag);
            octets.emplace_back(octet);
        }
    return SaveEntries(octets);
}


std::vector<Octet44> SignatureChargedTagger::Multiplets(analysis::Event &event, analysis::PreCuts &pre_cuts, const TMVA::Reader &reader)
{
    Print(Severity::information, "Bdt");

    std::vector<Quartet31> higgs_quartets = charged_higgs_semi_reader_.Multiplets<ChargedHiggsSemiTagger>(event);
    std::vector<Quartet31> jet_quartets = triplet_jet_pair_reader_.Multiplets<TripletJetPairTagger>(event);
    std::vector<Octet44> octets;
    for (const auto & jet_quartet : jet_quartets) {
        for (const auto & higgs_quartet : higgs_quartets) {
            Octet44 octet(higgs_quartet, jet_quartet);
            if (octet.Overlap()) continue;
            octet.SetBdt(Bdt(octet, reader));
            octets.emplace_back(octet);
        }
    }
    return ReduceResult(octets);
}

}

}
