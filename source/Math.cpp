#include "Math.hh"

#include <cmath>

#include "Debug.hh"

namespace analysis {

float Distance(float rapidity_1, float phi_1, float rapidity_2, float phi_2)
{
    return std::sqrt(sqr(rapidity_2 - rapidity_1) + sqr(DeltaPhi(phi_2, phi_1)));
}

float Length(float rapidity, float phi)
{
    return std::sqrt(sqr(rapidity) + sqr(phi));
}

float DeltaPhi(float phi_1, float phi_2)
{
    return RestrictPhi(phi_1 - phi_2);
}

float RestrictPhi(float phi){
  while (std::abs(phi) > M_PI) {
    if (phi < - M_PI) phi += 2 * M_PI;
    else if (phi > M_PI) phi -= 2 * M_PI;
    else Error(phi);
  }
  return phi;
}

int LargeNumber()
{
  return 999999999;
}

}

