/**
 * Copyright (C) 2015 Jan Hajer
 */
#pragma once

#include "fastjet/PseudoJet.hh"

#include "Identification.hh"
#include "Constituent.hh"

class Jet;
namespace delphes
{
typedef ::Jet Jet;
}

namespace boca
{

typedef std::vector<fastjet::PseudoJet> Jets;

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

    JetInfo(::delphes::Jet const& jet);

    JetInfo(int charge);

    JetInfo(Constituent const& constituent);

    JetInfo(Constituent const& constituent, int charge);

    JetInfo(std::vector<Constituent> const& constituents);

    JetInfo operator+(JetInfo const&jet_info);

    JetInfo& operator+=(JetInfo const&jet_info);

    void AddConstituent(Constituent const& constituent);

    void AddConstituents(std::vector<Constituent> const& constituents);

    void AddConstituents(std::vector<Constituent> const& constituents, std::vector<Constituent> const& displaced_constituents);

    float VertexMass() const;

    float MaxDisplacement() const;

    float MeanDisplacement() const;

    float SumDisplacement() const;

    int VertexNumber() const;

    fastjet::PseudoJet VertexJet() const;

    float VertexEnergy() const;

    float ElectroMagneticRadius(fastjet::PseudoJet const& jet) const;

    float TrackRadius(fastjet::PseudoJet const& jet) const;

    float LeadingTrackMomentumFraction() const;

    float CoreEnergyFraction(fastjet::PseudoJet const& jet) const;

    float ElectroMagneticFraction() const;

    float ClusterMass() const;

    float TrackMass() const;

    bool BTag() const;

    bool TauTag() const;

    int Charge() const;

//     boca::Family Family() const;

    void SetDelphesTags(::delphes::Jet const& jet);

    void SetConstituents(std::vector<Constituent> const& constituents);

    bool SubStructure() const{
      return sub_structure_;
    }

    void SetSubStructure(bool sub_structure){
      sub_structure_ = sub_structure;
    }

private:

    JetInfo(std::vector<Constituent> const& constituents, std::vector<Constituent> const& dispalced_constituents);

    void SetConstituent(Constituent const& constituent);

    void SetBTag(bool b_tag);

    void SetTauTag(bool tau_tag);

    void SetCharge(int charge);

    std::vector<Constituent> constituents() const;

    std::vector<Constituent> displaced_constituents() const;

    void SecondayVertex() const;

    std::vector<Constituent> ApplyVertexResolution(std::vector<Constituent> constituents) const;

    bool VertexResultion(Constituent const& constituent) const;

    std::vector<Constituent> constituents_;

    std::vector<Constituent> displaced_constituents_;

    bool b_tag_ = 0;

    bool tau_tag_ = 0;

    int charge_;

    bool sub_structure_ = true;

};

}
