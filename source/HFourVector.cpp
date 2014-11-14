# include "HFourVector.hh"

hanalysis::HFourVector::HFourVector() :
    CheckFourVectors(0),
    Check(0.00001),
    MassCheck(1)
{

    Print(HInformation, "Constructor");

}

hanalysis::HFourVector::~HFourVector()
{


    Print(HInformation, "Destructor");

}


fastjet::PseudoJet hanalysis::HFourVector::GetPseudoJet(const TLorentzVector &Vector) const
{

    const fastjet::PseudoJet Jet(Vector.Px(), Vector.Py(), Vector.Pz(), Vector.E());

    return Jet;

}

TLorentzVector hanalysis::HFourVector::GetLorentzVector(const TRootElectron *const Particle) const
{

    Print(HDebug, "Get Lorentz Vector", "TRootElectron");

    return GetLorentzVectorByMass(Particle, ElectronMass);

}

TLorentzVector hanalysis::HFourVector::GetLorentzVector(const TRootGenJet *const Particle) const
{

    Print(HDebug, "Get Lorentz Vector", "TRootGenJet");

    return GetLorentzVectorByMass(Particle);

}

TLorentzVector hanalysis::HFourVector::GetLorentzVector(const TRootGenParticle *const Particle) const
{

    Print(HDebug, "Get Lorentz Vector", "TRootGenParticle");

    return GetLorentzVectorByEnergy(Particle);

}

TLorentzVector hanalysis::HFourVector::GetLorentzVector(const TRootJet *const Particle) const
{

    Print(HDebug, "Get Lorentz Vector", "TRootJet");

    return GetLorentzVectorByMass(Particle);

}

TLorentzVector hanalysis::HFourVector::GetLorentzVector(const TRootLHEFParticle *const Particle) const
{

    Print(HDebug, "Get Lorentz Vector", "TRootLHEFParticle");

    return GetLorentzVectorByM(Particle);

}

TLorentzVector hanalysis::HFourVector::GetLorentzVector(const TRootMuon *const Particle) const
{

    Print(HDebug, "Get Lorentz Vector", "TRootMuon");

    return GetLorentzVectorByMass(Particle, MuonMass);

}

TLorentzVector hanalysis::HFourVector::GetLorentzVector(const TRootPhoton *const Particle) const
{

    Print(HDebug, "Get Lorentz Vector", "TRootPhoton");

    return GetLorentzVectorByMass(Particle, 0);

}

TLorentzVector hanalysis::HFourVector::GetLorentzVector(const TRootTau *const Particle) const
{

    Print(HDebug, "Get Lorentz Vector", "TRootTau");

    return GetLorentzVectorByMass(Particle, TauMass);

}

fastjet::PseudoJet hanalysis::HFourVector::GetPseudoJet(const TRootElectron *const Particle) const
{

    Print(HDebug, "Get Pseudo Jet", "TRootElectron");

    return GetPseudoJet(GetLorentzVectorByMass(Particle, ElectronMass));

}

fastjet::PseudoJet hanalysis::HFourVector::GetPseudoJet(const TRootGenJet *const Particle) const
{

    Print(HDebug, "Get Pseudo Jet", "TRootGenJet");

    return GetPseudoJet(GetLorentzVectorByMass(Particle));

}

fastjet::PseudoJet hanalysis::HFourVector::GetPseudoJet(const TRootGenParticle *const Particle) const
{

    Print(HDebug, "Get Pseudo Jet", "TRootGenParticle");

    return GetPseudoJet(GetLorentzVectorByEnergy(Particle));

}

fastjet::PseudoJet hanalysis::HFourVector::GetPseudoJet(const TRootJet *const Particle) const
{

    Print(HDebug, "Get Pseudo Jet", "TRootJet");

    return GetPseudoJet(GetLorentzVectorByMass(Particle));


}

fastjet::PseudoJet hanalysis::HFourVector::GetPseudoJet(const TRootLHEFParticle *const Particle) const
{

    Print(HDebug, "Get Pseudo Jet", "TRootLHEFParticle");

    return GetPseudoJet(GetLorentzVectorByM(Particle));

}

fastjet::PseudoJet hanalysis::HFourVector::GetPseudoJet(const TRootMuon *const Particle) const
{

    Print(HDebug, "Get Pseudo Jet", "TRootMuon");

    return GetPseudoJet(GetLorentzVectorByMass(Particle, MuonMass));

}

fastjet::PseudoJet hanalysis::HFourVector::GetPseudoJet(const TRootPhoton *const Particle) const
{

    Print(HDebug, "Get Pseudo Jet", "TRootPhoton");

    return GetPseudoJet(GetLorentzVectorByMass(Particle, 0));

}

fastjet::PseudoJet hanalysis::HFourVector::GetPseudoJet(const TRootTau *const Particle) const
{

    Print(HDebug, "Get Pseudo Jet", "TRootTau");

    return GetPseudoJet(GetLorentzVectorByMass(Particle, TauMass));

}
