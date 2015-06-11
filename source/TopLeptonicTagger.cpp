# include "TopLeptonicTagger.hh"

analysis::TopLeptonicTagger::TopLeptonicTagger()
{
    //     DebugLevel = analysis::Object::kDebug;

    Print(kNotification, "Constructor");
    set_tagger_name("TopLeptonic");
    bottom_reader_.set_tagger(bottom_tagger_);
    DefineVariables();
}

void analysis::TopLeptonicTagger::DefineVariables()
{
    Print(kNotification , "Define Variables");
    AddVariable(branch_.Mass, "Mass");
    AddVariable(branch_.Pt, "Pt");
    AddVariable(branch_.Rap, "Rap");
    AddVariable(branch_.Phi, "Phi");
    AddVariable(branch_.BottomPt, "BottomPt");
    AddVariable(branch_.LeptonPt, "LeptonPt");
    AddVariable(branch_.DeltaPhi, "DeltaPhi");
    AddVariable(branch_.DeltaRap, "DeltaRap");
    AddVariable(branch_.DeltaR, "DeltaR");
    AddVariable(branch_.Bdt, "Bdt");
    AddSpectator(branch_.Tag, "Tag");
}

int analysis::TopLeptonicTagger::Train(Event &event,PreCuts &pre_cuts, const Object::Tag tag)
{
    Print(kInformation, "Train");
    std::size_t number_of_tops = 2;
    Jets jets = bottom_reader_.Multiplets<BottomTagger>(event);
    Print(kInformation, "Jet Number", jets.size());

    Jets leptons = event.Leptons().leptons();
    Print(kInformation, "Lepton Number", leptons.size());

    std::vector<Doublet> doublets;
    for (const auto & lepton : leptons)
        for (const auto & jet : jets) {
            Doublet doublet(jet, lepton);
            if (tag == kSignal && doublet.Jet().m() > Mass(TopId)) continue;
            doublets.emplace_back(doublet);
        }
    Print(kInformation, "Number JetPairs", doublets.size());

    if (tag == kSignal) doublets = BestMass(doublets,Mass(TopId),number_of_tops);
    for(const auto &doublet : doublets) Print(kError,"TopLeptonic",doublet.Jet().pt(),doublet.DeltaR());
    return SaveEntries(doublets);
}

std::vector<analysis::Doublet>  analysis::TopLeptonicTagger::Multiplets(Event &event, const TMVA::Reader &reader)
{
    Jets jets = bottom_reader_.Multiplets<BottomTagger>(event);
    Jets leptons = event.Leptons().leptons();
    Print(kInformation, "Bdt");
    std::vector<Doublet> doublets;
    for (const auto & lepton : leptons) {
        for (const auto & jet : jets) {
            Doublet doublet(jet, lepton);
            branch_ = branch(doublet);
            doublet.SetBdt(Bdt(reader));
            doublets.emplace_back(doublet);
        }
    }
    return ReduceResult(doublets);
}
