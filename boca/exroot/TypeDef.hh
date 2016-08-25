/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#pragma once

/**
 * @ingroup ExRoot
 * @brief <a href="https://cp3.irmp.ucl.ac.be/projects/ExRootAnalysis/wiki/UserManual">ExRoot</a>
 *
 * ExRootAnalysis is a package designed to simplify ROOT tree production and analysis.
 */
namespace exroot
{
using LHEFEvent = ::TRootLHEFEvent;
using LHEFParticle = ::TRootLHEFParticle;
using GenEvent = ::TRootGenEvent;
using GenParticle = ::TRootGenParticle;
using GenJet = ::TRootGenJet;
using Event = ::TRootEvent;
using MissingET = ::TRootMissingET;
using Photon = ::TRootPhoton;
using Electron = ::TRootElectron;
using Muon = ::TRootMuon;
using Tau = ::TRootTau;
using Jet = ::TRootJet;
}
