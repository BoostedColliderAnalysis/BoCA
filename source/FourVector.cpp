#include "FourVector.hh"

#include "TClonesArray.h"
#include "Predicate.hh"
#include "Debug.hh"
#include "delphes/Delphes.hh"
#include "JetInfo.hh"

namespace analysis {

std::string Name(const analysis::JetDetail jet_detail)
{
    switch (jet_detail) {
    case JetDetail::plain:
        return  "Plain";
    case JetDetail:: tagging:
        return  "Tagging";
    case JetDetail:: isolation:
        return  "Isolation";
    case JetDetail:: structure:
        return  "Structure";
    case JetDetail:: tagging_isolation:
        return  "Tagging Isolation";
    case JetDetail:: tagging_structure:
        return  "Tagging Structure";
    }
}

FourVector::FourVector() :
    check_four_vectors_(1),
    check_value_(0.00001),
    mass_check_value_(1)
{
    Info("Constructor");
}

void FourVector::NewEvent(const ClonesArrays& clones_arrays)
{
    std::vector<Family>topology_;
    clones_arrays_ = &clones_arrays;
    topology_.assign(clones_arrays_->ParticleSum(), Family(Id::empty));
    Info("Topology", topology_.size());
}

LorentzVector FourVector::LorentzVector(const exroot::Electron& Particle) const
{
    Debug("Lorentz Vector", "Electron");
    return LorentzVectorByMass(Particle, Mass(Id::electron));
}

LorentzVector FourVector::LorentzVector(const exroot::GenJet& Particle) const
{
    Debug("Lorentz Vector", "GenJet");
    return LorentzVectorByMass(Particle);
}

LorentzVector FourVector::LorentzVector(const exroot::GenParticle& Particle) const
{
    Debug("Lorentz Vector", "GenParticle");
    return LorentzVectorByEnergy(Particle);
}

LorentzVector FourVector::LorentzVector(const exroot::Jet& Particle) const
{
    Debug("Lorentz Vector", "Jet");
    return LorentzVectorByMass(Particle);
}

LorentzVector FourVector::LorentzVector(const exroot::LHEFParticle& Particle) const
{
    Debug("Lorentz Vector", "LHEFParticle");
    return LorentzVectorByM(Particle);
}

LorentzVector FourVector::LorentzVector(const exroot::Muon& Particle) const
{
    Debug("Lorentz Vector", "Muon");
    return LorentzVectorByMass(Particle, Mass(Id::muon));
}

LorentzVector FourVector::LorentzVector(const exroot::Photon& Particle) const
{
    Debug("Lorentz Vector", "Photon");
    return LorentzVectorByMass(Particle, Mass(Id::photon));
}

LorentzVector FourVector::LorentzVector(const exroot::Tau& Particle) const
{
    Debug("Lorentz Vector", "Tau");
    return LorentzVectorByMass(Particle, Mass(Id::tau));
}

fastjet::PseudoJet FourVector::PseudoJet(const exroot::Electron& Particle) const
{
    Debug("Pseudo Jet", "Electron");
    return analysis::PseudoJet(LorentzVectorByMass(Particle, Mass(Id::electron)));
}

fastjet::PseudoJet FourVector::PseudoJet(const exroot::GenJet& Particle) const
{
    Debug("Pseudo Jet", "GenJet");
    return analysis::PseudoJet(LorentzVectorByMass(Particle));
}

fastjet::PseudoJet FourVector::PseudoJet(const exroot::GenParticle& Particle) const
{
    Debug("Pseudo Jet", "GenParticle");
    return analysis::PseudoJet(LorentzVectorByEnergy(Particle));
}

fastjet::PseudoJet FourVector::PseudoJet(const exroot::Jet& Particle) const
{
    Debug("Pseudo Jet", "Jet");
    return analysis::PseudoJet(LorentzVectorByMass(Particle));
}

fastjet::PseudoJet FourVector::PseudoJet(const exroot::LHEFParticle& Particle) const
{
    Debug("Pseudo Jet", "LHEFParticle");
    return analysis::PseudoJet(LorentzVectorByM(Particle));
}

fastjet::PseudoJet FourVector::PseudoJet(const exroot::Muon& Particle) const
{
    Debug("Pseudo Jet", "Muon");
    return analysis::PseudoJet(LorentzVectorByMass(Particle, Mass(Id::muon)));
}

fastjet::PseudoJet FourVector::PseudoJet(const exroot::Photon& Particle) const
{
    Debug("Pseudo Jet", "Photon");
    return analysis::PseudoJet(LorentzVectorByMass(Particle, 0));
}

fastjet::PseudoJet FourVector::PseudoJet(const exroot::Tau& Particle) const
{
    Debug("Pseudo Jet", "Tau");
    return analysis::PseudoJet(LorentzVectorByMass(Particle, Mass(Id::tau)));
}

Family FourVector::BranchFamily(const TObject& object) const
{
    std::vector<Family>topology_;
    Error("Code is disabled", clones_arrays().ParticleSum());
    Family family;
    if (object.IsA() != ::delphes::GenParticle::Class()/* || Object == 0*/) {
        Error("Object is", object.ClassName());
        return family;
    }
    const int Position = clones_arrays().ParticleClonesArray().IndexOf(&object);
    if (Position == EmptyPosition)
        return family;
    family = BranchFamily(family, Position);
    if (family.mother_1().id() == to_int(Id::empty))
        family = Family(family.particle().position(), Id::isr, family.mother_1().position(), Id::isr);
//       Error("Truth Level Tagging Failed");
    for (auto& node : topology_) if (node.Marker())
            node = family;
    //
    Debug("Branch Family", Name(family.particle().id()), Name(family.mother_1().id()));
    if (family.particle().id() == to_int(Id::empty) || family.mother_1().id() == to_int(Id::empty))
        Error(Name(family.particle().id()), Name(family.mother_1().id()));
    return family;
}

Family FourVector::BranchFamily(Family& family, int Position) const
{
    std::vector<Family>topology_;
    Info("Code is disabled", Name(family.particle().id()), Position);
    if (
        jet_tag().HeavyParticles.find(static_cast<Id>(std::abs(topology_.at(Position).mother_1().id()))) != end(jet_tag().HeavyParticles) ||
        jet_tag().HeavyParticles.find(static_cast<Id>(std::abs(topology_.at(Position).particle().id()))) != end(jet_tag().HeavyParticles) ||
        topology_.at(Position).particle().id() == to_int(Id::isr)
    )
        return topology_.at(Position);
    while (
        Position != EmptyPosition &&
        jet_tag().HeavyParticles.find(static_cast<Id>(std::abs(family.mother_1().id()))) == end(jet_tag().HeavyParticles) &&
        jet_tag().HeavyParticles.find(static_cast<Id>(std::abs(family.particle().id()))) == end(jet_tag().HeavyParticles)
    ) {
        Debug("Topology", Position, Name(topology_.at(Position).particle().id()), Name(topology_.at(Position).mother_1().id()));
        if (
            jet_tag().HeavyParticles.find(static_cast<Id>(std::abs(topology_.at(Position).mother_1().id()))) != end(jet_tag().HeavyParticles) ||
            jet_tag().HeavyParticles.find(static_cast<Id>(std::abs(topology_.at(Position).particle().id()))) != end(jet_tag().HeavyParticles) ||
            topology_.at(Position).particle().id() == to_int(Id::isr)
        )
            return topology_.at(Position);
        if (topology_.at(Position).mother_1().id() != to_int(Id::empty) && topology_.at(Position).particle().id() != to_int(Id::empty)
                && topology_.at(Position).Marker() == 0
           )
            return topology_.at(Position);
        topology_.at(Position).SetMarker();
//         if (Position < 3) return Family(Position, Id::isr, EmptyPosition, Id::isr);
        ::delphes::GenParticle& particle = static_cast<::delphes::GenParticle&>(clones_arrays().Particle(Position));
//         const int Status = ParticleClone.Status;
        int M1Id = to_int(Id::empty);
        int Mother1Status = to_int(Status::none);
        analysis::LorentzVector MotherVector;
        if (particle.M1 > 0) {
            ::delphes::GenParticle& Mother1Clone = static_cast<::delphes::GenParticle&>(clones_arrays().Particle(particle.M1));
            M1Id = Mother1Clone.PID;
            MotherVector = Mother1Clone.P4();
            Mother1Status = Mother1Clone.Status;
        }
        Family NodeFamily(particle.P4(), MotherVector, Position, particle.PID, particle.M1, M1Id);
        if (Mother1Status == to_int(Status::generator))
            family = jet_tag().BranchFamily(NodeFamily, family);
        Detail("Branch Id", Name(M1Id), Name(family.mother_1().id()));
        if (jet_tag().HeavyParticles.find(static_cast<Id>(std::abs(family.mother_1().id()))) != end(jet_tag().HeavyParticles))
            return family;
        if (jet_tag().HeavyParticles.find(static_cast<Id>(std::abs(family.particle().id()))) != end(jet_tag().HeavyParticles))
            return family;
        if (particle.M2 != EmptyPosition && particle.M2 != particle.M1) {
            if (particle.PID == to_int(Id::string)) {
                if (particle.M1 < particle.M2) {
                    Debug("String", Position, particle.M1, particle.M2);
                    JetInfo jet_info;
//                     for (int Counter = ParticleClone.M2; Counter >= ParticleClone.M1; --Counter) {
                    for (int Counter = particle.M1; Counter <= particle.M2; ++Counter) {
//                         BranchFamily = BranchFamily(BranchFamily, Counter);
                        Family NewFamily = BranchFamily(family, Counter);
                        jet_info.AddFamily(NewFamily, NewFamily.Pt());
                        Debug("StringPart", Counter, Name(family.particle().id()));
//                         if (std::abs(BranchFamily.particle().id()) == Id::isr) return BranchFamily;
                    }
                    jet_info.PrintAllFamInfos(Severity::debug);
                    if (jet_info.FamilyFractions().size() > 1) {
                        for (int Counter = particle.M1; Counter <= particle.M2; ++Counter)
                            topology_.at(Counter).UnSetMarker();
                        Debug("To many String fractions");
                    };
                    family = jet_info.MaximalFamily();
                } else
                    Error("Strange Particle String");
                if (jet_tag().HeavyParticles.find(static_cast<Id>(std::abs(family.mother_1().id()))) != end(jet_tag().HeavyParticles))
                    return family;
                if (jet_tag().HeavyParticles.find(static_cast<Id>(std::abs(family.particle().id()))) != end(jet_tag().HeavyParticles))
                    return family;
            } else
                Debug("Not a String", Position, particle.M1, particle.M2);
        }
        Position = particle.M1;
        Detail("Mother 1 Position", Position);
    }
    return family;
}

void FourVector::PrintTruthLevel(const analysis::Severity severity) const
{
    std::vector<Family>topology_;
    Error("Code is disabled");
    if (to_int(severity) <= 0) {
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
            ::delphes::GenParticle& Particle = static_cast<::delphes::GenParticle&>(clones_arrays().Particle(Position));
            PrintCell(Position);
            PrintCell(Name(topology_.at(Position).particle().id()));
            PrintCell(topology_.at(Position).particle().position());
            PrintCell(Name(topology_.at(Position).mother_1().id()));
            PrintCell(topology_.at(Position).mother_1().position());
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

std::string FourVector::PrintParticle(const int position) const
{
    if (position != -1)
        return Name(static_cast<::delphes::GenParticle&>(clones_arrays().Particle(position)).PID);
    else
        return " ";
}

}


