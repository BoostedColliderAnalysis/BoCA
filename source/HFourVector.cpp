# include "HFourVector.hh"

# include "TClonesArray.h"
# include "Predicate.hh"

analysis::HFourVector::HFourVector() :
    CheckFourVectors(1),
    Check(0.00001),
    MassCheck(1)
{
//     DebugLevel = kDebug;
    Print(kInformation, "Constructor");
}

analysis::HFourVector::~HFourVector()
{
    Print(kInformation, "Destructor");
}

void analysis::HFourVector::Newevent(const analysis::ClonesArrays &NewClonesArrays)
{
    clones_arrays_ = &NewClonesArrays;
    Topology.assign(clones_arrays().ParticleSum(), Family(EmptyId));
    Print(kInformation, "Topology", Topology.size());
}

// TLorentzVector analysis::HFourVector::GetLorentzVector(const MissingET & Particle) const
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

TLorentzVector analysis::HFourVector::GetLorentzVector(const TRootElectron &Particle) const
{
    Print(kDebug, "Get Lorentz Vector", "TRootElectron");
    return GetLorentzVectorByMass(Particle, ElectronMass);
}

TLorentzVector analysis::HFourVector::GetLorentzVector(const TRootGenJet &Particle) const
{
    Print(kDebug, "Get Lorentz Vector", "TRootGenJet");
    return GetLorentzVectorByMass(Particle);
}

TLorentzVector analysis::HFourVector::GetLorentzVector(const TRootGenParticle &Particle) const
{
    Print(kDebug, "Get Lorentz Vector", "TRootGenParticle");
    return GetLorentzVectorByEnergy(Particle);
}

TLorentzVector analysis::HFourVector::GetLorentzVector(const TRootJet &Particle) const
{
    Print(kDebug, "Get Lorentz Vector", "TRootJet");
    return GetLorentzVectorByMass(Particle);
}

TLorentzVector analysis::HFourVector::GetLorentzVector(const TRootLHEFParticle &Particle) const
{
    Print(kDebug, "Get Lorentz Vector", "TRootLHEFParticle");
    return GetLorentzVectorByM(Particle);
}

TLorentzVector analysis::HFourVector::GetLorentzVector(const TRootMuon &Particle) const
{
    Print(kDebug, "Get Lorentz Vector", "TRootMuon");
    return GetLorentzVectorByMass(Particle, MuonMass);
}

TLorentzVector analysis::HFourVector::GetLorentzVector(const TRootPhoton &Particle) const
{
    Print(kDebug, "Get Lorentz Vector", "TRootPhoton");
    return GetLorentzVectorByMass(Particle, 0);
}

TLorentzVector analysis::HFourVector::GetLorentzVector(const TRootTau &Particle) const
{
    Print(kDebug, "Get Lorentz Vector", "TRootTau");
    return GetLorentzVectorByMass(Particle, TauMass);
}

// fastjet::PseudoJet analysis::HFourVector::GetPseudoJet(const MissingET & Particle) const
// {
//     Print(kDebug, "Get Pseudo Jet", "TRootElectron");
//     return GetPseudoJet(GetLorentzVector(Particle));
// }

fastjet::PseudoJet analysis::HFourVector::GetPseudoJet(const TRootElectron &Particle) const
{
    Print(kDebug, "Get Pseudo Jet", "TRootElectron");
    return PseudoJet(GetLorentzVectorByMass(Particle, ElectronMass));
}

fastjet::PseudoJet analysis::HFourVector::GetPseudoJet(const TRootGenJet &Particle) const
{
    Print(kDebug, "Get Pseudo Jet", "TRootGenJet");
    return PseudoJet(GetLorentzVectorByMass(Particle));
}

fastjet::PseudoJet analysis::HFourVector::GetPseudoJet(const TRootGenParticle &Particle) const
{
    Print(kDebug, "Get Pseudo Jet", "TRootGenParticle");
    return PseudoJet(GetLorentzVectorByEnergy(Particle));
}

fastjet::PseudoJet analysis::HFourVector::GetPseudoJet(const TRootJet &Particle) const
{
    Print(kDebug, "Get Pseudo Jet", "TRootJet");
    return PseudoJet(GetLorentzVectorByMass(Particle));
}

