/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#include "delphes/Classes.hh"
#include "delphes/Partons.hh"

#include "physics/Particles.hh"
#include "generic/Types.hh"
#include "generic/DEBUG.hh"

namespace boca
{

namespace delphes
{

namespace
{

auto Family(TTreeReaderArray<::delphes::GenParticle>& gen_particles, boca::Family& family, Relative relative, int position)
{
    if (relative == Relative::none) {
        return family;
    }
    if (position == Member::EmptyPosition()) {
        return family;
    }
    family.SetMember( {gen_particles.At(position).PID, position}, relative);
    Family(gen_particles, family, Mother(relative), gen_particles.At(position).M1);
    Family(gen_particles, family, StepMother(relative), gen_particles.At(position).M2);
    return family;
}

auto Family(TTreeReaderArray<::delphes::GenParticle>& particles, Relative relative, int position)
{
    boca::Family family;
    return Family(particles, family, relative, position);
}

template<typename Data>
void PrintCell(Data data)
{
    std::cout << std::right << std::setw(9) << std::setfill(' ') << data;
}

void PrintCells(Particle const& particle)
{
    //     PrintCell(particle.Status);
    PrintCell(particle.Info().Family().Member(Relative::particle).Name());
    PrintCell(particle.Info().Family().Member(Relative::mother).Name());
    PrintCell(particle.Info().Family().Member(Relative::step_mother).Name());
    PrintCell(particle.Info().Family().Member(Relative::particle).Position());
    PrintCell(particle.Info().Family().Member(Relative::mother).Position());
    PrintCell(particle.Info().Family().Member(Relative::step_mother).Position());
    //     PrintCell(particle.M1);
    //     PrintCell(PrintParticle(particle.M1));
    //     PrintCell(particle.M2);
    //     PrintCell(PrintParticle(particle.M2));
    //     PrintCell(particle.D1);
    //     PrintCell(PrintParticle(particle.D1));
    //     PrintCell(particle.D2);
    //     PrintCell(PrintParticle(particle.D2));
    //     PrintCell(particle.E);
    //     PrintCell(particle.Px);
    //     PrintCell(particle.Py);
    //     PrintCell(particle.Pz);
    std::cout << "\n";
}

}

Partons::Partons(boca::TreeReader const& tree_reader) :
    boca::Partons(tree_reader) {}

std::vector<Particle> Partons::Particles() const
{
    return Particles(Status::stable);
}

std::vector<Particle> Partons::GenParticles() const
{
    return Particles(Status::generator);
}

std::vector<Particle> Partons::Particles(Status min_status) const
{
    INFO0;
    std::vector<Particle> particles;
    auto& gen_particles = TreeReader().Array<::delphes::GenParticle>(Branch::particle);
    auto position = 0;
    for (auto const & particle : gen_particles) {
        if (particle.Status < to_int(min_status)) {
            break;
        }
        particles.emplace_back(Particle(particle.P4(), Family(gen_particles, Relative::particle, position)));
        ++position;
#ifdef DEBUGGING
        PrintCells(particles.back());
#endif
    }
    return particles;
}

}

}
