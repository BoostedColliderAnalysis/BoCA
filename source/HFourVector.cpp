# include "HFourVector.hh"

hanalysis::HFourVector::HFourVector() :
    CheckFourVectors(1),
    Check(0.00001),
    MassCheck(1)
{
//     DebugLevel = HDebug;
    Print(HInformation, "Constructor");
}

hanalysis::HFourVector::~HFourVector()
{
    Print(HInformation, "Destructor");
}

void hanalysis::HFourVector::NewEvent(const HClonesArray *const NewClonesArrays)
{
    ClonesArrays = NewClonesArrays;
    Topology.assign(ClonesArrays->GetParticleSum(), HFamily(EmptyId, EmptyId, EmptyId));
    Print(HInformation, "Topology", Topology.size());
}


fastjet::PseudoJet hanalysis::HFourVector::GetPseudoJet(const TLorentzVector &Vector) const
{
    // construct a pseudojet from explicit components
    // PseudoJet(const double px, const double py, const double pz, const double E);
    const fastjet::PseudoJet Jet(Vector.Px(), Vector.Py(), Vector.Pz(), Vector.E());
    return Jet;
}

// TLorentzVector hanalysis::HFourVector::GetLorentzVector(const MissingET *const Particle) const
// {
//     Print(HDebug, "Get Lorentz Vector", "MissingET");
//
//     TLorentzVector LorentzVector;
//
//     const float Met = Particle->MET;
//     const float Eta = Particle->Eta;
//     const float Phi = Particle->Phi;
//     LorentzVector.SetPtEtaPhiM(Met, Eta, Phi, 0);
//
//     if (CheckFourVectors) {
//
//         const float LvMet = sqrt(std::pow(LorentzVector.M(),2)+std::pow(LorentzVector.Pt(),2));
//
//         if (std::abs(LvMet - Met) > Check) Print(HError, "Met", Met, LvMet);
//         if (std::abs(LorentzVector.Eta() - Eta) > Check) Print(HError, "Eta", Eta, LorentzVector.Eta());
//         if (std::abs(LorentzVector.Phi() - Phi) > Check) Print(HError, "Phi", Phi, LorentzVector.Phi());
//
//     }
//
//     return LorentzVector;
// }

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

// fastjet::PseudoJet hanalysis::HFourVector::GetPseudoJet(const MissingET *const Particle) const
// {
//     Print(HDebug, "Get Pseudo Jet", "TRootElectron");
//     return GetPseudoJet(GetLorentzVector(Particle));
// }

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
    Print(HDetailed, "Get Mother Id", ClonesArrays->GetParticleSum());

    if (Object->IsA() != GenParticle::Class() || Object == 0) {
        Print(HError, "Object is", Object->ClassName());
        return EmptyId;
    }

    const int Position = ClonesArrays->GetParticleClonesArray()->IndexOf(Object);
    if (Position == EmptyPosition) return EmptyId;

//     int MotherId = EmptyId;
    HFamily MotherId(EmptyId, EmptyId, EmptyId);
    Source = Topology.size();

    MotherId = GetMotherId(MotherId, Position);

//     Print(HError, "Mother Id", GetParticleName(MotherId.ParticleId), GetParticleName(MotherId.Mother1Id), GetParticleName(MotherId.Mother2Id));

    int Marker = MarkerId;
    std::replace(Topology.begin(), Topology.end(), HFamily(MarkerId, EmptyId, EmptyId), MotherId);

    if (MotherId.ParticleId == EmptyId) Print(HError, "Truth Level Tagging Failed");

    return MotherId.ParticleId;

}

