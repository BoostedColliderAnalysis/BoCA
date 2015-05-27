# pragma once

# include <iostream>
# include <iomanip>
# include <cmath>
# include <vector>

# include "TMath.h"
# include "TLorentzVector.h"

# include "fastjet/PseudoJet.hh"

namespace analysis{

typedef std::vector<fastjet::PseudoJet> Jets;
typedef std::vector<TLorentzVector> Vectors;
typedef std::vector<std::string> Strings;

class Range
{
public:
    Range(const int sum):
        last_(sum),
        iterator_(0)
    {}
    const Range &begin() const {
        return *this;
    }
    const Range &end() const {
        return *this;
    }
    bool operator!=(const Range &) const {
        return iterator_ < last_;
    }
    void operator++() {
        ++iterator_;
    }
    int operator*() const {
        return iterator_;
    }
private:
    int last_;
    int iterator_;
};

}
