# pragma once

# include <iostream>
# include <iomanip>
# include <cmath>
# include <vector>

# include "TLorentzVector.h"

# include "fastjet/PseudoJet.hh"

/**
 * @brief analysis namespace containing the general analysis and SM taggers
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

/**
 * @brief Calcualte distance in eta phi space
 *
 */
float Distance(const float rapidity_1, const float phi_1, const float rapidity_2, const float phi_2);

/**
 * @brief Calcualte distance from center in eta phi space
 *
 */
float Length(const float rapidity, const float phi);

/**
 * @brief Take care of phi angles around pi
 *
 */
float DeltaPhi(const float phi_1, const float phi_2);

/**
 * @brief provides an integer with the necessary information to work with range based for loop
 *
 */
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

template <typename Element>
std::vector<Element> Join(const std::vector<Element> &vector_1, const std::vector<Element> &vector_2)
{
  std::vector<Element> joined;
  joined.reserve(vector_1.size() + vector_2.size());
  joined.insert(joined.end(), vector_1.begin(), vector_1.end());
  joined.insert(joined.end(), vector_2.begin(), vector_2.end());
  return joined;
}

}
