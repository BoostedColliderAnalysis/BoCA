# include "HMvaEvent.hh"
# include "HReader.hh"

int main()
{

    hhiggscpv::HMvaEvent *Mva = new hhiggscpv::HMvaEvent();

    hanalysis::HReader  *Reader = new hanalysis::HReader (Mva);

    Reader->MVALoop();

    delete Reader;

    delete Mva;

    return 0;

}
