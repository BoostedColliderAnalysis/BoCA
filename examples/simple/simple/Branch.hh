/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#pragma once
// include Branch base
#include "boca/branch/Bdt.hh"
// include Observables
#include "boca/Observables.hh"
#include "simple/Observables.hh"

namespace simple
{

// define the branch for saving the root file
// inherits from the BDT branch base class
class Branch :  public boca::branch::Bdt
{

public:

    //  Constructor
    Branch();

    // All observables must be saved as floats
    float jet_number;
    float bottom_number;
    float missing_et;
    float scalar_ht;
    float jet_1_pt;
    float jet_2_pt;
    float jet_3_pt;
    float jet_4_pt;

    // define how the branches are going to be filled from the Observables
    void Fill(Observables const &observables);

    // return the Variables for TMVA
    boca::Observables Variables() override;

private:
    ClassDef(Branch, 1)
};

}
