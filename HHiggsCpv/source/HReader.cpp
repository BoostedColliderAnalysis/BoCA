# include "HMvaEvent.hh"
# include "Reader.hh"

int main()
{

    hhiggscpv::HMvaevent Mva;
    hanalysis::Reader Reader(Mva);
//     Reader.MVALoop();// must be reactvated
    return 0;
}
