#include "DoubletTagger.hh"

namespace analysis {

// No need to call this TemporaryFunction() function,
// it's just to avoid link error.
void TemporaryFunction ()
{
  DoubletTagger<WHadronicBranch> TempObj;
}

template <class DoubletBranch>
DoubletTagger<DoubletBranch>::DoubletTagger()
{
//     DebugLevel = Severity::debug;
    Print(Severity::notification, "Constructor");
    set_tagger_name("WHadronic");
    doublet_mass_window_ = 20;
    bottom_reader_.SetTagger(bottom_tagger_);
    DefineVariables();
}

template <class DoubletBranch>
void DoubletTagger<DoubletBranch>::DefineVariables()
{
    Print(Severity::notification , "Define Variables");
    AddVariable(branch().Mass, "Mass");
    AddVariable(branch().Rap, "Rap");
    AddVariable(branch().Phi, "Phi");
    AddVariable(branch().Pt, "Pt");
    AddVariable(branch().Ht, "Ht");
    AddVariable(branch().DeltaPt, "DeltaPt");
    AddVariable(branch().DeltaPhi, "DeltaPhi");
    AddVariable(branch().DeltaRap, "DeltaRap");
    AddVariable(branch().DeltaR, "DeltaR");
    AddVariable(branch().Bdt, "Bdt");
    AddSpectator(branch().Tag, "Tag");
}

template <class DoubletBranch>
int DoubletTagger<DoubletBranch>::Train(Event &event, PreCuts &pre_cuts, const Tag tag)
{
    Print(Severity::information, "Doublet Tags");
    std::vector<Doublet> doublets;
    return SaveEntries<DoubletBranch>(doublets);
}

template <class DoubletBranch>
std::vector<Doublet> DoubletTagger<DoubletBranch>::Multiplets(Event &event, const TMVA::Reader &reader)
{
    Print(Severity::information, "doublet Bdt");

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
        for (const auto & piece : pieces) doublets = Join(doublets, Multiplet(piece, reader));
    }

    std::sort(doublets.begin(), doublets.end());
    doublets.erase(doublets.begin() + std::min(max_combi(), int(doublets.size())), doublets.end());
    return doublets;
}

template <class DoubletBranch>
std::vector<Doublet> DoubletTagger<DoubletBranch>::Multiplets(const Jets &jets, const TMVA::Reader &reader)
{
    Print(Severity::information, "doublet Bdt");

    // W in 2 jets
    std::vector<Doublet>  doublets;
    for (auto Jet1 = jets.begin(); Jet1 != jets.end(); ++Jet1)
        for (auto Jet2 = Jet1 + 1; Jet2 != jets.end(); ++Jet2) {
            doublets = Join(doublets, Multiplet(*Jet1, *Jet2, reader));
        }

    std::sort(doublets.begin(), doublets.end());
    doublets.erase(doublets.begin() + std::min(max_combi(), int(doublets.size())), doublets.end());
    return doublets;
}

template <class DoubletBranch>
std::vector<Doublet> DoubletTagger<DoubletBranch>::Multiplets(const Jets &jets, const TMVA::Reader &reader, const int sub_jet_number)
{
    Print(Severity::information, "doublet Bdt");

    std::vector<Doublet>  doublets;
    for (const auto & jet : jets) {
        Jets pieces = static_cast<BottomTagger &>(bottom_reader_.tagger()).SubMultiplet(jet, bottom_reader_.reader(), sub_jet_number);
        for (const auto & piece : pieces) doublets = Join(doublets, Multiplet(piece, reader));
    }

//     std::sort(doublets.begin(), doublets.end());
//     doublets.erase(doublets.begin() + std::min(max_combi(), int(doublets.size())), doublets.end());
    return doublets;
}

template <class DoubletBranch>
std::vector<Doublet> DoubletTagger<DoubletBranch>::Multiplet(const fastjet::PseudoJet &jet_1, const fastjet::PseudoJet &jet_2, const TMVA::Reader &reader)
{
    Print(Severity::information, "doublet Bdt");
    Doublet doublet(jet_1, jet_2);
    if (doublet.DeltaR() < detector_geometry().MinCellResolution) return std::vector<Doublet>{};
    return Multiplet(doublet,reader);
}

template <class DoubletBranch>
std::vector<Doublet> DoubletTagger<DoubletBranch>::Multiplet(const fastjet::PseudoJet &jet, const TMVA::Reader &reader)
{
    Print(Severity::information, "doublet Bdt");
    Jets subjets = SubJets(jet, 2);
    if (subjets.empty()) return std::vector<Doublet>{};
    Doublet doublet;
    if (subjets.size() == 1) doublet.SetSinglets(jet);
    else doublet.SetSinglets(subjets.at(0), subjets.at(1));
    return Multiplet(doublet,reader);
}

template <class DoubletBranch>
std::vector<Doublet> DoubletTagger<DoubletBranch>::Multiplet(Doublet &doublet, const TMVA::Reader &reader)
{
  Print(Severity::information, "doublet Bdt");
  std::vector<Doublet>  doublets;
  if (std::abs(doublet.Jet().m() - Mass(Id::W)) > doublet_mass_window_) return doublets;
  branch() = branch<DoubletBranch>(doublet);
  doublet.SetBdt(Bdt(reader));
  doublets.emplace_back(doublet);
  return doublets;
}

}
