#include "boca/physics/Id.hh"
#include "boca/physics/Units.hh"
#include "boca/multiplets/Sort.hh"
#include "boca/generic/Vector.hh"
#include "boca/generic/DEBUG_MACROS.hh"

#include "toppartner/multiplets/TruthVariables.hh"

namespace toppartner
{

Momentum TruthVariables::LeptonPt(unsigned number) const
{
    return leptons_.size() > number ? leptons_.at(number).Pt() : at_rest;
}

Momentum TruthVariables::TopPt(unsigned number) const
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
    return bosons_.empty() ? 0_rad : *boost::min_element(UnorderedPairs(bosons_, [](Particle const & particle_1, Particle const & particle_2) {
        return particle_1.DeltaRTo(particle_2);
    }));
}

void TruthVariables::SetLeptons(const std::vector< Particle >& leptons)
{
    leptons_ = SortedByPt(leptons);
}

void TruthVariables::SetBosons(const std::vector< Particle >& bosons)
{
    CHECK(bosons.size() == 6, bosons.size());
    bosons_ = SortedByPt(bosons);
}

void TruthVariables::SetTops(const std::vector< Particle >& tops)
{
    CHECK(tops.size() == 2, tops.size());
    tops_ = SortedByPt(tops);
}

void TruthVariables::SetDetectable(const std::vector< Particle >& jets)
{
    detectable_ = SortedByPt(jets);
}

Energy TruthVariables::MissingEt() const
{
    return missing_et_.Pt();
}

Momentum TruthVariables::ScalarHt() const
{
    return scalar_ht_;
}

void TruthVariables::SetMissingEt(boca::MissingEt const& missing_et)
{
    missing_et_ = missing_et;
}

void TruthVariables::SetScalarHt(Momentum const& scalar_ht)
{
    scalar_ht_ = scalar_ht;
}

void TruthVariables::SetJets(std::vector<boca::Jet> const& jets)
{
    jets_ = SortedByPt(jets);
}

Momentum TruthVariables::JetPt(unsigned number) const
{
    return jets_.size() > number ? jets_.at(number).Pt() : at_rest;
}

}
