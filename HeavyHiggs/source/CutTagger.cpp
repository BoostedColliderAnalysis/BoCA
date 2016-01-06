#include "boost/range.hpp"
#include <boost/range/algorithm/copy.hpp>
#include <boost/range/adaptors.hpp>
#include "physics/Math.hh"
#include "CutTagger.hh"
#include "Event.hh"
#define DEBUG
#include "Debug.hh"

namespace boca
{

namespace heavyhiggs
{

int CutTagger::Train(Event const& event, PreCuts const&, Tag) const
{
    Info0;
    std::vector<CutVariables> variables;
    if (boost::optional<CutVariables> optional = CutMethod(event)) variables.emplace_back(*optional);
    return SaveEntries(variables);
}

std::vector<CutVariables> CutTagger::Multiplets(Event const& event, PreCuts const&, TMVA::Reader const& reader) const
{
    Info0;
    std::vector<CutVariables> variables;
    if (boost::optional<CutVariables> optional = CutMethod(event)) variables.emplace_back(*optional);
    for (auto & variable : variables) variable.SetPassed(Cuts(variable, reader));
    return ReduceResult(variables);
}

namespace
{

std::vector<Lepton> Signed(std::vector<Lepton> const& leptons, int charge)
{
    Info0;
    std::vector<Lepton> chosen;
    boost::range::copy(leptons | boost::adaptors::filtered([charge](Jet const & jet_1) {
        return sgn(jet_1.Info().Charge()) == sgn(charge);
    }), std::back_inserter(chosen));
    return chosen;
}

std::vector<Lepton> Window(std::vector<Lepton> const& leptons)
{
    Info0;
    if (leptons.size() < 2) return leptons;
    if (boost::units::abs(Lepton(leptons.at(0) + leptons.at(1)).Mass() - MassOf(Id::Z)) < 10_GeV) return {};
    return leptons;
}

std::vector<Lepton> IsolateLeptons(std::vector<Lepton> const& leptons, Jet const& jet)
{
    Info0;
    std::vector<Lepton> isolated;
    for (auto const & lepton : leptons) if (lepton.Pt() > 50_GeV || jet.DeltaRTo(lepton) > 0.3_rad) isolated.emplace_back(lepton);
    return isolated;
}

}

boost::optional<CutVariables> CutTagger::CutMethod(Event const& event) const
{
    Info0;
    CutVariables variables;

    std::vector<Particle> particles = event.Partons().GenParticles();
    std::vector<Particle> bottom = SortedByPt(CopyIfParticle(particles, Id::bottom));
    Debug(bottom.size());
    if (bottom.empty()) return boost::none;

    variables.SetBottomMinPt(bottom.back().Pt());

    bottom = SortedByRap(bottom);
    variables.SetBottomMaxRap(boost::units::abs(bottom.front().Rap()));

    std::vector<Jet> jets = RemoveIfSoft(event.Hadrons().Jets(), 40_GeV);
    std::vector<Lepton> electrons = event.Leptons().Electrons();
    std::vector<Lepton> muons = event.Leptons().Muons();

    for (auto const & jet : jets) {
        electrons = IsolateLeptons(electrons, jet);
        muons = IsolateLeptons(muons, jet);
    }

    Debug(electrons.size(), muons.size());
    if (electrons.size() + muons.size() != 2) return boost::none;
    electrons = Window(electrons);

    std::vector<Lepton> leptons = SortedByPt(RemoveIfSoft(Join(electrons, muons), 15_GeV));
    Debug(electrons.size(), muons.size());
    if (electrons.size() + muons.size() != 2) return boost::none;

    std::vector<Lepton> positive = Signed(leptons, 1);
    std::vector<Lepton> negative = Signed(leptons, -1);

    Debug(positive.size(), negative.size());
    if (positive.size() != 2 && negative.size() != 2) return boost::none;

    variables.SetLeadingPt(leptons.at(0).Pt());
    variables.SetSecondLeadingPt(leptons.at(1).Pt());

    Debug(jets.size());
    if (jets.size() < 4) return boost::none;
    variables.SetJetNumber(jets.size());

    std::vector<Jet> bottoms;
    boost::range::copy(jets | boost::adaptors::filtered([](Jet const & jet) {
        return jet.Info().BTag();
    }), std::back_inserter(bottoms));
    Debug(bottoms.size());
    if (bottoms.size() < 4) return boost::none;
    variables.SetBottomNumber(bottoms.size());

    boca::MissingEt missing_et = event.Hadrons().MissingEt();
    Debug(missing_et.Pt());
    if (missing_et.Pt() < 30_GeV) return boost::none;
    variables.SetEtMiss(missing_et.Pt());

    variables.SetHt(event.Hadrons().ScalarHt());

    Debug(variables.IsNaN());
    if (variables.IsNaN()) return boost::none;
    return variables;
}

std::string CutTagger::Name() const
{
    return "Cut";
}

TMVA::Types::EMVA CutTagger::Mva() const
{
    return TMVA::Types::EMVA::kCuts;
}

}

}
