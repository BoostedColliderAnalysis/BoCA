// # include "HReaderMulti.hh"
# include "HReader.hh"
# include "HMvaHiggsCpv.hh"
// # include "HReaderSimple.hh"


int main()
{

  hhiggscpv::HMva *Mva = new hhiggscpv::HMva();

    hanalysis::HReader *Reader = new hanalysis::HReader(Mva);

    delete Reader;

    delete Mva;

    return 0;

}
