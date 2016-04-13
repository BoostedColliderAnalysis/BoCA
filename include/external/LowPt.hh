#pragma once

#include "external/TopTagger2.hh"

namespace hep
{

// Example for a low_pt working point
class LowPt
{
public:
    LowPt();
    bool is_tagged(const hep::TopTagger2& htt);
};

}
