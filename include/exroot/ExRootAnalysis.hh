/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#pragma once

// #include <functional>

// #include "TClonesArray.h"

// #include "ExRootAnalysis/ExRootClasses.h"
// #include "ExRootAnalysis/ExRootTreeWriter.h"
// #include "ExRootAnalysis/ExRootTreeReader.h"
// #include "ExRootAnalysis/ExRootTreeBranch.h"
// #include "ExRootAnalysis/ExRootProgressBar.h"

#include "exroot/ExRootClasses.h"
// #include "exroot/TreeWriter.h"
// #include "exroot/TreeReader.h"
// #include "exroot/TreeBranch.h"
// #include "exroot/ExRootProgressBar.h"

// #include "generic/Types.hh"

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
}

// namespace boca
// {
//
// class TreeWriter
// {
// public:
//     TreeWriter(TFile& file, std::string const& name) : tree_writer_(&file, name.c_str()) {}
//     ~TreeWriter() {
//         tree_writer_.Write();
//     }
//     ::exroot::TreeBranch& NewBranch(std::string const& name, TClass& Class) {
//         return *tree_writer_.NewBranch(name.c_str(), &Class);
//     }
//     void Fill() {
//         tree_writer_.Fill();
//         tree_writer_.Clear();
//     }
// private:
//     ::exroot::TreeWriter tree_writer_;
// };

// class TreeReader
// {
// public:
//     TreeReader(TTree& tree) : tree_reader_(&tree) {}
//     template<typename Function>
//     void Read(std::string const& name, Function const& function) {
//         TClonesArray& clones_array = *tree_reader_.UseBranch(name.c_str());
//         for (auto const & event_number : IntegerRange(tree_reader_.GetEntries())) {
//             tree_reader_.ReadEntry(event_number);
//             for (auto const & entry : IntegerRange(clones_array.GetEntriesFast())) {
//                 function(entry);
//             }
// //             tree_writer.Fill();
// //             tree_writer.Clear();
//         }
//     }
// private:
//     ::exroot::TreeReader tree_reader_;
// };

// }
