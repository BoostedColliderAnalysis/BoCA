# pragma once

# include "ExRootAnalysis/ExRootClasses.h"
# include "ExRootAnalysis/ExRootTreeWriter.h"
# include "ExRootAnalysis/ExRootTreeReader.h"
# include "ExRootAnalysis/ExRootTreeBranch.h"
# include "ExRootAnalysis/ExRootProgressBar.h"

namespace exroot {

  typedef ::TRootLHEFEvent LHEFEvent;
  typedef ::TRootLHEFParticle LHEFParticle;
  typedef ::TRootGenEvent GenEvent;
  typedef ::TRootGenParticle GenParticle;
  typedef ::TRootGenJet GenJet;
  typedef ::TRootEvent Event;
  typedef ::TRootMissingET MissingET;
  typedef ::TRootPhoton Photon;
  typedef ::TRootElectron Electron;
  typedef ::TRootMuon Muon;
  typedef ::TRootTau Tau;
  typedef ::TRootJet Jet;
  typedef ::ExRootTreeWriter TreeWriter;
  typedef ::ExRootTreeBranch TreeBranch;
  typedef ::ExRootTreeReader TreeReader;
  typedef ::ExRootProgressBar ProgressBar;

}
