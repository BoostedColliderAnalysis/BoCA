#include "include/tagger/CutNeutral.hh"

#include "boca/generic/DEBUG_MACROS.hh"

namespace heavyhiggs
{

namespace tagger
{

int CutNeutral::Train(boca::Event const& event, PreCuts const&, Tag)
{
    INFO0;
    std::vector<CutVariables> variables;
    if (auto optional = CutMethod(event)) variables.emplace_back(*optional);
    return SaveEntries(variables);
}

std::vector<CutVariables> CutNeutral::Multiplets(boca::Event const& event, PreCuts const&, TMVA::Reader const& reader)
{
    INFO0;
    std::vector<CutVariables> variables;
    if (auto optional = CutMethod(event)) variables.emplace_back(*optional);
    for (auto & variable : variables) Mva() == TMVA::Types::EMVA::kCuts ? variable.SetPassed(Cuts(variable, reader)) : variable.SetBdt(Bdt(variable, reader));
    return variables;
}

boost::optional<CutVariables> CutNeutral::CutMethod(boca::Event const& event)
{
    INFO0;
    CutVariables variables;
    auto jets = bottom_reader_.Jets(event);
    variables.SetJetPts(jets);
    variables.SetHt(event.ScalarHt());
    auto bottoms = CopyIfTag(jets, 0.05);
    if(bottoms.size() < 3) return boost::none;
    variables.SetBottomNumber(bottoms.size());
    variables.SetLeptonPts(event.Leptons());
    return variables;
}

std::string CutNeutral::Name() const
{
    return "Cut";
}

TMVA::Types::EMVA CutNeutral::Mva() const
{
    return TMVA::Types::EMVA::kBDT;
    return TMVA::Types::EMVA::kCuts;
}

}

}
