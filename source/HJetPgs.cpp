# include "HJetPgs.hh"

hanalysis::hpgs::HJet::HJet()
{

    Print(HNotification, "Constructor");

//     Debug = 4;

}

hanalysis::hpgs::HJet::~HJet()
{

    Print(HNotification, "Destructor");

}

bool hanalysis::hpgs::HJet::GetJets(const hanalysis::HJet::HJetDetails JetDetails)
{

    Print(HInformation, "Get Jet", ClonesArrays->GetJetSum(), JetDetails);

    for (const int JetNumber : HRange(ClonesArrays->GetJetSum())) {

        Print(HDetailed, "Jet Number", JetNumber);
        TRootJet *JetClone = (TRootJet *)ClonesArrays->GetJet(JetNumber);

        Jets.push_back(GetPseudoJet(JetClone));

        if (JetClone->BTag > 0) {

            Print(HDetailed, "Has B Tag");

            BottomLorentzVectors.push_back(GetLorentzVector(JetClone));
            BottomJets.push_back(GetPseudoJet(JetClone));


        } else {

            JetLorentzVectors.push_back(GetLorentzVector(JetClone));

        }

    }

    Print(HDebug, "Untagged jets", JetLorentzVectors.size());

    return 1;

}
