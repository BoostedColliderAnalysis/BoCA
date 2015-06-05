# pragma once

# include "Quintet.hh"

namespace toppartner
{

class Quattuordecuplet : public analysis::Identification
{

public:

    Quattuordecuplet() {}

    Quattuordecuplet(const analysis::Quintet &quintet_1, const analysis::Quintet &quintet_2, const analysis::Doublet & doublet_1, const analysis::Doublet &doublet_2);

    inline analysis::Doublet doublet()const {
        return doublet_1_;
    }

    inline analysis::Doublet triplet()const {
        return doublet_2_;
    }

    inline fastjet::PseudoJet doublet_jet() const {
        return doublet_1_.Jet();
    }

    inline fastjet::PseudoJet triplet_jet() const {
        return doublet_2_.Jet();
    }

    inline fastjet::PseudoJet Jet() const {
        return doublet_jet() + triplet_jet();
    }

    inline float Ht() const {
        return doublet_1_.Ht() + doublet_2_.Ht();
    }

    inline float DeltaHt() const {
      return doublet_2_.Ht() - doublet_1_.Ht();
    }

    inline float DeltaPt() const {
        return doublet_jet().pt() - triplet_jet().pt();
    }

    inline float DeltaRap() const {
        return std::abs(doublet_jet().rap() - triplet_jet().rap());
    }

    inline float DeltaPhi() const {
        return doublet_jet().delta_phi_to(triplet_jet());
    }

    inline float DeltaR() const {
        return doublet_jet().delta_R(triplet_jet());
    }

    inline float DeltaM() const {
      return doublet_jet().m() - triplet_jet().m();
    }

    inline float MassDifferenceTo(const ParticleId particle_id) const {
        return std::abs(Jet().m() - Mass(particle_id));
    }

    bool overlap() const {
//         if (doublet_1.Singlet1().delta_R(doublet_2.singlet()) < detector_geometry_.JetConeSize) return true;
//         if (doublet_1.Singlet1().delta_R(doublet_2.doublet().Singlet1()) < detector_geometry_.JetConeSize) return true;
//         if (doublet_1.Singlet1().delta_R(doublet_2.doublet().Singlet2()) < detector_geometry_.JetConeSize) return true;
//         if (doublet_1.Singlet2().delta_R(doublet_2.singlet()) < detector_geometry_.JetConeSize) return true;
//         if (doublet_1.Singlet2().delta_R(doublet_2.doublet().Singlet1()) < detector_geometry_.JetConeSize) return true;
//         if (doublet_1.Singlet2().delta_R(doublet_2.doublet().Singlet2()) < detector_geometry_.JetConeSize) return true;
        return false;
    }

    //FIXME only two bdt, not four !!
    analysis::Quintet SubMultiplet1() const {
      return quintet_1_;
    }

    analysis::Quintet SubMultiplet2() const {
      return quintet_2_;
    }

protected:

    virtual inline std::string ClassName() const {
        return "Quattuordecuplet";
    }

private:

  analysis::Doublet doublet_1_;

  analysis::Doublet doublet_2_;

  analysis::Quintet quintet_1_;

  analysis::Quintet quintet_2_;

  analysis::DetectorGeometry detector_geometry_;
};

}
