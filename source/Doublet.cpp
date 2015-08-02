#include "Doublet.hh"
#include "Predicate.hh"
#include "Debug.hh"

namespace analysis
{

Singlet& Doublet::Singlet1() const
{
    return Multiplet1();
}

Singlet& Doublet::Singlet2() const
{
    return Multiplet2();
}

float Doublet::Dipolarity2() const
{
    float dipolarity = 0;
    for (const auto & constituent : Jet(Structure::constituents).constituents()) {

        float eta_0 = constituent.eta();
        float phi_0 = constituent.phi_std();

        float eta_1, eta_2, phi_1, phi_2;
        if (Multiplet1().Jet().eta() < Multiplet2().Jet().eta()) {
            eta_1 = Multiplet1().Jet().eta();
            phi_1 = Multiplet1().Jet().phi_std();
            eta_2 = Multiplet2().Jet().eta();
            phi_2 = Multiplet2().Jet().phi_std();
        } else {
            eta_1 = Multiplet2().Jet().eta();
            phi_1 = Multiplet2().Jet().phi_std();
            eta_2 = Multiplet1().Jet().eta();
            phi_2 = Multiplet1().Jet().phi_std();
        }

        float delta_phi = phi_2 - phi_1;
        float delta_eta = -(eta_2 - eta_1);
        float delta_eta_phi = eta_2 * phi_1 - eta_1 * phi_2;

        float delta_r_1 = constituent.delta_R(Multiplet1().Jet());
        float delta_r_2 = constituent.delta_R(Multiplet2().Jet());
        float eta3 = - (delta_phi * delta_eta_phi - delta_eta * delta_eta * eta_0 + delta_phi * delta_eta * phi_0) / (delta_phi * delta_phi + delta_eta * delta_eta);
        float phi3 = - (delta_eta * delta_eta_phi + delta_phi * delta_eta * eta_0 - delta_phi * delta_phi * phi_0) / (delta_phi * delta_phi + delta_eta * delta_eta);

        float distance_1;
        if ((eta3 >= eta_1 && eta3 <= eta_2 && phi3 >= phi_1 && phi3 <= phi_2) || (eta3 >= eta_1 && eta3 <= eta_2 && phi3 >= phi_2 && phi3 <= phi_1)) {
            float delta_r_3 = std::abs(delta_phi * eta_0 + delta_eta * phi_0 + delta_eta_phi) / std::sqrt(sqr(delta_phi) + sqr(delta_eta));
            distance_1 = delta_r_3;
        } else distance_1 = std::min(delta_r_1, delta_r_2);

        if (phi_0 < 0) phi_0 = phi_0 + 2 * M_PI;
        else  phi_0 = phi_0 - 2 * M_PI;

        eta3 =  - (delta_phi * delta_eta_phi - delta_eta * delta_eta * eta_0 + delta_phi * delta_eta * phi_0) / (delta_phi * delta_phi + delta_eta * delta_eta);
        phi3  =  - (delta_eta * delta_eta_phi + delta_phi * delta_eta * eta_0 - delta_phi * delta_phi * phi_0) / (delta_phi * delta_phi + delta_eta * delta_eta);


        float distance_2;
        if ((eta3 >= eta_1 && eta3 <= eta_2 && phi3 >= phi_1 && phi3 <= phi_2) || (eta3 >= eta_1 && eta3 <= eta_2 && phi3 >= phi_2 && phi3 <= phi_1)) {
            float delta_r_4 = std::abs(delta_phi * eta_0 + delta_eta * phi_0 + delta_eta_phi) / std::sqrt(sqr(delta_phi) + sqr(delta_eta));
            distance_2 = delta_r_4;
        } else  distance_2 = std::min(delta_r_1, delta_r_2);

        float distance = std::min(distance_1, distance_2);

        if (delta_r_1 < DeltaR() / std::sqrt(2) || delta_r_2 < DeltaR() / std::sqrt(2)) dipolarity += constituent.perp() / Jet().perp() * sqr(distance) / sqr(DeltaR());

    }
    if (dipolarity > 1) Error(DeltaR(), dipolarity);
    return dipolarity;

}

}



