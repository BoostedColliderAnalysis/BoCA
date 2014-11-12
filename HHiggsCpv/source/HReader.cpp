// # include "HReaderMulti.hh"
# include "HReader.hh"
# include "HMvaHiggsCpv.hh"
// # include "HReaderSimple.hh"


int main()
{

  hhiggscpv::HMva *Mva = new hhiggscpv::HMva();

    hmva::HReader *Reader = new hmva::HReader(Mva);

    delete Reader;

    delete Mva;

    return 0;

}
