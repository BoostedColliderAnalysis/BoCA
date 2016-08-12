#include "include/branch/Octet.hh"
#include "boca/OBSERVABLE_MACROS.hh"

namespace higgscpv
{

namespace branch
{

Octet::Octet()
{
    HiggsMass = InitialValue();
    PairRap = InitialValue();
    BottomBdt = InitialValue();
    PairBottomBdt = InitialValue();
    HiggsBdt = InitialValue();
    PairBdt = InitialValue();
    HardTopPt = InitialValue();
    SoftTopPt = InitialValue();
}

}

}
