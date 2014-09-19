# include "HConstants.hh"

HConstants::HConstants() :
    HiggsMass(125),
    TopMass(173.5),
    WMass(80.39),
    ElectronMass(0.000511),
    MuonMass(0.1134),
    HiggsUserIndex(1000),
    TopUserIndex(2000)
    {
        
        Print(0, "Constructor");

}

HConstants::~HConstants()
{
    
    Print(0, "Desstructor");

}
