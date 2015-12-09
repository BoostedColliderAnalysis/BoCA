#include "CutTagger.hh"
#include "Event.hh"
#include "physics/Math.hh"
#include "boost/range.hpp"
#include <boost/range/algorithm/copy.hpp>
#include <boost/range/adaptors.hpp>
#include <boost/range/join.hpp>
// #define INFORMATION
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

namespace {

std::vector<Lepton> Signed(std::vector<Lepton> leptons, int charge)
{
    std::vector<Lepton> chosen;
    boost::range::copy(leptons | boost::adaptors::filtered([charge](Jet const & jet_1) {
        return sgn(jet_1.Info().Charge()) == sgn(charge);
    }), std::back_inserter(chosen));
    return chosen;
}

std::vector<Lepton> Window(std::vector<Lepton> leptons)
{
    if (leptons.size() < 2) return leptons;
    if (boost::units::abs(Lepton(leptons.at(0) + leptons.at(1)).Mass() - MassOf(Id::Z)) < 10_GeV) return {};
    return leptons;
}

std::vector<Lepton> IsolateLeptons(std::vector<Lepton> const& leptons, Jet const& jet)
{
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
    if(bottom.empty()) return boost::none;

    variables.bottom_min_pt_ = bottom.back().Pt();

    bottom = SortedByRap(bottom);
    variables.bottom_max_rap_ = boost::units::abs(bottom.front().Rap());

    std::vector<Jet> jets = RemoveIfSoft(event.Hadrons().Jets(), 40_GeV);
    std::vector<Lepton> electrons = event.Leptons().Electrons();
    std::vector<Lepton> muons = event.Leptons().Muons();

    for (auto const & jet : jets) {
        electrons = IsolateLeptons(electrons, jet);
        muons = IsolateLeptons(muons, jet);
    }

    if (electrons.size() + muons.size() != 2) return boost::none;
    electrons = Window(electrons);

    std::vector<Lepton> leptons = SortedByPt(RemoveIfSoft(Join(electrons, muons), 15_GeV));
    if (electrons.size() + muons.size() != 2) return boost::none;

    std::vector<Lepton> positive = Signed(leptons, 1);
    std::vector<Lepton> negative = Signed(leptons, -1);

    if (positive.size() != 2 && negative.size() != 2) return boost::none;

    variables.leading_pt_ = leptons.at(0).Pt();
    variables.second_leading_pt_ = leptons.at(1).Pt();

    if (jets.size() < 4) return boost::none;
    variables.jet_number_ = jets.size();

    std::vector<Jet> bottoms;
    boost::range::copy(jets | boost::adaptors::filtered([](Jet const & jet) {
        return jet.Info().BTag();
    }), std::back_inserter(bottoms));
    if (bottoms.size() < 4) return boost::none;
    variables.bottom_number_ = bottoms.size();

    boca::MissingEt missing_et = event.Hadrons().MissingEt();
    if (missing_et.Pt() < 30_GeV) return boost::none;
    variables.et_miss_ = missing_et.Pt();

    variables.ht_ = event.Hadrons().ScalarHt();

    if (variables.IsNaN()) return boost::none;
    return variables;
}

std::string CutTagger::Name() const
{
    return "Cut";
}

}

}
