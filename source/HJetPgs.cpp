# include "HJetPgs.hh"

hanalysis::hpgs::HJet::HJet()
{

    Print(1, "Constructor");

//     Debug = 4;

}

hanalysis::hpgs::HJet::~HJet()
{

    Print(1, "Destructor");

}

bool hanalysis::hpgs::HJet::GetJets(const hanalysis::HJet::HJetDetails JetDetails)
{

    Print(2, "Get Jet", ClonesArrays->GetJetSum(), JetDetails);

    for (const int JetNumber : HRange(ClonesArrays->GetJetSum())) {

        Print(4, "Jet Number", JetNumber);
        TRootJet *JetClone = (TRootJet *)ClonesArrays->GetJet(JetNumber);

        Jets.push_back(GetPseudoJet(JetClone));

        if (JetClone->BTag > 0) {

            Print(4, "Has B Tag");

            BottomLorentzVectors.push_back(GetLorentzVector(JetClone));
            BottomJets.push_back(GetPseudoJet(JetClone));


        } else {

            JetLorentzVectors.push_back(GetLorentzVector(JetClone));

        }

    }

    Print(3, "Untagged jets", JetLorentzVectors.size());

    return 1;

}
