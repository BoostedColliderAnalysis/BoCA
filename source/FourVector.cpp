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

TLorentzVector analysis::FourVector::LorentzVector(const TRootElectron &Particle) const
{
    Print(kDebug, "Get Lorentz Vector", "TRootElectron");
    return LorentzVectorByMass(Particle, Mass(ElectronId));
}

TLorentzVector analysis::FourVector::LorentzVector(const TRootGenJet &Particle) const
{
    Print(kDebug, "Get Lorentz Vector", "TRootGenJet");
    return LorentzVectorByMass(Particle);
}

TLorentzVector analysis::FourVector::LorentzVector(const TRootGenParticle &Particle) const
{
    Print(kDebug, "Get Lorentz Vector", "TRootGenParticle");
    return LorentzVectorByEnergy(Particle);
}

TLorentzVector analysis::FourVector::LorentzVector(const TRootJet &Particle) const
{
    Print(kDebug, "Get Lorentz Vector", "TRootJet");
    return LorentzVectorByMass(Particle);
}

TLorentzVector analysis::FourVector::LorentzVector(const TRootLHEFParticle &Particle) const
{
    Print(kDebug, "Get Lorentz Vector", "TRootLHEFParticle");
    return LorentzVectorByM(Particle);
}

TLorentzVector analysis::FourVector::LorentzVector(const TRootMuon &Particle) const
{
    Print(kDebug, "Get Lorentz Vector", "TRootMuon");
    return LorentzVectorByMass(Particle, Mass(MuonId));
}

TLorentzVector analysis::FourVector::LorentzVector(const TRootPhoton &Particle) const
{
    Print(kDebug, "Get Lorentz Vector", "TRootPhoton");
    return LorentzVectorByMass(Particle, Mass(PhotonId));
}

TLorentzVector analysis::FourVector::LorentzVector(const TRootTau &Particle) const
{
    Print(kDebug, "Get Lorentz Vector", "TRootTau");
    return LorentzVectorByMass(Particle, Mass(TauId));
}

fastjet::PseudoJet analysis::FourVector::PseudoJet(const TRootElectron &Particle) const
{
    Print(kDebug, "Get Pseudo Jet", "TRootElectron");
    return analysis::PseudoJet(LorentzVectorByMass(Particle, Mass(ElectronId)));
}

fastjet::PseudoJet analysis::FourVector::PseudoJet(const TRootGenJet &Particle) const
{
    Print(kDebug, "Get Pseudo Jet", "TRootGenJet");
    return analysis::PseudoJet(LorentzVectorByMass(Particle));
}

fastjet::PseudoJet analysis::FourVector::PseudoJet(const TRootGenParticle &Particle) const
{
    Print(kDebug, "Get Pseudo Jet", "TRootGenParticle");
    return analysis::PseudoJet(LorentzVectorByEnergy(Particle));
}

fastjet::PseudoJet analysis::FourVector::PseudoJet(const TRootJet &Particle) const
{
    Print(kDebug, "Get Pseudo Jet", "TRootJet");
    return analysis::PseudoJet(LorentzVectorByMass(Particle));
}

fastjet::PseudoJet analysis::FourVector::PseudoJet(const TRootLHEFParticle &Particle) const
{
    Print(kDebug, "Get Pseudo Jet", "TRootLHEFParticle");
    return analysis::PseudoJet(LorentzVectorByM(Particle));
}

fastjet::PseudoJet analysis::FourVector::PseudoJet(const TRootMuon &Particle) const
{
    Print(kDebug, "Get Pseudo Jet", "TRootMuon");
    return analysis::PseudoJet(LorentzVectorByMass(Particle, Mass(MuonId)));
}

fastjet::PseudoJet analysis::FourVector::PseudoJet(const TRootPhoton &Particle) const
{
    Print(kDebug, "Get Pseudo Jet", "TRootPhoton");
    return analysis::PseudoJet(LorentzVectorByMass(Particle, 0));
}

fastjet::PseudoJet analysis::FourVector::PseudoJet(const TRootTau &Particle) const
{
    Print(kDebug, "Get Pseudo Jet", "TRootTau");
    return analysis::PseudoJet(LorentzVectorByMass(Particle, Mass(TauId)));
}

