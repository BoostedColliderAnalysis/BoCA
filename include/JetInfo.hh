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
class Jet;

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

    Mass VertexMass() const;

    Length MaxDisplacement() const;

    Length MeanDisplacement() const;

    Length SumDisplacement() const;

    int VertexNumber() const;

    boca::Jet VertexJet() const;

    Energy VertexEnergy() const;

    Angle ElectroMagneticRadius(boca::Jet const& jet) const;

    Angle TrackRadius(boca::Jet const& jet) const;

    float LeadingTrackMomentumFraction() const;

    float CoreEnergyFraction(boca::Jet const& jet) const;

    float ElectroMagneticFraction() const;

    Mass ClusterMass() const;

    Mass TrackMass() const;

    bool BTag() const;

    bool TauTag() const;

    int Charge() const;

    void SetDelphesTags(::delphes::Jet const& jet);

    void SetConstituents(std::vector<Constituent> const& constituents);

    bool SubStructure() const;

    void SetSubStructure(bool sub_structure);

    void SetBTag(bool b_tag);

    void SetCharge(int charge);

private:

    JetInfo(std::vector<Constituent> const& constituents, std::vector<Constituent> const& dispalced_constituents);

    void SetConstituent(Constituent const& constituent);

    void SetTauTag(bool tau_tag);

    std::vector<Constituent> Constituents() const;

    std::vector<Constituent> DisplacedConstituents() const;

    void SecondayVertex() const;

    std::vector<Constituent> ApplyVertexResolution(std::vector<Constituent> constituents) const;

    bool VertexResultion(boca::Constituent constituent) const;

    std::vector<Constituent> constituents_;

    std::vector<Constituent> displaced_constituents_;

    bool b_tag_ = 0;

    bool tau_tag_ = 0;

    int charge_ = -9999;

    bool sub_structure_ = true;

};

}
