/**
 * Copyright (C) 2015 Jan Hajer
 */
#pragma once

#include "PseudoJet.hh"
// #include "fastjet/JetDefinition.hh"
// #include "fastjet/PseudoJetStructureBase.hh"
// #include "fastjet/CompositeJetStructure.hh"
#include "JetInfo.hh"
#include "InfoRecombiner.hh"

namespace boca
{

class Jet : public PseudoJet
{

public:

    using boca::PseudoJet::PseudoJet;

    Jet();

    Jet(TLorentzVector const& vector, ::delphes::Jet const& jet);

    Jet(TLorentzVector const& vector, Constituent const& constituent);

    Jet(fastjet::PseudoJet const& pseudo_jet, JetInfo const& jet_info);

    Jet(double const Momentum[4]) : PseudoJet(Momentum[1], Momentum[2], Momentum[3], Momentum[0]){}

    JetInfo const& Info() const;

    JetInfo& Info();

    void SetInfo(JetInfo const& user_info);

private:

    JetInfo jet_info_;

};

using Lepton  = Jet;

std::vector<Jet> JetVector(std::vector<fastjet::PseudoJet> const& pseudo_jets);

std::vector<fastjet::PseudoJet> PseudoJetVector(std::vector<Jet> const& jets);

Jet Join(std::vector<Jet> const& jets);

Jet operator+ (const Jet& jet1, const Jet& jet2);

//----------------------------------------------------------------------
// return difference of two pseudojets
Jet operator- (const Jet& jet1, const Jet& jet2);

//----------------------------------------------------------------------
// return the product, coeff * jet
Jet operator* (double coeff, const Jet& jet);

//----------------------------------------------------------------------
// return the product, coeff * jet
Jet operator* (const Jet& jet, double coeff);

//----------------------------------------------------------------------
// return the ratio, jet / coeff
Jet operator/ (const Jet& jet, double coeff);

/*

//-------------------------------------------------------------------------------
// helper functions to build a jet made of pieces
//
// This is the extended version with support for a user-defined
// recombination-scheme
// -------------------------------------------------------------------------------

// build a "CompositeJet" from the vector of its pieces
//
// the user passes the reciombination scheme used to "sum" the pieces.
Jet join(std::vector<Jet> const& pieces, fastjet::JetDefinition::Recombiner const& recombiner)
{
    // compute the total momentum
    //--------------------------------------------------
    Jet result;  // automatically initialised to 0
    if (pieces.size() > 0) {
        result = pieces[0];
        for (unsigned int i = 1; i < pieces.size(); i++) recombiner.plus_equal(result, pieces[i]);
    }

    // attach a CompositeJetStructure to the result
    //--------------------------------------------------
    fastjet::CompositeJetStructure* cj_struct = new fastjet::CompositeJetStructure(pieces, &recombiner);

    result.set_structure_shared_ptr(fastjet::SharedPtr<fastjet::PseudoJetStructureBase>(cj_struct));

    return result;
}

// build a "CompositeJet" from a single Jet
Jet join(Jet const& j1, fastjet::JetDefinition::Recombiner const& recombiner)
{
    return join(std::vector<Jet>(1, j1), recombiner);
}

// build a "CompositeJet" from two Jet
Jet join(Jet const& j1, Jet const& j2, fastjet::JetDefinition::Recombiner const& recombiner)
{
    std::vector<Jet> pieces;
    pieces.push_back(j1);
    pieces.push_back(j2);
    return join(pieces, recombiner);
}

// build a "CompositeJet" from 3 Jet
Jet join(Jet const& j1, Jet const& j2, Jet const& j3, fastjet::JetDefinition::Recombiner const& recombiner)
{
    std::vector<Jet> pieces;
    pieces.push_back(j1);
    pieces.push_back(j2);
    pieces.push_back(j3);
    return join(pieces, recombiner);
}

// build a "CompositeJet" from 4 Jet
Jet join(Jet const& j1, Jet const& j2, Jet const& j3, Jet const& j4, fastjet::JetDefinition::Recombiner const& recombiner)
{
    std::vector<Jet> pieces;
    pieces.push_back(j1);
    pieces.push_back(j2);
    pieces.push_back(j3);
    pieces.push_back(j4);
    return join(pieces, recombiner);
}*/


}
