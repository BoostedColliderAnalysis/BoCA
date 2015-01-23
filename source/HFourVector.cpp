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
    Topology.assign(ClonesArrays->GetParticleSum(), HFamily(EmptyId));
    Print(HInformation, "Topology", Topology.size());
}


fastjet::PseudoJet hanalysis::HFourVector::PseudoJet(const TLorentzVector &Vector) const
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
    return PseudoJet(GetLorentzVectorByMass(Particle, ElectronMass));
}

fastjet::PseudoJet hanalysis::HFourVector::GetPseudoJet(const TRootGenJet *const Particle) const
{
    Print(HDebug, "Get Pseudo Jet", "TRootGenJet");
    return PseudoJet(GetLorentzVectorByMass(Particle));
}

fastjet::PseudoJet hanalysis::HFourVector::GetPseudoJet(const TRootGenParticle *const Particle) const
{
    Print(HDebug, "Get Pseudo Jet", "TRootGenParticle");
    return PseudoJet(GetLorentzVectorByEnergy(Particle));
}

fastjet::PseudoJet hanalysis::HFourVector::GetPseudoJet(const TRootJet *const Particle) const
{
    Print(HDebug, "Get Pseudo Jet", "TRootJet");
    return PseudoJet(GetLorentzVectorByMass(Particle));
}

fastjet::PseudoJet hanalysis::HFourVector::GetPseudoJet(const TRootLHEFParticle *const Particle) const
{
    Print(HDebug, "Get Pseudo Jet", "TRootLHEFParticle");
    return PseudoJet(GetLorentzVectorByM(Particle));
}

fastjet::PseudoJet hanalysis::HFourVector::GetPseudoJet(const TRootMuon *const Particle) const
{
    Print(HDebug, "Get Pseudo Jet", "TRootMuon");
    return PseudoJet(GetLorentzVectorByMass(Particle, MuonMass));
}

fastjet::PseudoJet hanalysis::HFourVector::GetPseudoJet(const TRootPhoton *const Particle) const
{
    Print(HDebug, "Get Pseudo Jet", "TRootPhoton");
    return PseudoJet(GetLorentzVectorByMass(Particle, 0));
}

fastjet::PseudoJet hanalysis::HFourVector::GetPseudoJet(const TRootTau *const Particle) const
{
    Print(HDebug, "Get Pseudo Jet", "TRootTau");
    return PseudoJet(GetLorentzVectorByMass(Particle, TauMass));
}

hanalysis::HFamily hanalysis::HFourVector::GetBranchFamily(TObject *Object)
{
    Print(HDetailed, "Get Mother Id", ClonesArrays->GetParticleSum());

    HFamily BranchFamily;
    if (Object->IsA() != delphes::GenParticle::Class() || Object == 0) {
        Print(HError, "Object is", Object->ClassName());
        return BranchFamily;
    }

    const int Position = ClonesArrays->GetParticleClonesArray()->IndexOf(Object);
    if (Position == EmptyPosition) return BranchFamily;

    BranchFamily = GetBranchFamily(BranchFamily, Position);
    if (BranchFamily.Mother1Id == EmptyId)
        BranchFamily = HFamily(BranchFamily.ParticlePosition, IsrId, BranchFamily.Mother1Position, IsrId);
//       Print(HError, "Truth Level Tagging Failed");

    for (auto & Node : Topology) if (Node.GetMarker()) Node = BranchFamily;
    Print(HDebug,"Branch Family",BranchFamily.ParticleId,BranchFamily.Mother1Id);
    return BranchFamily;

}

