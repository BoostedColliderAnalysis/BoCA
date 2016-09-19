/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#pragma once
// include the Units header
#include "boca/physics/Units.hh"
// include Branch base
#include "boca/branch/Bdt.hh"
// include Observables
#include "boca/Observables.hh"

namespace simple
{

// use the namespace for units
using namespace boca::units;

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
    template<typename Multiplet_>
    void Fill(Multiplet_ const &multiplet)
    {
        // store the BDT value in the BDT member
        boca::branch::Bdt::Fill(multiplet);
        //  store the other multiplet in their fields
        jet_number = multiplet.JetNumber();
        bottom_number = multiplet.BottomNumber();
        // note that the Branch only takes plain numbers
        missing_et = multiplet.MissingEt() / GeV;
        scalar_ht = multiplet.ScalarHt() / GeV;
        jet_1_pt = multiplet.JetPt(0) / GeV;
        jet_2_pt = multiplet.JetPt(1) / GeV;
        jet_3_pt = multiplet.JetPt(2) / GeV;
        jet_4_pt = multiplet.JetPt(3) / GeV;
    }

    // return the Variables for TMVA
    boca::Observables Variables() override;

private:
    ClassDef(Branch, 1)
};

}
