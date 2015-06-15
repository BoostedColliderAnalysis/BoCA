# include "../include/SignatureTagger.hh"

namespace toppartner {

SignatureTagger::SignatureTagger()
{
//         DebugLevel = analysis::Object::kDetailed;
    Print(kNotification, "Constructor");
    set_tagger_name("HeavyHiggsSemi");
    top_partner_pair_reader_.set_tagger(top_partner_pair_tagger_);
    higgs_pair_reader_.set_tagger(higgs_pair_tagger);
    DefineVariables();
}

void SignatureTagger::DefineVariables()
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

int SignatureTagger::Train(analysis::Event &event, analysis::PreCuts &pre_cuts, const Tag tag)
{
    Print(kInformation, "Higgs Tags");
    std::vector< Decuplet> decuplets = top_partner_pair_reader_.Multiplets<TopPartnerPairTagger>(event);
    std::vector< analysis::Quartet22> quartets = higgs_pair_reader_.Multiplets<HiggsPairTagger>(event);
    std::vector< Quattuordecuplet > quattuordecuplets;
    for (const auto decuplet : decuplets) {
        for (const auto quartet : quartets) {
            Quattuordecuplet quattuordecuplet(decuplet, quartet);
            if (quattuordecuplet.Overlap()) continue;
            quattuordecuplet.SetTag(tag);
            quattuordecuplets.emplace_back(quattuordecuplet);
        }
    }
    return SaveEntries(quattuordecuplets);
}

std::vector< Quattuordecuplet > SignatureTagger::Multiplets(analysis::Event &event, const TMVA::Reader &reader)
{
    std::vector< Decuplet> decuplets = top_partner_pair_reader_.Multiplets<TopPartnerPairTagger>(event);
    std::vector< analysis::Quartet22> quartets = higgs_pair_reader_.Multiplets<HiggsPairTagger>(event);
    std::vector< Quattuordecuplet > quattuordecuplets;
    for (const auto decuplet : decuplets) {
        for (const auto quartet : quartets) {
            Quattuordecuplet quattuordecuplet(decuplet, quartet);
            if (quattuordecuplet.Overlap()) continue;
            if (quattuordecuplet.Overlap()) continue;
            quattuordecuplet.SetBdt(Bdt(quattuordecuplet,reader));
            quattuordecuplets.emplace_back(quattuordecuplet);
        }
    }
    return ReduceResult(quattuordecuplets);
}

}
