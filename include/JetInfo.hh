#pragma once

#include "fastjet/JetDefinition.hh"

#include "Identification.hh"
#include "Constituent.hh"

class Jet;
namespace delphes
{
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

    friend class InfoRecombiner;

    /**
     * @brief Constructor
     *
     */
    JetInfo();

    JetInfo(float bdt);

    JetInfo(const ::delphes::Jet& jet);

    JetInfo(int charge);

    JetInfo(const Constituent& constituent);

    JetInfo(const Constituent& constituent, int charge);

    JetInfo(const std::vector<Constituent>& constituents);

    JetInfo operator+(const JetInfo &jet_info);

    JetInfo& operator+=(const JetInfo &jet_info);

    void AddConstituent(const Constituent& constituent);

    void AddConstituents(const std::vector<Constituent>& constituents);

    void AddConstituents(const std::vector<Constituent>& constituents, const std::vector<Constituent>& displaced_constituents);

    float VertexMass() const;

    float MaxDisplacement() const;

    float MeanDisplacement() const;

    float SumDisplacement() const;

    int VertexNumber() const;

    fastjet::PseudoJet VertexJet() const;

    float VertexEnergy() const;

    float ElectroMagneticRadius(const fastjet::PseudoJet& jet) const;

    float TrackRadius(const fastjet::PseudoJet& jet) const;

    float LeadingTrackMomentumFraction() const;

    float CoreEnergyFraction(const fastjet::PseudoJet& jet) const;

    float ElectroMagneticFraction() const;

    float ClusterMass() const;

    float TrackMass() const;

    bool BTag() const;

    bool TauTag() const;

    int Charge() const;

    analysis::Family Family() const;

    void SetDelphesTags(const ::delphes::Jet& jet);

    void SetConstituents(const std::vector<Constituent>& constituents);

private:

    JetInfo(const std::vector<Constituent>& constituents, const std::vector<Constituent>& dispalced_constituents);

    void SetConstituent(const Constituent& constituent);

    void SetBTag(bool b_tag);

    void SetTauTag(bool tau_tag);

    void SetCharge(int charge);

    std::vector<Constituent> constituents() const;

    std::vector<Constituent> displaced_constituents() const;

    void SecondayVertex() const;

    std::vector<Constituent> ApplyVertexResolution(std::vector<Constituent> constituents) const;

    bool VertexResultion(const Constituent& constituent) const;

    std::vector<Constituent> constituents_;

    std::vector<Constituent> displaced_constituents_;

    bool b_tag_ = 0;

    bool tau_tag_ = 0;

    int charge_ = LargeNumber();

};

/**
 * @brief sort vector of jets with largest bdt at the front
 *
 */
struct SortByBdt {
  bool operator()(const fastjet::PseudoJet& jet_1, const fastjet::PseudoJet& jet_2);
};

}
