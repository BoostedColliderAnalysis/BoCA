# include "HFourVector.hh"

HFourVector::HFourVector() :
    CheckFourVectors(0),
    Check(0.00001),
    MassCheck(1)
{

    Print(2, "Constructor");

}

HFourVector::~HFourVector()
{


    Print(2, "Destructor");

}


PseudoJet HFourVector::GetPseudoJet(const TLorentzVector &Vector) const
{

    const PseudoJet Jet(Vector.Px(), Vector.Py(), Vector.Pz(), Vector.E());

    return Jet;

}

TLorentzVector HFourVector::GetConstituent(const TObject &Object) const
{

    TLorentzVector LorentzVector;

    if (Object.IsA() == GenParticle::Class()) {

        LorentzVector = const_cast<GenParticle *>((GenParticle *) &Object)->P4();

    } else if (Object.IsA() == Track::Class()) {

        LorentzVector = const_cast<Track *>((Track *) &Object)->P4();

    } else if (Object.IsA() == Tower::Class()) {

        LorentzVector = const_cast<Tower *>((Tower *) &Object)->P4();

    } else if (Object.IsA() == Muon::Class()) {

        LorentzVector = const_cast<Muon *>((Muon *) &Object)->P4();

    } else {

        Print(0, "Unkonw Object", Object.ClassName());

    }

    return LorentzVector;

}

PseudoJet HFourVector::GetConstituentJet(const TObject &Object) const
{

    return GetPseudoJet(GetConstituent(Object));

}


TLorentzVector HFourVector::GetLorentzVector(TRootElectron *Particle)
{

    Print(3, "Get Lorentz Vector", "TRootElectron");

    TLorentzVector LorentzVector = GetLorentzVectorByMass(Particle, ElectronMass);

    return LorentzVector;

}

TLorentzVector HFourVector::GetLorentzVector(TRootGenJet *Particle)
{

    Print(3, "Get Lorentz Vector", "TRootGenJet");

    TLorentzVector LorentzVector = GetLorentzVectorByMass(Particle);

    return LorentzVector;

}

TLorentzVector HFourVector::GetLorentzVector(TRootGenParticle *Particle)
{

    Print(3, "Get Lorentz Vector", "TRootGenParticle");

    TLorentzVector LorentzVector = GetLorentzVectorByEnergy(Particle);

    return LorentzVector;

}

TLorentzVector HFourVector::GetLorentzVector(TRootJet *Particle)
{

    Print(3, "Get Lorentz Vector", "TRootJet");

    TLorentzVector LorentzVector = GetLorentzVectorByMass(Particle);

    return LorentzVector;

}

TLorentzVector HFourVector::GetLorentzVector(TRootLHEFParticle *Particle)
{

    Print(3, "Get Lorentz Vector", "TRootLHEFParticle");

    TLorentzVector LorentzVector = GetLorentzVectorByM(Particle);

    return LorentzVector;

}

TLorentzVector HFourVector::GetLorentzVector(TRootMuon *Particle)
{

    Print(3, "Get Lorentz Vector", "TRootMuon");

    TLorentzVector LorentzVector = GetLorentzVectorByMass(Particle, MuonMass);

    return LorentzVector;

}

TLorentzVector HFourVector::GetLorentzVector(TRootPhoton *Particle)
{

    Print(3, "Get Lorentz Vector", "TRootPhoton");

    TLorentzVector LorentzVector = GetLorentzVectorByMass(Particle, 0);

    return LorentzVector;

}

TLorentzVector HFourVector::GetLorentzVector(TRootTau *Particle)
{

    Print(3, "Get Lorentz Vector", "TRootTau");

    TLorentzVector LorentzVector = GetLorentzVectorByMass(Particle, TauMass);

    return LorentzVector;

}

PseudoJet HFourVector::GetPseudoJet(TRootElectron *Particle)
{

    Print(3, "Get Pseudo Jet", "TRootElectron");

    PseudoJet Jet = GetPseudoJetByMass(Particle, ElectronMass);

    return Jet;

}

PseudoJet HFourVector::GetPseudoJet(TRootGenJet *Particle)
{

    Print(3, "Get Pseudo Jet", "TRootGenJet");

    PseudoJet Jet = GetPseudoJetByMass(Particle);

    return Jet;

}

PseudoJet HFourVector::GetPseudoJet(TRootGenParticle *Particle)
{

    Print(3, "Get Pseudo Jet", "TRootGenParticle");

    PseudoJet Jet = GetPseudoJetByEnergy(Particle);

    return Jet;

}

PseudoJet HFourVector::GetPseudoJet(TRootJet *Particle)
{

    Print(3, "Get Pseudo Jet", "TRootJet");

    PseudoJet Jet = GetPseudoJetByMass(Particle);

    return Jet;

}

PseudoJet HFourVector::GetPseudoJet(TRootLHEFParticle *Particle)
{

    Print(3, "Get Pseudo Jet", "TRootLHEFParticle");

    PseudoJet Jet = GetPseudoJetByM(Particle);

    return Jet;

}

PseudoJet HFourVector::GetPseudoJet(TRootMuon *Particle)
{

    Print(3, "Get Pseudo Jet", "TRootMuon");

    PseudoJet Jet = GetPseudoJetByMass(Particle, MuonMass);

    return Jet;

}

PseudoJet HFourVector::GetPseudoJet(TRootPhoton *Particle)
{

    Print(3, "Get Pseudo Jet", "TRootPhoton");

    PseudoJet Jet = GetPseudoJetByMass(Particle, 0);

    return Jet;

}

PseudoJet HFourVector::GetPseudoJet(TRootTau *Particle)
{

    Print(3, "Get Pseudo Jet", "TRootTau");

    PseudoJet Jet = GetPseudoJetByMass(Particle, TauMass);

    return Jet;

}
