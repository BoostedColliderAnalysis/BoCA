#include "EventShape.hh"
#include "fastjet/PseudoJet.hh"

namespace analysis {

class Peg
{

public:
  Peg(const fastjet::PseudoJet& jet) {
    SetMomentum(jet);
    SetPointer();
  }

  ThePEG::Lorentz5Vector<double> Vector(double x, double y, double z, double t) {
    return ThePEG::Lorentz5Vector<double>(x, y, z, t);
  }

  ThePEG::Lorentz5Momentum Momentum(double x, double y, double z, double t) {
    return ThePEG::Lorentz5Momentum(Vector(x, y, z, t) * ThePEG::GeV);
  }

  void SetMomentum(const fastjet::PseudoJet& jet) {
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

void EventShape::SetJets(const std::vector< fastjet::PseudoJet >& jets)
{
    std::vector<ThePEG::Lorentz5Momentum> momenta;
    std::vector<ThePEG::ParticleData> particle_datas(jets.size());
    std::vector<ThePEG::PPtr> pointers;
    std::vector<ThePEG::Ptr<ThePEG::Particle>::transient_pointer> ptrs;
    for (const auto & jet : jets) {
        int i = &jet - &jets[0];
        momenta.emplace_back(ThePEG::Lorentz5Momentum(ThePEG::Lorentz5Vector<double>(jet.px(), jet.py(), jet.pz(), jet.e())* ThePEG::GeV));
        pointers.emplace_back(particle_datas.at(i).produceParticle(momenta.at(i)));
    }
    for (const auto & pointer : pointers) ptrs.emplace_back(pointer);



//       std::vector<Peg> pegs;
//       for (const auto & jet : jets) pegs.emplace_back(Peg(jet));
    //         std::vector<ThePEG::Ptr<ThePEG::Particle>::transient_pointer> ptrs;
    //         for (const auto & peg : pegs)  ptrs.emplace_back(peg.pointer);


//       EventShapes event_shapes;
    EventShapes().reset(ptrs);
    //         Error(EventShapes().aplanarity());
    //         Error(EventShapes().sphericity());

}

float EventShape::Sphericity() const
{
    return const_cast<analysis::EventShapes &>(EventShapes()).sphericity();
}
float EventShape::Aplanarity() const
{
  return const_cast<analysis::EventShapes &>(EventShapes()).aplanarity();
}

}