HFamily hanalysis::HFourVector::GetMotherId(HFamily &BranchId, int Position)
{

    Print(HDetailed, "Get Mother Id", GetParticleName(BranchId.ParticleId), Position);

    if (Position == EmptyPosition) Print(HError, "Initial Proton");
    while (Position != EmptyPosition
//             && JetTag->HeavyParticles.find(static_cast<HParticleId>(std::abs(BranchId))) == end(JetTag->HeavyParticles)
            && JetTag->HeavyFamily.find(BranchId.Abs()) == end(JetTag->HeavyFamily)
          ) {

        Print(HDetailed, "Topology", Topology.at(Position).ParticleId);
//         Print(HError, "Position", Position,GetParticleName(BranchId.ParticleId));

        if (Topology.at(Position).ParticleId != EmptyId && Topology.at(Position).ParticleId  != MarkerId) {
            BranchId = Topology.at(Position);
            break;
        }

        Topology.at(Position).ParticleId = MarkerId;
        if (Position < Source) Source = Position;
        const GenParticle *const ParticleClone = (GenParticle *) ClonesArrays->GetParticle(Position);

        int M1Id = EmptyId;
//         Print(HError, "Mother1", ParticleClone->M1);
        if (ParticleClone->M1 > 0) {
            GenParticle *Mother1Clone = (GenParticle *) ClonesArrays->GetParticle(ParticleClone->M1);
            M1Id = Mother1Clone->PID;
        }

//         Print(HError, "Mother2", ParticleClone->M2);
        int M2Id = EmptyId;
        if (ParticleClone->M2 > 0) {
            GenParticle *Mother2Clone = (GenParticle *) ClonesArrays->GetParticle(ParticleClone->M2);
            M2Id = Mother2Clone->PID;
        }
        const int Status = ParticleClone->Status;

//         Print(HError, "Family",ParticleClone->PID, M1Id, M2Id);
        HFamily Family(ParticleClone->PID, M1Id, M2Id);
        if (Status == GeneratorParticle) BranchId = JetTag->GetBranchId(Family, BranchId);
//         if (Status == GeneratorParticle) BranchId = JetTag->GetBranchId(ParticleClone->PID, BranchId);
        Print(HDetailed, "Branch Id", GetParticleName(ParticleClone->PID), GetParticleName(BranchId.ParticleId));

        if (JetTag->HeavyFamily.find(BranchId.Abs()) != end(JetTag->HeavyFamily)) break;

        if (ParticleClone->M2 != EmptyPosition && ParticleClone->M2 != ParticleClone->M1) {
            if (ParticleClone->PID == StringId) {
                if (ParticleClone->M1 < ParticleClone->M2) {
                    Print(HDetailed, "String", ParticleClone->M1, Position);
                    for (int Counter = ParticleClone->M2; Counter >= ParticleClone->M1; --Counter) {
                        BranchId = GetMotherId(BranchId, Counter);
                        Print(HDetailed, "StringPart", Counter, BranchId.ParticleId);
                        if (JetTag->HeavyFamily.find(BranchId.Abs()) != end(JetTag->HeavyFamily)) break;
                    }
                }
            } else {
                Print(HDetailed, "Mother 2 Position", GetParticleName(BranchId.ParticleId), Position);
                BranchId = GetMotherId(BranchId, ParticleClone->M2);
                if (JetTag->HeavyFamily.find(BranchId.Abs()) != end(JetTag->HeavyFamily)) break;
            }
        }

        Position = ParticleClone->M1;
        Print(HDetailed, "Mother 1 Position", Position);
    }

//     if (Source < 4 && JetTag->HeavyFamily.find(BranchId.Abs()) != end(JetTag->HeavyFamily)) BranchId = HFamily(MixedJetId,EmptyId,EmptyId);
//     Print(HDetailed, "Branch Id Result", GetParticleName(BranchId));

// Print(HError,"Source",Source);
    return BranchId;

}

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
        PrintCell("Energy");
        PrintCell("Px");
        PrintCell("Py");
        PrintCell("Pz");
        std::cout << std::endl;

//         for (const int Position : HRange(ClonesArrays->GetParticleSum())) {
        for (const int Position : HRange(100)) {

            const GenParticle *Particle = (GenParticle *)ClonesArrays->GetParticle(Position);

            PrintCell(Position);
            PrintCell(GetParticleName(Topology.at(Position).ParticleId));
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
            PrintCell(Particle->E);
            PrintCell(Particle->Px);
            PrintCell(Particle->Py);
            PrintCell(Particle->Pz);
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

