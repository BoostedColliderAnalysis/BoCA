# pragma once

# include <map>
# include <unordered_map>
# include <numeric>

# include "HTag.hh"
# include "HJetTag.hh"
# include "HFourVector.hh"

# include "fastjet/JetDefinition.hh"

class DetectorGeometry
{
public:
    enum HDetectorType {CMS, Spp};

    DetectorGeometry();
    float JetMinPt;
    float JetConeSize;
    float MinCellPt;
    float MinCellResolution;
    float TrackerEtaMax;
    float JetRadiusParameter;
    fastjet::JetDefinition JetDefinition;
    fastjet::JetDefinition SubJetDefinition;
    float TrackerDistanceMin;
    float TrackerDistanceMax;

};


class Constituent
{

public:
    enum SubDetector {HGenParticle, HTrack, HPhoton, HTower, HMuon, HNone};


    Constituent() {};

    Constituent(const TLorentzVector &NewMomentum, const TLorentzVector &NewPosition, const hanalysis::HFamily &NewFamily) {
        momentum_ = NewMomentum;
        position_ = NewPosition;
        family_ = NewFamily;
    }

    Constituent(const TLorentzVector &NewMomentum, const TLorentzVector &NewPosition) {
        momentum_ = NewMomentum;
        position_ = NewPosition;
    }

    Constituent(const TLorentzVector &NewMomentum, const TLorentzVector &NewPosition, const SubDetector NewDetector) {
        momentum_ = NewMomentum;
        position_ = NewPosition;
        sub_detector_ = NewDetector;
    }

    Constituent(const TLorentzVector &NewMomentum, const hanalysis::HFamily &NewFamily) {
        momentum_ = NewMomentum;
        family_ = NewFamily;
    }

    inline Constituent(const TLorentzVector &NewMomentum) {
        momentum_ = NewMomentum;
    }

    inline Constituent(const TLorentzVector &NewMomentum, const SubDetector NewDetector) {
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

    Constituent operator+(Constituent &constituent) {
        constituent.position_ += this->position_;
        constituent.momentum_ += this->momentum_;
        return constituent;
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

/**
 * @brief Jet infos subclassed from Fastjet
 *
 */
class hanalysis::JetInfo: public HTag, public fastjet::PseudoJet::UserInfoBase
{

public:

    /**
     * @brief Constructor
     *
     */
    JetInfo();

//     JetInfo(const int NewBTag);

    JetInfo(const Constituent &Newconstituent);

    JetInfo(const std::vector<Constituent> &Newconstituents);

//     JetInfo(const std::vector<Constituent> &Newconstituents, const int NewBTag);

//     JetInfo(const JetInfo &Newjet_info);

    void Addconstituent(const Constituent &Newconstituent) {
        constituents_.emplace_back(Newconstituent);
    }

    void Addconstituents(const std::vector<Constituent> &Newconstituents) {
        constituents_.insert(constituents_.end(), Newconstituents.begin(), Newconstituents.end());
    }

    void AddDaughter(const int NewDaughter) {
        if (constituents().size() > 0) {
            Print(kError, "constituents", constituents().size(), constituents().front().Family().ParticleId);
            constituents().front().Family().AddDaughter(NewDaughter);
            return;
        }
        Print(kError, "No constituent");
    }

    std::vector<Constituent> constituents() const {
        return constituents_;
    }
    

    inline std::unordered_map<HFamily, float> FamilyFractions() {
        return family_fractions_;
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

    void PrintAllconstituentInfos(const hanalysis::HObject::HSeverity Severity) const;

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

//     JetInfo(JetInfoPrivate &jet_infoPrivate);

    inline std::string ClassName() const {
        return "JetInfo";
    }

private:

    DetectorGeometry detector_geometry_;

    DetectorGeometry detector_geometry()const {
        return detector_geometry_;
    }

    void AddParticle(const int constituentId, const float Weight);

    float GetWeightSum() const;

    std::vector<Constituent> ApplyVertexResolution() const;

    std::vector<Constituent> constituents_;



    std::unordered_map<HFamily, float> family_fractions_;

    std::map<int, float> id_fractions_;

};


/**
 * @brief sort vector of jets with largest bdt at the front
 *
 */
struct SortByBdt {
    inline bool operator()(const fastjet::PseudoJet &Jet1, const fastjet::PseudoJet &Jet2) {
        return (Jet1.user_info<hanalysis::JetInfo>().Bdt() > Jet2.user_info<hanalysis::JetInfo>().Bdt());
    }
};
