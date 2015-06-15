# include "TopPartnerPairTagger.hh"

namespace toppartner
{

TopPartnerPairTagger::TopPartnerPairTagger()
{
//         DebugLevel = analysis::Object::kDetailed;
    Print(kNotification, "Constructor");
    set_tagger_name("TopPartnerPairTagger");
    top_partner_hadronic_reader_.set_tagger(top_partner_hadronic_tagger_);
    top_partner_semi_reader_.set_tagger(top_partner_semi_tagger_);
    DefineVariables();
}

void TopPartnerPairTagger::DefineVariables()
{
    Print(kNotification , "Define Variables");
    AddVariable(branch().Mass, "Mass");
    AddVariable(branch().Rap, "Rap");
    AddVariable(branch().Phi, "Phi");
    AddVariable(branch().Pt, "Pt");
    AddVariable(branch().Ht, "Ht");
    AddVariable(branch().DeltaPt, "DeltaPt");
    AddVariable(branch().DeltaM, "DeltaM");
    AddVariable(branch().DeltaHt, "DeltaHt");
    AddVariable(branch().DeltaR, "DeltaR");
    AddVariable(branch().DeltaRap, "DeltaRap");
    AddVariable(branch().DeltaPhi, "DeltaPhi");
    AddVariable(branch().Rho, "Rho");
    AddVariable(branch().Bdt, "Bdt");
    AddSpectator(branch().Tag, "Tag");
}

int TopPartnerPairTagger::Train(analysis::Event &event, analysis::PreCuts &pre_cuts, const Tag tag)
{
    Print(kInformation, "Higgs Tags");
    std::vector< analysis::Quintet> quintets_1 = top_partner_hadronic_reader_.Multiplets<TopPartnerHadronicTagger>(event);
    std::vector< analysis::Quintet> quintets_2 = top_partner_semi_reader_.Multiplets<TopPartnerSemiTagger>(event);
    std::vector< Decuplet > decuplets;
    for (const auto quintet_1 :  quintets_1) {
        for (const auto quintet_2 : quintets_2) {
            Decuplet decuplet(quintet_1, quintet_2);
            if (decuplet.Overlap()) continue;
            decuplet.SetTag(tag);
            decuplets.emplace_back(decuplet);
        }

    }
    return SaveEntries(decuplets);
}

std::vector<Decuplet> TopPartnerPairTagger::Multiplets(analysis::Event &event, const TMVA::Reader &reader)
{
  std::vector< analysis::Quintet> quintets_1 = top_partner_hadronic_reader_.Multiplets<TopPartnerHadronicTagger>(event);
  std::vector< analysis::Quintet> quintets_2 = top_partner_semi_reader_.Multiplets<TopPartnerSemiTagger>(event);
    std::vector< Decuplet > decuplets;
    for (const auto quintet_1 :  quintets_1) {
      for (const auto quintet_2 : quintets_2) {
            Decuplet decuplet(quintet_1, quintet_2);
            if (decuplet.Overlap()) continue;
            decuplet.SetBdt(Bdt(decuplet,reader));
            decuplets.emplace_back(decuplet);
        }
    }
    return ReduceResult(decuplets);
}

}
