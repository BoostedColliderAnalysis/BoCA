/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#pragma once

#include <boost/range/algorithm/unique.hpp>

#include "boca/generic/Vector.hh"
#include "boca/fastjet/ClusterSequence.hh"
#include "boca/multiplets/Multiplet.hh"
#include "boca/multiplets/Sort.hh"

namespace boca
{

/**
* @ingroup Multiplets
* @brief Two body base class
*
*/
template <typename Multiplet_1_, typename Multiplet_2_>
class TwoBody : public Multiplet
{

public:

    /**
    * @name Constructors
    * @{
    */

    /**
    * @brief Default constructor
    *
    */
    TwoBody() {};

    /**
    * @brief Constructor accepting two different Multiplets
    */
    TwoBody(Multiplet_1_ const &multiplet_1, Multiplet_2_ const &multiplet_2)
    {
        multiplet_1_ = multiplet_1;
        multiplet_2_ = multiplet_2;
        if (multiplet_1.Bdt() != InitialValue() && multiplet_2.Bdt() != InitialValue()) SetBdt(multiplet_1.Bdt(), multiplet_2.Bdt());
        else if (multiplet_1.Bdt() != InitialValue()) SetBdt(multiplet_1.Bdt());
        else if (multiplet_2.Bdt() != InitialValue()) SetBdt(multiplet_2.Bdt());
    }
    //@}

    /**
    * @name Enforce Multiplet from other Objects
    *
    * this ensures strong type safety
    * @{
    */

    /**
    * @brief Enforce Multiplet from a single other Multiplet
    */
    template<typename Multiplet_3_, typename Multiplet_4_>
    void Enforce(TwoBody<Multiplet_3_, Multiplet_4_> const &multiplet)
    {
        multiplet_1_.Enforce(multiplet.Multiplet1());
        multiplet_2_.Enforce(multiplet.Multiplet2());
        SetBdt(multiplet.Bdt());
    }

    /**
    * @brief Enforce a Multiplet from a Jet
    */
    void Enforce(boca::Jet const &jet)
    {
        Enforce(jet, jet.Bdt());
    }

    /**
    * @brief Enforce a Multiplet from a vector of jets
    */
    void Enforce(std::vector<boca::Jet> const &jets)
    {
        if (jets.empty()) return;
        if (jets.size() == 1) return EnforceJet(jets.front(), jets.front().Bdt());
        multiplet_1_.Enforce(jets.at(0));
        multiplet_2_.Enforce(jets.at(1));
        SetBdt(jets.at(0).Bdt(), jets.at(1).Bdt());
        if (jets.size() > 2) std::cout << "to many jets to enforce a multiplet" << std::endl;
    }

    /**
    * @brief Enforce a Multiplet from a jet and a seperate bdt
    */
    void Enforce(boca::Jet const &jet, double bdt)
    {
        if (jet.Constituents().size() < 2) return EnforceJet(jet, bdt);
        ClusterSequence cluster_sequence(jet.Constituents(), Settings::SubJetDefinition());
        auto jets = cluster_sequence.ExclusiveJetsUpTo(2);
        if (jets.size() != 2) std::cout << "not the sub-jet number we expected: " << jets.size();
        multiplet_1_.Enforce(jets.at(0), bdt);
        multiplet_2_.Enforce(jets.at(1), bdt);
        SetBdt(bdt);
    }

    /**
    * @brief Enforce a Multiplet from a jet and a seperate bdt
    */
    void EnforceJet(boca::Jet jet, double bdt)
    {
        jet.Info().SetSubStructure(false);
        multiplet_1_.Enforce(jet / 2, bdt);
        multiplet_2_.Enforce(jet / 2, bdt);
        SetBdt(bdt);
    }
    //@}

    /**
    * @brief Setter for two Multiplets
    */
    void Set(Multiplet_1_ const &multiplet_1, Multiplet_2_ const &multiplet_2)
    {
        multiplet_1_ = multiplet_1;
        multiplet_2_ = multiplet_2;
    }

    /**
    * @name Global accessors
    * @{
    */

    /**
    * @brief Accessor for event shapes
    */
    boca::EventShapes EventShapes() const
    {
        return event_shapes_.Get([this]() {
            return boca::EventShapes(Jets());
        });
    }

    /**
    * @brief Accessor for jets
    */
    std::vector<boca::Jet> Jets() const override
    {
        return Combine(Multiplet1().Jets(), Multiplet2().Jets());
    }