hanalysis::HFamily hanalysis::HFourVector::GetBranchFamily(HFamily &BranchFamily, int Position)
{
    Print(HDetailed, "Get Mother Id", GetParticleName(BranchFamily.ParticleId), Position);
    if (Position == 0 && JetTag->HeavyParticles.find(static_cast<HParticleId>(std::abs(BranchFamily.ParticleId))) != end(JetTag->HeavyParticles)) Print(HError, "Proton", std::abs(BranchFamily.ParticleId));

    if (Position < 4 && std::abs(BranchFamily.ParticleId) == 5) Print(HError, "Hello");

    while (
//       Position != EmptyPosition
        Position > 4 // FIXME make it work without this cheat
        && JetTag->HeavyParticles.find(static_cast<HParticleId>(std::abs(BranchFamily.Mother1Id))) == end(JetTag->HeavyParticles)
        && JetTag->HeavyParticles.find(static_cast<HParticleId>(std::abs(BranchFamily.ParticleId))) == end(JetTag->HeavyParticles)
    ) {

        Print(HDetailed, "Topology", Topology.at(Position).ParticleId);

        if (JetTag->HeavyParticles.find(static_cast<HParticleId>(std::abs(Topology.at(Position).Mother1Id))) != end(JetTag->HeavyParticles) || JetTag->HeavyParticles.find(static_cast<HParticleId>(std::abs(Topology.at(Position).ParticleId))) != end(JetTag->HeavyParticles)) {
//             Print(HError, "Abbort 1", Position);
            return Topology.at(Position);
        }

        if (Topology.at(Position).Mother1Id != EmptyId && Topology.at(Position).ParticleId != EmptyId
                && Topology.at(Position).GetMarker() == 0

           ) {
//             Print(HError, "Abbort 2", Position);
            return Topology.at(Position);
        }


        Topology.at(Position).SetMarker();
//         if (Position < Source) Source = Position;
        const delphes::GenParticle *const ParticleClone = (delphes::GenParticle *) ClonesArrays->GetParticle(Position);
        const int Status = ParticleClone->Status;

        int M1Id = EmptyId;
        if (ParticleClone->M1 > 0) {
            const delphes::GenParticle *const Mother1Clone = (delphes::GenParticle *) ClonesArrays->GetParticle(ParticleClone->M1);
            M1Id = Mother1Clone->PID;
        }

        HFamily NodeFamily(Position, ParticleClone->PID, ParticleClone->M1, M1Id);
        if (Status == GeneratorParticle)
            BranchFamily = JetTag->GetBranchFamily(NodeFamily, BranchFamily);

        Print(HDetailed, "Branch Id", GetParticleName(M1Id), GetParticleName(BranchFamily.Mother1Id));

        if (JetTag->HeavyParticles.find(static_cast<HParticleId>(std::abs(BranchFamily.Mother1Id))) != end(JetTag->HeavyParticles)) return BranchFamily;
        if (JetTag->HeavyParticles.find(static_cast<HParticleId>(std::abs(BranchFamily.ParticleId))) != end(JetTag->HeavyParticles)) return BranchFamily;

        if (ParticleClone->M2 != EmptyPosition && ParticleClone->M2 != ParticleClone->M1) {
            if (ParticleClone->PID == StringId) {
                if (ParticleClone->M1 < ParticleClone->M2) {
                    Print(HDetailed, "String", ParticleClone->M1, Position);
                    for (int Counter = ParticleClone->M2; Counter >= ParticleClone->M1; --Counter) {
                        BranchFamily = GetBranchFamily(BranchFamily, Counter);
//                         Print(HError, "Position", Position, BranchFamily.ParticlePosition, BranchFamily.Mother1Position);
                        Print(HDetailed, "StringPart", Counter, BranchFamily.ParticleId);
//                         if (JetTag->HeavyFamily.find(BranchId.Abs()) != end(JetTag->HeavyFamily)) break;
                        if (JetTag->HeavyParticles.find(static_cast<HParticleId>(std::abs(BranchFamily.Mother1Id))) != end(JetTag->HeavyParticles)) return BranchFamily;
                        if (JetTag->HeavyParticles.find(static_cast<HParticleId>(std::abs(BranchFamily.ParticleId))) != end(JetTag->HeavyParticles)) return BranchFamily;
                    }
                }
//             } else {
//                 Print(HDetailed, "Mother 2 Position", GetParticleName(BranchFamily.ParticleId), Position);
//                 BranchFamily = GetBranchFamily(BranchFamily, ParticleClone->M2);
// //                 if (JetTag->HeavyFamily.find(BranchId.Abs()) != end(JetTag->HeavyFamily)) break;
//                 if (JetTag->HeavyParticles.find(static_cast<HParticleId>(std::abs(BranchFamily.Mother1Id))) != end(JetTag->HeavyParticles)) return BranchFamily;
//                 if (JetTag->HeavyParticles.find(static_cast<HParticleId>(std::abs(BranchFamily.ParticleId))) != end(JetTag->HeavyParticles)) return BranchFamily;
            }
        }

        Position = ParticleClone->M1;
        Print(HDetailed, "Mother 1 Position", Position);
    }

//     if (Source < 4 && JetTag->HeavyFamily.find(BranchId.Abs()) != end(JetTag->HeavyFamily)) BranchId = HFamily(MixedJetId,EmptyId,EmptyId);
//     Print(HDetailed, "Branch Id Result", GetParticleName(BranchId));

// Print(HError,"Source",Source);
    return BranchFamily;

}

void hanalysis::HFourVector::PrintTruthLevel(int const Severity) const
{
    if (Severity <= DebugLevel) {

        PrintCell("Position");
        PrintCell("Top Part");
        PrintCell("Top PP");
        PrintCell("Top Moth");
        PrintCell("Top MP");
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
        for (const int Position : HRange(30)) {

            const delphes::GenParticle *Particle = (delphes::GenParticle *)ClonesArrays->GetParticle(Position);

            PrintCell(Position);
            PrintCell(GetParticleName(Topology.at(Position).ParticleId));
            PrintCell(Topology.at(Position).ParticlePosition);
            PrintCell(GetParticleName(Topology.at(Position).Mother1Id));
            PrintCell(Topology.at(Position).Mother1Position);
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
        return GetParticleName(((delphes::GenParticle *)ClonesArrays->GetParticle(Position))->PID);
    } else {
        return " ";
    };

}