fastjet::PseudoJet analysis::HFourVector::GetPseudoJet(const TRootLHEFParticle &Particle) const
{
    Print(kDebug, "Get Pseudo Jet", "TRootLHEFParticle");
    return PseudoJet(GetLorentzVectorByM(Particle));
}

fastjet::PseudoJet analysis::HFourVector::GetPseudoJet(const TRootMuon &Particle) const
{
    Print(kDebug, "Get Pseudo Jet", "TRootMuon");
    return PseudoJet(GetLorentzVectorByMass(Particle, MuonMass));
}

fastjet::PseudoJet analysis::HFourVector::GetPseudoJet(const TRootPhoton &Particle) const
{
    Print(kDebug, "Get Pseudo Jet", "TRootPhoton");
    return PseudoJet(GetLorentzVectorByMass(Particle, 0));
}

fastjet::PseudoJet analysis::HFourVector::GetPseudoJet(const TRootTau &Particle) const
{
    Print(kDebug, "Get Pseudo Jet", "TRootTau");
    return PseudoJet(GetLorentzVectorByMass(Particle, TauMass));
}

analysis::Family analysis::HFourVector::GetBranchFamily(const TObject &object)
{
    Print(kInformation, "Get Mother Id", clones_arrays().ParticleSum());
    Family family;
    if (object.IsA() != delphes::GenParticle::Class()/* || Object == 0*/) {
        Print(kError, "Object is", object.ClassName());
        return family;
    }
    const int Position = clones_arrays().ParticleClonesArray().IndexOf(&object);
    if (Position == EmptyPosition) return family;
    family = GetBranchFamily(family, Position);
    if (family.mother_1().Id == EmptyId)
        family = Family(family.particle().Position, IsrId, family.mother_1().Position, IsrId);
//       Print(kError, "Truth Level Tagging Failed");
    for (auto & Node : Topology) if (Node.Marker()) Node = family;
    //
    Print(kDebug, "Branch Family", GetParticleName(family.particle().Id), GetParticleName(family.mother_1().Id));
    if (family.particle().Id == EmptyId || family.mother_1().Id == EmptyId) Print(kError, "Branch Family", GetParticleName(family.particle().Id), GetParticleName(family.mother_1().Id));
    return family;
}

