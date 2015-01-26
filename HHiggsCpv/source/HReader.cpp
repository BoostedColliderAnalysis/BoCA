# include "HMvaEvent.hh"
# include "HReader.hh"

int main()
{

    hhiggscpv::HMvaEvent Mva;
    hanalysis::HReader Reader(Mva);
    Reader.MVALoop();
    return 0;
}
