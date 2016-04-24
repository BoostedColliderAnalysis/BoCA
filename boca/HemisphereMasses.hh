#pragma once
#include "boca/physics/Range.hh"

namespace boca
{
/**
 * Hemisphere masses
 */
class HemisphereMasses
{

public:
    void SetMasses(Range<double> const& masses);
    void SetBroadenings(Range<double> const& broadenings);
    /**
     * Jet mass related event shapes
     */
    //@{
    /**
     * The high hemishpere mass squared divided by the visible energy squared
     */
    double MHigh2() const;
    /**
     * The low hemishpere mass squared divided by the visible energy squared
     */
    double MLow2() const;
    /**
     * The difference between the hemishpere masses squared divided by the visible energy squared
     */
    double MDiff2() const;
    //@}
    /**
     * Jet broadening related event shapes
     */
    //@{
    /**
     * The wide jet broadening
     */
    double BMax() const;
    /**
     * The narrow jet broadening
     */
    double BMin() const;
    /**
     * The sum of the jet broadenings
     */
    double BSum() const;
    /**
     * The difference of the jet broadenings
     */
    double BDiff() const;
    //@}
private:
    /**
     * hemisphere masses
     */
    Range<double> masses_;
    /**
     * The jet broadenings
     */
    Range<double> broadenings_;

};

}
