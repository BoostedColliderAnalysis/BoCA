# pragma once

# include <iostream>
# include <iomanip>
# include <cmath>
# include <vector>

# include "TMath.h"
# include "TLorentzVector.h"

# include "fastjet/PseudoJet.hh"

/**
 * @brief Namespace of analysis containing all the underlying libraries and SM taggers
 *
 */

namespace analysis
{

typedef std::vector<fastjet::PseudoJet> Jets;
typedef std::vector<TLorentzVector> Vectors;
typedef std::vector<std::string> Strings;

template <typename Value>
inline int sgn(const Value value)
{
    return (Value(0) < value) - (value < Value(0));
}

int LargeNumber();

class Range
{
public:
    Range(const int sum) : last_(sum), iterator_(0) {}

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
