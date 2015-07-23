#include "PreCuts.hh"

namespace analysis {

void PreCuts::SetPtLowerCut(const Id id, float value)
{
    pt_lower_cut_.emplace(id, value);
}
float PreCuts::PtLowerCut(const Id id) const
{
    try {
        return pt_lower_cut_.at(id);
    } catch (const std::out_of_range&) {
        return 0;
    }
}
void PreCuts::SetPtUpperCut(const Id id, float value)
{
    pt_upper_cut_.emplace(id, value);
}
float PreCuts::PtUpperCut(const analysis::Id id) const
{
    try {
        return pt_upper_cut_.at(id);
    } catch (const std::out_of_range&) {
        return 0;
    }
}
void PreCuts::SetMassLowerCut(const Id id, float value)
{
    mass_lower_cut_.emplace(id, value);
}
float PreCuts::MassLowerCut(const Id id) const
{
    try {
        return mass_lower_cut_.at(id);
    } catch (const std::out_of_range&) {
        return 0;
    }
}
void PreCuts::SetMassUpperCut(const Id id, float value)
{
    mass_upper_cut_.emplace(id, value);
}
float PreCuts::MassUpperCut(const Id id) const
{
    try {
        return mass_upper_cut_.at(id);
    } catch (const std::out_of_range&) {
        return 0;
    }
}
void PreCuts::SetTrackerMaxEta(const Id id, float value)
{
    tracker_eta_upper_cut_.emplace(id, value);
}
float PreCuts::TrackerMaxEta(const Id id) const
{
    try {
        return tracker_eta_upper_cut_.at(id);
    } catch (const std::out_of_range&) {
        return 0;
    }
}
bool PreCuts::DoSubJets() const
{
    return do_sub_jets_;
}
void PreCuts::SetSubJets(const bool do_sub_jets)
{
    do_sub_jets_ = do_sub_jets;
}
}
