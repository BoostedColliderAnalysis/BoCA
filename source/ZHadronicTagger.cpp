# include "ZHadronicTagger.hh"

namespace analysis
{

ZHadronicTagger::ZHadronicTagger()
{
    //         DebugLevel = Object::kDetailed;
    Print(kNotification, "Constructor");
    set_tagger_name("Higgs");
    bottom_reader_.set_tagger(bottom_tagger_);
    DefineVariables();
}

void ZHadronicTagger::DefineVariables()
{
    Print(kNotification , "Define Variables");
    AddVariable(branch().Mass, "Mass");
    AddVariable(branch().Rap, "Rap");
    AddVariable(branch().Phi, "Phi");
    AddVariable(branch().Pt, "Pt");
    AddVariable(branch().Ht, "Ht");

    AddVariable(branch().DeltaPt, "DeltaPt");
    AddVariable(branch().DeltaM, "DeltaM");
    AddVariable(branch().DeltaR, "DeltaR");
    AddVariable(branch().DeltaRap, "DeltaRap");
    AddVariable(branch().DeltaPhi, "DeltaPhi");
    AddVariable(branch().Rho, "Rho");

    AddVariable(branch().Bdt1, "Bdt1");
    AddVariable(branch().Bdt2, "Bdt2");
    AddSpectator(branch().Tag, "Tag");
}

int ZHadronicTagger::Train(Event &event, PreCuts &pre_cuts, const Tag tag)
{
    Print(kInformation, "Higgs Tag");
    Jets jets =  bottom_reader_.Multiplets<BottomTagger>(event);
    std::vector< Doublet > doublets;
    for (auto jet_1 = jets.begin(); jet_1 != jets.end(); ++jet_1) {
        for (auto jet_2 = jet_1 + 1; jet_2 != jets.end(); ++jet_2) {
            Doublet doublet(*jet_1, *jet_2);
            if (doublet.Overlap()) continue;
            if (tag == kSignal && std::abs(doublet.Jet().m() - Mass(HiggsId)) > z_mass_window) continue;
            if (tag == kSignal && (doublet.Rho() > 2 || doublet.Rho() < 0.5)) continue;
            doublet.SetTag(tag);
            doublets.emplace_back(doublet);
        }
    }
    for (const auto jet : jets) {
        const int sub_jet_number = 2;
        Jets pieces = bottom_reader_.SubMultiplet<BottomTagger>(jet, sub_jet_number);
        if (pieces.size() < sub_jet_number) continue;
        Doublet doublet(pieces.at(0), pieces.at(1));
        if (tag == kSignal && std::abs(doublet.Jet().m() - Mass(HiggsId)) > z_mass_window) continue;
        if (tag == kSignal && (doublet.Rho() > 2 || doublet.Rho() < 0.5)) continue;
        doublet.SetTag(tag);
        doublets.emplace_back(doublet);
    }
    Jets particles = event.Partons().GenParticles();
    Jets higgses = copy_if_abs_particle(particles, HiggsId, CpvHiggsId);
    switch (tag) {
    case kSignal :
        doublets = BestMatch(doublets, higgses);
        break;
    case kBackground  :
        doublets = RemoveBestMatch(doublets, higgses);
        break;
    }
    return SaveEntries(doublets);
}

std::vector<Doublet>  ZHadronicTagger::Multiplets(Event &event, PreCuts &pre_cuts, const TMVA::Reader &reader)
{
    Print(kInformation, "Higgs Bdt");
    Jets jets =  bottom_reader_.Multiplets<BottomTagger>(event);
    std::vector< Doublet > doublets;
    for (auto jet_1 = jets.begin(); jet_1 != jets.end(); ++jet_1) {
        for (auto jet_2 = jet_1 + 1; jet_2 != jets.end(); ++jet_2) {
            Doublet doublet(*jet_1, *jet_2);
            if (doublet.Overlap()) continue;
            doublet.SetBdt(Bdt(doublet,reader));
            doublets.emplace_back(doublet);
        }
    }
    for (const auto jet : jets) {
        const int sub_jet_number = 2;
        Jets pieces = bottom_reader_.SubMultiplet<BottomTagger>(jet, sub_jet_number);
        if (pieces.size() < sub_jet_number) continue;
        Doublet doublet(pieces.at(0), pieces.at(1));
        doublet.SetBdt(Bdt(doublet, reader));
        doublets.emplace_back(doublet);
    }
    return ReduceResult(doublets);
}

}
