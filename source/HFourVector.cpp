# include "HFourVector.hh"

hanalysis::HFourVector::HFourVector() :
    CheckFourVectors(1),
    Check(0.00001),
    MassCheck(1)
{
//     DebugLevel = kDebug;
    Print(kInformation, "Constructor");
}

hanalysis::HFourVector::~HFourVector()
{
    Print(kInformation, "Destructor");
}

void hanalysis::HFourVector::Newevent(const hanalysis::ClonesArrays &NewClonesArrays)
{
  clones_arrays_ = &NewClonesArrays;
  Topology.assign(clones_arrays_->GetParticleSum(), HFamily(EmptyId));
    Print(kInformation, "Topology", Topology.size());
}


fastjet::PseudoJet hanalysis::HFourVector::PseudoJet(const TLorentzVector &Vector) const
{
    // construct a pseudojet from explicit components
    // PseudoJet(const double px, const double py, const double pz, const double E);
    const fastjet::PseudoJet Jet(Vector.Px(), Vector.Py(), Vector.Pz(), Vector.E());
    return Jet;
}

// TLorentzVector hanalysis::HFourVector::GetLorentzVector(const MissingET & Particle) const
// {
//     Print(kDebug, "Get Lorentz Vector", "MissingET");
//
//     TLorentzVector LorentzVector;
//
//     const float Met = Particle.MET;
//     const float Eta = Particle.Eta;
//     const float Phi = Particle.Phi;
//     LorentzVector.SetPtEtaPhiM(Met, Eta, Phi, 0);
//
//     if (CheckFourVectors) {
//
//         const float LvMet = sqrt(std::pow(LorentzVector.M(),2)+std::pow(LorentzVector.Pt(),2));
//
//         if (std::abs(LvMet - Met) > Check) Print(kError, "Met", Met, LvMet);
//         if (std::abs(LorentzVector.Eta() - Eta) > Check) Print(kError, "Eta", Eta, LorentzVector.Eta());
//         if (std::abs(LorentzVector.Phi() - Phi) > Check) Print(kError, "Phi", Phi, LorentzVector.Phi());
//
//     }
//
//     return LorentzVector;
// }

TLorentzVector hanalysis::HFourVector::GetLorentzVector(const TRootElectron &Particle) const
{
    Print(kDebug, "Get Lorentz Vector", "TRootElectron");
    return GetLorentzVectorByMass(Particle, ElectronMass);
}

TLorentzVector hanalysis::HFourVector::GetLorentzVector(const TRootGenJet &Particle) const
{
    Print(kDebug, "Get Lorentz Vector", "TRootGenJet");
    return GetLorentzVectorByMass(Particle);
}

TLorentzVector hanalysis::HFourVector::GetLorentzVector(const TRootGenParticle &Particle) const
{
    Print(kDebug, "Get Lorentz Vector", "TRootGenParticle");
    return GetLorentzVectorByEnergy(Particle);
}

TLorentzVector hanalysis::HFourVector::GetLorentzVector(const TRootJet &Particle) const
{
    Print(kDebug, "Get Lorentz Vector", "TRootJet");
    return GetLorentzVectorByMass(Particle);
}

TLorentzVector hanalysis::HFourVector::GetLorentzVector(const TRootLHEFParticle &Particle) const
{
    Print(kDebug, "Get Lorentz Vector", "TRootLHEFParticle");
    return GetLorentzVectorByM(Particle);
}

TLorentzVector hanalysis::HFourVector::GetLorentzVector(const TRootMuon &Particle) const
{
    Print(kDebug, "Get Lorentz Vector", "TRootMuon");
    return GetLorentzVectorByMass(Particle, MuonMass);
}

TLorentzVector hanalysis::HFourVector::GetLorentzVector(const TRootPhoton &Particle) const
{
    Print(kDebug, "Get Lorentz Vector", "TRootPhoton");
    return GetLorentzVectorByMass(Particle, 0);
}

TLorentzVector hanalysis::HFourVector::GetLorentzVector(const TRootTau &Particle) const
{
    Print(kDebug, "Get Lorentz Vector", "TRootTau");
    return GetLorentzVectorByMass(Particle, TauMass);
}

// fastjet::PseudoJet hanalysis::HFourVector::GetPseudoJet(const MissingET & Particle) const
// {
//     Print(kDebug, "Get Pseudo Jet", "TRootElectron");
//     return GetPseudoJet(GetLorentzVector(Particle));
// }

fastjet::PseudoJet hanalysis::HFourVector::GetPseudoJet(const TRootElectron &Particle) const
{
    Print(kDebug, "Get Pseudo Jet", "TRootElectron");
    return PseudoJet(GetLorentzVectorByMass(Particle, ElectronMass));
}

fastjet::PseudoJet hanalysis::HFourVector::GetPseudoJet(const TRootGenJet &Particle) const
{
    Print(kDebug, "Get Pseudo Jet", "TRootGenJet");
    return PseudoJet(GetLorentzVectorByMass(Particle));
}

