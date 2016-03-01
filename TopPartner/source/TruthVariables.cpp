#include "../include/TruthVariables.hh"
#include "physics/Particles.hh"
#include "physics/Units.hh"
#include "Sort.hh"
#include "Vector.hh"

namespace boca
{
namespace naturalness
{
Momentum TruthVariables::LeptonPt(int number) const
{
    return leptons_.size() > number ? leptons_.at(number).Pt() : at_rest;
}
Momentum TruthVariables::TopPt(int number) const
{
    return tops_.size() > number ? tops_.at(number).Pt() : at_rest;
}
int TruthVariables::BosonNumber() const
{
    return bosons_.size();
}
int TruthVariables::HardBosonNumber() const
{
    return RemoveIfSoft(bosons_, 20_GeV).size();
}
int TruthVariables::DetectableBosonNumber() const
{
    return detectable_.size();
}
Momentum TruthVariables::HardBosonPt() const
{
    return bosons_.empty() ? at_rest : bosons_.front().Pt();
}
Momentum TruthVariables::SoftBosonPt() const
{
    return bosons_.empty() ? at_rest : bosons_.back().Pt();
}
Angle TruthVariables::BosonDeltaRMin() const
{
    return *boost::min_element(UnorderedPairs(bosons_, [](Particle const & particle_1, Particle const & particle_2) {
        return particle_1.DeltaRTo(particle_2);
    }));
}
void TruthVariables::SetLeptons(const std::vector< Particle >& leptons)
{
    leptons_ = SortedByPt(leptons);
}
void TruthVariables::SetBosons(const std::vector< Particle >& bosons)
{
    bosons_ = SortedByPt(bosons);
}
void TruthVariables::SetTops(const std::vector< Particle >& tops)
{
    tops_ = SortedByPt(tops);
}
void TruthVariables::SetDetectable(const std::vector< Particle >& jets)
{
    detectable_ = SortedByPt(jets);
}
}
}
