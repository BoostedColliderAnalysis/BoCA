/**
 * Copyright (C) 2015 Jan Hajer
 */
#include "JetInfoFamily.hh"

#include <numeric>
#include "Types.hh"
#include "delphes/Delphes.hh"
#include "Debug.hh"

namespace boca {

JetInfoFamily::JetInfoFamily()
{
    Debug0;
}

JetInfoFamily::JetInfoFamily(float bdt)
{
    SetBdt(bdt);
}

void JetInfoFamily::AddDaughter(int)
{
//     if (!constituents().empty()) {
//         Error(constituents().size(), constituents().front().family().Particle().Id());
//         constituents().front().family().AddDaughter(daughter);
//         return;
//     }
    Error("No constituent");
}

std::unordered_map<Family, float> JetInfoFamily::FamilyFractions()
{
    return family_fractions_;
}

void JetInfoFamily::AddFamily(Family const& family, float weight)
{
    Debug(family.Particle().Id(), family.Mother().Id(), weight);
    family_fractions_[family] += weight;
}

void JetInfoFamily::ExtractFamilyFraction()
{
    Info0;
//     for (auto const& constituent : constituents())
//         family_fractions_[constituent.family()] += constituent.Momentum().Pt();
}

struct SortPairs {
    template <typename Template>
    bool operator()(std::pair<Template, float> const& pair_1, std::pair<Template, float> const& pair_2)
    {
        return pair_1.second < pair_2.second;
    }
};

Family JetInfoFamily::MaximalFamily()
{
    Debug0;
    return std::max_element(family_fractions_.begin(), family_fractions_.end(), SortPairs())->first;
}

void JetInfoFamily::AddParticle(int constituent_id, float weight)
{
    Debug(constituent_id, weight);
    id_fractions_[constituent_id] += weight;
    Detail(id_fractions_[constituent_id]);
}

void JetInfoFamily::AddParticle(Id constituent_id, float weight)
{
    Debug(Name(constituent_id), weight);
    id_fractions_[int(constituent_id)] += weight;
    Detail(id_fractions_[int(constituent_id)]);
}

void JetInfoFamily::ExtractFraction(int id)
{
    INFO(id);
    ExtractFamilyFraction();
    for (auto const& pair : family_fractions_) {
        if (pair.first.Particle().Id() == id || pair.first.Mother().Id() == id)
            AddParticle(id, pair.second);
        else if (pair.first.Particle().Id() == -id || pair.first.Mother().Id() == -id)
            AddParticle(-id, pair.second);
        else
            AddParticle(pair.first.Particle().Id(), pair.second);
    }
}

void JetInfoFamily::ExtractFraction(int id, int mother_id)
{
    INFO(id, mother_id);
    for (auto const& pair : family_fractions_) {
        if (std::abs(pair.first.Particle().Id()) == id && std::abs(pair.first.Mother().Id()) == mother_id)
            AddParticle(pair.first.Particle().Id(), pair.second);
        else
            AddParticle(Id::isr, pair.second);
    }
}

void JetInfoFamily::ExtractAbsFraction(int id)
{
    INFO(id);
    ExtractFamilyFraction();
    for (auto const& pair : family_fractions_) {
        if (std::abs(pair.first.Particle().Id()) == id || std::abs(pair.first.Mother().Id()) == id)
            AddParticle(id, pair.second);
        else
            AddParticle(pair.first.Particle().Id(), pair.second);
    }
}

float JetInfoFamily::GetWeightSum() const
{
    Debug(id_fractions_.size());
    float weight_sum = std::accumulate(begin(id_fractions_), end(id_fractions_), 0.0, [](float previous, std::pair<int, float> const& pair) {
        return (previous + pair.second);
    });
    Detail(weight_sum);
    return weight_sum;
}

float JetInfoFamily::Fraction(int id) const
{
    INFO(id);
    if (!id_fractions_.count(id))
        return 0;
    if (GetWeightSum() == 0)
        return 0;
    return (id_fractions_.at(id) / GetWeightSum());
}

float JetInfoFamily::MaximalFraction() const
{
    Info0;
    std::pair<int, float> maximal_weight = *std::max_element(id_fractions_.begin(), id_fractions_.end(), SortPairs());
    if (GetWeightSum() == 0) return 0;
    else return (maximal_weight.second / GetWeightSum());
}

int JetInfoFamily::MaximalId() const
{
    Debug0;
    return std::max_element(id_fractions_.begin(), id_fractions_.end(), SortPairs())->first;
}

void JetInfoFamily::PrintAllInfos(Severity) const
{
    Debug0;
//     for (auto pair = id_fractions_.begin(); pair != id_fractions_.end(); ++pair) {
//         if (GetWeightSum() == 0) Print(severity, "Jet Fraction", Name((*pair).first), 0);
//         else Print(severity, "Jet Fraction", Name((*pair).first), (*pair).second / GetWeightSum());
//     }
}

void JetInfoFamily::PrintAllconstituentInfos(Severity) const
{
    Debug0;
//     for (auto const& constituent : constituents())
//         Print(severity, "Jet Fraction", Name(constituent.family().Particle().Id()), Name(constituent.family().Mother().Id()), constituent.family().Particle().Momentum.Pt(), constituent.family().Mother().Momentum.Pt());
}
void JetInfoFamily::PrintAllFamInfos(Severity) const
{
    Debug0;
//     for (auto const& family_fraction : family_fractions_)
//         Print(severity, "Family Fraction", Name(family_fraction.first.Particle().Id()), Name(family_fraction.first.Mother().Id()), family_fraction.first.Particle().Momentum.Pt(), family_fraction.first.Mother().Momentum.Pt());
}


}
