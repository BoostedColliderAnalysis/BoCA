# include "HiggsTagger.hh"

analysis::HiggsTagger::HiggsTagger()
{
    //         DebugLevel = analysis::Object::kDetailed;
    Print(kNotification, "Constructor");
    set_tagger_name("HeavyHiggsSemi");
    bottom_reader_.set_tagger(bottom_tagger_);
    DefineVariables();
}

void analysis::HiggsTagger::DefineVariables()
{
    Print(kNotification , "Define Variables");
    AddVariable(branch_.Mass, "Mass");
    AddVariable(branch_.Rap, "Rap");
    AddVariable(branch_.Phi, "Phi");
    AddVariable(branch_.Pt, "Pt");
    AddVariable(branch_.Ht, "Ht");

    AddVariable(branch_.DeltaPt, "DeltaPt");
    AddVariable(branch_.DeltaM, "DeltaM");
//     AddVariable(branch_.DeltaHt, "DeltaHt");
    AddVariable(branch_.DeltaR, "DeltaR");
    AddVariable(branch_.DeltaRap, "DeltaRap");
    AddVariable(branch_.DeltaPhi, "DeltaPhi");

    AddVariable(branch_.Bdt, "Bdt");
    AddSpectator(branch_.Tag, "Tag");
}

int analysis::HiggsTagger::Train(analysis::Event &event,  analysis::PreCuts &pre_cuts, const Tag tag)
{
    Print(kInformation, "Higgs Tags");

    Jets jets =  bottom_reader_.Multiplets<BottomTagger>(event);

    std::vector< analysis::Doublet > doublets;
    for (auto jet_1 = jets.begin(); jet_1 != jets.end(); ++jet_1) {
        for (auto jet_2 = jet_1 + 1; jet_2 != jets.end(); ++jet_2) {
            analysis::Doublet doublet(*jet_1, *jet_2);
            if (doublet.overlap()) continue;
            doublet.SetTag(tag);
            doublets.emplace_back(doublet);
        }
    }
    return SaveEntries<HiggsBranch>(doublets);
}

std::vector<analysis::Doublet>  analysis::HiggsTagger::Multiplets(analysis::Event &event, const TMVA::Reader &reader)
{
  Jets jets =  bottom_reader_.Multiplets<BottomTagger>(event);

    std::vector< analysis::Doublet > doublets;
    for (auto jet_1 = jets.begin(); jet_1 != jets.end(); ++jet_1) {
        for (auto jet_2 = jet_1 + 1; jet_2 != jets.end(); ++jet_2) {
            analysis::Doublet doublet(*jet_1, *jet_2);
            if (doublet.overlap()) continue;
            branch_ = branch<HiggsBranch>(doublet);
            doublet.SetBdt(Bdt(reader));
            doublets.emplace_back(doublet);
        }
    }
    return ReduceResult(doublets);
}
