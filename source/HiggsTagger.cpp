# include "HiggsTagger.hh"

namespace analysis {

HiggsTagger::HiggsTagger()
{
    //         DebugLevel = Object::kDetailed;
    Print(kNotification, "Constructor");
    set_tagger_name("Higgs");
    bottom_reader_.set_tagger(bottom_tagger_);
    DefineVariables();
}

void HiggsTagger::DefineVariables()
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

    AddVariable(branch_.Bdt1, "Bdt1");
    AddVariable(branch_.Bdt2, "Bdt2");
    AddSpectator(branch_.Tag, "Tag");
}

int HiggsTagger::Train(Event &event, PreCuts &pre_cuts, const Tag tag)
{
    Print(kInformation, "Higgs Tag");
    Jets jets =  bottom_reader_.Multiplets<BottomTagger>(event);
    std::vector< Doublet > doublets;
    for (auto jet_1 = jets.begin(); jet_1 != jets.end(); ++jet_1) {
        for (auto jet_2 = jet_1 + 1; jet_2 != jets.end(); ++jet_2) {
            Doublet doublet(*jet_1, *jet_2);
            if (doublet.Overlap()) continue;
//             if (tag == kSignal) std::abs(doublet.Jet().m() - Mass(HiggsId)) > 50) continue;
            doublet.SetTag(tag);
            doublets.emplace_back(doublet);
        }
    }
    Jets particles = event.Partons().GenParticles();
    Jets tops = copy_if_abs_particle(particles, HiggsId, CpvHiggsId);
    switch (tag) {
    case kSignal :
        doublets = BestMatch(doublets, tops);
        break;
    case kBackground  :
        doublets = RemoveBestMatch(doublets, tops);
        break;
    }
    return SaveEntries(doublets);
}

std::vector<Doublet>  HiggsTagger::Multiplets(Event &event, PreCuts &pre_cuts, const TMVA::Reader &reader)
{
    Print(kInformation, "Higgs Bdt");
    Jets jets =  bottom_reader_.Multiplets<BottomTagger>(event);
    std::vector< Doublet > doublets;
    for (auto jet_1 = jets.begin(); jet_1 != jets.end(); ++jet_1) {
        for (auto jet_2 = jet_1 + 1; jet_2 != jets.end(); ++jet_2) {
            Doublet doublet(*jet_1, *jet_2);
            if (doublet.Overlap()) continue;
            branch_ = branch(doublet);
            doublet.SetBdt(Bdt(reader));
            doublets.emplace_back(doublet);
        }
    }
    return ReduceResult(doublets);
}

}
