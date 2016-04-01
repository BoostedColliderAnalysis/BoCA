/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#include "JetInfoFamily.hh"

#include <numeric>
#include "generic/Types.hh"
#include "delphes/Delphes.hh"
#include "generic/DEBUG.hh"

namespace boca {

JetInfoFamily::JetInfoFamily()
{
    DEBUG0;
}

JetInfoFamily::JetInfoFamily(double bdt)
{
    SetBdt(bdt);
}

void JetInfoFamily::AddDaughter(int)
{
//     if (!constituents().empty()) {
//         ERROR(constituents().size(), constituents().front().family().Member(Relative::particle).Id());
//         constituents().front().family().AddDaughter(daughter);
//         return;
//     }
    ERROR("No constituent");
}

std::unordered_map<Family, double> JetInfoFamily::FamilyFractions()
{
    return family_fractions_;
}

void JetInfoFamily::AddFamily(Family const& family, double weight)
{
    DEBUG(family.Member(Relative::particle).Id(), family.Member(Relative::mother).Id(), weight);
    family_fractions_[family] += weight;
}

void JetInfoFamily::ExtractFamilyFraction()
{
    INFO0;
//     for (auto const& constituent : constituents())
//         family_fractions_[constituent.family()] += constituent.Momentum().Pt();
}

struct SortPairs {
    template <typename Template>
    bool operator()(std::pair<Template, double> const& pair_1, std::pair<Template, double> const& pair_2)
    {
        return pair_1.second < pair_2.second;
    }
};

Family JetInfoFamily::MaximalFamily()
{
    DEBUG0;
    return std::max_element(family_fractions_.begin(), family_fractions_.end(), SortPairs())->first;
}

void JetInfoFamily::AddParticle(int constituent_id, double weight)
{
    DEBUG(constituent_id, weight);
    id_fractions_[constituent_id] += weight;
    DETAIL(id_fractions_[constituent_id]);
}

void JetInfoFamily::AddParticle(Id constituent_id, double weight)
{
    DEBUG(Name(constituent_id), weight);
    id_fractions_[int(constituent_id)] += weight;
    DETAIL(id_fractions_[int(constituent_id)]);
}

void JetInfoFamily::ExtractFraction(int id)
{
    INFO(id);
    ExtractFamilyFraction();
    for (auto const& pair : family_fractions_) {
        if (pair.first.Member(Relative::particle).Id() == id || pair.first.Member(Relative::mother).Id() == id)
            AddParticle(id, pair.second);
        else if (pair.first.Member(Relative::particle).Id() == -id || pair.first.Member(Relative::mother).Id() == -id)
            AddParticle(-id, pair.second);
        else
            AddParticle(pair.first.Member(Relative::particle).Id(), pair.second);
    }
}

void JetInfoFamily::ExtractFraction(int id, int mother_id)
{
    INFO(id, mother_id);
    for (auto const& pair : family_fractions_) {
        if (std::abs(pair.first.Member(Relative::particle).Id()) == id && std::abs(pair.first.Member(Relative::mother).Id()) == mother_id)
            AddParticle(pair.first.Member(Relative::particle).Id(), pair.second);
        else
            AddParticle(Id::isr, pair.second);
    }
}

void JetInfoFamily::ExtractAbsFraction(int id)
{
    INFO(id);
    ExtractFamilyFraction();
    for (auto const& pair : family_fractions_) {
        if (std::abs(pair.first.Member(Relative::particle).Id()) == id || std::abs(pair.first.Member(Relative::mother).Id()) == id)
            AddParticle(id, pair.second);
        else
            AddParticle(pair.first.Member(Relative::particle).Id(), pair.second);
    }
}

double JetInfoFamily::GetWeightSum() const
{
    DEBUG(id_fractions_.size());
    double weight_sum = std::accumulate(begin(id_fractions_), end(id_fractions_), 0.0, [](double previous, std::pair<int, double> const& pair) {
        return (previous + pair.second);
    });
    DETAIL(weight_sum);
    return weight_sum;
}

double JetInfoFamily::Fraction(int id) const
{
    INFO(id);
    if (!id_fractions_.count(id))
        return 0;
    if (GetWeightSum() == 0)
        return 0;
    return (id_fractions_.at(id) / GetWeightSum());
}

double JetInfoFamily::MaximalFraction() const
{
    INFO0;
    std::pair<int, double> maximal_weight = *std::max_element(id_fractions_.begin(), id_fractions_.end(), SortPairs());
    if (GetWeightSum() == 0) return 0;
    else return (maximal_weight.second / GetWeightSum());
}

int JetInfoFamily::MaximalId() const
{
    DEBUG0;
    return std::max_element(id_fractions_.begin(), id_fractions_.end(), SortPairs())->first;
}

}
