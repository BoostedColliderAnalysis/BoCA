#pragma once
#include "boca/tagger/Tagger.hh"
#include "boca/PreCuts.hh"
#include "boca/Event.hh"
#include "boca/branch/Particle.hh"
#include "boca/multiplets/Doublet.hh"

class Tagger : public boca::Tagger<boca::Doublet, boca::branch::Particle> {

public:

  int Train(boca::Event const&, boca::PreCuts const&, boca::Tag ) override {
    return 1;
  }

  std::vector<boca::Doublet> Multiplets(boca::Event const&, boca::PreCuts const&, TMVA::Reader const&) override {
    return {};
  };


  std::string Name() const override {
    return "Simple";
  }

};
