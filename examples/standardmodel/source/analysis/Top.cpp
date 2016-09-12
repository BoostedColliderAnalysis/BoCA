#include "standardmodel/analysis/Top.hh"
#include "boca/generic/DEBUG_MACROS.hh"

namespace standardmodel
{

std::string Name(TopTagger top_tagger)
{
    switch (top_tagger) {
      case TopTagger::boca : return "BoCA";
      case TopTagger::hep : return "HEP";
      case TopTagger::hep2 : return "HEP_2";
        DEFAULT(to_int(top_tagger), "");
    }
}

}
