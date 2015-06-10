# include "../include/SignatureTagger.hh"

toppartner::SignatureTagger::SignatureTagger()
{
//         DebugLevel = analysis::Object::kDetailed;
    Print(kNotification, "Constructor");
    set_tagger_name("HeavyHiggsSemi");
    top_partner_reader_.set_tagger(top_partner_tagger_);
    higgs_reader_.set_tagger(higgs_tagger);
    DefineVariables();
}

void toppartner::SignatureTagger::DefineVariables()
{
    Print(kNotification , "Define Variables");
    AddVariable(branch_.Mass, "Mass");
    AddVariable(branch_.Rap, "Rap");
    AddVariable(branch_.Phi, "Phi");
    AddVariable(branch_.Pt, "Pt");
    AddVariable(branch_.Ht, "Ht");

    AddVariable(branch_.DeltaPt, "DeltaPt");
    AddVariable(branch_.DeltaM, "DeltaM");
    AddVariable(branch_.DeltaHt, "DeltaHt");
    AddVariable(branch_.DeltaR, "DeltaR");
    AddVariable(branch_.DeltaRap, "DeltaRap");
    AddVariable(branch_.DeltaPhi, "DeltaPhi");

    AddVariable(branch_.Bdt, "Bdt");
    AddSpectator(branch_.Tag, "Tag");
}

int toppartner::SignatureTagger::Train(analysis::Event &event, analysis::PreCuts &pre_cuts, const Tag tag)
{
    Print(kInformation, "Higgs Tags");
    std::vector< analysis::Quintet> quintets = top_partner_reader_.Multiplets<TopPartnerTagger>(event);
    std::vector< analysis::Doublet> doublets = higgs_reader_.Multiplets<analysis::HiggsTagger>(event);
    std::vector< Quattuordecuplet > quattuordecuplets;
    for (auto quintet_1 = quintets.begin(); quintet_1 != quintets.end(); ++quintet_1) {
        for (auto quintet_2 = quintet_1 + 1; quintet_2 != quintets.end(); ++quintet_2) {
            for (auto doublet_1 = doublets.begin(); doublet_1 != doublets.end(); ++doublet_1) {
                for (auto doublet_2 = doublet_1 + 1; doublet_2 != doublets.end(); ++doublet_2) {
// // // // //                   analysis::Quartet22 quartet(*doublet_1, *doublet_2);
// // // // //                   Decuplet  decuplet(*quintet_1, *quintet_2);
                  analysis::Quartet22 quartet(*doublet_1, *doublet_2);
                  Decuplet  decuplet(*quintet_1, *quintet_2);
                  Quattuordecuplet quattuordecuplet(decuplet,quartet);

                    if (quattuordecuplet.overlap()) continue;
                    quattuordecuplet.SetTag(tag);
                    quattuordecuplets.emplace_back(quattuordecuplet);
                }
            }
        }
    }
    return SaveEntries<SignatureBranch>(quattuordecuplets);
}

std::vector< toppartner::Quattuordecuplet > toppartner::SignatureTagger::Quintets(analysis::Event &event, const TMVA::Reader &reader)
{
    std::vector< analysis::Quintet> quintets = top_partner_reader_.Multiplets<TopPartnerTagger>(event);
    std::vector< analysis::Doublet> doublets = higgs_reader_.Multiplets<analysis::HiggsTagger>(event);
    std::vector< Quattuordecuplet > quattuordecuplets;
    for (auto quintet_1 = quintets.begin(); quintet_1 != quintets.end(); ++quintet_1) {
        for (auto quintet_2 = quintet_1 + 1; quintet_2 != quintets.end(); ++quintet_2) {
            for (auto doublet_1 = doublets.begin(); doublet_1 != doublets.end(); ++doublet_1) {
                for (auto doublet_2 = doublet_1 + 1; doublet_2 != doublets.end(); ++doublet_2) {
                  analysis::Quartet22 quartet(*doublet_1, *doublet_2);
                  Decuplet  decuplet(*quintet_1, *quintet_2);
                  Quattuordecuplet quattuordecuplet(decuplet,quartet);

//                     Quattuordecuplet quattuordecuplet(*quintet_1, *quintet_2, *doublet_1, *doublet_2);
                    if (quattuordecuplet.overlap()) continue;
                    branch_ = branch<SignatureBranch>(quattuordecuplet);
                    quattuordecuplet.SetBdt(Bdt(reader));
                    quattuordecuplets.emplace_back(quattuordecuplet);
                }
            }
        }
    }
    return ReduceResult(quattuordecuplets);
}


