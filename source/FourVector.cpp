# include "FourVector.hh"

# include "TClonesArray.h"
# include "Predicate.hh"

analysis::FourVector::FourVector() :
    check_four_vectors_(1),
    check_value_(0.00001),
    mass_check_value_(1)
{
//     DebugLevel = kDebug;
    Print(kInformation, "Constructor");
}

void analysis::FourVector::NewEvent(const analysis::ClonesArrays &clones_arrays)
{
    clones_arrays_ = &clones_arrays;
    topology_.assign(clones_arrays_->ParticleSum(), Family(EmptyId));
    Print(kInformation, "Topology", topology_.size());
}

TLorentzVector analysis::FourVector::GetLorentzVector(const TRootElectron &Particle) const
{
    Print(kDebug, "Get Lorentz Vector", "TRootElectron");
    return GetLorentzVectorByMass(Particle, ElectronMass);
}

TLorentzVector analysis::FourVector::GetLorentzVector(const TRootGenJet &Particle) const
{
    Print(kDebug, "Get Lorentz Vector", "TRootGenJet");
    return GetLorentzVectorByMass(Particle);
}

TLorentzVector analysis::FourVector::GetLorentzVector(const TRootGenParticle &Particle) const
{
    Print(kDebug, "Get Lorentz Vector", "TRootGenParticle");
    return GetLorentzVectorByEnergy(Particle);
}

TLorentzVector analysis::FourVector::GetLorentzVector(const TRootJet &Particle) const
{
    Print(kDebug, "Get Lorentz Vector", "TRootJet");
    return GetLorentzVectorByMass(Particle);
}

TLorentzVector analysis::FourVector::GetLorentzVector(const TRootLHEFParticle &Particle) const
{
    Print(kDebug, "Get Lorentz Vector", "TRootLHEFParticle");
    return GetLorentzVectorByM(Particle);
}

TLorentzVector analysis::FourVector::GetLorentzVector(const TRootMuon &Particle) const
{
    Print(kDebug, "Get Lorentz Vector", "TRootMuon");
    return GetLorentzVectorByMass(Particle, MuonMass);
}

TLorentzVector analysis::FourVector::GetLorentzVector(const TRootPhoton &Particle) const
{
    Print(kDebug, "Get Lorentz Vector", "TRootPhoton");
    return GetLorentzVectorByMass(Particle, 0);
}

TLorentzVector analysis::FourVector::GetLorentzVector(const TRootTau &Particle) const
{
    Print(kDebug, "Get Lorentz Vector", "TRootTau");
    return GetLorentzVectorByMass(Particle, TauMass);
}

fastjet::PseudoJet analysis::FourVector::GetPseudoJet(const TRootElectron &Particle) const
{
    Print(kDebug, "Get Pseudo Jet", "TRootElectron");
    return PseudoJet(GetLorentzVectorByMass(Particle, ElectronMass));
}

fastjet::PseudoJet analysis::FourVector::GetPseudoJet(const TRootGenJet &Particle) const
{
    Print(kDebug, "Get Pseudo Jet", "TRootGenJet");
    return PseudoJet(GetLorentzVectorByMass(Particle));
}

fastjet::PseudoJet analysis::FourVector::GetPseudoJet(const TRootGenParticle &Particle) const
{
    Print(kDebug, "Get Pseudo Jet", "TRootGenParticle");
    return PseudoJet(GetLorentzVectorByEnergy(Particle));
}

fastjet::PseudoJet analysis::FourVector::GetPseudoJet(const TRootJet &Particle) const
{
    Print(kDebug, "Get Pseudo Jet", "TRootJet");
    return PseudoJet(GetLorentzVectorByMass(Particle));
}

fastjet::PseudoJet analysis::FourVector::GetPseudoJet(const TRootLHEFParticle &Particle) const
{
    Print(kDebug, "Get Pseudo Jet", "TRootLHEFParticle");
    return PseudoJet(GetLorentzVectorByM(Particle));
}

fastjet::PseudoJet analysis::FourVector::GetPseudoJet(const TRootMuon &Particle) const
{
    Print(kDebug, "Get Pseudo Jet", "TRootMuon");
    return PseudoJet(GetLorentzVectorByMass(Particle, MuonMass));
}

fastjet::PseudoJet analysis::FourVector::GetPseudoJet(const TRootPhoton &Particle) const
{
    Print(kDebug, "Get Pseudo Jet", "TRootPhoton");
    return PseudoJet(GetLorentzVectorByMass(Particle, 0));
}

fastjet::PseudoJet analysis::FourVector::GetPseudoJet(const TRootTau &Particle) const
{
    Print(kDebug, "Get Pseudo Jet", "TRootTau");
    return PseudoJet(GetLorentzVectorByMass(Particle, TauMass));
}

