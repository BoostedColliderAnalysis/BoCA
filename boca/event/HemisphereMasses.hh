#pragma once
#include "boca/math/Range.hh"
#include "boca/math/GradedLorentzVector.hh"

namespace boca
{
/**
 * Hemisphere masses
 */
class HemisphereMasses
{

public:

    /**
     * @name Constructors
     * @{
     */

    /**
    * @brief Default constructor
    */
    HemisphereMasses();

    /**
    * @brief Constructor accepting two graded Lorentz vectors and the scalar momentum
    */
    HemisphereMasses(GradedLorentzVector<Momentum> const &negative, GradedLorentzVector<Momentum> const &positive, Momentum const &scalar_momentum);

    /**
    * @brief Constructor accepting ranges for the mass and jet broadenings
    */
    HemisphereMasses(Range<double> const &masses, Range<double> const &broadenings);
    //@}

    /**
     * @name Setter
     * @{
     */

    /**
    * @brief Set masses
    */
    void SetMasses(GradedLorentzVector<Momentum> const &negative, GradedLorentzVector<Momentum> const &positive);

    /**
    * @brief Set masses
    */
    void SetMasses(Range<double> const &masses);

    /**
    * @brief Set jet broadenings
    */
    void SetBroadenings(GradedLorentzVector<Momentum> const &negative, GradedLorentzVector<Momentum> const &positive, Momentum const &scalar_momentum);

    /**
    * @brief Set jet broadenings
    */
    void SetBroadenings(Range<double> const &broadenings);
    //@}

    /**
     * @name Jet mass related event shapes
     * @{
     */

    /**
     * @brief The high hemishpere mass squared divided by the visible energy squared
     */
    double MHigh2() const;

    /**
     * @brief The low hemishpere mass squared divided by the visible energy squared
     */
    double MLow2() const;

    /**
     * @brief The difference between the hemishpere masses squared divided by the visible energy squared
     */
    double MDiff2() const;
    //@}

    /**
     * @name Jet broadening related event shapes
     */
    //@{

    /**
     * @brief The wide jet broadening
     */
    double BMax() const;

    /**
     * @brief The narrow jet broadening
     */
    double BMin() const;

    /**
     * @brief The sum of the jet broadenings
     */
    double BSum() const;

    /**
     * @brief The difference of the jet broadenings
     */
    double BDiff() const;
    //@}

private:

    /**
     * @brief hemisphere masses
     */
    Range<double> masses_;

    /**
     * @brief The jet broadenings
     */
    Range<double> broadenings_;

};

}
