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
class TreeWriter;
class TreeBranch;
class TreeReader;
}
