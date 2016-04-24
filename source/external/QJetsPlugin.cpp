#include "boca/external/QJetsPlugin.hh"
#include "boca/external/QJets.hh"

namespace qjets
{

QJetsPlugin::QJetsPlugin(double zcut, double dcut_fctr, double exp_min, double exp_max, double rigidity, double truncation_fctr)
    : _zcut(zcut),
      _dcut_fctr(dcut_fctr),
      _exp_min(exp_min),
      _exp_max(exp_max),
      _rigidity(rigidity),
      _truncation_fctr(truncation_fctr),
      _rand_seed_set(false)
{
}

void QJetsPlugin::SetRandSeed(unsigned int seed)
{
    _rand_seed_set = true;
    _seed = seed;
}

double QJetsPlugin::R()const
{
    return 0.;
}

std::string QJetsPlugin::description() const
{
    return "Qjets pruning plugin";
}

void QJetsPlugin::run_clustering(fastjet::ClusterSequence& cs) const
{
    QJets qjets(_zcut, _dcut_fctr, _exp_min, _exp_max, _rigidity, _truncation_fctr);
    if (_rand_seed_set) qjets.SetRandSeed(_seed);
    qjets.Cluster(cs);
}

}
