# include "HJetPgs.hh"

hanalysis::hpgs::HJet::HJet()
{

    Print(kNotification, "Constructor");

//     Debug = 4;

}

hanalysis::hpgs::HJet::~HJet()
{

    Print(kNotification, "Destructor");

}

bool hanalysis::hpgs::HJet::GetJets(const hanalysis::HJet::HJetDetails JetDetails)
{

  Print(kInformation, "Get Jet", clones_arrays_->JetSum(), JetDetails);

  for (const int JetNumber : Range(clones_arrays_->JetSum())) {

        Print(kDetailed, "Jet Number", JetNumber);
        TRootJet *JetClone = (TRootJet *)clones_arrays_->Jet(JetNumber);

        jets_.emplace_back(GetPseudoJet(*JetClone));

        if (JetClone->BTag > 0) {

            Print(kDetailed, "Has B Tag");

            BottomLorentzVectors.emplace_back(GetLorentzVector(*JetClone));
            BottomJets.emplace_back(GetPseudoJet(*JetClone));


        } else {

            JetLorentzVectors.emplace_back(GetLorentzVector(*JetClone));

        }

    }

    Print(kDebug, "Untagged jets", JetLorentzVectors.size());

    return 1;

}
