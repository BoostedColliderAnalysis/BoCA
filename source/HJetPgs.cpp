# include "HJetPgs.hh"

HPgs::HJet::HJet()
{

    Print(1, "Constructor");

//     Debug = 4;

}

HPgs::HJet::~HJet()
{

    Print(1, "Destructor");

}

bool HPgs::HJet::GetJets()
{

    Print(2, "Get Jet");

    TClonesArray *JetClonesArray = ClonesArrays->JetClonesArray;
    Print(3, "Number of Jets", JetClonesArray->GetEntriesFast());

    for (int JetNumber = 0; JetNumber < JetClonesArray->GetEntriesFast(); ++JetNumber) {

        Print(4, "Jet Number", JetNumber);
        TRootJet *JetClone = (TRootJet *)JetClonesArray->At(JetNumber);

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
