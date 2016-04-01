#include "exroot/ExRootAnalysis.hh"
#include "exroot/Hadrons.hh"
#include "generic/DEBUG.hh"

namespace boca
{

namespace exroot
{

Hadrons::Hadrons(boca::TreeReader const& tree_reader) :
    boca::Hadrons(tree_reader) {}

std::vector<Jet> Hadrons::Jets() const
{
    INFO0;
    std::vector<Jet> jets;
    for (auto const & exroot_jet : TreeReader().Objects<::exroot::Jet>(Branch::jet)) {
        Jet jet(exroot_jet);
        jet.Info().SetBTag(exroot_jet.BTag);
        jets.emplace_back(jet);
    }
    return jets;
}

}

}
