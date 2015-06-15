# include "TopPartnerSemiTagger.hh"

namespace toppartner
{

TopPartnerSemiTagger::TopPartnerSemiTagger()
{
//         DebugLevel = analysis::Object::kDetailed;
    Print(kNotification, "Constructor");
    set_tagger_name("HeavyHiggsSemi");
    top_reader_.set_tagger(top_tagger_);
    z_hadronic_reader_.set_tagger(z_hadronic_tagger);
    DefineVariables();
}

void TopPartnerSemiTagger::DefineVariables()
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

int TopPartnerSemiTagger::Train(analysis::Event &event, analysis::PreCuts &pre_cuts, const Tag tag)
{
    Print(kInformation, "Higgs Tags");
    std::vector< analysis::Triplet> triplets = top_reader_.Multiplets<analysis::TopSemiTagger>(event);
    std::vector< analysis::Doublet> doublets = z_hadronic_reader_.Multiplets<analysis::ZHadronicTagger>(event);
    std::vector< analysis::Quintet > quintets;
    for (const auto & doublet : doublets)
        for (const auto & triplet : triplets) {
            analysis::Quintet quintet(triplet, doublet);
            if (quintet.Overlap()) continue;
            quintet.SetTag(tag);
            quintets.emplace_back(quintet);
        }
    return SaveEntries(quintets);
}

std::vector<analysis::Quintet> TopPartnerSemiTagger::Multiplets(analysis::Event &event, const TMVA::Reader &reader)
{
    std::vector< analysis::Triplet> triplets = top_reader_.Multiplets<analysis::TopSemiTagger>(event);
    std::vector< analysis::Doublet> doublets = z_hadronic_reader_.Multiplets<analysis::ZHadronicTagger>(event);
    std::vector< analysis::Quintet > quintets;
    for (const auto & doublet : doublets)
        for (const auto & triplet : triplets) {
            analysis::Quintet quintet(triplet, doublet);
            if (quintet.Overlap()) continue;
            quintet.SetBdt(Bdt(quintet,reader));
            quintets.emplace_back(quintet);
        }
    return ReduceResult(quintets);
}

}
