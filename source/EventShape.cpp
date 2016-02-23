/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#include "ThePEG/Vectors/Lorentz5Vector.h"
#include "ThePEG/EventRecord/Particle.h"
#include "EventShape.hh"
#include "Jet.hh"
// #include "fastjet/PseudoJet.hh"

namespace boca {

class Peg
{

public:
  Peg(Jet const& jet) {
    SetMomentum(jet);
    SetPointer();
  }

  ThePEG::Lorentz5Vector<double> Vector(double x, double y, double z, double t) {
    return ThePEG::Lorentz5Vector<double>(x, y, z, t);
  }

  ThePEG::Lorentz5Momentum Momentum(double x, double y, double z, double t) {
    return ThePEG::Lorentz5Momentum(Vector(x, y, z, t) * ThePEG::GeV);
  }

  void SetMomentum(Jet const& jet) {
    momentum = Momentum(jet.px(), jet.py(), jet.pz(), jet.e());
  }

  void SetPointer() {
    pointer = particle_data.produceParticle(momentum);
    //       pointer->setMomentum(momentum);
  }

  ThePEG::Lorentz5Momentum momentum;
  ThePEG::Ptr<ThePEG::Particle>::pointer pointer;
  ThePEG::ParticleData particle_data;
};

void EventShape::SetJets(const std::vector< Jet >& jets)
{
    std::vector<ThePEG::Lorentz5Momentum> momenta;
    std::vector<ThePEG::ParticleData> particle_datas(jets.size());
    std::vector<ThePEG::PPtr> pointers;
    std::vector<ThePEG::Ptr<ThePEG::Particle>::transient_pointer> ptrs;
    for (auto const& jet : jets) {
        int index = &jet - &jets.front();
        momenta.emplace_back(ThePEG::Lorentz5Momentum(ThePEG::Lorentz5Vector<double>(jet.px(), jet.py(), jet.pz(), jet.e())* ThePEG::GeV));
        pointers.emplace_back(particle_datas.at(index).produceParticle(momenta.at(index)));
    }
    for (auto const& pointer : pointers) ptrs.emplace_back(pointer);



//       std::vector<Peg> pegs;
//       for (auto const& jet : jets) pegs.emplace_back(Peg(jet));
    //         std::vector<ThePEG::Ptr<ThePEG::Particle>::transient_pointer> ptrs;
    //         for (auto const& peg : pegs)  ptrs.emplace_back(peg.pointer);


//       EventShapes event_shapes;
//     EventShapes().reset(ptrs);
    EventShapes().Reset(jets);
    //         ERROR(EventShapes().aplanarity());
    //         ERROR(EventShapes().sphericity());

}

float EventShape::Sphericity() const
{
    return const_cast<boca::EventShapes &>(EventShapes()).Sphericity();
}

float EventShape::Aplanarity() const
{
  return const_cast<boca::EventShapes &>(EventShapes()).Aplanarity();
}

}