analysis::Family analysis::FourVector::GetBranchFamily(const TObject &object)
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
    if (family.mother_1().Id == EmptyId) family = Family(family.particle().Position, IsrId, family.mother_1().Position, IsrId);
//       Print(kError, "Truth Level Tagging Failed");
    for (auto & Node : topology_) if (Node.Marker()) Node = family;
    //
    Print(kDebug, "Branch Family", GetParticleName(family.particle().Id), GetParticleName(family.mother_1().Id));
    if (family.particle().Id == EmptyId || family.mother_1().Id == EmptyId) Print(kError, "Branch Family", GetParticleName(family.particle().Id), GetParticleName(family.mother_1().Id));
    return family;
}

analysis::Family analysis::FourVector::GetBranchFamily(Family &family, int Position)
{
    Print(kInformation, "Get Branch Family ", GetParticleName(family.particle().Id), Position);
    if (
        jet_tag_->HeavyParticles.find(static_cast<HParticleId>(std::abs(topology_.at(Position).mother_1().Id))) != end(jet_tag_->HeavyParticles) ||
        jet_tag_->HeavyParticles.find(static_cast<HParticleId>(std::abs(topology_.at(Position).particle().Id))) != end(jet_tag_->HeavyParticles) ||
        topology_.at(Position).particle().Id == IsrId
    ) {
        return topology_.at(Position);
    }
    while (
        Position != EmptyPosition &&
        jet_tag_->HeavyParticles.find(static_cast<HParticleId>(std::abs(family.mother_1().Id))) == end(jet_tag_->HeavyParticles) &&
        jet_tag_->HeavyParticles.find(static_cast<HParticleId>(std::abs(family.particle().Id))) == end(jet_tag_->HeavyParticles)
    ) {
        Print(kDebug, "Topology", Position, GetParticleName(topology_.at(Position).particle().Id), GetParticleName(topology_.at(Position).mother_1().Id));
        if (
            jet_tag_->HeavyParticles.find(static_cast<HParticleId>(std::abs(topology_.at(Position).mother_1().Id))) != end(jet_tag_->HeavyParticles) ||
            jet_tag_->HeavyParticles.find(static_cast<HParticleId>(std::abs(topology_.at(Position).particle().Id))) != end(jet_tag_->HeavyParticles) ||
            topology_.at(Position).particle().Id == IsrId
        ) {
            return topology_.at(Position);
        }
        if (topology_.at(Position).mother_1().Id != EmptyId && topology_.at(Position).particle().Id != EmptyId
                && topology_.at(Position).Marker() == 0
           ) {
            return topology_.at(Position);
        }
        topology_.at(Position).SetMarker();
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
            family = jet_tag_->GetBranchFamily(NodeFamily, family);
        Print(kDetailed, "Branch Id", GetParticleName(M1Id), GetParticleName(family.mother_1().Id));
        if (jet_tag_->HeavyParticles.find(static_cast<HParticleId>(std::abs(family.mother_1().Id))) != end(jet_tag_->HeavyParticles)) return family;
        if (jet_tag_->HeavyParticles.find(static_cast<HParticleId>(std::abs(family.particle().Id))) != end(jet_tag_->HeavyParticles)) return family;
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
                            topology_.at(Counter).UnSetMarker();
                        }
                        Print(kDebug, "To many String fractions");
                    };
                    family = jet_info.MaximalFamily();
                } else {
                    Print(kError, "Strange Particle String");
                }
                if (jet_tag_->HeavyParticles.find(static_cast<HParticleId>(std::abs(family.mother_1().Id))) != end(jet_tag_->HeavyParticles)) return family;
                if (jet_tag_->HeavyParticles.find(static_cast<HParticleId>(std::abs(family.particle().Id))) != end(jet_tag_->HeavyParticles)) return family;
            } else {
                Print(kDebug, "Not a String", Position, particle.M1, particle.M2);
            }
        }
        Position = particle.M1;
        Print(kDetailed, "Mother 1 Position", Position);
    }
    return family;
}

void analysis::FourVector::PrintTruthLevel(int const severity) const
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
            PrintCell(GetParticleName(topology_.at(Position).particle().Id));
            PrintCell(topology_.at(Position).particle().Position);
            PrintCell(GetParticleName(topology_.at(Position).mother_1().Id));
            PrintCell(topology_.at(Position).mother_1().Position);
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

std::string analysis::FourVector::PrintParticle(const int Position) const
{
    if (Position != -1) return GetParticleName(static_cast<delphes::GenParticle &>(clones_arrays().Particle(Position)).PID);
    else return " ";
}

