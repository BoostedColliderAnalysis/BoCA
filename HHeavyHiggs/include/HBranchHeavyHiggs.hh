# ifndef HBranchHeavyHiggs_hh
# define HBranchHeavyHiggs_hh

# include "HBranch.hh"
# include "HObject.hh"
# include "HTriplePair.hh"

namespace hheavyhiggs
{

class HAnalysisHeavyHiggsDelphes;
class HAnalysisHeavyHiggsPgs;
class HAnalysisHeavyHiggsParton;
class HAnalysisMva;
class HHeavyHiggsJetTag;
class HMva;
class HBranchHeavyHiggs;
class HEventBranch;
class HMvaEvent;

}

/**
 * @brief Class for saving leptons to root
 *
 */
class hheavyhiggs::HBranchHeavyHiggs : public HBranch
{

public:

    int JetNumber;
    int BTag;
    float Isolation;

    float BottomRap1;
    float BottomRap2;
    float BottomDeltaRap;
    float BottomSumRap;

    float BottomPhi1;
    float BottomPhi2;
    float BottomDeltaPhi;
    float BottomSumPhi;

    float BottomPt1;
    float BottomPt2;
    float BottomInvMass;
    float BottomDeltaPt;

//     float TopRap1;
//     float TopRap2;
//     float TopDeltaRap;
//
//     float TopPhi1;
//     float TopPhi2;
//     float TopDeltaPhi;
//
//     float TopPt1;
//     float TopPt2;
//     float TopInvMass;

    HBranchHeavyHiggs();

    virtual ~HBranchHeavyHiggs() {};

private:

    ClassDef(HBranchHeavyHiggs, 1)

};




/**
 *
 * @brief Higgs cpv tagger root tree structure
 *
 */
class hheavyhiggs::HEventBranch : public HBranch
{

public:

    HEventBranch();

    float ScalarHt;
    int JetNumber;
    int BottomNumber;
    int LeptonNumber;

    float HeavyParticleBdt;
    float HeavyHiggsBdt;

    float DeltaRap;
    float DeltaPhi;
    float DeltaR;

    float DeltaRapSum;
    float DeltaPhiSum;
    float DeltaRSum;

    float DeltaRapDiff;
    float DeltaPhiDiff;
    float DeltaRDiff;

    int Signal;

private:

    ClassDef(HEventBranch, 1)

};

class HHeavyHiggsEvent : public hanalysis::HTag
{

public:

    HHeavyHiggsEvent(const hanalysis::HTriplePair &NewHeavyHiggs, const fastjet::PseudoJet &NewBottom, const fastjet::PseudoJet &NewAntiBottom) {
        HeavyHiggs = NewHeavyHiggs;
        Bottom = NewBottom;
        AntiBottom = NewAntiBottom;
    }

    hanalysis::HTriplePair GetHeavyHiggs()const {
        return HeavyHiggs;
    }

    float GetBdt() const {
        return (HeavyHiggs.GetBdt() * Bottom.user_info<hanalysis::HJetInfo>().GetBdt() * Bottom.user_info<hanalysis::HJetInfo>().GetBdt());
    }

    float GetDeltaRap() const {
        return (Bottom.rap() - AntiBottom.rap());
    }

    float DeltaPhi() const {
        return Bottom.delta_phi_to(AntiBottom);
    }

    float GetDeltaR() const {
        return Bottom.delta_R(AntiBottom);
    }

    float GetDeltaRSum() const {
        return GetDeltaR1() + GetDeltaR2();
    }

    float GetDeltaRDiff() const {
        return std::abs(GetDeltaR1() - GetDeltaR2());
    }

    float GetDeltaRapSum() const {
        return GetDeltaRap1() + GetDeltaRap2();
    }

    float GetDeltaRapDiff() const {
        return std::abs(GetDeltaRap1() - GetDeltaRap2());
    }

    float GetDeltaPhiSum() const {
        return GetDeltaPhi1() + GetDeltaPhi2();
    }

    float GetDeltaPhiDiff() const {
        return GetDeltaPhi(GetDeltaPhi1(), GetDeltaPhi2());
    }

    void SetScalarHt(const float NewScalarHt) {
        ScalarHt = NewScalarHt;
    }

    void SetJetNumber(const int NewJetNumber) {
        JetNumber = NewJetNumber;
    }
    void SetBottomNumber(const int NewBottomNumber) {
        BottomNumber = NewBottomNumber;
    }

    void SetLeptonNumber(const int NewLeptonNumber) {
        LeptonNumber = NewLeptonNumber;
    }

    float GetScalarHt() const {
        return ScalarHt;
    }
    int GetJetNumber()const {
        return JetNumber;
    }
    int GetBottomNumber()const {
        return BottomNumber;
    }
    int GetLeptonNumber()const {
        return LeptonNumber;
    }

private:

    float GetDeltaR1() const {
        return HeavyHiggs.GetPairJet().delta_R(Bottom);
    }

    float GetDeltaR2() const {
        return HeavyHiggs.GetPairJet().delta_R(AntiBottom);
    }

    float GetDeltaPhi1() const {
        return HeavyHiggs.GetPairJet().delta_phi_to(Bottom);
    }

    float GetDeltaPhi2() const {
        return HeavyHiggs.GetPairJet().delta_phi_to(AntiBottom);
    }

    float GetDeltaRap1() const {
        return (HeavyHiggs.GetPairJet().rap() - Bottom.rap());
    }

    float GetDeltaRap2() const {
        return (HeavyHiggs.GetPairJet().rap() - AntiBottom.rap());
    }

    fastjet::PseudoJet Bottom;
    fastjet::PseudoJet AntiBottom;
    hanalysis::HTriplePair HeavyHiggs;
    int LeptonNumber;
    int BottomNumber;
    int JetNumber;
    int ScalarHt;

};

# endif
