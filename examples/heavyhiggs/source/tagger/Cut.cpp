#include "boost/range.hpp"
#include <boost/range/algorithm/copy.hpp>
#include <boost/range/adaptors.hpp>

#include "boca/generic/Vector.hh"
#include "boca/math/Math.hh"
#include "boca/event/Event.hh"
#include "boca/fastjet/Particles.hh"

#include "heavyhiggs/tagger/Cut.hh"

// #define DEBUGGING
#include "boca/generic/DEBUG_MACROS.hh"

namespace heavyhiggs
{

namespace tagger
{

namespace
{

std::vector<Lepton> Signed(std::vector<Lepton> const& leptons, int charge)
{
    INFO0;
    std::vector<Lepton> chosen;
    boost::range::copy(leptons | boost::adaptors::filtered([charge](boca::Jet const & jet_1) {
        return sgn(jet_1.Info().Charge()) == sgn(charge);
    }), std::back_inserter(chosen));
    return chosen;
}

std::vector<Lepton> Window(std::vector<Lepton> const& leptons)
{
    INFO0;
    if (leptons.size() < 2) return leptons;
    if (boost::units::abs(Lepton(leptons.at(0) + leptons.at(1)).Mass() - MassOf(Id::Z)) < 10_GeV) return {};
    return leptons;
}

std::vector<Lepton> IsolateLeptons(std::vector<Lepton> const& leptons, boca::Jet const& jet)
{
    INFO0;
    std::vector<Lepton> isolated;
    for (auto const & lepton : leptons) if (lepton.Pt() > 50_GeV || jet.DeltaRTo(lepton) > 0.3_rad) isolated.emplace_back(lepton);
    return isolated;
}

}

int Cut::Train(boca::Event const& event, PreCuts const&, Tag)
{
    INFO0;
    std::vector<CutVariables> variables;
    if (auto optional = CutMethod(event)) variables.emplace_back(*optional);
    return SaveEntries(variables);
}

std::vector<CutVariables> Cut::Multiplets(boca::Event const& event, PreCuts const&, TMVA::Reader const& reader)
{
    INFO0;
    std::vector<CutVariables> variables;
    if (auto optional = CutMethod(event)) variables.emplace_back(*optional);
    for (auto & variable : variables) variable.SetPassed(Cuts(variable, reader));
    return variables;
}

boost::optional<CutVariables> Cut::CutMethod(boca::Event const& event)
{
    INFO0;
    CutVariables variables;

    auto particles = event.GenParticles();
    auto bottom = SortedByPt(CopyIfParticle(particles, Id::bottom));
    DEBUG(bottom.size());
    if (bottom.empty()) return boost::none;

    variables.SetBottomMinPt(bottom.back().Pt());

    bottom = SortedByRap(bottom);
    variables.SetBottomMaxRap(boost::units::abs(bottom.front().Rap()));

    auto jets = RemoveIfSoft(bottom_reader_.Jets(event), 40_GeV);
    auto electrons = event.Electrons();
    auto muons = event.Muons();

    for (auto const & jet : jets) {
        electrons = IsolateLeptons(electrons, jet);
        muons = IsolateLeptons(muons, jet);
    }

    DEBUG(electrons.size(), muons.size());
    if (electrons.size() + muons.size() != 2) return boost::none;
    electrons = Window(electrons);

    auto leptons = SortedByPt(RemoveIfSoft(Combine(electrons, muons), 15_GeV));
    DEBUG(electrons.size(), muons.size());
    if (electrons.size() + muons.size() != 2) return boost::none;

    auto positive = Signed(leptons, 1);
    auto negative = Signed(leptons, -1);

    DEBUG(positive.size(), negative.size());
    if (positive.size() != 2 && negative.size() != 2) return boost::none;

    variables.SetLeptonPts(leptons);

    DEBUG(jets.size());
    if (jets.size() < 4) return boost::none;
    variables.SetJetNumber(jets.size());

    auto bottoms = CopyIf(jets, [](boca::Jet const & jet) {
//         return jet.Info().BTag();
      return jet.Info().Bdt() > 0.05;
    });
    DEBUG(bottoms.size());
    if (bottoms.size() < 4) return boost::none;
    variables.SetBottomNumber(bottoms.size());

    auto missing_et = event.MissingEt();
    DEBUG(missing_et.Pt());
    if (missing_et.Pt() < 30_GeV) return boost::none;
    variables.SetEtMiss(missing_et.Pt());

    variables.SetHt(event.ScalarHt());

    DEBUG(variables.IsNaN());
    if (variables.IsNaN()) return boost::none;
    return variables;
}

std::string Cut::Name() const
{
    return "Cut";
}

TMVA::Types::EMVA Cut::Mva() const
{
    return TMVA::Types::EMVA::kCuts;
}

}

}
