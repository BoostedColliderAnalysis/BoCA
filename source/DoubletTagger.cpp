# include "DoubletTagger.hh"

// No need to call this TemporaryFunction() function,
// it's just to avoid link error.
void TemporaryFunction ()
{
  analysis::DoubletTagger<analysis::WHadronicBranch> TempObj;
}

template <class DoubletBranch>
analysis::DoubletTagger<DoubletBranch>::DoubletTagger()
{
//     DebugLevel = analysis::Object::kDebug;
    Print(kNotification, "Constructor");
    set_tagger_name("WHadronic");
    doublet_mass_window_ = 20;
    bottom_reader_.set_tagger(bottom_tagger_);
    DefineVariables();
}

template <class DoubletBranch>
void analysis::DoubletTagger<DoubletBranch>::DefineVariables()
{
    Print(kNotification , "Define Variables");
    AddVariable(branch_.Mass, "Mass");
    AddVariable(branch_.Rap, "Rap");
    AddVariable(branch_.Phi, "Phi");
    AddVariable(branch_.Pt, "Pt");
    AddVariable(branch_.Ht, "Ht");
    AddVariable(branch_.DeltaPt, "DeltaPt");
    AddVariable(branch_.DeltaPhi, "DeltaPhi");
    AddVariable(branch_.DeltaRap, "DeltaRap");
    AddVariable(branch_.DeltaR, "DeltaR");
    AddVariable(branch_.Bdt, "Bdt");
    AddSpectator(branch_.Tag, "Tag");
}

template <class DoubletBranch>
int analysis::DoubletTagger<DoubletBranch>::Train(analysis::Event &event, PreCuts &pre_cuts, const analysis::Object::Tag tag)
{
    Print(kInformation, "Doublet Tags");
    std::vector<Doublet> doublets;
    return SaveEntries<DoubletBranch>(doublets);
}

template <class DoubletBranch>
std::vector<analysis::Doublet> analysis::DoubletTagger<DoubletBranch>::Multiplets(Event &event, const TMVA::Reader &reader)
{
    Print(kInformation, "doublet Bdt");

    Jets jets = bottom_reader_.Multiplets<BottomTagger>(event);

    // 2 jets form a W
    std::vector<Doublet> doublets = Multiplets(jets, reader);

    // 1 jet (2 subjets) form a W
    Multiplets(jets, reader, 2);

    // 2 of 3 subjets form a W
    Multiplets(jets, reader, 3);

    // 1 of 2 subjets forms a W
    for (const auto & jet : jets) {
        Jets pieces = static_cast<BottomTagger &>(bottom_reader_.tagger()).SubMultiplet(jet, bottom_reader_.reader(), 2);
        for (const auto & piece : pieces) doublets = JoinVectors(doublets, Multiplet(piece, reader));
    }

    std::sort(doublets.begin(), doublets.end());
    doublets.erase(doublets.begin() + std::min(max_combi(), int(doublets.size())), doublets.end());
    return doublets;
}

template <class DoubletBranch>
std::vector<analysis::Doublet> analysis::DoubletTagger<DoubletBranch>::Multiplets(const Jets &jets, const TMVA::Reader &reader)
{
    Print(kInformation, "doublet Bdt");

    // W in 2 jets
    std::vector<Doublet>  doublets;
    for (auto Jet1 = jets.begin(); Jet1 != jets.end(); ++Jet1)
        for (auto Jet2 = Jet1 + 1; Jet2 != jets.end(); ++Jet2) {
            doublets = JoinVectors(doublets, Multiplet(*Jet1, *Jet2, reader));
        }

    std::sort(doublets.begin(), doublets.end());
    doublets.erase(doublets.begin() + std::min(max_combi(), int(doublets.size())), doublets.end());
    return doublets;
}

template <class DoubletBranch>
std::vector<analysis::Doublet> analysis::DoubletTagger<DoubletBranch>::Multiplets(const Jets &jets, const TMVA::Reader &reader, const int sub_jet_number)
{
    Print(kInformation, "doublet Bdt");

    std::vector<Doublet>  doublets;
    for (const auto & jet : jets) {
        Jets pieces = static_cast<BottomTagger &>(bottom_reader_.tagger()).SubMultiplet(jet, bottom_reader_.reader(), sub_jet_number);
        for (const auto & piece : pieces) doublets = JoinVectors(doublets, Multiplet(piece, reader));
    }

//     std::sort(doublets.begin(), doublets.end());
//     doublets.erase(doublets.begin() + std::min(max_combi(), int(doublets.size())), doublets.end());
    return doublets;
}

template <class DoubletBranch>
std::vector<analysis::Doublet> analysis::DoubletTagger<DoubletBranch>::Multiplet(const fastjet::PseudoJet &jet_1, const fastjet::PseudoJet &jet_2, const TMVA::Reader &reader)
{
    Print(kInformation, "doublet Bdt");
    Doublet doublet(jet_1, jet_2);
    if (doublet.DeltaR() < detector_geometry().MinCellResolution) return std::vector<Doublet>{};
    return Multiplet(doublet,reader);
}

template <class DoubletBranch>
std::vector<analysis::Doublet> analysis::DoubletTagger<DoubletBranch>::Multiplet(const fastjet::PseudoJet &jet, const TMVA::Reader &reader)
{
    Print(kInformation, "doublet Bdt");
    Jets subjets = SubJets(jet, 2);
    if (subjets.empty()) return std::vector<Doublet>{};
    Doublet doublet;
    if (subjets.size() == 1) doublet.SetSinglets(jet);
    else doublet.SetSinglets(subjets.at(0), subjets.at(1));
    return Multiplet(doublet,reader);
}

template <class DoubletBranch>
std::vector<analysis::Doublet> analysis::DoubletTagger<DoubletBranch>::Multiplet(Doublet &doublet, const TMVA::Reader &reader)
{
  Print(kInformation, "doublet Bdt");
  std::vector<Doublet>  doublets;
  if (std::abs(doublet.Jet().m() - Mass(WId)) > doublet_mass_window_) return doublets;
  branch_ = branch<DoubletBranch>(doublet);
  doublet.SetBdt(Bdt(reader));
  doublets.emplace_back(doublet);
  return doublets;
}