    /**
    * @brief Accessor for lorentz vectors
    */
    std::vector<LorentzVector<Momentum>> LorentzVectors() const override
    {
        return DeltaR() > Settings::JetConeSize() ? Combine(Multiplet1().LorentzVectors(), Multiplet2().LorentzVectors()) : std::vector<LorentzVector<Momentum>> {Jet().LorentzVector()};
    }
    //@}

    /**
    * @name Acessors to the Multiplets
    * @{
    */

    /**
    * @brief Accessor to the first multiplet
    */
    Multiplet_1_ &Multiplet1()
    {
        return multiplet_1_;
    }

    /**
    * @brief Const accessor to the first multiplet
    */
    Multiplet_1_ const &Multiplet1() const
    {
        return multiplet_1_;
    }

    /**
    * @brief Accessor to the second multiplet
    */
    Multiplet_2_ &Multiplet2()
    {
        return multiplet_2_;
    }

    /**
    * @brief Const accessor to the second multiplet
    */
    Multiplet_2_ const &Multiplet2() const
    {
        return multiplet_2_;
    }
    //@}

    /**
    * @name Calculate overlap between multiplets
    * @{
    */

    /**
    * @brief Overlap with another multiplet
    */
    template <typename Multiplet_3_>
    bool Overlap(Multiplet_3_ const &multiplet) const
    {
        return multiplet.Overlap(multiplet_1_) || multiplet.Overlap(multiplet_2_);
    }

    /**
    * @brief Overlap with a singlet
    */
    bool Overlap(boca::Singlet const &singlet) const
    {
        return multiplet_1_.Overlap(singlet) || multiplet_2_.Overlap(singlet);
    }

    /**
    * @brief Overlap with a jet
    */
    bool Overlap(boca::Jet const &jet) const
    {
        return multiplet_1_.Overlap(jet) || multiplet_2_.Overlap(jet);
    }

    /**
    * @brief Overlap within a multiplet
    */
    bool Overlap() const
    {
        return multiplet_1_.Overlap(multiplet_2_);
    }
    //@}

    /**
    * @name Energy related accessors
    * @{
    */

    /**
    * @brief Transverse momentum \f$\Delta p_T\f$
    */
    Momentum DeltaPt() const
    {
        return Multiplet2().Pt() - Multiplet1().Pt();
    }

    /**
    * @brief Scalar sum of transverse momenta \f$H_T = \sum_i \left|p_{Ti}\right|\f$
    */
    Momentum Ht() const
    {
        return Multiplet1().Ht() + Multiplet2().Ht();
    }

    /**
    * @brief Mass difference
    */
    boca::Mass DeltaM() const
    {
        return Multiplet2().Mass() - Multiplet1().Mass();
    }

    /**
    * @brief Difference in the scalar sum of transverse moenta
    */
    Momentum DeltaHt() const
    {
        return Multiplet2().Ht() - Multiplet1().Ht();
    }

    /**
    * @brief Mass difference to a particle with Id
    */
    boca::Mass MassDifferenceTo(Id id) const
    {
        return boost::units::abs(Mass() - MassOf(id));
    }
    //@}

    /**
    * @name Angle related accessors
    * @{
    */

    /**
    * @brief Difference rapidity \f$\Delta y\f$
    */
    Angle DeltaRap() const
    {
        return Multiplet1().DeltaRapTo(Multiplet2());
    }

    /**
    * @brief Difference in azimuth \f$\Delta \phi\f$
    */
    Angle DeltaPhi() const
    {
        return Multiplet1().DeltaPhiTo(Multiplet2());
    }

    /**
    * @brief Difference in angular distance \f$\Delta R = \sqrt{(\Delta y)^2 + (\Delta \phi)^2}\f$
    */
    Angle DeltaR() const
    {
        return Multiplet1().DeltaRTo(Multiplet2());
    }

    /**
    * @brief Line in agular space from the second component to the first
    */
    Line2<Angle> AngleLine() const
    {
        return {Multiplet2().Angles(), Multiplet1().AnglesMinTo(Multiplet2())};
    }
    //@}

    /**
    * @name Sub-structure
    * @{
    */

    /**
    * @brief Pull towards another multiplet
    */
    template<typename Multiplet_>
    Angle PullTo(Multiplet_ const &multiplet) const
    {
        return ConstituentJet().PullAngle(DeltaTo(multiplet));
    }

