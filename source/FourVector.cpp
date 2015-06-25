# include "FourVector.hh"

# include "TClonesArray.h"
# include "Predicate.hh"

namespace analysis {

FourVector::FourVector() :
    check_four_vectors_(1),
    check_value_(0.00001),
    mass_check_value_(1)
{
//     DebugLevel = Severity::Debug;
    Print(Severity::Information, "Constructor");
}

void FourVector::NewEvent(const ClonesArrays &clones_arrays)
{
    clones_arrays_ = &clones_arrays;
    topology_.assign(clones_arrays_->ParticleSum(), Family(Id::Empty));
    Print(Severity::Information, "Topology", topology_.size());
}

TLorentzVector FourVector::LorentzVector(const exroot::Electron &Particle) const
{
    Print(Severity::Debug, "Lorentz Vector", "Electron");
    return LorentzVectorByMass(Particle, Mass(Id::Electron));
}

TLorentzVector FourVector::LorentzVector(const exroot::GenJet &Particle) const
{
    Print(Severity::Debug, "Lorentz Vector", "GenJet");
    return LorentzVectorByMass(Particle);
}

TLorentzVector FourVector::LorentzVector(const exroot::GenParticle &Particle) const
{
    Print(Severity::Debug, "Lorentz Vector", "GenParticle");
    return LorentzVectorByEnergy(Particle);
}

TLorentzVector FourVector::LorentzVector(const exroot::Jet &Particle) const
{
    Print(Severity::Debug, "Lorentz Vector", "Jet");
    return LorentzVectorByMass(Particle);
}

TLorentzVector FourVector::LorentzVector(const exroot::LHEFParticle &Particle) const
{
    Print(Severity::Debug, "Lorentz Vector", "LHEFParticle");
    return LorentzVectorByM(Particle);
}

TLorentzVector FourVector::LorentzVector(const exroot::Muon &Particle) const
{
    Print(Severity::Debug, "Lorentz Vector", "Muon");
    return LorentzVectorByMass(Particle, Mass(Id::Muon));
}

TLorentzVector FourVector::LorentzVector(const exroot::Photon &Particle) const
{
    Print(Severity::Debug, "Lorentz Vector", "Photon");
    return LorentzVectorByMass(Particle, Mass(Id::Photon));
}

TLorentzVector FourVector::LorentzVector(const exroot::Tau &Particle) const
{
    Print(Severity::Debug, "Lorentz Vector", "Tau");
    return LorentzVectorByMass(Particle, Mass(Id::Tau));
}

fastjet::PseudoJet FourVector::PseudoJet(const exroot::Electron &Particle) const
{
    Print(Severity::Debug, "Pseudo Jet", "Electron");
    return analysis::PseudoJet(LorentzVectorByMass(Particle, Mass(Id::Electron)));
}

fastjet::PseudoJet FourVector::PseudoJet(const exroot::GenJet &Particle) const
{
    Print(Severity::Debug, "Pseudo Jet", "GenJet");
    return analysis::PseudoJet(LorentzVectorByMass(Particle));
}

fastjet::PseudoJet FourVector::PseudoJet(const exroot::GenParticle &Particle) const
{
    Print(Severity::Debug, "Pseudo Jet", "GenParticle");
    return analysis::PseudoJet(LorentzVectorByEnergy(Particle));
}

fastjet::PseudoJet FourVector::PseudoJet(const exroot::Jet &Particle) const
{
    Print(Severity::Debug, "Pseudo Jet", "Jet");
    return analysis::PseudoJet(LorentzVectorByMass(Particle));
}

fastjet::PseudoJet FourVector::PseudoJet(const exroot::LHEFParticle &Particle) const
{
    Print(Severity::Debug, "Pseudo Jet", "LHEFParticle");
    return analysis::PseudoJet(LorentzVectorByM(Particle));
}

fastjet::PseudoJet FourVector::PseudoJet(const exroot::Muon &Particle) const
{
    Print(Severity::Debug, "Pseudo Jet", "Muon");
    return analysis::PseudoJet(LorentzVectorByMass(Particle, Mass(Id::Muon)));
}

fastjet::PseudoJet FourVector::PseudoJet(const exroot::Photon &Particle) const
{
    Print(Severity::Debug, "Pseudo Jet", "Photon");
    return analysis::PseudoJet(LorentzVectorByMass(Particle, 0));
}

fastjet::PseudoJet FourVector::PseudoJet(const exroot::Tau &Particle) const
{
    Print(Severity::Debug, "Pseudo Jet", "Tau");
    return analysis::PseudoJet(LorentzVectorByMass(Particle, Mass(Id::Tau)));
}

Family FourVector::BranchFamily(const TObject &object)
{
    Print(Severity::Information, "Mother Id", clones_arrays().ParticleSum());
    Family family;
    if (object.IsA() != ::delphes::GenParticle::Class()/* || Object == 0*/) {
        Print(Severity::Error, "Object is", object.ClassName());
        return family;
    }
    const int Position = clones_arrays().ParticleClonesArray().IndexOf(&object);
    if (Position == EmptyPosition) return family;
    family = BranchFamily(family, Position);
    if (family.mother_1().Id == to_int(Id::Empty)) family = Family(family.particle().Position, Id::Isr, family.mother_1().Position, Id::Isr);
//       Print(Severity::Error, "Truth Level Tagging Failed");
    for (auto & Node : topology_) if (Node.Marker()) Node = family;
    //
    Print(Severity::Debug, "Branch Family", Name(family.particle().Id), Name(family.mother_1().Id));
    if (family.particle().Id == to_int(Id::Empty) || family.mother_1().Id == to_int(Id::Empty)) Print(Severity::Error, "Branch Family", Name(family.particle().Id), Name(family.mother_1().Id));
    return family;
}

Family FourVector::BranchFamily(Family &family, int Position)
{
    Print(Severity::Information, "Branch Family ", Name(family.particle().Id), Position);
    if (
        jet_tag().HeavyParticles.find(static_cast<Id>(std::abs(topology_.at(Position).mother_1().Id))) != end(jet_tag().HeavyParticles) ||
        jet_tag().HeavyParticles.find(static_cast<Id>(std::abs(topology_.at(Position).particle().Id))) != end(jet_tag().HeavyParticles) ||
        topology_.at(Position).particle().Id == to_int(Id::Isr)
    ) {
        return topology_.at(Position);
    }
    while (
        Position != EmptyPosition &&
        jet_tag().HeavyParticles.find(static_cast<Id>(std::abs(family.mother_1().Id))) == end(jet_tag().HeavyParticles) &&
        jet_tag().HeavyParticles.find(static_cast<Id>(std::abs(family.particle().Id))) == end(jet_tag().HeavyParticles)
    ) {
        Print(Severity::Debug, "Topology", Position, Name(topology_.at(Position).particle().Id), Name(topology_.at(Position).mother_1().Id));
        if (
            jet_tag().HeavyParticles.find(static_cast<Id>(std::abs(topology_.at(Position).mother_1().Id))) != end(jet_tag().HeavyParticles) ||
            jet_tag().HeavyParticles.find(static_cast<Id>(std::abs(topology_.at(Position).particle().Id))) != end(jet_tag().HeavyParticles) ||
            topology_.at(Position).particle().Id == to_int(Id::Isr)
        ) {
            return topology_.at(Position);
        }
        if (topology_.at(Position).mother_1().Id != to_int(Id::Empty) && topology_.at(Position).particle().Id != to_int(Id::Empty)
                && topology_.at(Position).Marker() == 0
           ) {
            return topology_.at(Position);
        }
        topology_.at(Position).SetMarker();
//         if (Position < 3) return Family(Position, Id::Isr, EmptyPosition, Id::Isr);
        ::delphes::GenParticle &particle = static_cast<::delphes::GenParticle &>(clones_arrays().Particle(Position));
//         const int Status = ParticleClone.Status;
        int M1Id = to_int(Id::Empty);
        int Mother1Status = to_int(Status::None);
        TLorentzVector MotherVector;
        if (particle.M1 > 0) {
            ::delphes::GenParticle &Mother1Clone = static_cast<::delphes::GenParticle &>(clones_arrays().Particle(particle.M1));
            M1Id = Mother1Clone.PID;
            MotherVector = Mother1Clone.P4();
            Mother1Status = Mother1Clone.Status;
        }
        Family NodeFamily(particle.P4(), MotherVector, Position, particle.PID, particle.M1, M1Id);
        if (Mother1Status == to_int(Status::Generator))
            family = jet_tag().BranchFamily(NodeFamily, family);
        Print(Severity::Detailed, "Branch Id", Name(M1Id), Name(family.mother_1().Id));
        if (jet_tag().HeavyParticles.find(static_cast<Id>(std::abs(family.mother_1().Id))) != end(jet_tag().HeavyParticles)) return family;
        if (jet_tag().HeavyParticles.find(static_cast<Id>(std::abs(family.particle().Id))) != end(jet_tag().HeavyParticles)) return family;
        if (particle.M2 != EmptyPosition && particle.M2 != particle.M1) {
            if (particle.PID == to_int(Id::String)) {
                if (particle.M1 < particle.M2) {
                    Print(Severity::Debug, "String", Position, particle.M1, particle.M2);
                    JetInfo jet_info;
//                     for (int Counter = ParticleClone.M2; Counter >= ParticleClone.M1; --Counter) {
                    for (int Counter = particle.M1; Counter <= particle.M2; ++Counter) {
//                         BranchFamily = BranchFamily(BranchFamily, Counter);
                        Family NewFamily = BranchFamily(family, Counter);
                        jet_info.AddFamily(NewFamily, NewFamily.Pt());
                        Print(Severity::Debug, "StringPart", Counter, Name(family.particle().Id));
//                         if (std::abs(BranchFamily.particle().Id) == Id::Isr) return BranchFamily;
                    }
                    jet_info.PrintAllFamInfos(Severity::Debug);
                    if (jet_info.FamilyFractions().size() > 1) {
                        for (int Counter = particle.M1; Counter <= particle.M2; ++Counter) {
                            topology_.at(Counter).UnSetMarker();
                        }
                        Print(Severity::Debug, "To many String fractions");
                    };
                    family = jet_info.MaximalFamily();
                } else {
                    Print(Severity::Error, "Strange Particle String");
                }
                if (jet_tag().HeavyParticles.find(static_cast<Id>(std::abs(family.mother_1().Id))) != end(jet_tag().HeavyParticles)) return family;
                if (jet_tag().HeavyParticles.find(static_cast<Id>(std::abs(family.particle().Id))) != end(jet_tag().HeavyParticles)) return family;
            } else {
                Print(Severity::Debug, "Not a String", Position, particle.M1, particle.M2);
            }
        }
        Position = particle.M1;
        Print(Severity::Detailed, "Mother 1 Position", Position);
    }
    return family;
}

void FourVector::PrintTruthLevel(const analysis::Severity severity) const
{
    if (severity <= debug_level_) {
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

std::string FourVector::PrintParticle(const int Position) const
{
    if (Position != -1) return Name(static_cast<::delphes::GenParticle &>(clones_arrays().Particle(Position)).PID);
    else return " ";
}

}
