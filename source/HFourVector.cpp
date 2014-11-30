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

int hanalysis::HFourVector::GetMotherId(TObject *Object)
{

    Print(HDebug, "Get Mother Id", ClonesArrays->GetParticleSum());

    if (Object->IsA() != GenParticle::Class() || Object == 0) {
        Print(HError, "Object is", Object->ClassName());
        return EmptyId;
    }

    const int Position = ClonesArrays->GetParticleClonesArray()->IndexOf(Object);
    if (Position == EmptyPosition) return EmptyId;

//     int Status  = ((GenParticle *) ClonesArrays->GetParticle(Position))->Status;
//     int MotherId = Topology.at(Position);
    int MotherId = EmptyId;
    Source = Topology.size();
//     Topology.at(Position) = MarkerId;
    MotherId = GetMotherId(MotherId, Position);

    Print(HDebug, "Mother Id", GetParticleName(MotherId));
//     if (MotherId == EmptyId) Print(HError, "No Mother Id", Position, GetParticleName(Topology.at(Position)));
//     if(Source<5) MotherId = IsrId;

    int Marker = MarkerId;
//     std::replace(Topology.begin(), Topology.begin()+20, Marker, EmptyId);
//     if(std::find(Topology.begin(),Topology.end(),Marker)<Topology.begin()+3) MotherId = IsrId;

    std::replace(Topology.begin(), Topology.end(), Marker, MotherId);

    return MotherId;

}

int hanalysis::HFourVector::GetMotherId(int BranchId, int Position)
{

    Print(HDebug, "Get Mother Id", GetParticleName(BranchId), Position);

    while (Position != EmptyPosition
            && (JetTag->HeavyParticles.find(std::abs(BranchId)) == end(JetTag->HeavyParticles))
//             && (Topology.at(Position) == EmptyId)
          ) {

        Topology.at(Position) = MarkerId;
        if (Position < Source) Source = Position;
        const GenParticle *const ParticleClone = (GenParticle *) ClonesArrays->GetParticle(Position);
        const int Status = ParticleClone->Status;

        if (Status == GeneratorParticle) BranchId = JetTag->GetBranchId(ParticleClone->PID, BranchId);
        Print(HDebug, "Branch Id", GetParticleName(ParticleClone->PID), GetParticleName(BranchId));
        if (JetTag->HeavyParticles.find(std::abs(BranchId)) != end(JetTag->HeavyParticles)) break;

        if (ParticleClone->M2 != EmptyPosition && ParticleClone->M2 != ParticleClone->M1) {
            if (ParticleClone->PID == StringId) {
                if (ParticleClone->M1 < ParticleClone->M2) {
                    Print(HDebug, "String", ParticleClone->M1, Position);
                    for (int Counter = ParticleClone->M2; Counter >= ParticleClone->M1; --Counter) {
                        BranchId = GetMotherId(BranchId, Counter);
                        Print(HDetailed, "StringPart", Counter, BranchId);
                    }
                }
            } else {
                Print(HDebug, "Mother 2 Position", GetParticleName(BranchId), Position);
                BranchId = GetMotherId(BranchId, ParticleClone->M2);
            }
        }

        Position = ParticleClone->M1;
        Print(HDebug, "Mother 1 Position", Position);
    }

    if (Source  < 4 && JetTag->HeavyParticles.find(std::abs(BranchId)) != end(JetTag->HeavyParticles)) BranchId = MixJetId;
//     if (Position == EmptyPosition) BranchId = IsrId;
    Print(HDebug, "Branch Id Result", GetParticleName(BranchId));

    return BranchId;

}

//         if (Topology.at(Position) != EmptyId && Topology.at(Position) != MarkerId) {
//             Print(HDebug, "Topology", GetParticleName(BranchId), GetParticleName(Topology.at(Position)));
//             BranchId = JetTag->GetBranchId(BranchId, Topology.at(Position));
//         }

void hanalysis::HFourVector::PrintTruthLevel(int const Severity) const
{
    if (Severity <= DebugLevel) {

        PrintCell("Position");
        PrintCell("Topology");
        PrintCell("Status");
        PrintCell("Particle");
        PrintCell("Pos M1");
        PrintCell("Mother 1");
        PrintCell("Pos M2");
        PrintCell("Mother 2");
        PrintCell("Pos D1");
        PrintCell("Child 1");
        PrintCell("Pos D2");
        PrintCell("Child 2");
        std::cout << std::endl;

//         for (const int Position : HRange(ClonesArrays->GetParticleSum())) {
        for (const int Position : HRange(20)) {

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
