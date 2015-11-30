/**
 * Copyright (C) 2015 Jan Hajer
 */
#include "delphes/Delphes.hh"

#include "FourVector.hh"
#include "Types.hh"
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
        default : name += "";
        }
    });
    return name;
}

void FourVector::NewEvent(TreeReader const& tree_reader)
{
    tree_reader_ = &tree_reader;
}


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

TreeReader const& FourVector::tree_reader() const
{
    return *tree_reader_;
}

}


