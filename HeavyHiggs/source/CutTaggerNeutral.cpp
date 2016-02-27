// #include "physics/Math.hh"
#include "CutTaggerNeutral.hh"
// #include "Event.hh"
// #include "Vector.hh"
// #define DEBUGGING
#include "Debug.hh"

namespace boca
{

namespace heavyhiggs
{

int CutTaggerNeutral::Train(Event const& event, PreCuts const&, Tag) const
{
    INFO0;
    std::vector<CutVariables> variables;
    if (boost::optional<CutVariables> optional = CutMethod(event)) variables.emplace_back(*optional);
    return SaveEntries(variables);
}

std::vector<CutVariables> CutTaggerNeutral::Multiplets(Event const& event, PreCuts const&, TMVA::Reader const& reader) const
{
    INFO0;
    std::vector<CutVariables> variables;
    if (boost::optional<CutVariables> optional = CutMethod(event)) variables.emplace_back(*optional);
    for (auto & variable : variables) Mva() == TMVA::Types::EMVA::kCuts ? variable.SetPassed(Cuts(variable, reader)) : variable.SetBdt(Bdt(variable, reader));
    return ReduceResult(variables);
}

boost::optional<CutVariables> CutTaggerNeutral::CutMethod(Event const& event) const
{
    INFO0;
    CutVariables variables;
    auto jets = bottom_reader_.Jets(event);
    variables.SetJetPts(jets);
    variables.SetHt(event.Hadrons().ScalarHt());
    std::vector<Jet> bottoms;
    for (auto const& jet : jets) if(jet.Info().Bdt() > 0) bottoms.emplace_back(jet);
    if(bottoms.size() < 3) return boost::none;
    variables.SetBottomNumber(bottoms.size());
    variables.SetLeptonPts(event.Leptons().leptons());
    return variables;
}

std::string CutTaggerNeutral::Name() const
{
    return "Cut";
}

TMVA::Types::EMVA CutTaggerNeutral::Mva() const
{
    return TMVA::Types::EMVA::kBDT;
    return TMVA::Types::EMVA::kCuts;
}

}

}
