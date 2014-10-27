# include "HFourVector.hh"

hanalysis::HFourVector::HFourVector() :
    CheckFourVectors(0),
    Check(0.00001),
    MassCheck(1)
{

    Print(2, "Constructor");

}

hanalysis::HFourVector::~HFourVector()
{


    Print(2, "Destructor");

}


PseudoJet hanalysis::HFourVector::GetPseudoJet(const TLorentzVector &Vector) const
{

    const PseudoJet Jet(Vector.Px(), Vector.Py(), Vector.Pz(), Vector.E());

    return Jet;

}

TLorentzVector hanalysis::HFourVector::GetConstituent(const TObject *const Object) const
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

PseudoJet hanalysis::HFourVector::GetConstituentJet(const TObject *const Object) const
{

    return GetPseudoJet(GetConstituent(Object));

}


TLorentzVector hanalysis::HFourVector::GetLorentzVector(const TRootElectron *const Particle) const
{

    Print(3, "Get Lorentz Vector", "TRootElectron");

    return GetLorentzVectorByMass(Particle, ElectronMass);

}

TLorentzVector hanalysis::HFourVector::GetLorentzVector(const TRootGenJet *const Particle) const
{

    Print(3, "Get Lorentz Vector", "TRootGenJet");

    return GetLorentzVectorByMass(Particle);

}

TLorentzVector hanalysis::HFourVector::GetLorentzVector(const TRootGenParticle *const Particle) const
{

    Print(3, "Get Lorentz Vector", "TRootGenParticle");

    return GetLorentzVectorByEnergy(Particle);

}

TLorentzVector hanalysis::HFourVector::GetLorentzVector(const TRootJet *const Particle) const
{

    Print(3, "Get Lorentz Vector", "TRootJet");

    return GetLorentzVectorByMass(Particle);

}

TLorentzVector hanalysis::HFourVector::GetLorentzVector(const TRootLHEFParticle *const Particle) const
{

    Print(3, "Get Lorentz Vector", "TRootLHEFParticle");

    return GetLorentzVectorByM(Particle);

}

TLorentzVector hanalysis::HFourVector::GetLorentzVector(const TRootMuon *const Particle) const
{

    Print(3, "Get Lorentz Vector", "TRootMuon");

    return GetLorentzVectorByMass(Particle, MuonMass);

}

TLorentzVector hanalysis::HFourVector::GetLorentzVector(const TRootPhoton *const Particle) const
{

    Print(3, "Get Lorentz Vector", "TRootPhoton");

    return GetLorentzVectorByMass(Particle, 0);

}

TLorentzVector hanalysis::HFourVector::GetLorentzVector(const TRootTau *const Particle) const
{

    Print(3, "Get Lorentz Vector", "TRootTau");

    return GetLorentzVectorByMass(Particle, TauMass);

}

PseudoJet hanalysis::HFourVector::GetPseudoJet(const TRootElectron *const Particle) const
{

    Print(3, "Get Pseudo Jet", "TRootElectron");

    return GetPseudoJet(GetLorentzVectorByMass(Particle, ElectronMass));

}

PseudoJet hanalysis::HFourVector::GetPseudoJet(const TRootGenJet *const Particle) const
{

    Print(3, "Get Pseudo Jet", "TRootGenJet");

    return GetPseudoJet(GetLorentzVectorByMass(Particle));

}

PseudoJet hanalysis::HFourVector::GetPseudoJet(const TRootGenParticle *const Particle) const
{

    Print(3, "Get Pseudo Jet", "TRootGenParticle");

    return GetPseudoJet(GetLorentzVectorByEnergy(Particle));

}

PseudoJet hanalysis::HFourVector::GetPseudoJet(const TRootJet *const Particle) const
{

    Print(3, "Get Pseudo Jet", "TRootJet");

    return GetPseudoJet(GetLorentzVectorByMass(Particle));


}

PseudoJet hanalysis::HFourVector::GetPseudoJet(const TRootLHEFParticle *const Particle) const
{

    Print(3, "Get Pseudo Jet", "TRootLHEFParticle");

    return GetPseudoJet(GetLorentzVectorByM(Particle));

}

PseudoJet hanalysis::HFourVector::GetPseudoJet(const TRootMuon *const Particle) const
{

    Print(3, "Get Pseudo Jet", "TRootMuon");

    return GetPseudoJet(GetLorentzVectorByMass(Particle, MuonMass));

}

PseudoJet hanalysis::HFourVector::GetPseudoJet(const TRootPhoton *const Particle) const
{

    Print(3, "Get Pseudo Jet", "TRootPhoton");

    return GetPseudoJet(GetLorentzVectorByMass(Particle, 0));

}

PseudoJet hanalysis::HFourVector::GetPseudoJet(const TRootTau *const Particle) const
{

    Print(3, "Get Pseudo Jet", "TRootTau");

    return GetPseudoJet(GetLorentzVectorByMass(Particle, TauMass));

}
