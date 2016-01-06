/**
 * Copyright (C) 2015 Jan Hajer
 */
#pragma once

#include <iomanip>
#include <iostream>

#include "delphes/DelphesForward.hh"
#include "Flag.hh"
#include "TreeReader.hh"

namespace boca
{

enum class Status
{
    none = 0,
    stable = 1,
    unstable = 2,
    generator = 3
};


/**
 * @brief flags defining to which level of detail jets should be analyzed
 *
 */
enum class JetDetail
{
    plain = 1 << 0,
    structure = 1 << 1,
    isolation = 1 << 2,
};

template<>
struct Flag<JetDetail> {
    static const bool enable = true;
};

enum class Severity
{
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
class FourVector
{

public:

  FourVector(boca::TreeReader const& tree_reader);

protected:

    void PrintTruthLevel(Severity severity) const;

    boca::TreeReader const& TreeReader() const;

private:

    std::string PrintParticle(int position) const;

    void PrintCells(::delphes::GenParticle const& particle) const;

    const boca::TreeReader* tree_reader_;

};

}
