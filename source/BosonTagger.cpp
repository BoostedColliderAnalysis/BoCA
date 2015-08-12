#include "BosonTagger.hh"
#include "Event.hh"
#include "Doublet.hh"
#include "Debug.hh"

namespace analysis {

BosonTagger::BosonTagger()
{
  Info();
    DefineVariables();
}

int BosonTagger::Train(Event const& event, PreCuts const& pre_cuts, Tag tag) const
{
  Info(analysis::Name(tag));
  Jets jets = bottom_reader_.Multiplets(event);
  std::vector<Doublet> doublets = unordered_pairs(jets,[&](fastjet::PseudoJet const& jet_1, fastjet::PseudoJet const& jet_2) {
    return Doublett(Doublet(jet_1, jet_2), pre_cuts, tag);
  });

  for (auto const& jet : jets) {
    try {
      doublets.emplace_back(Doublett(Doublet(jet), pre_cuts, tag));
    } catch (...) {}
    try {
      Jets pieces = bottom_reader_.SubMultiplet(jet, 2);
      doublets.emplace_back(Doublett(Doublet(pieces.at(0), pieces.at(1)), pre_cuts, tag));
    } catch (...) {}
  }
    Jets particles = event.Partons().GenParticles();
    Jets higgses = CopyIfParticles(particles, Id::higgs, Id::CP_violating_higgs);
    Jets vectors = CopyIfParticles(particles, Id::W, Id::Z);
    Jets bosons;// = Join(higgses,vectors);
    if (vectors.empty()) bosons = higgses;
    else bosons = vectors;
    return SaveEntries(doublets, bosons, tag);
}

Doublet BosonTagger::Doublett(Doublet doublet, PreCuts const& pre_cuts, Tag tag) const
{
  if (Problematic(doublet, pre_cuts, tag)) throw "problematic";
  doublet.SetTag(tag);
  return doublet;
}

bool BosonTagger::Problematic(Doublet const& doublet, PreCuts const& pre_cuts, Tag tag) const
{
    if (Problematic(doublet, pre_cuts)) return true;
    switch (tag) {
    case Tag::signal :
        if (std::abs(doublet.Jet().m() - (Mass(Id::higgs) + Mass(Id::W)) / 2) > boson_mass_window)
            return true;
        if ((doublet.Rho() > 2 || doublet.Rho() < 0.5) && doublet.Rho() > 0)
            return true;
        break;
    case Tag::background :
        break;
    }
    return false;
}

bool BosonTagger::Problematic(Doublet const& doublet, PreCuts const& pre_cuts) const
{
    if (pre_cuts.PtLowerCut(Id::higgs) > 0 && pre_cuts.PtLowerCut(Id::higgs) > doublet.Jet().pt()) return true;
    if (pre_cuts.PtUpperCut(Id::higgs) > 0 && pre_cuts.PtUpperCut(Id::higgs) < doublet.Jet().pt()) return true;
    if (pre_cuts.MassUpperCut(Id::higgs) > 0 && pre_cuts.MassUpperCut(Id::higgs) < doublet.Jet().m()) return true;
    return false;
}

std::vector<Doublet>  BosonTagger::Multiplets(Event const& event, PreCuts const& pre_cuts, TMVA::Reader const& reader) const
{
  Info();
  Jets jets =  bottom_reader_.Multiplets(event);
  std::vector<Doublet> doublets = unordered_pairs(jets,[&](fastjet::PseudoJet const& jet_1, fastjet::PseudoJet const& jet_2) {
    Doublet doublet(jet_1, jet_2);
    return Multiplet(doublet,pre_cuts,reader);
  });
  for (auto const& jet : jets) {
    try {
      Doublet doublet(jet);
      doublets.emplace_back(Multiplet(doublet,pre_cuts,reader));
    } catch (...) {}
    try {
      Jets pieces = bottom_reader_.SubMultiplet(jet, 2);
      Doublet doublet(pieces.at(0), pieces.at(1));
      doublets.emplace_back(Multiplet(doublet,pre_cuts,reader));
    } catch (...) {}
  }
    return ReduceResult(doublets);
}

Doublet BosonTagger::Multiplet(Doublet & doublet, PreCuts const& pre_cuts, TMVA::Reader const& reader) const
{
  if (Problematic(doublet, pre_cuts)) throw "problematic";
  doublet.SetBdt(Bdt(doublet, reader));
  return doublet;
}

int BosonTagger::GetBdt(Event const& event, PreCuts const& pre_cuts, TMVA::Reader const& reader) const
{
    return SaveEntries(Multiplets(event, pre_cuts, reader), 1);
}

}
