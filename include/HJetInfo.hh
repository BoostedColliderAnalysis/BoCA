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
    enum SubDetector {HGenParticle, HTrack, HPhoton, HTower, HMuon, HNone};


    HConstituent() {};

    HConstituent(const TLorentzVector &NewMomentum, const TLorentzVector &NewPosition, const hanalysis::HFamily &NewFamily) {
        momentum_ = NewMomentum;
        position_ = NewPosition;
        family_ = NewFamily;
    }

    HConstituent(const TLorentzVector &NewMomentum, const TLorentzVector &NewPosition) {
        momentum_ = NewMomentum;
        position_ = NewPosition;
    }

    HConstituent(const TLorentzVector &NewMomentum, const TLorentzVector &NewPosition, const SubDetector NewDetector) {
        momentum_ = NewMomentum;
        position_ = NewPosition;
        sub_detector_ = NewDetector;
    }

    HConstituent(const TLorentzVector &NewMomentum, const hanalysis::HFamily &NewFamily) {
        momentum_ = NewMomentum;
        family_ = NewFamily;
    }

    inline HConstituent(const TLorentzVector &NewMomentum) {
        momentum_ = NewMomentum;
    }

    inline HConstituent(const TLorentzVector &NewMomentum, const SubDetector NewDetector) {
        momentum_ = NewMomentum;
        sub_detector_ = NewDetector;
    }

    inline  void SetPosition(const TLorentzVector &NewPosition) {
        position_ = NewPosition;
    }

    inline void SetPosition(const float X, const float Y, const float Z, const float T) {
        position_.SetXYZT(X, Y, Z, T);
    }

    inline void SetMomentum(const TLorentzVector &NewMomentum) {
        momentum_ = NewMomentum;
    }

    inline void SetFamily(const hanalysis::HFamily &NewFamily) {
        family_ = NewFamily;
    }

    inline TLorentzVector Position() const {
        return position_;
    }

    inline TLorentzVector Momentum() const {
        return momentum_;
    }

    inline hanalysis::HFamily Family() const {
        return family_;
    }

    HConstituent operator+(HConstituent &Constituent) {
        Constituent.position_ += this->position_;
        Constituent.momentum_ += this->momentum_;
        return Constituent;
    }

    void SetDetector(const SubDetector NewDetector) {
        sub_detector_ = NewDetector;
    }

    SubDetector sub_detector() const {
        return sub_detector_;
    }

private:

    SubDetector sub_detector_ = HNone;

    TLorentzVector position_;

    TLorentzVector momentum_;

    hanalysis::HFamily family_;
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
        constituents_.push_back(NewConstituent);
    }

    void AddConstituents(const std::vector<HConstituent> &NewConstituents) {
        constituents_.insert(constituents_.end(), NewConstituents.begin(), NewConstituents.end());
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
        return constituents_;
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
//       Print(HError,"Multiplicity",ApplyVertexResolution().size());
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

  struct DetectorGeometry {
    float MaxTrackerEta = 5;
    float MinTrackerDistance = 0.1;
    float MaxTrackerDistance = 1000;
  };

  DetectorGeometry detector_geometry_;


    void AddParticle(const int ConstituentId, const float Weight);

    float GetWeightSum() const;

    std::vector<HConstituent> ApplyVertexResolution() const;

    std::vector<HConstituent> constituents_;

    std::unordered_map<HFamily, float> FamilyFractionsM;

    std::map<int, float> IdFractions;

//     float SecondaryVertexResolution = 0.1;

    int BTagM;

};


/**
 * @brief sort vector of jets with largest bdt at the front
 *
 */
struct SortByBdt {
  inline bool operator()(const fastjet::PseudoJet &Jet1, const fastjet::PseudoJet &Jet2) {
    return (Jet1.user_info<hanalysis::HJetInfo>().Bdt() > Jet2.user_info<hanalysis::HJetInfo>().Bdt());
  }
};

# endif
