# include "HConstants.hh"

HConstants::HConstants() :
    HiggsMass(125),
    TopMass(173),
    HiggsUserIndex(1000),
    TopUserIndex(2000)
    {
        
        Print(0, "Constructor");

}

HConstants::~HConstants()
{
    
    Print(0, "Desstructor");

}
