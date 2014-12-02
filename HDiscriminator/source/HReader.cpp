// # include "HReaderMulti.hh"
# include "HReader.hh"
# include "HMvaDiscriminator.hh"
// # include "HReaderSimple.hh"


int main()
{

  hanalysis::HMva *Mva = new hcpvhiggs::HMva();

  hanalysis::HReader  *Reader = new hanalysis::HReader (Mva);

  Reader->MVALoop();

    delete Reader;

    delete Mva;

    return 0;

}
