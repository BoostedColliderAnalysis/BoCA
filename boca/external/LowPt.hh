#pragma once

#include "boca/external/TopTagger2.hh"

namespace hep
{

// Example for a low_pt working point
class LowPt
{
public:
    LowPt();
    bool is_tagged(hep::TopTagger2 const& htt);
};

}
