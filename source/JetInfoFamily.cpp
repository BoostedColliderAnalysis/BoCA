#include "JetInfoFamily.hh"

#include "Types.hh"
#include "delphes/Delphes.hh"
#include "Debug.hh"

namespace analysis {

JetInfoFamily::JetInfoFamily()
{
    Debug();
}

JetInfoFamily::JetInfoFamily(float bdt)
{
    SetBdt(bdt);
}

void JetInfoFamily::AddDaughter(int)
{
//     if (!constituents().empty()) {
//         Error(constituents().size(), constituents().front().family().particle().id());
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
    Debug(family.particle().id(), family.mother_1().id(), weight);
    family_fractions_[family] += weight;
}

void JetInfoFamily::ExtractFamilyFraction()
{
    Info();
//     for (auto const& constituent : constituents())
//         family_fractions_[constituent.family()] += constituent.Momentum().Pt();
}

struct SortPairs {
    template <typename Template>
    bool operator()(const std::pair<Template, float>& pair_1, const std::pair<Template, float>& pair_2)
    {
        return (pair_1.second < pair_2.second);
    }
};

Family JetInfoFamily::MaximalFamily()
{
    Debug();
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
    Info(id);
    ExtractFamilyFraction();
    for (auto const& pair : family_fractions_) {
        if (pair.first.particle().id() == id || pair.first.mother_1().id() == id)
            AddParticle(id, pair.second);
        else if (pair.first.particle().id() == -id || pair.first.mother_1().id() == -id)
            AddParticle(-id, pair.second);
        else
            AddParticle(pair.first.particle().id(), pair.second);
    }
}

void JetInfoFamily::ExtractFraction(int id, int mother_id)
{
    Info(id, mother_id);
    for (auto const& pair : family_fractions_) {
        if (std::abs(pair.first.particle().id()) == id && std::abs(pair.first.mother_1().id()) == mother_id)
            AddParticle(pair.first.particle().id(), pair.second);
        else
            AddParticle(Id::isr, pair.second);
    }
}

void JetInfoFamily::ExtractAbsFraction(int id)
{
    Info(id);
    ExtractFamilyFraction();
    for (auto const& pair : family_fractions_) {
        if (std::abs(pair.first.particle().id()) == id || std::abs(pair.first.mother_1().id()) == id)
            AddParticle(id, pair.second);
        else
            AddParticle(pair.first.particle().id(), pair.second);
    }
}

float JetInfoFamily::GetWeightSum() const
{
    Debug(id_fractions_.size());
    float weight_sum = std::accumulate(begin(id_fractions_), end(id_fractions_), 0.0, [](float previous, const std::pair<int, float>& pair) {
        return (previous + pair.second);
    });
    Detail(weight_sum);
    return weight_sum;
}

float JetInfoFamily::Fraction(int id) const
{
    Info(id);
    if (!id_fractions_.count(id))
        return 0;
    if (GetWeightSum() == 0)
        return 0;
    return (id_fractions_.at(id) / GetWeightSum());
}

float JetInfoFamily::MaximalFraction() const
{
    Info();
    std::pair<int, float> maximal_weight = *std::max_element(id_fractions_.begin(), id_fractions_.end(), SortPairs());
    if (GetWeightSum() == 0)
        return 0;
    else
        return (maximal_weight.second / GetWeightSum());
}

int JetInfoFamily::MaximalId() const
{
    Debug();
    return std::max_element(id_fractions_.begin(), id_fractions_.end(), SortPairs())->first;
}

void JetInfoFamily::PrintAllInfos(const Severity) const
{
    Debug();
//     for (auto pair = id_fractions_.begin(); pair != id_fractions_.end(); ++pair) {
//         if (GetWeightSum() == 0) Print(severity, "Jet Fraction", Name((*pair).first), 0);
//         else Print(severity, "Jet Fraction", Name((*pair).first), (*pair).second / GetWeightSum());
//     }
}

void JetInfoFamily::PrintAllconstituentInfos(const Severity) const
{
    Debug();
//     for (auto const& constituent : constituents())
//         Print(severity, "Jet Fraction", Name(constituent.family().particle().id()), Name(constituent.family().mother_1().id()), constituent.family().particle().Momentum.Pt(), constituent.family().mother_1().Momentum.Pt());
}
void JetInfoFamily::PrintAllFamInfos(const Severity) const
{
    Debug();
//     for (auto const& family_fraction : family_fractions_)
//         Print(severity, "Family Fraction", Name(family_fraction.first.particle().id()), Name(family_fraction.first.mother_1().id()), family_fraction.first.particle().Momentum.Pt(), family_fraction.first.mother_1().Momentum.Pt());
}


}
