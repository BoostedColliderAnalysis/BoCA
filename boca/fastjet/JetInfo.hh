/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#pragma once

#include "fastjet/PseudoJet.hh"

#include "boca/generic/Mutable.hh"
#include "boca/fastjet/Identification.hh"
#include "boca/physics/Constituent.hh"

namespace boca
{
class Jet;
class Singlet;

/**
 * @brief Jet infos subclassed from Fastjet
 *
 */
class JetInfo: public Identification,
    public fastjet::PseudoJet::UserInfoBase,
    boost::additive<JetInfo>
{

public:

    JetInfo();

    JetInfo(double bdt);

    JetInfo(::delphes::Jet const &jet);

    JetInfo(int charge);

    JetInfo(Constituent const &constituent);

    JetInfo(Constituent const &constituent, int charge);

    JetInfo(std::vector<Constituent> const &constituents);

    JetInfo &operator+=(JetInfo const &jet_info);

    void AddConstituent(Constituent const &constituent);

    void AddConstituents(std::vector<Constituent> const &constituents);

    Mass VertexMass() const;

    Length MaxDisplacement() const;

    Length MeanDisplacement() const;

    Length SumDisplacement() const;

    int VertexNumber() const;

    boca::Singlet VertexJet() const;

    Energy VertexEnergy() const;

    Angle ElectroMagneticRadius(boca::Jet const &jet) const;

    Angle TrackRadius(boca::Jet const &jet) const;

    double LeadingTrackMomentumFraction() const;

    double CoreEnergyFraction(boca::Jet const &jet) const;

    double ElectroMagneticFraction() const;

    Mass ClusterMass() const;

    Mass TrackMass() const;

    bool BTag() const;

    bool TauTag() const;

    int Charge() const;

    void SetDelphesTags(::delphes::Jet const &jet);

    void SetConstituents(std::vector<Constituent> const &constituents);

    bool SubStructure() const;

    void SetSubStructure(bool sub_structure);

    void SetBTag(bool b_tag);

    void SetCharge(int charge);

    std::vector<Family> Families() const;

    bool ContainsDetectorPart(DetectorPart detector_part) const;

    void SetMuBTag(double min_x, double fraction);

    double EnergyRatio() const;

    double MomentumRatio() const;

    bool InMuonChamber() const;

//     JetInfo(JetInfo const&) = default;
//     JetInfo(JetInfo &&) = default;
//     JetInfo &operator=(JetInfo const&) & = default;
//     JetInfo &operator=(JetInfo &&) & = default;
//
// protected:
//
//     ~JetInfo() {}

private:

    JetInfo(std::vector<Constituent> const &constituents, std::vector<Constituent> const &dispalced_constituents);

    void SetConstituent(Constituent const &constituent);

    void SetTauTag(bool tau_tag);

    std::vector<Constituent> Constituents() const;

    std::vector<Constituent> DisplacedConstituents() const;

    void SecondayVertex() const;

    std::vector<Constituent> constituents_;

    Mutable<std::vector<Constituent>> displaced_constituents_;

    bool b_tag_ = 0;

    bool tau_tag_ = 0;

    int charge_ = 0;

    bool sub_structure_ = true;

    double min_x_ = 0;

    double fraction_ = 0;

};

}
