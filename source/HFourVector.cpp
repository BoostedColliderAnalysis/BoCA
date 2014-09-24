# include "HFourVector.hh"

HFourVector::HFourVector() :
    CheckFourVectors(0),
    PtCheck(0.00001),
    MassCheck(1),
    EtaCheck(0.00001),
    PhiCheck(0.00001),
    EnergyCheck(0.00001)
{

    Print(1, "Constructor");

}

HFourVector::~HFourVector()
{


    Print(1, "Destructor");

}

HFourVectorExRoot::HFourVectorExRoot()
{


    Print(1, "Constructor");

}

HFourVectorExRoot::~HFourVectorExRoot()
{


    Print(1, "Destructor");

}

HFourVectorDelphes::HFourVectorDelphes()
{


    Print(1, "Constructor");

}

HFourVectorDelphes::~HFourVectorDelphes()
{


    Print(1, "Destructor");

}


TLorentzVector HFourVectorExRoot::GetLorentzVector(TRootElectron *Particle)
{

    Print(2, "Get Lorentz Vector", "TRootElectron");

    TLorentzVector LorentzVector = GetLorentzVectorByMass(Particle, ElectronMass);

    return LorentzVector;

}

TLorentzVector HFourVectorExRoot::GetLorentzVector(TRootGenJet *Particle)
{

    Print(2, "Get Lorentz Vector", "TRootGenJet");

    TLorentzVector LorentzVector = GetLorentzVectorByMass(Particle);

    return LorentzVector;

}

TLorentzVector HFourVectorExRoot::GetLorentzVector(TRootGenParticle *Particle)
{

    Print(2, "Get Lorentz Vector", "TRootGenParticle");

    TLorentzVector LorentzVector = GetLorentzVectorByEnergy(Particle);

    return LorentzVector;

}

TLorentzVector HFourVectorExRoot::GetLorentzVector(TRootJet *Particle)
{

    Print(2, "Get Lorentz Vector", "TRootJet");

    TLorentzVector LorentzVector = GetLorentzVectorByMass(Particle);

    return LorentzVector;

}

TLorentzVector HFourVectorExRoot::GetLorentzVector(TRootLHEFParticle *Particle)
{

    Print(2, "Get Lorentz Vector", "TRootLHEFParticle");

    TLorentzVector LorentzVector = GetLorentzVectorByM(Particle);

    return LorentzVector;

}

TLorentzVector HFourVectorExRoot::GetLorentzVector(TRootMuon *Particle)
{

    Print(2, "Get Lorentz Vector", "TRootMuon");

    TLorentzVector LorentzVector = GetLorentzVectorByMass(Particle, MuonMass);

    return LorentzVector;

}

TLorentzVector HFourVectorExRoot::GetLorentzVector(TRootPhoton *Particle)
{

    Print(2, "Get Lorentz Vector", "TRootPhoton");

    TLorentzVector LorentzVector = GetLorentzVectorByMass(Particle, 0);

    return LorentzVector;

}

TLorentzVector HFourVectorExRoot::GetLorentzVector(TRootTau *Particle)
{

    Print(2, "Get Lorentz Vector", "TRootTau");

    TLorentzVector LorentzVector = GetLorentzVectorByMass(Particle, TauMass);

    return LorentzVector;

}

TLorentzVector HFourVectorDelphes::GetLorentzVector(Electron *Particle)
{

    Print(2, "Get Lorentz Vector", "Electron");

    TLorentzVector LorentzVector = GetLorentzVectorByMass(Particle, ElectronMass);

    return LorentzVector;

}

TLorentzVector HFourVectorDelphes::GetLorentzVector(GenParticle *Particle)
{

    Print(2, "Get Lorentz Vector", "GenParticle");

    TLorentzVector LorentzVector = GetLorentzVectorByMass(Particle);

    return LorentzVector;

}

TLorentzVector HFourVectorDelphes::GetLorentzVector(Jet *Particle)
{

    Print(2, "Get Lorentz Vector", "Jet");

    TLorentzVector LorentzVector = GetLorentzVectorByMass(Particle);

    return LorentzVector;

}

TLorentzVector HFourVectorDelphes::GetLorentzVector(Muon *Particle)
{

    Print(2, "Get Lorentz Vector", "Muon");

    TLorentzVector LorentzVector = GetLorentzVectorByMass(Particle, MuonMass);

    return LorentzVector;

}

TLorentzVector HFourVectorDelphes::GetLorentzVector(Photon *Particle)
{

    Print(2, "Get Lorentz Vector", "Photon");

    TLorentzVector LorentzVector = GetLorentzVectorByEnergy(Particle);

    return LorentzVector;

}

TLorentzVector HFourVectorDelphes::GetLorentzVector(Tower *Particle)
{

    Print(2, "Get Lorentz Vector", "Tower");

    TLorentzVector LorentzVector;

    float Et = Particle->ET;
    float Eta = Particle->Eta;
    float Phi = Particle->Phi;
    float Energy = Particle->E;
    float Pt = sqrt(pow(Energy, 2) - pow(Et, 2) / pow(sinh(Eta), 2));

    LorentzVector.SetPtEtaPhiE(Pt, Eta, Phi, Energy);

    if (CheckFourVectors) {

        if (LorentzVector.Pt() - Pt > EnergyCheck) Print(-1, "Pt", Pt, LorentzVector.Pt());
        if (LorentzVector.Et() - Et > EnergyCheck) Print(-1, "Et", Et, LorentzVector.Et());
        if (LorentzVector.Eta() - Eta > EtaCheck) Print(-1, "Eta", Eta, LorentzVector.Eta());
        if (LorentzVector.Phi() - Phi > PhiCheck) Print(-1, "Phi", Phi, LorentzVector.Phi());
        if (LorentzVector.E() - Energy > EnergyCheck) Print(-1, "Energy", Energy, LorentzVector.E());

    }

    return LorentzVector;

}