fastjet::PseudoJet hanalysis::HFourVector::GetPseudoJet(const TRootGenParticle &Particle) const
{
    Print(kDebug, "Get Pseudo Jet", "TRootGenParticle");
    return PseudoJet(GetLorentzVectorByEnergy(Particle));
}

fastjet::PseudoJet hanalysis::HFourVector::GetPseudoJet(const TRootJet &Particle) const
{
    Print(kDebug, "Get Pseudo Jet", "TRootJet");
    return PseudoJet(GetLorentzVectorByMass(Particle));
}

fastjet::PseudoJet hanalysis::HFourVector::GetPseudoJet(const TRootLHEFParticle &Particle) const
{
    Print(kDebug, "Get Pseudo Jet", "TRootLHEFParticle");
    return PseudoJet(GetLorentzVectorByM(Particle));
}

fastjet::PseudoJet hanalysis::HFourVector::GetPseudoJet(const TRootMuon &Particle) const
{
    Print(kDebug, "Get Pseudo Jet", "TRootMuon");
    return PseudoJet(GetLorentzVectorByMass(Particle, MuonMass));
}

fastjet::PseudoJet hanalysis::HFourVector::GetPseudoJet(const TRootPhoton &Particle) const
{
    Print(kDebug, "Get Pseudo Jet", "TRootPhoton");
    return PseudoJet(GetLorentzVectorByMass(Particle, 0));
}

fastjet::PseudoJet hanalysis::HFourVector::GetPseudoJet(const TRootTau &Particle) const
{
    Print(kDebug, "Get Pseudo Jet", "TRootTau");
    return PseudoJet(GetLorentzVectorByMass(Particle, TauMass));
}

hanalysis::HFamily hanalysis::HFourVector::GetBranchFamily(const TObject &Object)
{
  Print(kInformation, "Get Mother Id", clones_arrays_->GetParticleSum());

    HFamily BranchFamily;
    if (Object.IsA() != delphes::GenParticle::Class()/* || Object == 0*/) {
        Print(kError, "Object is", Object.ClassName());
        return BranchFamily;
    }

    const int Position = clones_arrays_->GetParticleClonesArray()->IndexOf(&Object);
    if (Position == EmptyPosition) return BranchFamily;

    BranchFamily = GetBranchFamily(BranchFamily, Position);
    if (BranchFamily.Mother1Id == EmptyId)
        BranchFamily = HFamily(BranchFamily.ParticlePosition, IsrId, BranchFamily.Mother1Position, IsrId);
//       Print(kError, "Truth Level Tagging Failed");

    for (auto & Node : Topology) if (Node.Marker()) Node = BranchFamily;
    //
    Print(kDebug, "Branch Family", GetParticleName(BranchFamily.ParticleId), GetParticleName(BranchFamily.Mother1Id));

    if (BranchFamily.ParticleId == EmptyId || BranchFamily.Mother1Id == EmptyId) Print(kError, "Branch Family", GetParticleName(BranchFamily.ParticleId), GetParticleName(BranchFamily.Mother1Id));
    return BranchFamily;

}

