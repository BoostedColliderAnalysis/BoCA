# include "SignatureSingleTagger.hh"

namespace analysis
{

namespace toppartner
{

SignatureSingleTagger::SignatureSingleTagger()
{
//         DebugLevel = Severity::kDetailed;
    Print(Severity::notification, "Constructor");
    set_tagger_name("SignatureSingle");
    top_partner_higgs_pair_reader_.SetTagger(top_partner_higgs_pair_tagger_);
    top_hadronic_reader_.SetTagger(top_hadronic_tagger_);
    DefineVariables();
}

int SignatureSingleTagger::Train(Event &event, PreCuts &pre_cuts, const Tag tag)
{
    Print(Severity::information, "Higgs Tags");
    std::vector< Septet> septets = top_partner_higgs_pair_reader_.Multiplets<TopPartnerHiggsPairTagger>(event);
    std::vector< Triplet> triplets = top_hadronic_reader_.Multiplets<TopHadronicTagger>(event);
    std::vector< Decuplet73 > decuplets;
    for (const auto septet :  septets) {
        for (const auto triplet : triplets) {
            Decuplet73 decuplet(septet, triplet);
            if (decuplet.Overlap()) continue;
            decuplet.SetTag(tag);
            decuplets.emplace_back(decuplet);
        }

    }
    return SaveEntries(decuplets);
}

std::vector<Decuplet73> SignatureSingleTagger::Multiplets(analysis::Event &event, analysis::PreCuts &pre_cuts, const TMVA::Reader &reader)
{
  std::vector< Septet> septets = top_partner_higgs_pair_reader_.Multiplets<TopPartnerHiggsPairTagger>(event);
  std::vector< Triplet> triplets = top_hadronic_reader_.Multiplets<TopHadronicTagger>(event);
    std::vector< Decuplet73 > decuplets;
    for (const auto septet :  septets) {
      for (const auto triplet : triplets) {
            Decuplet73 decuplet(septet, triplet);
            if (decuplet.Overlap()) continue;
            decuplet.SetBdt(Bdt(decuplet,reader));
            decuplets.emplace_back(decuplet);
        }
    }
    return ReduceResult(decuplets);
}

}

}
