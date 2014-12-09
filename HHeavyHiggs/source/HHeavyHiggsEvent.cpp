# include "HHeavyHiggsEvent.hh"

  HHeavyHiggsEvent::HHeavyHiggsEvent(const hanalysis::HTriplePair &NewHeavyHiggs, const fastjet::PseudoJet &NewBottom, const fastjet::PseudoJet &NewAntiBottom) {
    HeavyHiggs = NewHeavyHiggs;
    Bottom = NewBottom;
    AntiBottom = NewAntiBottom;
  }