    /**
    * @brief Pull from the first component to the second
    */
    Angle Pull12() const
    {
        return Multiplet1().PullTo(Multiplet2());
    }

    /**
    * @brief Pull from the second component to the first
    */
    Angle Pull21() const
    {
        return Multiplet2().PullTo(Multiplet1());
    }

    /**
    * @brief Dipolarity according to \f$\mathcal D = \frac{1}{R_{12}^2 p_{TJ}} \sum_{i\in J}p_{Ti}R_i^2\f$
    */
    double Dipolarity() const
    {
        if (Pt() <= Settings::MinCellPt() || DeltaR() <= Settings::MinCellResolution()) return 0;
        auto sum = ConstituentJet().DipolaritySum(AngleLine());
        auto dipolarity = sum / Pt() / sqr(DeltaR());
        if(dipolarity > 100) std::cerr << "dipol: " << dipolarity << " sum: " <<  sum <<  " inv mom: " << 1. / Pt() << " inv deltar: " << 1. / sqr(DeltaR()) <<  "\n";
        return dipolarity;
    }
    //@}

    /**
    * @name Selectors for subcomponents
    * @{
    */

    /**
    * @brief Harder subcomponent
    */
    boca::Jet HarderComponent() const {
        return Multiplet1().Pt() > Multiplet2().Pt() ? Multiplet1().Jet() : Multiplet2().Jet();
    }

    /**
    * @brief Softer subcomponent
    */
    boca::Jet SofterComponent() const {
        return Multiplet1().Pt() < Multiplet2().Pt() ? Multiplet1().Jet() : Multiplet2().Jet();
    }

    /**
    * @brief Subcomponent with the better mass of an object with Id
    */
    boca::Jet ComponentWithBetterMass(Id id) const {
        return Multiplet1().MassDifferenceTo(id) < Multiplet2().MassDifferenceTo(id) ? Multiplet1().Jet() : Multiplet2().Jet();
    }

    boca::Jet ComponentWithWorseMass(Id id) const {
        return Multiplet1().MassDifferenceTo(id) > Multiplet2().MassDifferenceTo(id) ? Multiplet1().Jet() : Multiplet2().Jet();
    }
    //@}

    /**
    * @brief Particle likeliness \f$\rho = \frac{2 m}{p_T \Delta R}\f$
    *
    * \f$\rho = 1\f$ for a particle
    *
    */
    double Rho() const
    {
        return Pt() > Settings::MinCellPt() && DeltaR() > Settings::MinCellResolution() ? static_cast<double>(Mass() / Pt() / DeltaR() * 2_rad) : 0;
    }

    /**
    * @brief Charge
    */
    int Charge() const
    {
        return Multiplet1().Charge() + Multiplet2().Charge();
    }

protected:

    void SetMultiplet1(Multiplet_1_ const &multiplet_1)
    {
        multiplet_1_ = multiplet_1;
    }

    void SetMultiplet2(Multiplet_2_ const &multiplet_2)
    {
        multiplet_2_ = multiplet_2;
    }

private:

    boca::Jet GetJet() const override
    {
        return Join(Multiplet1(), Multiplet2());
    }

    Singlet GetConstituentJet() const override
    {
        return JoinConstituents(Multiplet1(), Multiplet2());
    }

    Multiplet_1_ multiplet_1_;

    Multiplet_2_ multiplet_2_;

};

template<typename Multiplet_1_, typename Multiplet_2_>
Jet Join(Multiplet_1_ const &multiplet_1, Multiplet_2_ const &multiplet_2)
{
    return Join(multiplet_1.Jet(), multiplet_2.Jet());
}

template<typename Multiplet_1_, typename Multiplet_2_>
boca::Singlet JoinConstituents(Multiplet_1_ const &multiplet_1, Multiplet_2_ const &multiplet_2)
{
    auto constituents = SortedByPt(Combine(multiplet_1.Constituents(), multiplet_2.Constituents()));
    boost::erase(constituents, boost::unique<boost::return_found_end>(constituents));
    return Join(constituents);
}

template<typename Multiplet_>
Jet Join(Jet const &jet, Multiplet_ const &multiplet)
{
    return Join(jet, multiplet.Jet());
}

template<typename Multiplet_>
Jet Join(Multiplet_ const &multiplet, Jet const &jet)
{
    return Join(jet, multiplet.Jet());
}

}

