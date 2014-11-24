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

void hanalysis::HFourVector::NewEvent(const HClonesArray *const NewClonesArrays)
{

    ClonesArrays = NewClonesArrays;
    Topology.assign(ClonesArrays->GetParticleSum(), EmptyId);
    Print(HInformation, "Topology", Topology.size());

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

int hanalysis::HFourVector::GetMotherId(const TObject *const Object)
{

    Print(HDebug, "Get Mother Id", ClonesArrays->GetParticleSum());

    if (Object->IsA() != GenParticle::Class() || Object == 0) {
        Print(HError, "Object is", Object->ClassName());
        return EmptyId;
    }

    Print(HDebug, "Object", Object->ClassName());

    const int Position = ClonesArrays->GetParticleClonesArray()->IndexOf(Object);
    if (Position == EmptyPosition) return EmptyId;

    int MotherId = Topology.at(Position);
    MotherId = GetMotherId(MotherId, Position);

    Print(HDebug, "Mother Id", GetParticleName(MotherId));
    if (MotherId == EmptyId) Print(HError, "No Mother Id", Position, Topology.at(Position));

    int Marker = MarkerId;
    std::replace(Topology.begin(), Topology.end(), Marker, MotherId);

    return MotherId;

}

int hanalysis::HFourVector::GetMotherId(int BranchId, int Position)
{

    Print(HDebug, "Get Mother Id", GetParticleName(BranchId), Position);

    while (Position != EmptyPosition && JetTag->HeavyParticles.find(std::abs(BranchId)) == end(JetTag->HeavyParticles)) {

        if (Topology.at(Position) != EmptyId && Topology.at(Position) != MarkerId) {
            Print(HDebug, "Topology", GetParticleName(BranchId), GetParticleName(Topology.at(Position)));
            BranchId = JetTag->GetBranchId(BranchId, Topology.at(Position));
        }

        Topology.at(Position) = MarkerId;
        const GenParticle *const ParticleClone = (GenParticle *) ClonesArrays->GetParticle(Position);

        BranchId = JetTag->GetBranchId(ParticleClone->PID, BranchId);
        Print(HDebug, "Branch Id", GetParticleName(ParticleClone->PID), GetParticleName(BranchId));

        Position = ParticleClone->M2;
        if (Position != EmptyPosition) {
            Print(HDebug, "Mother 2 Position", GetParticleName(BranchId), Position);
            BranchId = GetMotherId(BranchId, Position);
        }

        Position = ParticleClone->M1;
        Print(HDebug, "Mother 1 Position", Position);
    }

    if (Position == EmptyPosition) BranchId = IsrId;
    Print(HDebug, "Branch Id Result", GetParticleName(BranchId));

    return BranchId;

}

void hanalysis::HFourVector::PrintTruthLevel(int const Severity) const
{
    if (Severity <= DebugLevel) {

        for (const int Position : HRange(ClonesArrays->GetParticleSum())) {
            //     for (const int Position : HRange(100)) {

            const GenParticle *Particle = (GenParticle *)ClonesArrays->GetParticle(Position);

            PrintCell(Position);
            PrintCell(GetParticleName(Topology.at(Position)));
            PrintCell(Particle->Status);
            PrintCell(GetParticleName(Particle->PID));
            PrintCell(Particle->M1);
            PrintCell(PrintParticle(Particle->M1));
            PrintCell(Particle->M2);
            PrintCell(PrintParticle(Particle->M2));
            PrintCell(Particle->D1);
            PrintCell(PrintParticle(Particle->D1));
            PrintCell(Particle->D2);
            PrintCell(PrintParticle(Particle->D2));
            std::cout << std::endl;

        }

        Print(HNotification, "");

    }

}

std::string hanalysis::HFourVector::PrintParticle(const int Position) const
{

    if (Position != -1) {
        return GetParticleName(((GenParticle *)ClonesArrays->GetParticle(Position))->PID);
    } else {
        return " ";
    };

}
