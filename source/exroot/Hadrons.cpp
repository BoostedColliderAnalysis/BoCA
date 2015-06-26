# include "exroot/Hadrons.hh"

namespace analysis
{

namespace exroot
{

Jets Hadrons::Jets()
{
    Print(Severity::information, "Jets", clones_arrays().JetSum());
    analysis::Jets jets;
    for (const int JetNumber : Range(clones_arrays().JetSum())) {
        ::exroot::Jet &jet = static_cast<::exroot::Jet &>(clones_arrays().Jet(JetNumber));
        fastjet::PseudoJet pseudo_jet = PseudoJet(jet);
        pseudo_jet.set_user_info(new JetInfo(bool(jet.BTag)));
        jets.emplace_back(pseudo_jet);
    }
    return jets;
}

}

}
