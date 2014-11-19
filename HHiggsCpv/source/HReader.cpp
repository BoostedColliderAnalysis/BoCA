# include "HMvaHiggsCpv.hh"
# include "HReader.hh"

int main()
{

    hhiggscpv::HMva *Mva = new hhiggscpv::HMva();

    hmva::HReader *Reader = new hmva::HReader(Mva);

    Reader->MVALoop();

    delete Reader;

    delete Mva;

    return 0;

}
