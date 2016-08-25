#pragma once

#include <map>
#include <queue>

namespace fastjet
{
class PseudoJet;
class ClusterSequence;
}

/**
* \ingroup External
* @brief <a href="http://jets.physics.harvard.edu/Qjets/html/Welcome.html">Qjets</a>: A Non-Deterministic Approach to Tree-Based Jet Substructure
*
*/
namespace qjets
{

struct jet_distance {
    double dij;
    int j1;
    int j2;
};

class JetDistanceCompare
{
public:
    JetDistanceCompare() {};
    bool operator()(const jet_distance& lhs, const jet_distance& rhs) const;
};

class QJets
{
private:
    double _zcut, _dcut_fctr, _exp_min, _exp_max, _rigidity, _dcut, _truncation_fctr;
    bool _rand_seed_set;
    unsigned _seed;
    double Omega;
    std::map<int, bool> _merged_jets;
    std::priority_queue <jet_distance, std::vector<jet_distance>, JetDistanceCompare> _distances;

    double d_ij(fastjet::PseudoJet const& v1, fastjet::PseudoJet const& v2) const;
    void ComputeDCut(fastjet::ClusterSequence& cs);

    double Rand();
    bool Prune(jet_distance& jd, fastjet::ClusterSequence& cs);
    bool JetsUnmerged(const jet_distance& jd) const;
    bool JetUnmerged(int num) const;
    void ComputeNewDistanceMeasures(fastjet::ClusterSequence& cs, unsigned new_jet);
    void ComputeAllDistances(std::vector<fastjet::PseudoJet> const& inp);
    double ComputeMinimumDistance();
    double ComputeNormalization(double dmin);
    jet_distance GetNextDistance();
    bool Same(const jet_distance& lhs, const jet_distance& rhs);

public:
    QJets(double zcut, double dcut_fctr, double exp_min, double exp_max, double rigidity, double truncation_fctr);
    void Cluster(fastjet::ClusterSequence& cs);
    void SetRandSeed(unsigned seed); /* In case you want reproducible behavior */
};

}
