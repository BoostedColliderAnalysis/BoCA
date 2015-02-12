# ifndef HJetInfo_hh
# define HJetInfo_hh

# include <map>
# include <unordered_map>
# include <numeric>

# include "HTag.hh"
# include "HJetTag.hh"
# include "HFourVector.hh"

class HConstituent
{

public:
    enum HDetector {HGenParticle, HTrack, HPhoton, HTower, HMuon, HNone};


    HConstituent() {};

    HConstituent(const TLorentzVector &NewMomentum, const TLorentzVector &NewPosition, const hanalysis::HFamily &NewFamily) {
        MomentumM = NewMomentum;
        PositionM = NewPosition;
        FamilyM = NewFamily;
    }

    HConstituent(const TLorentzVector &NewMomentum, const TLorentzVector &NewPosition) {
        MomentumM = NewMomentum;
        PositionM = NewPosition;
    }

    HConstituent(const TLorentzVector &NewMomentum, const TLorentzVector &NewPosition, const HDetector NewDetector) {
        MomentumM = NewMomentum;
        PositionM = NewPosition;
        DetectorM = NewDetector;
    }

    HConstituent(const TLorentzVector &NewMomentum, const hanalysis::HFamily &NewFamily) {
        MomentumM = NewMomentum;
        FamilyM = NewFamily;
    }

    inline HConstituent(const TLorentzVector &NewMomentum) {
        MomentumM = NewMomentum;
    }

    inline HConstituent(const TLorentzVector &NewMomentum, const HDetector NewDetector) {
        MomentumM = NewMomentum;
        DetectorM = NewDetector;
    }

    inline  void SetPosition(const TLorentzVector &NewPosition) {
        PositionM = NewPosition;
    }

    inline void SetPosition(const float X, const float Y, const float Z, const float T) {
        PositionM.SetXYZT(X, Y, Z, T);
    }

    inline void SetMomentum(const TLorentzVector &NewMomentum) {
        MomentumM = NewMomentum;
    }

    inline void SetFamily(const hanalysis::HFamily &NewFamily) {
        FamilyM = NewFamily;
    }

    inline TLorentzVector Position() const {
        return PositionM;
    }

    inline TLorentzVector Momentum() const {
        return MomentumM;
    }

    inline hanalysis::HFamily Family() const {
        return FamilyM;
    }

    HConstituent operator+(HConstituent &Constituent) {
        Constituent.PositionM += this->PositionM;
        Constituent.MomentumM += this->MomentumM;
        return Constituent;
    }

    void SetDetector(const HDetector NewDetector) {
        DetectorM = NewDetector;
    }

    HDetector Detector() const {
        return DetectorM;
    }

private:

    HDetector DetectorM = HNone;

    TLorentzVector PositionM;

    TLorentzVector MomentumM;

    hanalysis::HFamily FamilyM;
};

struct MaxDistance {
    inline bool operator()(const HConstituent &Constituent1, const HConstituent &Constituent2) const {
        return (Constituent1.Position().Vect().Mag() > Constituent2.Position().Vect().Mag());
    }

};


/**
 * @brief Jet infos subclassed from Fastjet
 *
 */
class hanalysis::HJetInfo: public HTag, public fastjet::PseudoJet::UserInfoBase
{

public:

    /**
     * @brief Constructor
     *
     */
    HJetInfo();

    HJetInfo(const int NewBTag);

    HJetInfo(const HConstituent &NewConstituent);

    HJetInfo(const std::vector<HConstituent> &NewConstituents);

    HJetInfo(const std::vector<HConstituent> &NewConstituents, const int NewBTag);

//     HJetInfo(const HJetInfo &NewJetInfo);

    void AddConstituent(const HConstituent &NewConstituent) {
        ConstituentsM.push_back(NewConstituent);
    }

    void AddConstituents(const std::vector<HConstituent> &NewConstituents) {
        ConstituentsM.insert(ConstituentsM.end(), NewConstituents.begin(), NewConstituents.end());
    }

    void AddDaughter(const int NewDaughter) {
        if (Constituents().size() > 0) {
          Print(HError, "Constituents", Constituents().size(),Constituents().front().Family().ParticleId);
            Constituents().front().Family().AddDaughter(NewDaughter);
            return;
        }
        Print(HError, "No Constituent");
    }

    std::vector<HConstituent> Constituents() const {
        return ConstituentsM;
    }

    inline void SetBTag(const int NewBTag) {
        BTagM = NewBTag;
    }

    inline int BTag() const {
        return BTagM;
    }


    inline std::unordered_map<HFamily, float> FamilyFractions() {
        return FamilyFractionsM;
    }

    float VertexMass() const;

    float MaxDisplacement() const;

    float MeanDisplacement() const;

    float SumDisplacement() const;

    int VertexNumber() const {
        return ApplyVertexResolution().size();
    }

    fastjet::PseudoJet VertexJet() const;

    float VertexEnergy() const;

    void ExtractFraction(const int ParticleId);

    void ExtractAbsFraction(const int ParticleId);

    void ExtractFraction(const int ParticleId, const int MotherId);

    void PrintAllInfos(const hanalysis::HObject::HSeverity Severity) const;

    void PrintAllConstituentInfos(const hanalysis::HObject::HSeverity Severity) const;

    void PrintAllFamInfos(const hanalysis::HObject::HSeverity Severity) const;

    float MaximalFraction() const;

    float Fraction(const int ParticleId) const;

    int MaximalId() const;

    void AddFamily(const HFamily &Family, const float Weight);

    void ExtractFamilyFraction();

    HFamily MaximalFamily();

    float ElectroMagneticRadius(const fastjet::PseudoJet &Jet) const;

    float TrackRadius(const fastjet::PseudoJet &Jet) const;

    float LeadingTrackMomentumFraction() const;

    float CoreEnergyFraction(const fastjet::PseudoJet &Jet) const;

    float ElectroMagneticFraction() const;

    float ClusterMass() const;

    float TrackMass() const;

protected:

//     HJetInfo(HJetInfoPrivate &JetInfoPrivate);

    inline std::string ClassName() const {
        return "HJetInfo";
    }

private:


    void AddParticle(const int ConstituentId, const float Weight);

    float GetWeightSum() const;

    std::vector<HConstituent> ApplyVertexResolution() const;

    std::vector<HConstituent> ConstituentsM;

    std::unordered_map<HFamily, float> FamilyFractionsM;

    std::map<int, float> IdFractions;

    float SecondaryVertexResolution = 0.1;

    int BTagM;

};

# endif