analysis::Family analysis::HFourVector::GetBranchFamily(Family &family, int Position)
{
    Print(kInformation, "Get Branch Family ", GetParticleName(family.particle().Id), Position);
    if (
        JetTag->HeavyParticles.find(static_cast<HParticleId>(std::abs(Topology.at(Position).mother_1().Id))) != end(JetTag->HeavyParticles) ||
        JetTag->HeavyParticles.find(static_cast<HParticleId>(std::abs(Topology.at(Position).particle().Id))) != end(JetTag->HeavyParticles) ||
        Topology.at(Position).particle().Id == IsrId
    ) {
        return Topology.at(Position);
    }
    while (
        Position != EmptyPosition &&
        JetTag->HeavyParticles.find(static_cast<HParticleId>(std::abs(family.mother_1().Id))) == end(JetTag->HeavyParticles) &&
        JetTag->HeavyParticles.find(static_cast<HParticleId>(std::abs(family.particle().Id))) == end(JetTag->HeavyParticles)
    ) {
        Print(kDebug, "Topology", Position, GetParticleName(Topology.at(Position).particle().Id), GetParticleName(Topology.at(Position).mother_1().Id));
        if (
            JetTag->HeavyParticles.find(static_cast<HParticleId>(std::abs(Topology.at(Position).mother_1().Id))) != end(JetTag->HeavyParticles) ||
            JetTag->HeavyParticles.find(static_cast<HParticleId>(std::abs(Topology.at(Position).particle().Id))) != end(JetTag->HeavyParticles) ||
            Topology.at(Position).particle().Id == IsrId
        ) {
            return Topology.at(Position);
        }
        if (Topology.at(Position).mother_1().Id != EmptyId && Topology.at(Position).particle().Id != EmptyId
                && Topology.at(Position).Marker() == 0
           ) {
            return Topology.at(Position);
        }
        Topology.at(Position).SetMarker();
//         if (Position < 3) return Family(Position, IsrId, EmptyPosition, IsrId);
        delphes::GenParticle &particle = static_cast<delphes::GenParticle &>(clones_arrays().Particle(Position));
//         const int Status = ParticleClone.Status;
        int M1Id = EmptyId;
        int Mother1Status = EmptyStatus;
        TLorentzVector MotherVector;
        if (particle.M1 > 0) {
            delphes::GenParticle &Mother1Clone = static_cast<delphes::GenParticle &>(clones_arrays().Particle(particle.M1));
            M1Id = Mother1Clone.PID;
            MotherVector = Mother1Clone.P4();
            Mother1Status = Mother1Clone.Status;
        }
        Family NodeFamily(particle.P4(), MotherVector, Position, particle.PID, particle.M1, M1Id);
        if (Mother1Status == GeneratorParticle)
            family = JetTag->GetBranchFamily(NodeFamily, family);
        Print(kDetailed, "Branch Id", GetParticleName(M1Id), GetParticleName(family.mother_1().Id));
        if (JetTag->HeavyParticles.find(static_cast<HParticleId>(std::abs(family.mother_1().Id))) != end(JetTag->HeavyParticles)) return family;
        if (JetTag->HeavyParticles.find(static_cast<HParticleId>(std::abs(family.particle().Id))) != end(JetTag->HeavyParticles)) return family;
        if (particle.M2 != EmptyPosition && particle.M2 != particle.M1) {
            if (particle.PID == StringId) {
                if (particle.M1 < particle.M2) {
                    Print(kDebug, "String", Position, particle.M1, particle.M2);
                    JetInfo jet_info;
//                     for (int Counter = ParticleClone.M2; Counter >= ParticleClone.M1; --Counter) {
                    for (int Counter = particle.M1; Counter <= particle.M2; ++Counter) {
//                         BranchFamily = GetBranchFamily(BranchFamily, Counter);
                        Family NewFamily = GetBranchFamily(family, Counter);
                        jet_info.AddFamily(NewFamily, NewFamily.Pt());
                        Print(kDebug, "StringPart", Counter, GetParticleName(family.particle().Id));
//                         if (std::abs(BranchFamily.particle().Id) == IsrId) return BranchFamily;
                    }
                    jet_info.PrintAllFamInfos(kDebug);
                    if (jet_info.FamilyFractions().size() > 1) {
                        for (int Counter = particle.M1; Counter <= particle.M2; ++Counter) {
                            Topology.at(Counter).UnSetMarker();
                        }
                        Print(kDebug, "To many String fractions");
                    };
                    family = jet_info.MaximalFamily();
                } else {
                    Print(kError, "Strange Particle String");
                }
                if (JetTag->HeavyParticles.find(static_cast<HParticleId>(std::abs(family.mother_1().Id))) != end(JetTag->HeavyParticles)) return family;
                if (JetTag->HeavyParticles.find(static_cast<HParticleId>(std::abs(family.particle().Id))) != end(JetTag->HeavyParticles)) return family;
            } else {
                Print(kDebug, "Not a String", Position, particle.M1, particle.M2);
            }
        }
        Position = particle.M1;
        Print(kDetailed, "Mother 1 Position", Position);
    }
    return family;
}

void analysis::HFourVector::PrintTruthLevel(int const severity) const
{
    if (severity <= DebugLevel) {
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
        //         for (const int Position : HRange(clones_arrays().GetParticleSum())) {
        for (const int Position : Range(30)) {
            delphes::GenParticle &Particle = static_cast<delphes::GenParticle &>(clones_arrays().Particle(Position));
            PrintCell(Position);
            PrintCell(GetParticleName(Topology.at(Position).particle().Id));
            PrintCell(Topology.at(Position).particle().Position);
            PrintCell(GetParticleName(Topology.at(Position).mother_1().Id));
            PrintCell(Topology.at(Position).mother_1().Position);
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

std::string analysis::HFourVector::PrintParticle(const int Position) const
{
    if (Position != -1) {
        return GetParticleName(static_cast<delphes::GenParticle &>(clones_arrays().Particle(Position)).PID);
    } else {
        return " ";
    };
}

