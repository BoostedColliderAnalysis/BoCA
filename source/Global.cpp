# include "Global.hh"

int analysis::LargeNumber()
{
    return 999999999;
}

float analysis::Distance(const float rapidity_1, const float phi_1, const float rapidity_2, const float phi_2)
{
  return std::sqrt(std::pow((rapidity_2 - rapidity_1), 2) + std::pow(DeltaPhi(phi_2, phi_1), 2));
}

float analysis::Length(const float rapidity, const float phi)
{
  return std::sqrt(std::pow(rapidity, 2) + std::pow(phi, 2));
}

float analysis::DeltaPhi(const float phi_1, const float phi_2)
{
  float delta_phi = phi_1 - phi_2;
  while (std::abs(delta_phi) > M_PI) {
    if (delta_phi < - M_PI) {
      delta_phi += 2 * M_PI;
    } else if (delta_phi > M_PI) {
      delta_phi -= 2 * M_PI;
    } else {
//       Print(kError, "Delta Phi", delta_phi);
      break;
    }
  }
  return delta_phi;
}
