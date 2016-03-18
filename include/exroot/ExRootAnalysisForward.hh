/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#pragma once

class TRootLHEFEvent;
class TRootLHEFParticle;
class TRootGenEvent;
class TRootGenParticle;
class TRootGenJet;
class TRootEvent;
class TRootMissingET;
class TRootPhoton;
class TRootElectron;
class TRootMuon;
class TRootTau;
class TRootJet;
class ExRootTreeWriter;
class ExRootTreeBranch;
class ExRootTreeReader;
class ExRootProgressBar;

/**
 * @brief ExRoot
 *
 */
namespace exroot
{

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
