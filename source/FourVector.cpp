/**
 * Copyright (C) 2015 Jan Hajer
 */
#include "FourVector.hh"

#include "TClonesArray.h"
#include "delphes/Delphes.hh"
#include "exroot/ExRootAnalysis.hh"
#include "Types.hh"
#include "JetInfoFamily.hh"
#include "Debug.hh"

namespace boca
{

std::string Name(JetDetail jet_detail)
{
    std::string name;
    FlagSwitch(jet_detail, [&](JetDetail jet_detail) {
        switch (jet_detail) {
        case JetDetail::plain:
            name += "Plain";
            break;
        case JetDetail::tagging:
            name += "Tagging";
            break;
        case JetDetail::isolation:
            name += "Isolation";
            break;
        case JetDetail::structure:
            name += "Structure";
            break;
        default :
            name += "";
        }
    });
    return name;
}

FourVector::FourVector() :
    check_four_vectors_(1),
    check_value_(0.00001),
    mass_check_value_(1)
{
    Info0;
}

void FourVector::NewEvent(TreeReader const& tree_reader)
{
//     std::vector<Family>topology_;
    tree_reader_ = &tree_reader;
//     topology_.assign(tree_reader.ParticleSum(), Family(to_int(Id::empty)));
//     Info(topology_.size());
}

LorentzVector FourVector::LorentzVector(const exroot::Electron& Particle) const
{
    Debug0;
    return LorentzVectorByMass(Particle, MassOf(Id::electron));
}

LorentzVector FourVector::LorentzVector(const exroot::GenJet& Particle) const
{
    Debug0;
    return LorentzVectorByMass(Particle);
}

LorentzVector FourVector::LorentzVector(const exroot::GenParticle& Particle) const
{
    Debug0;
    return LorentzVectorByEnergy(Particle);
}

LorentzVector FourVector::LorentzVector(const exroot::Jet& Particle) const
{
    Debug0;
    return LorentzVectorByMass(Particle);
}

LorentzVector FourVector::LorentzVector(const exroot::LHEFParticle& Particle) const
{
    Debug0;
    return LorentzVectorByM(Particle);
}

LorentzVector FourVector::LorentzVector(const exroot::Muon& Particle) const
{
    Debug0;
    return LorentzVectorByMass(Particle, MassOf(Id::muon));
}

LorentzVector FourVector::LorentzVector(const exroot::Photon& Particle) const
{
    Debug0;
    return LorentzVectorByMass(Particle, MassOf(Id::photon));
}

LorentzVector FourVector::LorentzVector(const exroot::Tau& Particle) const
{
    Debug0;
    return LorentzVectorByMass(Particle, MassOf(Id::tau));
}

fastjet::PseudoJet FourVector::PseudoJet(const exroot::Electron& Particle) const
{
    Debug0;
    return boca::PseudoJet(LorentzVectorByMass(Particle, MassOf(Id::electron)));
}

fastjet::PseudoJet FourVector::PseudoJet(const exroot::GenJet& Particle) const
{
    Debug0;
    return boca::PseudoJet(LorentzVectorByMass(Particle));
}

fastjet::PseudoJet FourVector::PseudoJet(const exroot::GenParticle& Particle) const
{
    Debug0;
    return boca::PseudoJet(LorentzVectorByEnergy(Particle));
}

fastjet::PseudoJet FourVector::PseudoJet(const exroot::Jet& Particle) const
{
    Debug0;
    return boca::PseudoJet(LorentzVectorByMass(Particle));
}

fastjet::PseudoJet FourVector::PseudoJet(const exroot::LHEFParticle& Particle) const
{
    Debug0;
    return boca::PseudoJet(LorentzVectorByM(Particle));
}

fastjet::PseudoJet FourVector::PseudoJet(const exroot::Muon& Particle) const
{
    Debug0;
    return boca::PseudoJet(LorentzVectorByMass(Particle, MassOf(Id::muon)));
}

fastjet::PseudoJet FourVector::PseudoJet(const exroot::Photon& Particle) const
{
    Debug0;
    return boca::PseudoJet(LorentzVectorByMass(Particle, 0));
}

fastjet::PseudoJet FourVector::PseudoJet(const exroot::Tau& Particle) const
{
    Debug0;
    return boca::PseudoJet(LorentzVectorByMass(Particle, MassOf(Id::tau)));
}

// Family FourVector::BranchFamily(TObject const& object) const
// {
// //     Error("Code is disabled", tree_reader().ParticleSum());
//     std::vector<Family>topology_;
//     Family family;
//     if (object.IsA() != ::delphes::GenParticle::Class()/* || Object == 0*/) {
//         Error("Object is", object.ClassName());
//         return family;
//     }
//     int Position = tree_reader().ParticleClonesArray().IndexOf(&object);
//     if (Position == EmptyPosition)
//         return family;
//     family = BranchFamily(family, Position);
//     if (family.Mother().Id() == to_int(Id::empty))
//       family = Family(family.Particle().Position(), to_int(Id::isr), family.Mother().Position(), to_int(Id::isr), to_int(Id::isr));
// //       Error("Truth Level Tagging Failed");
//     for (auto & node : topology_) if (node.Marker())
//             node = family;
//     //
//     Debug("Branch Family", Name(family.Particle().Id()), Name(family.Mother().Id()));
//     if (family.Particle().Id() == to_int(Id::empty) || family.Mother().Id() == to_int(Id::empty))
//         Error(Name(family.Particle().Id()), Name(family.Mother().Id()));
//     return family;
// }
//
// Family FourVector::BranchFamily(Family& family, int Position) const
// {
//     std::vector<Family>topology_;
//     Info("Code is disabled", Name(family.Particle().Id()), Position);
//     if (
//         jet_tag().HeavyParticles.find(static_cast<Id>(std::abs(topology_.at(Position).Mother().Id()))) != end(jet_tag().HeavyParticles) ||
//         jet_tag().HeavyParticles.find(static_cast<Id>(std::abs(topology_.at(Position).Particle().Id()))) != end(jet_tag().HeavyParticles) ||
//         topology_.at(Position).Particle().Id() == to_int(Id::isr)
//     )
//         return topology_.at(Position);
//     while (
//         Position != EmptyPosition &&
//         jet_tag().HeavyParticles.find(static_cast<Id>(std::abs(family.Mother().Id()))) == end(jet_tag().HeavyParticles) &&
//         jet_tag().HeavyParticles.find(static_cast<Id>(std::abs(family.Particle().Id()))) == end(jet_tag().HeavyParticles)
//     ) {
//         Debug("Topology", Position, Name(topology_.at(Position).Particle().Id()), Name(topology_.at(Position).Mother().Id()));
//         if (
//             jet_tag().HeavyParticles.find(static_cast<Id>(std::abs(topology_.at(Position).Mother().Id()))) != end(jet_tag().HeavyParticles) ||
//             jet_tag().HeavyParticles.find(static_cast<Id>(std::abs(topology_.at(Position).Particle().Id()))) != end(jet_tag().HeavyParticles) ||
//             topology_.at(Position).Particle().Id() == to_int(Id::isr)
//         )
//             return topology_.at(Position);
//         if (topology_.at(Position).Mother().Id() != to_int(Id::empty) && topology_.at(Position).Particle().Id() != to_int(Id::empty)
//                 && topology_.at(Position).Marker() == 0
//            )
//             return topology_.at(Position);
//         topology_.at(Position).SetMarker();
// //         if (Position < 3) return Family(Position, Id::isr, EmptyPosition, Id::isr);
//         ::delphes::GenParticle& particle = static_cast<::delphes::GenParticle&>(tree_reader().Particle(Position));
// //         int Status = ParticleClone.Status;
//         int M1Id = to_int(Id::empty);
//         int Mother1Status = to_int(Status::none);
//         boca::LorentzVector MotherVector;
//         if (particle.M1 > 0) {
//             ::delphes::GenParticle& Mother1Clone = static_cast<::delphes::GenParticle&>(tree_reader().Particle(particle.M1));
//             M1Id = Mother1Clone.PID;
//             MotherVector = Mother1Clone.P4();
//             Mother1Status = Mother1Clone.Status;
//         }
//         Family NodeFamily(particle.P4(), MotherVector, Position, particle.PID, particle.M1, M1Id);
//         if (Mother1Status == to_int(Status::generator))
//             family = jet_tag().BranchFamily(NodeFamily, family);
//         Detail("Branch Id", Name(M1Id), Name(family.Mother().Id()));
//         if (jet_tag().HeavyParticles.find(static_cast<Id>(std::abs(family.Mother().Id()))) != end(jet_tag().HeavyParticles))
//             return family;
//         if (jet_tag().HeavyParticles.find(static_cast<Id>(std::abs(family.Particle().Id()))) != end(jet_tag().HeavyParticles))
//             return family;
//         if (particle.M2 != EmptyPosition && particle.M2 != particle.M1) {
//             if (particle.PID == to_int(Id::string)) {
//                 if (particle.M1 < particle.M2) {
//                     Debug("String", Position, particle.M1, particle.M2);
//                     JetInfoFamily jet_info;
//                     //                     for (auto const& Counter = ParticleClone.M2; Counter >= ParticleClone.M1; --Counter) {
//                     for (auto const& counter : Range(particle.M1,particle.M2)) {
// //                         BranchFamily = BranchFamily(BranchFamily, Counter);
//                         Family NewFamily = BranchFamily(family, counter);
//                         jet_info.AddFamily(NewFamily, NewFamily.Pt());
//                         Debug("StringPart", counter, Name(family.Particle().Id()));
// //                         if (std::abs(BranchFamily.Particle().Id()) == Id::isr) return BranchFamily;
//                     }
//                     jet_info.PrintAllFamInfos(Severity::debug);
//                     if (jet_info.FamilyFractions().size() > 1) {
//                       for (auto const& counter : Range(particle.M1,particle.M2)) topology_.at(counter).UnSetMarker();
//                         Debug("To many String fractions");
//                     };
//                     family = jet_info.MaximalFamily();
//                 } else
//                     Error("Strange Particle String");
//                 if (jet_tag().HeavyParticles.find(static_cast<Id>(std::abs(family.Mother().Id()))) != end(jet_tag().HeavyParticles))
//                     return family;
//                 if (jet_tag().HeavyParticles.find(static_cast<Id>(std::abs(family.Particle().Id()))) != end(jet_tag().HeavyParticles))
//                     return family;
//             } else
//                 Debug("Not a String", Position, particle.M1, particle.M2);
//         }
//         Position = particle.M1;
//         Detail("Mother 1 Position", Position);
//     }
//     return family;
// }

void FourVector::PrintTruthLevel(const boca::Severity severity) const
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
        std::cout << "\n";
        //         for (auto const& Position : HRange(tree_reader().GetParticleSum())) {
        for (auto const& Particle : tree_reader().Objects<::delphes::GenParticle>(Branch::particle)) {
//             ::delphes::GenParticle& Particle = static_cast<::delphes::GenParticle&>(tree_reader().Particle(Position));
//             PrintCell(Position);
//             PrintCell(Name(topology_.at(Position).Particle().Id()));
//             PrintCell(topology_.at(Position).Particle().Position());
//             PrintCell(Name(topology_.at(Position).Mother().Id()));
//             PrintCell(topology_.at(Position).Mother().Position());
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
            std::cout << "\n";
        }
    }
}

std::string FourVector::PrintParticle(int position) const
{
  if (position != -1) return Name(tree_reader().Objects<::delphes::GenParticle>(Branch::particle).At(position).PID);
    else return " ";
}

}


