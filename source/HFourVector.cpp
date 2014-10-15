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

TLorentzVector HFourVector::GetConstituent(const TObject *const Object) const
{

    TLorentzVector LorentzVector;

    if (Object->IsA() == GenParticle::Class()) {

        LorentzVector = const_cast<GenParticle *>((GenParticle *) Object)->P4();

    } else if (Object->IsA() == Track::Class()) {

        LorentzVector = const_cast<Track *>((Track *) Object)->P4();

    } else if (Object->IsA() == Tower::Class()) {

        LorentzVector = const_cast<Tower *>((Tower *) Object)->P4();

    } else if (Object->IsA() == Muon::Class()) {

        LorentzVector = const_cast<Muon *>((Muon *) Object)->P4();

    } else {

        Print(0, "Unkonw Object", Object->ClassName());

    }

    return LorentzVector;

}

PseudoJet HFourVector::GetConstituentJet(const TObject *const Object) const
{

    return GetPseudoJet(GetConstituent(Object));

}


TLorentzVector HFourVector::GetLorentzVector(const TRootElectron *const Particle) const
{

    Print(3, "Get Lorentz Vector", "TRootElectron");

    return GetLorentzVectorByMass(Particle, ElectronMass);

}

TLorentzVector HFourVector::GetLorentzVector(const TRootGenJet *const Particle) const
{

    Print(3, "Get Lorentz Vector", "TRootGenJet");

    return GetLorentzVectorByMass(Particle);

}

TLorentzVector HFourVector::GetLorentzVector(const TRootGenParticle *const Particle) const
{

    Print(3, "Get Lorentz Vector", "TRootGenParticle");

    return GetLorentzVectorByEnergy(Particle);

}

TLorentzVector HFourVector::GetLorentzVector(const TRootJet *const Particle) const
{

    Print(3, "Get Lorentz Vector", "TRootJet");

    return GetLorentzVectorByMass(Particle);

}

TLorentzVector HFourVector::GetLorentzVector(const TRootLHEFParticle *const Particle) const
{

    Print(3, "Get Lorentz Vector", "TRootLHEFParticle");

    return GetLorentzVectorByM(Particle);

}

TLorentzVector HFourVector::GetLorentzVector(const TRootMuon *const Particle) const
{

    Print(3, "Get Lorentz Vector", "TRootMuon");

    return GetLorentzVectorByMass(Particle, MuonMass);

}

TLorentzVector HFourVector::GetLorentzVector(const TRootPhoton *const Particle) const
{

    Print(3, "Get Lorentz Vector", "TRootPhoton");

    return GetLorentzVectorByMass(Particle, 0);

}

TLorentzVector HFourVector::GetLorentzVector(const TRootTau *const Particle) const
{

    Print(3, "Get Lorentz Vector", "TRootTau");

    return GetLorentzVectorByMass(Particle, TauMass);

}

PseudoJet HFourVector::GetPseudoJet(const TRootElectron *const Particle) const
{

    Print(3, "Get Pseudo Jet", "TRootElectron");

    return GetPseudoJet(GetLorentzVectorByMass(Particle, ElectronMass));

}

PseudoJet HFourVector::GetPseudoJet(const TRootGenJet *const Particle) const
{

    Print(3, "Get Pseudo Jet", "TRootGenJet");

    return GetPseudoJet(GetLorentzVectorByMass(Particle));

}

PseudoJet HFourVector::GetPseudoJet(const TRootGenParticle *const Particle) const
{

    Print(3, "Get Pseudo Jet", "TRootGenParticle");

    return GetPseudoJet(GetLorentzVectorByEnergy(Particle));

}

PseudoJet HFourVector::GetPseudoJet(const TRootJet *const Particle) const
{

    Print(3, "Get Pseudo Jet", "TRootJet");

    return GetPseudoJet(GetLorentzVectorByMass(Particle));


}

PseudoJet HFourVector::GetPseudoJet(const TRootLHEFParticle *const Particle) const
{

    Print(3, "Get Pseudo Jet", "TRootLHEFParticle");

    return GetPseudoJet(GetLorentzVectorByM(Particle));

}

PseudoJet HFourVector::GetPseudoJet(const TRootMuon *const Particle) const
{

    Print(3, "Get Pseudo Jet", "TRootMuon");

    return GetPseudoJet(GetLorentzVectorByMass(Particle, MuonMass));

}

PseudoJet HFourVector::GetPseudoJet(const TRootPhoton *const Particle) const
{

    Print(3, "Get Pseudo Jet", "TRootPhoton");

    return GetPseudoJet(GetLorentzVectorByMass(Particle, 0));

}

PseudoJet HFourVector::GetPseudoJet(const TRootTau *const Particle) const
{

    Print(3, "Get Pseudo Jet", "TRootTau");

    return GetPseudoJet(GetLorentzVectorByMass(Particle, TauMass));

}
