/**
 * Copyright (C) 2015 Jan Hajer
 */
#pragma once

#include <iomanip>
#include <iostream>

#include "JetTag.hh"
#include "Jet.hh"
#include "Flag.hh"
// #include "ClonesArrays.hh"
#include "TreeReader.hh"

class TRootLHEFParticle;
class TRootGenParticle;
class TRootGenJet;
class TRootMissingET;
class TRootPhoton;
class TRootElectron;
class TRootMuon;
class TRootTau;
class TRootJet;

namespace exroot {
  typedef ::TRootLHEFParticle LHEFParticle;
  typedef ::TRootGenParticle GenParticle;
  typedef ::TRootGenJet GenJet;
  typedef ::TRootMissingET MissingET;
  typedef ::TRootPhoton Photon;
  typedef ::TRootElectron Electron;
  typedef ::TRootMuon Muon;
  typedef ::TRootTau Tau;
  typedef ::TRootJet Jet;
}

namespace boca {

enum class Status {
    none = 0,
    stable = 1,
    unstable = 2,
    generator = 3
};


/**
 * @brief flags defining to which level of detail jets should be analyzed
 *
 */
enum class JetDetail {
    plain = 1 << 0,
    structure = 1 << 1,
    tagging = 1 << 2,
    isolation = 1 << 3,
};

template<>
struct Flag<JetDetail> {
  static const bool enable = true;
};

enum class Severity {
  error,
  notification,
  information,
  debug,
  detailed
};

std::string Name(JetDetail jet_detail);

/**
 * @brief converts Clones to LorentzVectors and Jets
 *
 */
class FourVector {

public:

    /**
     * @brief Constructor
     *
     */
    FourVector();

protected:

    void NewEvent(TreeReader const& tree_reader);

    template<typename Data>
    void PrintCell(Data const data) const
    {
        std::cout << std::right << std::setw(9) << std::setfill(' ') << data;
    }

    void PrintTruthLevel(Severity severity) const;

    std::string PrintParticle(int Position) const;

    TreeReader const& tree_reader() const
    {
        return *tree_reader_;
    }

    /**
     * @brief Clones Arrays
     *
     */
    const TreeReader* tree_reader_;

//     std::vector<Family> topology_;

    int source_;

    JetTag& jet_tag() const
    {
        return *jet_tag_;
    }

    void set_jet_tag(JetTag& jet_tag)
    {
        jet_tag_ = &jet_tag;
    }

    bool check_four_vectors_;

    float check_value_;

    float mass_check_value_;

private:

    JetTag* jet_tag_;

};

}
