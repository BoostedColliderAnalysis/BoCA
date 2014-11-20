# include "HMvaHiggsCpv.hh"
# include "HReader.hh"

int main()
{

    hhiggscpv::HMvaEvent *Mva = new hhiggscpv::HMvaEvent();

    hmva::HReader *Reader = new hmva::HReader(Mva);

    Reader->MVALoop();

    delete Reader;

    delete Mva;

    return 0;

}