analysis::Family analysis::FourVector::GetBranchFamily(const TObject &object)
{
    Print(kInformation, "Get Mother Id", clones_arrays().ParticleSum());
    Family family;
    if (object.IsA() != ::delphes::GenParticle::Class()/* || Object == 0*/) {
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
    Print(kDebug, "Branch Family", Name(family.particle().Id), Name(family.mother_1().Id));
    if (family.particle().Id == EmptyId || family.mother_1().Id == EmptyId) Print(kError, "Branch Family", Name(family.particle().Id), Name(family.mother_1().Id));
    return family;
}

analysis::Family analysis::FourVector::GetBranchFamily(Family &family, int Position)
{
    Print(kInformation, "Get Branch Family ", Name(family.particle().Id), Position);
    if (
        jet_tag().HeavyParticles.find(static_cast<ParticleId>(std::abs(topology_.at(Position).mother_1().Id))) != end(jet_tag().HeavyParticles) ||
        jet_tag().HeavyParticles.find(static_cast<ParticleId>(std::abs(topology_.at(Position).particle().Id))) != end(jet_tag().HeavyParticles) ||
        topology_.at(Position).particle().Id == IsrId
    ) {
        return topology_.at(Position);
    }
    while (
        Position != EmptyPosition &&
        jet_tag().HeavyParticles.find(static_cast<ParticleId>(std::abs(family.mother_1().Id))) == end(jet_tag().HeavyParticles) &&
        jet_tag().HeavyParticles.find(static_cast<ParticleId>(std::abs(family.particle().Id))) == end(jet_tag().HeavyParticles)
    ) {
        Print(kDebug, "Topology", Position, Name(topology_.at(Position).particle().Id), Name(topology_.at(Position).mother_1().Id));
        if (
            jet_tag().HeavyParticles.find(static_cast<ParticleId>(std::abs(topology_.at(Position).mother_1().Id))) != end(jet_tag().HeavyParticles) ||
            jet_tag().HeavyParticles.find(static_cast<ParticleId>(std::abs(topology_.at(Position).particle().Id))) != end(jet_tag().HeavyParticles) ||
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
        ::delphes::GenParticle &particle = static_cast<::delphes::GenParticle &>(clones_arrays().Particle(Position));
//         const int Status = ParticleClone.Status;
        int M1Id = EmptyId;
        int Mother1Status = kNoStatus;
        TLorentzVector MotherVector;
        if (particle.M1 > 0) {
            ::delphes::GenParticle &Mother1Clone = static_cast<::delphes::GenParticle &>(clones_arrays().Particle(particle.M1));
            M1Id = Mother1Clone.PID;
            MotherVector = Mother1Clone.P4();
            Mother1Status = Mother1Clone.Status;
        }
        Family NodeFamily(particle.P4(), MotherVector, Position, particle.PID, particle.M1, M1Id);
        if (Mother1Status == kGenerator)
            family = jet_tag().GetBranchFamily(NodeFamily, family);
        Print(kDetailed, "Branch Id", Name(M1Id), Name(family.mother_1().Id));
        if (jet_tag().HeavyParticles.find(static_cast<ParticleId>(std::abs(family.mother_1().Id))) != end(jet_tag().HeavyParticles)) return family;
        if (jet_tag().HeavyParticles.find(static_cast<ParticleId>(std::abs(family.particle().Id))) != end(jet_tag().HeavyParticles)) return family;
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
                        Print(kDebug, "StringPart", Counter, Name(family.particle().Id));
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
                if (jet_tag().HeavyParticles.find(static_cast<ParticleId>(std::abs(family.mother_1().Id))) != end(jet_tag().HeavyParticles)) return family;
                if (jet_tag().HeavyParticles.find(static_cast<ParticleId>(std::abs(family.particle().Id))) != end(jet_tag().HeavyParticles)) return family;
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
            ::delphes::GenParticle &Particle = static_cast<::delphes::GenParticle &>(clones_arrays().Particle(Position));
            PrintCell(Position);
            PrintCell(Name(topology_.at(Position).particle().Id));
            PrintCell(topology_.at(Position).particle().Position);
            PrintCell(Name(topology_.at(Position).mother_1().Id));
            PrintCell(topology_.at(Position).mother_1().Position);
            PrintCell(Particle.Status);
            PrintCell(Name(Particle.PID));
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
    if (Position != -1) return Name(static_cast<::delphes::GenParticle &>(clones_arrays().Particle(Position)).PID);
    else return " ";
}

