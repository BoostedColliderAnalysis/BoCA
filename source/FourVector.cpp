/**
 * Copyright (C) 2015 Jan Hajer
 */
#include "delphes/Delphes.hh"
#include "physics/Particles.hh"

#include "FourVector.hh"
#include "Types.hh"
#include "Family.hh"
#include "Debug.hh"

namespace boca
{

namespace
{

template<typename Data>
void PrintCell(Data data)
{
    std::cout << std::right << std::setw(9) << std::setfill(' ') << data;
}

}

std::string Name(JetDetail jet_detail)
{
    std::string name;
    FlagSwitch(jet_detail, [&](JetDetail jet_detail) {
        switch (jet_detail) {
        case JetDetail::plain:
            name += "Plain";
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
        //         for (auto const& Position : HRange(TreeReader().GetParticleSum())) {
        for (auto const & particle : TreeReader().Objects<::delphes::GenParticle>(Branch::particle)) PrintCells(particle);
    }
}

boca::TreeReader const& FourVector::TreeReader() const
{
    return *tree_reader_;
}

std::string FourVector::PrintParticle(int position) const
{
    if (position == -1) return " ";
    return Name(TreeReader().Objects<::delphes::GenParticle>(Branch::particle).At(position).PID);
}

void FourVector::PrintCells(const delphes::GenParticle& particle) const
{
    PrintCell(particle.Status);
    PrintCell(Name(particle.PID));
    PrintCell(particle.M1);
    PrintCell(PrintParticle(particle.M1));
    PrintCell(particle.M2);
    PrintCell(PrintParticle(particle.M2));
    PrintCell(particle.D1);
    PrintCell(PrintParticle(particle.D1));
    PrintCell(particle.D2);
    PrintCell(PrintParticle(particle.D2));
    PrintCell(particle.E);
    PrintCell(particle.Px);
    PrintCell(particle.Py);
    PrintCell(particle.Pz);
    std::cout << "\n";
}

FourVector::FourVector(boca::TreeReader const& tree_reader)
{
    tree_reader_ = &tree_reader;
}

}


