#pragma once

#include <map>
#include <unordered_map>

// #include "fastjet/JetDefinition.hh"

#include "Identification.hh"
#include "Constituent.hh"

class Jet;
namespace delphes{
  typedef ::Jet Jet;
}

namespace analysis
{

/**
 * @brief Jet infos subclassed from Fastjet
 *
 */
class JetInfo: public Identification, public fastjet::PseudoJet::UserInfoBase
{

public:

    /**
     * @brief Constructor
     *
     */
    JetInfo();

    JetInfo(const float bdt);

    JetInfo(const ::delphes::Jet &jet);

    JetInfo(const bool b_tag);

//     JetInfo(const bool b_tag, const int charge);

    JetInfo(const bool b_tag, const bool tau_tag);

    JetInfo(const int charge);

    JetInfo(const Constituent &constituent);

    JetInfo(const Constituent &constituent, const int charge);

    JetInfo(const std::vector<Constituent> &constituents);

    JetInfo(const std::vector<Constituent> &constituents, const std::vector<Constituent> &dispalced_constituents);

//     JetInfo operator+(const JetInfo &jet_info);

    void AddConstituent(const Constituent &constituent);

    void AddConstituents(const std::vector<Constituent> &constituents);

    void AddDaughter(const int daughter);

    std::vector<Constituent> constituents() const;

    std::vector<Constituent> displaced_constituents() const;

    std::unordered_map<Family, float> FamilyFractions();

    float VertexMass() const;

    float MaxDisplacement() const;

    float MeanDisplacement() const;

    float SumDisplacement() const;

    int VertexNumber() const;

    fastjet::PseudoJet VertexJet() const;

    float VertexEnergy() const;

    void ExtractFraction(const int id);

    void ExtractAbsFraction(const int id);

    void ExtractFraction(const int id, const int mother_id);

    void PrintAllInfos(const Severity severity) const;

    void PrintAllconstituentInfos(const Severity severity) const;

    void PrintAllFamInfos(const Severity severity) const;

    float MaximalFraction() const;

    float Fraction(const int id) const;

    int MaximalId() const;

    void AddFamily(const Family &family, const float weight);

    void ExtractFamilyFraction();

    Family MaximalFamily();

    float ElectroMagneticRadius(const fastjet::PseudoJet &jet) const;

    float TrackRadius(const fastjet::PseudoJet &jet) const;

    float LeadingTrackMomentumFraction() const;

    float CoreEnergyFraction(const fastjet::PseudoJet &jet) const;

    float ElectroMagneticFraction() const;

    float ClusterMass() const;

    float TrackMass() const;

    void SetBTag(const bool b_tag) {
        b_tag_ = b_tag;
    }

    bool BTag() const {
        return b_tag_;
    }

    void SetTauTag(const bool tau_tag) {
        tau_tag_ = tau_tag;
    }

    bool TauTag() const {
        return tau_tag_;
    }

    void SetCharge(const int charge) {
        charge_ = charge;
    }

    int Charge() const;

    void SetDelphesTags(const ::delphes::Jet &jet);

private:

    void AddParticle(const int constituent_id, const float weight);

    void AddParticle(const Id constituent_id, const float weight);

    float GetWeightSum() const;

    std::vector<Constituent> ApplyVertexResolution(std::vector< Constituent > constituents) const;

    bool VertexResultion(const Constituent &constituent) const;

    std::vector<Constituent> constituents_;

    std::vector<Constituent> displaced_constituents_;

    std::unordered_map<Family, float> family_fractions_;

    std::map<int, float> id_fractions_;

    bool b_tag_ = 0;

    bool tau_tag_ = 0;

    int charge_ = LargeNumber();

};

/**
 * @brief sort vector of jets with largest bdt at the front
 *
 */
struct SortByBdt {
    bool operator()(const fastjet::PseudoJet &jet_1, const fastjet::PseudoJet &jet_2);
};

}
