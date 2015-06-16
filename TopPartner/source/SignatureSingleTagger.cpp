# include "SignatureSingleTagger.hh"

namespace analysis
{

namespace toppartner
{

SignatureSingleTagger::SignatureSingleTagger()
{
//         DebugLevel = Object::kDetailed;
    Print(kNotification, "Constructor");
    set_tagger_name("SignatureSingleTagger");
    top_partner_higgs_pair_reader_.set_tagger(top_partner_higgs_pair_tagger_);
    top_hadronic_reader_.set_tagger(top_hadronic_tagger_);
    DefineVariables();
}

int SignatureSingleTagger::Train(Event &event, PreCuts &pre_cuts, const Tag tag)
{
    Print(kInformation, "Higgs Tags");
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

std::vector<Decuplet73> SignatureSingleTagger::Multiplets(Event &event, const TMVA::Reader &reader)
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
