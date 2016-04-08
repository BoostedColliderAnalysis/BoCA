#pragma once

#include "PlottingBase.hh"
#include "Observables.hh"
#include "generic/Types.hh"
#include "math/Vector3.hh"

namespace boca{

template<typename Tagger_>
class Plotting : public PlottingBase {

public:

  Plotting(Tagger_ const& tagger) : tagger_(tagger){}

//   Plots PlotResult(int tree_number, Phase const& phase) const {
//     Plots plots(InfoBranch(phase, tree_number).first);
//     TreeReader tree_reader(Tagger().FileName(phase), Tagger().TreeNames(phase).at(tree_number));
//     plots.PlotVector() = UnorderedPairs(ConstCast(Tagger().Branch()).Variables().Vector(), [&](Observable const & variable_1, Observable const & variable_2) {
//       Plot plot;
//       for (auto const & entry : IntegerRange(tree_reader.GetEntries())) {
//         tree_reader.ReadEntry(entry);
//           plot.Add(Vector3<double>(variable_1.Value(), variable_2.Value(), ConstCast(Tagger().Branch()).Bdt()));
//       }
//       plot.x_is_int = variable_1.IsInt();
//       plot.y_is_int = variable_2.IsInt();
//       return plot;
//     });
//     plots.Names().SetName(Tagger().TreeNames(phase).at(tree_number));
//     return plots;
//   }

  Tagger_ const& Tagger() const{
      return tagger_;
  }

  Tagger_ & Tagger() {
    return tagger_;
  }

private:

  Tagger_ tagger_;

};

}
