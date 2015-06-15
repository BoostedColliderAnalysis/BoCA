# include "HiggsPairTagger.hh"

namespace toppartner
{

HiggsPairTagger::HiggsPairTagger()
{
//         DebugLevel = analysis::Object::kDetailed;
    Print(kNotification, "Constructor");
    set_tagger_name("HiggsPairPair");
    higgs_reader_.set_tagger(higgs_tagger_);
    DefineVariables();
}

void HiggsPairTagger::DefineVariables()
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

int HiggsPairTagger::Train(analysis::Event &event,  analysis::PreCuts &pre_cuts, const Tag tag)
{
    Print(kInformation, "Higgs Tags");
    std::vector< analysis::Doublet> doublets = higgs_reader_.Multiplets<analysis::HiggsTagger>(event);
    std::vector< analysis::Quartet22 > quartets;
    for (auto doublet_1 = doublets.begin(); doublet_1 != doublets.end(); ++doublet_1) {
        for (auto doublet_2 = doublet_1 + 1; doublet_2 != doublets.end(); ++doublet_2) {
            analysis::Quartet22 quartet(*doublet_1, *doublet_2);
            if (quartet.Overlap()) continue;
            quartet.SetTag(tag);
            quartets.emplace_back(quartet);
        }

    }
    return SaveEntries(quartets);
}

std::vector<analysis::Quartet22> HiggsPairTagger::Multiplets(analysis::Event &event, const TMVA::Reader &reader)
{
    std::vector< analysis::Doublet> doublets = higgs_reader_.Multiplets<analysis::HiggsTagger>(event);
    std::vector< analysis::Quartet22 > quartets;
    for (auto doublet_1 = doublets.begin(); doublet_1 != doublets.end(); ++doublet_1) {
        for (auto doublet_2 = doublet_1 + 1; doublet_2 != doublets.end(); ++doublet_2) {
            analysis::Quartet22 quartet(*doublet_1, *doublet_2);
            if (quartet.Overlap()) continue;
            quartet.SetBdt(Bdt(quartet,reader));
            quartets.emplace_back(quartet);
        }
    }
    return ReduceResult(quartets);
}

}
