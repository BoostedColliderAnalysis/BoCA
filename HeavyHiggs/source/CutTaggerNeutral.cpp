#include "CutTaggerNeutral.hh"
#include "generic/DEBUG.hh"

namespace boca
{

namespace heavyhiggs
{

int CutTaggerNeutral::Train(Event const& event, PreCuts const&, Tag)
{
    INFO0;
    std::vector<CutVariables> variables;
    if (auto optional = CutMethod(event)) variables.emplace_back(*optional);
    return SaveEntries(variables);
}

std::vector<CutVariables> CutTaggerNeutral::Multiplets(Event const& event, PreCuts const&, TMVA::Reader const& reader)
{
    INFO0;
    std::vector<CutVariables> variables;
    if (auto optional = CutMethod(event)) variables.emplace_back(*optional);
    for (auto & variable : variables) Mva() == TMVA::Types::EMVA::kCuts ? variable.SetPassed(Cuts(variable, reader)) : variable.SetBdt(Bdt(variable, reader));
    return variables;
}

boost::optional<CutVariables> CutTaggerNeutral::CutMethod(Event const& event)
{
    INFO0;
    CutVariables variables;
    auto jets = bottom_reader_.Jets(event);
    variables.SetJetPts(jets);
    variables.SetHt(event.Hadrons().ScalarHt());
    auto bottoms = CopyIfTag(jets, 0.05);
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
    return TMVA::Types::EMVA::kCuts;
    return TMVA::Types::EMVA::kBDT;
}

}

}
