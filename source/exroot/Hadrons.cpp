# include "exroot/Hadrons.hh"

bool analysis::exroot::Hadrons::GetJets(const analysis::Hadrons::JetDetail jet_detail)
{
    Print(kInformation, "Get Jet", clones_arrays_->JetSum(), jet_detail);
    for (const int JetNumber : Range(clones_arrays_->JetSum())) {
        Print(kDetailed, "Jet Number", JetNumber);
        TRootJet &jet = static_cast<TRootJet &>(clones_arrays().Jet(JetNumber));
        jets_.emplace_back(PseudoJet(jet));
        if (jet.BTag > 0) {
            Print(kDetailed, "Has B Tag");
            BottomLorentzVectors.emplace_back(LorentzVector(jet));
            BottomJets.emplace_back(PseudoJet(jet));
        } else {
            JetLorentzVectors.emplace_back(LorentzVector(jet));
        }
    }
    Print(kDebug, "Untagged jets", JetLorentzVectors.size());
    return 1;
}