TLorentzVector HFourVectorDelphes::GetLorentzVector(Track *Particle)
{

    Print(2, "Get Lorentz Vector", "Track");

    TLorentzVector LorentzVector = GetLorentzVectorByMass(Particle, 0);

    return LorentzVector;

}





PseudoJet HFourVectorExRoot::GetPseudoJet(TRootElectron *Particle)
{

    Print(2, "Get Pseudo Jet", "TRootElectron");

    PseudoJet Jet = GetPseudoJetByMass(Particle, ElectronMass);

    return Jet;

}

PseudoJet HFourVectorExRoot::GetPseudoJet(TRootGenJet *Particle)
{

    Print(2, "Get Pseudo Jet", "TRootGenJet");

    PseudoJet Jet = GetPseudoJetByMass(Particle);

    return Jet;

}

PseudoJet HFourVectorExRoot::GetPseudoJet(TRootGenParticle *Particle)
{

    Print(2, "Get Pseudo Jet", "TRootGenParticle");

    PseudoJet Jet = GetPseudoJetByEnergy(Particle);

    return Jet;

}

PseudoJet HFourVectorExRoot::GetPseudoJet(TRootJet *Particle)
{

    Print(2, "Get Pseudo Jet", "TRootJet");

    PseudoJet Jet = GetPseudoJetByMass(Particle);

    return Jet;

}

PseudoJet HFourVectorExRoot::GetPseudoJet(TRootLHEFParticle *Particle)
{

    Print(2, "Get Pseudo Jet", "TRootLHEFParticle");

    PseudoJet Jet = GetPseudoJetByM(Particle);

    return Jet;

}

PseudoJet HFourVectorExRoot::GetPseudoJet(TRootMuon *Particle)
{

    Print(2, "Get Pseudo Jet", "TRootMuon");

    PseudoJet Jet = GetPseudoJetByMass(Particle, MuonMass);

    return Jet;

}

PseudoJet HFourVectorExRoot::GetPseudoJet(TRootPhoton *Particle)
{

    Print(2, "Get Pseudo Jet", "TRootPhoton");

    PseudoJet Jet = GetPseudoJetByMass(Particle, 0);

    return Jet;

}

PseudoJet HFourVectorExRoot::GetPseudoJet(TRootTau *Particle)
{

    Print(2, "Get Pseudo Jet", "TRootTau");

    PseudoJet Jet = GetPseudoJetByMass(Particle, TauMass);

    return Jet;

}

PseudoJet HFourVectorDelphes::GetPseudoJet(Electron *Particle)
{

    Print(2, "Get Pseudo Jet", "Electron");

    PseudoJet Jet = GetPseudoJetByMass(Particle, ElectronMass);
    Jet.set_user_index(((GenParticle *) Particle->Particle.GetObject())->PID);

    return Jet;

}

PseudoJet HFourVectorDelphes::GetPseudoJet(GenParticle *Particle)
{

    Print(2, "Get Pseudo Jet", "GenParticle");

    PseudoJet Jet = GetPseudoJetByMass(Particle);

    return Jet;

}

PseudoJet HFourVectorDelphes::GetPseudoJet(Jet *Particle)
{

    Print(2, "Get Pseudo Jet", "Jet");

    PseudoJet Jet = GetPseudoJetByMass(Particle);

    return Jet;

}

PseudoJet HFourVectorDelphes::GetPseudoJet(Muon *Particle)
{

    Print(2, "Get Pseudo Jet", "Muon");

    PseudoJet Jet = GetPseudoJetByMass(Particle, MuonMass);
    Jet.set_user_index(((GenParticle *) Particle->Particle.GetObject())->PID);

    return Jet;

}

PseudoJet HFourVectorDelphes::GetPseudoJet(Photon *Particle)
{

    Print(2, "Get Pseudo Jet", "Photon");

    PseudoJet Jet = GetPseudoJetByEnergy(Particle);

    return Jet;

}

PseudoJet HFourVectorDelphes::GetPseudoJet(Tower *Particle)
{

    Print(2, "Get Pseudo Jet", "Tower");

    // http://en.wikipedia.org/wiki/Transverse_mass
    float Et = Particle->ET;
    float Eta = Particle->Eta;
    float Phi = Particle->Phi;
    float Energy = Particle->E;
    float Pt = sqrt(pow(Energy, 2) - pow(Et, 2) / pow(sinh(Eta), 2));

    PseudoJet Jet = PseudoJet(Pt * cos(Phi), Pt * sin(Phi), Pt * sinh(Eta), Energy);

    if (CheckFourVectors) {

        if (Jet.pt() - Pt > PtCheck) Print(-1, "Pt", Pt, Jet.pt());
        if (Jet.Et() - Et > EnergyCheck) Print(-1, "Et", Et, Jet.Et());
        if (Jet.eta() - Eta > EtaCheck) Print(-1, "Eta", Eta, Jet.eta());
        if (Jet.phi_std() - Phi > PhiCheck) Print(-1, "Phi", Phi, Jet.phi_std());
        if (Jet.e() - Energy > EnergyCheck) Print(-1, "Energy", Energy, Jet.e());

    }

    return Jet;

}

PseudoJet HFourVectorDelphes::GetPseudoJet(Track *Particle)
{

    Print(2, "Get Pseudo Jet", "Track");

    PseudoJet Jet = GetPseudoJetByMass(Particle, 0);
    Jet.set_user_index(((GenParticle *) Particle->Particle.GetObject())->PID);

    return Jet;

}