hanalysis::HFamily hanalysis::HFourVector::GetBranchFamily(HFamily &BranchFamily, int Position)
{
    Print(kInformation, "Get Branch Family ", GetParticleName(BranchFamily.ParticleId), Position);

    if (
        JetTag->HeavyParticles.find(static_cast<HParticleId>(std::abs(Topology.at(Position).Mother1Id))) != end(JetTag->HeavyParticles) ||
        JetTag->HeavyParticles.find(static_cast<HParticleId>(std::abs(Topology.at(Position).ParticleId))) != end(JetTag->HeavyParticles) ||
        Topology.at(Position).ParticleId == IsrId
    ) {
        return Topology.at(Position);
    }

    while (
        Position != EmptyPosition &&
        JetTag->HeavyParticles.find(static_cast<HParticleId>(std::abs(BranchFamily.Mother1Id))) == end(JetTag->HeavyParticles) &&
        JetTag->HeavyParticles.find(static_cast<HParticleId>(std::abs(BranchFamily.ParticleId))) == end(JetTag->HeavyParticles)
    ) {

        Print(kDebug, "Topology", Position, GetParticleName(Topology.at(Position).ParticleId), GetParticleName(Topology.at(Position).Mother1Id));

        if (
            JetTag->HeavyParticles.find(static_cast<HParticleId>(std::abs(Topology.at(Position).Mother1Id))) != end(JetTag->HeavyParticles) ||
            JetTag->HeavyParticles.find(static_cast<HParticleId>(std::abs(Topology.at(Position).ParticleId))) != end(JetTag->HeavyParticles) ||
            Topology.at(Position).ParticleId == IsrId
        ) {
            return Topology.at(Position);
        }

        if (Topology.at(Position).Mother1Id != EmptyId && Topology.at(Position).ParticleId != EmptyId
                && Topology.at(Position).Marker() == 0

           ) {
            return Topology.at(Position);
        }

        Topology.at(Position).SetMarker();
//         if (Position < 3) return HFamily(Position, IsrId, EmptyPosition, IsrId);


        delphes::GenParticle &ParticleClone = static_cast<delphes::GenParticle &>(*clones_arrays_->GetParticle(Position));
//         const int Status = ParticleClone.Status;

        int M1Id = EmptyId;
        int Mother1Status = EmptyStatus;
        TLorentzVector MotherVector;
        if (ParticleClone.M1 > 0) {
          delphes::GenParticle &Mother1Clone = static_cast<delphes::GenParticle &>(*clones_arrays_->GetParticle(ParticleClone.M1));
            M1Id = Mother1Clone.PID;
            MotherVector = Mother1Clone.P4();
            Mother1Status = Mother1Clone.Status;
        }

        HFamily NodeFamily(ParticleClone.P4(), MotherVector, Position, ParticleClone.PID, ParticleClone.M1, M1Id);
        if (Mother1Status == GeneratorParticle)
            BranchFamily = JetTag->GetBranchFamily(NodeFamily, BranchFamily);

        Print(kDetailed, "Branch Id", GetParticleName(M1Id), GetParticleName(BranchFamily.Mother1Id));

        if (JetTag->HeavyParticles.find(static_cast<HParticleId>(std::abs(BranchFamily.Mother1Id))) != end(JetTag->HeavyParticles)) return BranchFamily;
        if (JetTag->HeavyParticles.find(static_cast<HParticleId>(std::abs(BranchFamily.ParticleId))) != end(JetTag->HeavyParticles)) return BranchFamily;

        if (ParticleClone.M2 != EmptyPosition && ParticleClone.M2 != ParticleClone.M1) {
            if (ParticleClone.PID == StringId) {
                if (ParticleClone.M1 < ParticleClone.M2) {
                    Print(kDebug, "String", Position, ParticleClone.M1, ParticleClone.M2);
                    JetInfo jet_info;
//                     for (int Counter = ParticleClone.M2; Counter >= ParticleClone.M1; --Counter) {
                    for (int Counter = ParticleClone.M1; Counter <= ParticleClone.M2; ++Counter) {
//                         BranchFamily = GetBranchFamily(BranchFamily, Counter);
                        HFamily NewFamily = GetBranchFamily(BranchFamily, Counter);
                        jet_info.AddFamily(NewFamily, NewFamily.Pt);
                        Print(kDebug, "StringPart", Counter, GetParticleName(BranchFamily.ParticleId));
//                         if (std::abs(BranchFamily.ParticleId) == IsrId) return BranchFamily;
                    }
                    jet_info.PrintAllFamInfos(kDebug);
                    if (jet_info.FamilyFractions().size() > 1) {
                        for (int Counter = ParticleClone.M1; Counter <= ParticleClone.M2; ++Counter) {
                            Topology.at(Counter).UnSetMarker();
                        }
                        Print(kDebug, "To many String fractions");
                    };
                    BranchFamily = jet_info.MaximalFamily();
                } else {
                    Print(kError, "Strange Particle String");
                }
                if (JetTag->HeavyParticles.find(static_cast<HParticleId>(std::abs(BranchFamily.Mother1Id))) != end(JetTag->HeavyParticles)) return BranchFamily;
                if (JetTag->HeavyParticles.find(static_cast<HParticleId>(std::abs(BranchFamily.ParticleId))) != end(JetTag->HeavyParticles)) return BranchFamily;
            } else {
                Print(kDebug, "Not a String", Position, ParticleClone.M1, ParticleClone.M2);
            }
        }

        Position = ParticleClone.M1;
        Print(kDetailed, "Mother 1 Position", Position);
    }
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

        //         for (const int Position : HRange(clones_arrays_->GetParticleSum())) {
        for (const int Position : Range(30)) {

          delphes::GenParticle &Particle = static_cast<delphes::GenParticle &>(*clones_arrays_->GetParticle(Position));

            PrintCell(Position);
            PrintCell(GetParticleName(Topology.at(Position).ParticleId));
            PrintCell(Topology.at(Position).ParticlePosition);
            PrintCell(GetParticleName(Topology.at(Position).Mother1Id));
            PrintCell(Topology.at(Position).Mother1Position);
            PrintCell(Particle.Status);
            PrintCell(GetParticleName(Particle.PID));
            PrintCell(Particle.M1);
            PrintCell(PrintParticle(Particle.M1));
            PrintCell(Particle.M2);
            PrintCell(PrintParticle(Particle.M2));
            PrintCell(Particle.D1);
            PrintCell(PrintParticle(Particle.D1));
            PrintCell(Particle.D2);
            PrintCell(PrintParticle(Particle.D2));
            PrintCell(Particle.E);
            PrintCell(Particle.Px);
            PrintCell(Particle.Py);
            PrintCell(Particle.Pz);
            std::cout << std::endl;

        }

    }

}

std::string hanalysis::HFourVector::PrintParticle(const int Position) const
{

    if (Position != -1) {
      return GetParticleName(((delphes::GenParticle *)clones_arrays_->GetParticle(Position))->PID);
    } else {
        return " ";
    };

}

