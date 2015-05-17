# pragma once

# include <map>
# include <unordered_map>

# include "fastjet/JetDefinition.hh"

# include "HTag.hh"
# include "Family.hh"
# include "Constituent.hh"

namespace analysis
{

class DetectorGeometry
{
public:
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
    float VertexMassMin;
private:
    enum DetectorType {CMS, Spp};
};

/**
 * @brief Jet infos subclassed from Fastjet
 *
 */
class JetInfo: public HTag, public fastjet::PseudoJet::UserInfoBase
{

public:

    /**
     * @brief Constructor
     *
     */
    JetInfo();

    JetInfo(const Constituent &constituent);

    JetInfo(const std::vector<Constituent> &constituents);

    void Addconstituent(const Constituent &constituent);

    void Addconstituents(const std::vector<Constituent> &constituents);

    void AddDaughter(const int daughter);

    std::vector<Constituent> constituents() const;

    std::unordered_map<Family, float> FamilyFractions();

    float VertexMass() const;

    float MaxDisplacement() const;

    float MeanDisplacement() const;

    float SumDisplacement() const;

    int VertexNumber() const;

    fastjet::PseudoJet VertexJet() const;

    float VertexEnergy() const;

    void ExtractFraction(const int particle_id);

    void ExtractAbsFraction(const int particle_id);

    void ExtractFraction(const int particle_id, const int mother_id);

    void PrintAllInfos(const Object::Severity severity) const;

    void PrintAllconstituentInfos(const Object::Severity severity) const;

    void PrintAllFamInfos(const Object::Severity severity) const;

    float MaximalFraction() const;

    float Fraction(const int particle_id) const;

    int MaximalId() const;

    void AddFamily(const Family &family, const float weight);

    void ExtractFamilyFraction();

    Family MaximalFamily();

    float ElectroMagneticRadius(const fastjet::PseudoJet &jet) const;

    float TrackRadius(const fastjet::PseudoJet &jet) const;

    float LeadingTrackMomentumFraction() const;

    float CoreEnergyFraction(const fastjet::PseudoJet &jet) const;

    float ElectroMagneticFraction() const;

    float ClusterMass() const;

    float TrackMass() const;

protected:

    inline std::string ClassName() const {
        return "JetInfo";
    }

private:

    DetectorGeometry detector_geometry_;

    DetectorGeometry detector_geometry() const {
        return detector_geometry_;
    }

    void AddParticle(const int constituent_id, const float weight);

    float GetWeightSum() const;

    std::vector<Constituent> ApplyVertexResolution() const;

    std::vector<Constituent> constituents_;

    std::unordered_map<Family, float> family_fractions_;

    std::map<int, float> id_fractions_;

};

/**
 * @brief sort vector of jets with largest bdt at the front
 *
 */
struct SortByBdt {
    inline bool operator()(const fastjet::PseudoJet &jet_1, const fastjet::PseudoJet &jet_2) {
        return (jet_1.user_info<analysis::JetInfo>().Bdt() > jet_2.user_info<analysis::JetInfo>().Bdt());
    }
};

}
