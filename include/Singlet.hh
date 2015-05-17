# pragma once

# include "HTag.hh"
# include "JetInfo.hh"

namespace analysis
{
class Singlet : public HTag
{

public:

    Singlet(const fastjet::PseudoJet &singlet);

    inline fastjet::PseudoJet singlet() const {
        return singlet_;
    }

    fastjet::PseudoJet Jet() const {
        return singlet();
    }

    float VertexMass() const {
        return singlet_.user_info<JetInfo>().VertexMass();
    }

    float MaxDisplacement() const {
        return log(singlet_.user_info<JetInfo>().MaxDisplacement());
    }

    float MeanDisplacement() const {
        return log(singlet_.user_info<JetInfo>().MeanDisplacement());
    }

    float SumDisplacement() const {
        return log(singlet_.user_info<JetInfo>().SumDisplacement());
    }

    float Multiplicity() const {
        return singlet_.user_info<JetInfo>().VertexNumber();
    }

    float DeltaR() const {
        return GetDeltaR(singlet_);
    }

    float Spread() const {
        return GetSpread(singlet_);
    }

    float VertexDeltaR() const {
        return GetDeltaR(singlet_.user_info<JetInfo>().VertexJet());
    }

    float VertexSpread() const {
        return GetSpread(singlet_.user_info<JetInfo>().VertexJet());
    }

    float EnergyFraction() const {
        return singlet_.user_info<JetInfo>().VertexEnergy() / singlet_.e();
    }

    float Tag() const {
        return singlet_.user_info<JetInfo>().Tag();
    }

    float Bdt() const {
        return singlet_.user_info<JetInfo>().Bdt();
    }

protected:

    virtual inline std::string ClassName() const {
        return "Singlet";
    }

private:

    float log(const float Number) const {
        if (Number > 0) return std::log10(Number);
        else return std::log10(detector_geometry_.TrackerDistanceMin / 10);
    }

    float GetDeltaR(const fastjet::PseudoJet &jet) const;

    float GetSpread(const fastjet::PseudoJet &jet) const;

    fastjet::PseudoJet singlet_;

    DetectorGeometry detector_geometry_;

};
}

