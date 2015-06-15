# pragma once

# include "Quartet31.hh"

namespace heavyhiggs
{

/**
 * @brief An octet composed of two quartets
 *
 */
class Octet44 : public analysis::Multiplet<analysis::Quartet31, analysis::Quartet31>
{

public:

    using analysis::Multiplet<analysis::Quartet31, analysis::Quartet31>::Multiplet;

//     bool Overlap() const;

//     bool Overlap(const fastjet::PseudoJet &jet) const;

    inline analysis::Quartet31 Quartet1()const {
        return Multiplet1();
    }

    inline analysis::Quartet31 Quartet2() const {
        return Multiplet2();
    }

    inline float BottomBdt() const {
        return Quartet1().SingletJet().user_info<analysis::JetInfo>().Bdt() + Quartet1().Triplet().SingletJet().user_info<analysis::JetInfo>().Bdt() + Quartet2().SingletJet().user_info<analysis::JetInfo>().Bdt() + Quartet2().Triplet().SingletJet().user_info<analysis::JetInfo>().Bdt();
    }

    inline float PairBottomBdt() const {
        return Quartet2().SingletJet().user_info<analysis::JetInfo>().Bdt() + Quartet2().Triplet().SingletJet().user_info<analysis::JetInfo>().Bdt();
    }

protected:

    virtual inline std::string ClassName() const {
        return "Octet44";
    }

private:

};

}
